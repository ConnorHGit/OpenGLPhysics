#include "Terrain.h"
#include <math.h>
#include "Shader_Loader.h"
#include "Player.h"
const unsigned int TERRAIN_SIZE_X = 257;
const unsigned int TERRAIN_SIZE_Z = 257;
const int TERRAIN_OFFSET_X = 20;
const int TERRAIN_OFFSET_Z = 20;
const int TERRAIN_OFFSET_Y = 20;
const unsigned int TERRAIN_VIEW_DIST = 16;
const float TERRAIN_SCALE_X = 5;
const float TERRAIN_SCALE_Y = 1;
const  float TERRAIN_SCALE_Z = 5;

float terrainData[TERRAIN_SIZE_X][TERRAIN_SIZE_Z];
float terrainColorData[TERRAIN_SIZE_X][TERRAIN_SIZE_Z];
unsigned int vao, arrayVBO, indexVBO;
GLuint terrainProgram;
void diamondSquare(glm::vec2 min, glm::vec2 max, float randMag,float randCMag);
glm::vec3 Terrain::normal;
//TODO make sure to delete stuff everywhere - memory leaks are bad
void Terrain::initTerrain(){
	double x = 0.0;
	for (int i = 0; i < 100000; i++){
		x += (rand() % 50 - 24.49);
	}
	Shader_Loader sl;
	terrainProgram = sl.CreateProgram("Shaders\\TerrainVertex_Shader.glsl", "Shaders\\TerrainFragment_Shader.glsl");
	terrainData[0][0] = 0;
	terrainData[TERRAIN_SIZE_X - 1][0] = 0;
	terrainData[0][TERRAIN_SIZE_Z - 1] = 0;
	terrainData[TERRAIN_SIZE_X - 1][TERRAIN_SIZE_Z - 1] = 0;

	terrainColorData[0][0] = 20;
	terrainColorData[TERRAIN_SIZE_X - 1][0] = 20;
	terrainColorData[0][TERRAIN_SIZE_Z - 1] = 20;
	terrainColorData[TERRAIN_SIZE_X - 1][TERRAIN_SIZE_Z - 1] = 20;

	float randMag = 0;
	float randCMag = 5;
	for (unsigned int step = 0; step < log2(TERRAIN_SIZE_X - 1); step++){
		unsigned int e2s = pow(2,step);
		for (unsigned int squareX = 0; squareX < (e2s); squareX++){
			for (unsigned int squareZ = 0; squareZ < (e2s); squareZ++){
				diamondSquare(glm::vec2(squareX * ((TERRAIN_SIZE_X-1) / (e2s)), squareZ * ((TERRAIN_SIZE_Z-1) / (e2s))),
					glm::vec2((squareX + 1) * ((TERRAIN_SIZE_X-1) / (e2s)), (squareZ + 1) * ((TERRAIN_SIZE_Z-1) / (e2s))),randMag,randCMag);
			}
		}
		randMag /= 2;
		randCMag /= 1.1;
	}
	
	createTerrainModel("TerrainModel");
	createTerrainIndexBuffer(glm::vec2(0, 0), glm::vec2(1, 1), false);
}
void Terrain::createTerrainModel(std::string modelName){
	std::vector<tVertData> terrainModelVerticies;
	for (int z = 0; z < TERRAIN_SIZE_Z; z+=1){
		for (int x = 0; x < TERRAIN_SIZE_X; x+=1){
			terrainModelVerticies.push_back(tVertData(glm::vec3(x * TERRAIN_SCALE_X,terrainData[x][z] * TERRAIN_SCALE_Y, z  * TERRAIN_SCALE_Z),terrainColorData[x][z]));
		}
	}
	unsigned int a = sizeof(tVertData);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &arrayVBO);
	glBindBuffer(GL_ARRAY_BUFFER, arrayVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tVertData) * terrainModelVerticies.size(), &terrainModelVerticies[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(tVertData), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 1, GL_FLOAT, false, sizeof(tVertData), (void*)12);
}
unsigned int Terrain::createTerrainIndexBuffer(glm::vec2 start, glm::vec2 end,bool existing){
	if (existing) glDeleteBuffers(1, &indexVBO);
	std::vector<unsigned int> verticies; 
	for (unsigned int zOffset = start.y; zOffset < end.y; zOffset+=1){
		for (unsigned int xOffset = start.x; xOffset < end.x; xOffset+=1){
			unsigned int modX = (xOffset % 2);
			unsigned int modZ = (zOffset % 2);
			unsigned int modT = modX ^ modZ;
			//Math
			verticies.push_back(xOffset + zOffset * TERRAIN_SIZE_Z);
			verticies.push_back(xOffset + 1 + (zOffset + 1 - modT) * TERRAIN_SIZE_Z);
			verticies.push_back(xOffset + (zOffset + 1) * TERRAIN_SIZE_Z);

			verticies.push_back(xOffset + modT + zOffset * TERRAIN_SIZE_Z);
			verticies.push_back(xOffset + 1 + (zOffset + modT) * TERRAIN_SIZE_Z);
			verticies.push_back(xOffset + 1 - modT + (zOffset + 1) * TERRAIN_SIZE_Z);
		}
	}
	glBindVertexArray(vao);
	glGenBuffers(1, &indexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * verticies.size(), &verticies[0], GL_STATIC_DRAW);

	return verticies.size();
}
void Terrain::renderTerrain(glm::mat4 viewProjectMatrix){
	glUseProgram(terrainProgram);

	unsigned int nElements = createTerrainIndexBuffer(
		glm::vec2(fmax(0, (Player::playerView.position.x / TERRAIN_SCALE_X * -1) - TERRAIN_VIEW_DIST + TERRAIN_OFFSET_X),
		fmax(0, (Player::playerView.position.z / TERRAIN_SCALE_Z * -1) - TERRAIN_VIEW_DIST + TERRAIN_OFFSET_Z)),

		glm::vec2(fmin(TERRAIN_SIZE_X - 1, (Player::playerView.position.x / TERRAIN_SCALE_X * -1) + TERRAIN_VIEW_DIST + TERRAIN_OFFSET_X),
				  fmin(TERRAIN_SIZE_Z - 1, (Player::playerView.position.z / TERRAIN_SCALE_Z * -1) + TERRAIN_VIEW_DIST + TERRAIN_OFFSET_Z)), true
		);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, arrayVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);

	glUniformMatrix4fv(glGetUniformLocation(terrainProgram,"matrix"), 1, false, &(glm::translate(viewProjectMatrix,glm::vec3(-1 * TERRAIN_OFFSET_X * TERRAIN_SCALE_X,TERRAIN_OFFSET_Y,-1 * TERRAIN_OFFSET_Z * TERRAIN_SCALE_Z))[0][0]));

	glDrawElements(GL_TRIANGLES, nElements, GL_UNSIGNED_INT, (void*)0);

}
void diamondSquare(glm::vec2 min, glm::vec2 max,float randMag,float randCMag){
	
	unsigned int ltx = (int)min.x, lty = (int)min.y, rtx = (int)max.x, rty = (int)min.y, lbx = (int)min.x, lby = (int)max.y, rbx = (int)max.x, rby = (int)max.y;
	//Diamond step
	unsigned int avg = (terrainData[ltx][lty] +
		terrainData[rtx][rty] +
		terrainData[lbx][lby] +
		terrainData[rbx][rby]) / 4;

	terrainData[(ltx + rtx) / 2][(lty + lby) / 2] = avg + ((rand() % 50) / 10.f * randMag);
	
	terrainData[(ltx + rtx) / 2][lty] = (terrainData[ltx][lty] + terrainData[rtx][rty]) / 2 + ((rand() % 50) / 10.f * randMag);
	terrainData[ltx][(lty + lby) / 2] = (terrainData[ltx][lty] + terrainData[lbx][lby]) / 2 + ((rand() % 50) / 10.f * randMag);
	terrainData[(lbx + rbx) / 2][lby] = (terrainData[lbx][lby] + terrainData[rbx][rby]) / 2 + ((rand() % 50) / 10.f * randMag);
	terrainData[rtx][(rty + rby) / 2] = (terrainData[rtx][rty] + terrainData[rbx][rty]) / 2 + ((rand() % 50) / 10.f * randMag);

	float cAvg = (terrainColorData[ltx][lty] +
		terrainColorData[rtx][rty] +
		terrainColorData[lbx][lby] +
		terrainColorData[rbx][rby]) / 4;

	terrainColorData[(ltx + rtx) / 2][(lty + lby) / 2] = cAvg + ((rand() % 50 - 24.4) / 50.f * randCMag);

	terrainColorData[(ltx + rtx) / 2][lty] = (terrainColorData[ltx][lty] + terrainColorData[rtx][rty]) / 2 + ((rand() % 50 - 24.4) / 50.f * randCMag);
	terrainColorData[ltx][(lty + lby) / 2] = (terrainColorData[ltx][lty] + terrainColorData[lbx][lby]) / 2 + ((rand() % 50 - 24.4) / 50.f * randCMag);
	terrainColorData[(lbx + rbx) / 2][lby] = (terrainColorData[lbx][lby] + terrainColorData[rbx][rby]) / 2 + ((rand() % 50 - 24.4) / 50.f * randCMag);
	terrainColorData[rtx][(rty + rby) / 2] = (terrainColorData[rtx][rty] + terrainColorData[rbx][rty]) / 2 + ((rand() % 50 - 24.4) / 50.f * randCMag);
}
void destroyTerrain(){
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &arrayVBO);
	glDeleteBuffers(1, &indexVBO);
}
float Terrain::getElevation(glm::vec2 pos){
	float terX = pos.x / TERRAIN_SCALE_X + TERRAIN_OFFSET_X;
	float terZ = pos.y / TERRAIN_SCALE_Z + TERRAIN_OFFSET_Z;

	glm::vec2 min = glm::vec2(floor(terX), floor(terZ));

	unsigned int modT = ((int)min.x % 2) ^ ((int)min.y % 2);
	
	glm::vec2 squareCoord = glm::vec2(terX - min.x, terZ - min.y);

	unsigned int aboveBelow = modT ? squareCoord.y < (1 - squareCoord.x) : squareCoord.y < squareCoord.x; //Above 0 below 1
	
	glm::vec3 p1, p2, p3;

	if (aboveBelow){
		p1 = glm::vec3(min.x, terrainData[(int)min.x][(int)min.y], min.y);
		p2 = glm::vec3(min.x + 1, terrainData[(int)min.x + 1][(int)min.y], min.y);
		p3 = glm::vec3(min.x + 1 - modT, terrainData[(int)min.x + 1 - modT][(int)min.y + 1], min.y + 1);
	}
	else{
		p1 = glm::vec3(min.x + modT, terrainData[(int)min.x + modT][(int)min.y], min.y);
		p2 = glm::vec3(min.x + modT, terrainData[(int)min.x + modT][(int)min.y + 1], min.y + 1);
		p3 = glm::vec3(min.x + 1 - modT, terrainData[(int)min.x + 1 - modT][(int)min.y + 1], min.y + 1);
	}
	
	glm::vec3 axis1 = p3 - p1;
	glm::vec3 axis2 = p2 - p1;

	glm::vec3 planeNormal = glm::normalize(glm::cross(axis1, axis2));
	
	float d = glm::dot(planeNormal, p1);
	
	float elevation = (d - planeNormal.x * terX - planeNormal.z * terZ) / planeNormal.y;
	
	return elevation * TERRAIN_SCALE_Y - TERRAIN_OFFSET_Y;
}
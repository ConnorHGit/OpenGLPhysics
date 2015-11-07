#include "Collision.h"
bool Collision::intersecting(Cube* a, Cube* b){
	glm::vec4 btv[8];

	memcpy(&btv[0], &Cube::cubeVerticies[0], 8 * sizeof(glm::vec4));

	btv[0] = btv[0] * b->cubeTransformMatrix / a->cubeTransformMatrix;
	btv[1] = btv[1] * b->cubeTransformMatrix / a->cubeTransformMatrix;
	btv[2] = btv[2] * b->cubeTransformMatrix / a->cubeTransformMatrix;
	btv[3] = btv[3] * b->cubeTransformMatrix / a->cubeTransformMatrix;
	btv[4] = btv[4] * b->cubeTransformMatrix / a->cubeTransformMatrix;
	btv[5] = btv[5] * b->cubeTransformMatrix / a->cubeTransformMatrix;
	btv[6] = btv[6] * b->cubeTransformMatrix / a->cubeTransformMatrix;
	btv[7] = btv[7] * b->cubeTransformMatrix / a->cubeTransformMatrix;

	glm::vec3 bEdge1 = glm::vec3(btv[1] - btv[0]);
	glm::vec3 bEdge2 = glm::vec3(btv[1] - btv[2]);
	glm::vec3 bEdge3 = glm::vec3(btv[1] - btv[5]);

	glm::vec3 nFace1 = glm::cross(bEdge1, bEdge2);
	glm::vec3 nFace2 = glm::cross(bEdge2, bEdge3);
	glm::vec3 nFace3 = glm::cross(bEdge1, bEdge3);

	glm::vec3 minA = glm::vec3(-0.5f, -0.5f, -0.5f);
	glm::vec3 maxA = glm::vec3(0.5f, 0.5f, 0.5f);

	glm::vec3 minB = glm::vec3(btv[0]);
	glm::vec3 maxB = glm::vec3(btv[0]);

	for (int i = 1; i < 8; i++){
		minB = glm::vec3(std::min(minB.x, btv[i].x), std::min(minB.y, btv[i].y), std::min(minB.z, btv[i].z));
		maxB = glm::vec3(std::max(maxB.x, btv[i].x), std::max(maxB.y, btv[i].y), std::max(maxB.z, btv[i].z));
	}

}
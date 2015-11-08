#include "Collision.h"
bool Collision::intersecting(Cube* a, Cube* b){
	glm::vec4 btv[8];

	memcpy(&btv[0], &Cube::cubeVerticies[0], 8 * sizeof(glm::vec4));
	
	glm::mat4 spaceTransform = (glm::inverse(a->cubeTransformMatrix) * b->cubeTransformMatrix);
	
	for (int i = 0; i < 8; i++)btv[i] = spaceTransform * btv[i];

	glm::vec3 bEdges[3];

	bEdges[0] = glm::vec3(btv[1] - btv[0]);
	bEdges[1] = glm::vec3(btv[1] - btv[2]);
	bEdges[2] = glm::vec3(btv[1] - btv[5]);

	glm::vec3 aEdges[] = { glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0) };

	glm::vec3 minA = glm::vec3(-0.5f, -0.5f, -0.5f);
	glm::vec3 maxA = glm::vec3(0.5f, 0.5f, 0.5f);

	glm::vec3 minB = glm::vec3(btv[0]);
	glm::vec3 maxB = glm::vec3(btv[0]);

	for (int i = 1; i < 8; i++){
		minB = glm::vec3(std::min(minB.x, btv[i].x), std::min(minB.y, btv[i].y), std::min(minB.z, btv[i].z));
		maxB = glm::vec3(std::max(maxB.x, btv[i].x), std::max(maxB.y, btv[i].y), std::max(maxB.z, btv[i].z));
	}

	for (int i = 0; i < 3; i++){
		glm::vec3 axis = bEdges[i];

		float bMinProj = glm::dot(axis, minB);
		float bMaxProj = glm::dot(axis, maxB);

		float aMinProj = glm::dot(axis, minA);
		float aMaxProj = glm::dot(axis, maxB);

		if (std::max(bMinProj,bMaxProj) < std::min(aMaxProj,aMinProj) || std::max(aMinProj,aMaxProj) < std::min(bMaxProj,bMinProj))
			return false;
	}

	//X-Axis(Cube A nFace1)
	if (maxB.x < minA.x || maxA.x < minB.x) 
		return false;
	//Y-Axis(Cube A nFace2)
	if (maxB.y < minA.y || maxA.y < minB.y) 
		return false;
	//Z-Axis(Cube B nFace3)
	if (maxB.z < minA.z || maxA.z < minB.z) 
		return false;

	for (int i = 0; i < 9; i++){
		glm::vec3 axis = glm::cross(bEdges[i / 3], aEdges[i % 3]);

		float bMinProj = glm::dot(axis, minB);
		float bMaxProj = glm::dot(axis, maxB);

		float aMinProj = glm::dot(axis, minA);
		float aMaxProj = glm::dot(axis, maxB);

		if (std::max(bMinProj, bMaxProj) < std::min(aMaxProj, aMinProj) || std::max(aMinProj, aMaxProj) < std::min(bMaxProj, bMinProj))
			return false;
	}
	return true;
}
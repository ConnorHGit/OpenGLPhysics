#include "Collision.h"

float seperatingAxis(glm::vec3 axis, glm::vec3* aVerts,glm::vec3* bVerts){
	//Find projects of min and max of both objects along axis
	float bMax = glm::dot(bVerts[0], axis), bMin = glm::dot(bVerts[0], axis), aMax = glm::dot(aVerts[0], axis), aMin = glm::dot(aVerts[0],axis);

	for (int i = 1; i < 8;i++){
		float aProj = glm::dot(aVerts[i], axis);
		if (aProj > aMax)aMax = aProj;
		else if (aProj < aMin)aMin = aProj;

		float bProj = glm::dot(bVerts[i], axis);
		if (bProj > bMax)bMax = bProj;
		else if (bProj < bMin)bMin = bProj;
	}

	if (bMax < aMin || aMax < bMin) return -FLT_MAX;
	if (aMin < bMin) return aMax - bMin;
	return bMax - aMin;
}

bool Collision::intersecting(Cube* a, Cube* b,glm::vec3* leastOverlapAxis,float* overlap){
	glm::vec3 leastOverlapingAxis;
	float penLeastOverlap = FLT_MAX;

	glm::vec3 aEdges[3], bEdges[3];

	//3 Unique axies of the edges of both cubes

	bEdges[0] = glm::normalize(b->instanceCubeVerticies[1] - b->instanceCubeVerticies[0]);
	bEdges[1] = glm::normalize(b->instanceCubeVerticies[1] - b->instanceCubeVerticies[2]);
	bEdges[2] = glm::normalize(b->instanceCubeVerticies[1] - b->instanceCubeVerticies[5]);

	aEdges[0] = glm::normalize(a->instanceCubeVerticies[1] - a->instanceCubeVerticies[0]);
	aEdges[1] = glm::normalize(a->instanceCubeVerticies[1] - a->instanceCubeVerticies[2]);
	aEdges[2] = glm::normalize(a->instanceCubeVerticies[1] - a->instanceCubeVerticies[5]);

	//Check if objects overlap in the edges of object b
	for (int i = 0; i < 3; i++){
		glm::vec3 axis = bEdges[i];

		float overlap = seperatingAxis(axis, a->instanceCubeVerticies, b->instanceCubeVerticies);
		
		if (overlap == -FLT_MAX)
			return false;
		
		if (overlap < penLeastOverlap){
			leastOverlapingAxis = axis;
			penLeastOverlap = overlap;
		}
	}

	//Check if objects overlap in edges of object a
	for (int i = 0; i < 3; i++){
		glm::vec3 axis = aEdges[i];

		float overlap = seperatingAxis(axis, a->instanceCubeVerticies, b->instanceCubeVerticies);
		
		if (overlap == -FLT_MAX)
			return false;

		if (overlap < penLeastOverlap){
			leastOverlapingAxis = axis;
			penLeastOverlap = overlap;
		}
	}

	//Check if objects overlap in cross products of edges of a and b
	for (int i = 0; i < 9; i++){
		glm::vec3 axis = glm::normalize(glm::cross(bEdges[i / 3], aEdges[i % 3]));

		float overlap = seperatingAxis(axis, a->instanceCubeVerticies, b->instanceCubeVerticies);

		if (overlap == -FLT_MAX)
			return false;

		if (overlap < penLeastOverlap){
			leastOverlapingAxis = axis;
			penLeastOverlap = overlap;
		}
	}

	//If overlap in all 15 axis objects are intersecting return true

	if(leastOverlapAxis != NULL)(*leastOverlapAxis) = leastOverlapingAxis;
	if (overlap != NULL)(*overlap) = penLeastOverlap;

	return true;
}
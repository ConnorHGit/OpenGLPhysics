#include "Collision.h"

Collision::intersectingAxis seperatingAxis(glm::vec3 axis, glm::vec3* aVerts,glm::vec3* bVerts){
	float bMax = glm::dot(bVerts[0], axis), bMin = glm::dot(bVerts[0], axis), aMax = glm::dot(aVerts[0], axis), aMin = glm::dot(aVerts[0],axis);

	for (int i = 1; i < 8;i++){
		float aProj = glm::dot(aVerts[i], axis);
		if (aProj > aMax)aMax = aProj;
		else if (aProj < aMin)aMin = aProj;

		float bProj = glm::dot(bVerts[i], axis);
		if (bProj > bMax)bMax = bProj;
		else if (bProj < bMin)bMin = bProj;
	}
	Collision::intersectingAxis iAxis;
	iAxis.axis = axis;
	iAxis.side = bMin > aMin;
	iAxis.overlapL = iAxis.side ? bMin - aMax : aMin - bMax;
	iAxis.overlapR = iAxis.side ? aMin - bMax : bMin - aMax;
	return iAxis;
}

std::vector<Collision::intersectingAxis> Collision::intersecting(Cube* a, Cube* b){

	std::vector<Collision::intersectingAxis> axies;

	glm::vec3 aEdges[3], bEdges[3];

	bEdges[0] = glm::normalize(b->instanceCubeVerticies[1] - b->instanceCubeVerticies[0]);
	bEdges[1] = glm::normalize(b->instanceCubeVerticies[1] - b->instanceCubeVerticies[2]);
	bEdges[2] = glm::normalize(b->instanceCubeVerticies[1] - b->instanceCubeVerticies[5]);

	aEdges[0] = glm::normalize(a->instanceCubeVerticies[1] - a->instanceCubeVerticies[0]);
	aEdges[1] = glm::normalize(a->instanceCubeVerticies[1] - a->instanceCubeVerticies[2]);
	aEdges[2] = glm::normalize(a->instanceCubeVerticies[1] - a->instanceCubeVerticies[5]);

	for (int i = 0; i < 3; i++){
		glm::vec3 axis = bEdges[i];
		axies.push_back(seperatingAxis(axis, a->instanceCubeVerticies, b->instanceCubeVerticies));
	}
	for (int i = 0; i < 3; i++){
		glm::vec3 axis = aEdges[i];
		axies.push_back(seperatingAxis(axis, a->instanceCubeVerticies, b->instanceCubeVerticies));
	}
	for (int i = 0; i < 9; i++){
		glm::vec3 axis = glm::cross(bEdges[i / 3], aEdges[i % 3]);

		if (axis == glm::vec3(0, 0, 0)){
			Collision::intersectingAxis parallel;
			parallel.axis = glm::vec3(0, 0, 0);
			axies.push_back(parallel);
			continue;
		}

		axis = glm::normalize(axis);

		axies.push_back(seperatingAxis(axis, a->instanceCubeVerticies, b->instanceCubeVerticies));
	}
	return axies;
}
//Returns when collision will happen in milliseconds, if no collision returns -1
bool Collision::detectCollision(Cube* a, Cube* b, float delta, Collision::intersectingAxis* collisionAxis){

	/*
	float radA = glm::length(a->instanceCubeVerticies[1] - a->position);
	float radB = glm::length(b->instanceCubeVerticies[1] - b->position);
	glm::vec3 betweenAxis = a->position - b->position;
	
	float dist = glm::length(betweenAxis);

	float velAlong = glm::dot(betweenAxis, b->velocity - a->velocity) / dist;
	
	float overlap = (glm::length(radA) + glm::length(radB)) - dist;

	if (overlap + velAlong * delta < 0)
		return false;
	*/

	std::vector<Collision::intersectingAxis> axies = Collision::intersecting(a, b);
	bool intersecting = true;
	int axisLeast = 0;
	for (int i = 0; i < 15; i++){
		if (axies[i].overlapL > 0)intersecting = false;
		if (axies[i].overlapL > axies[axisLeast].overlapL)axisLeast = i;
	}
	if (intersecting){
		axies[axisLeast].time = 0;
		if (collisionAxis != NULL)(*collisionAxis) = axies[axisLeast];
		return true;//If objects already intersecting return 0(Intersected at this time)
	}
	Collision::intersectingAxis lastAxis;
	lastAxis.time = 0;

	for (int i = 0; i < 15; i++){
		if (axies[i].axis == glm::vec3(0, 0, 0))continue;
		//Find how fast objects are approaching eachother in axis direction
		float velProj = glm::dot(axies[i].side ? b->velocity - a->velocity : a->velocity - b->velocity, axies[i].axis);
		axies[i].velAlong = velProj;
		if (axies[i].overlapL <= 0)continue;

		//Check if objects will overlap in axis between this update and next update
		float timeToCollide = axies[i].overlapL / velProj * -1;
		if (timeToCollide <= delta){
			axies[i].time = timeToCollide;
			if (axies[i].time > lastAxis.time)lastAxis = axies[i];//If it overlaps after previous last axis to overlap it is last axis, objects will be colliding when all axis are overlaping
		}
		else 
			return false;//If it will not overlap objects will not collide between this update and next return -1


	}

	float colTime = lastAxis.time; //Time collision may happen between this update and next

	for (int i = 0; i < 15; i++){
		if (axies[i].axis == glm::vec3(0, 0, 0))continue;
		float curOverlap = axies[i].overlapL + axies[i].velAlong * colTime;//Check how far the objects overlap in axis at this time
		if (curOverlap > 0 || curOverlap < axies[i].overlapR)//Check if objects are not overlaping in axis return -1 if not -objects not colliding-
			return false;
	}
	if (collisionAxis != NULL)(*collisionAxis) = lastAxis;
	return true;//Return time collision will happen
}
void resolveCollision(Collision::manifold m){
	m.a->update(m.collisionAxis.time);
	m.b->update(m.collisionAxis.time);

	m.a->velocity -= glm::dot(m.a->velocity, m.collisionAxis.axis) * m.collisionAxis.axis;
	m.b->velocity -= glm::dot(m.b->velocity, m.collisionAxis.axis) * m.collisionAxis.axis;

}

void Collision::handleCollisions(std::vector<Cube*> bodies,float delta){
	std::vector<Collision::manifold> collisions;
	for (size_t a = 0; a < bodies.size() - 1; a++)
		for (size_t b = a + 1; b < bodies.size(); b++){
			Collision::intersectingAxis axis;
			if (detectCollision(bodies[a], bodies[b], delta, &axis)){
				Collision::manifold m;
				m.a = bodies[a];
				m.b = bodies[b];
				m.collisionAxis = axis;

				collisions.push_back(m);
			}
		}
	std::sort(collisions.begin(), collisions.end(), [](const Collision::manifold a, const Collision::manifold b) -> bool{
		return a.collisionAxis.time < b.collisionAxis.time;
	});

	for (size_t i = 0; i < collisions.size(); i++){
		resolveCollision(collisions[i]);
	}
}
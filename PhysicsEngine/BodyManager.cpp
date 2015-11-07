#include "BodyManager.h"


BodyManager::BodyManager()
{
}

Cube* BodyManager::addCube(Cube& newCube){
	Cube* cubeCopy = new Cube(newCube);
	cubes.push_back(cubeCopy);
	return cubeCopy;
}
BodyManager::~BodyManager()
{
	for (size_t i = 0; i < cubes.size(); ++i)delete cubes[i];
}

void BodyManager::renderCubes(){
	for (size_t i = 0; i < cubes.size(); ++i){
		Cube* cur = cubes[i];
		Render::renderModel("cube", "brick", cur->cubeTransformMatrix);
	}
}
void BodyManager::updateCubes(){
	for (size_t i = 0; i < cubes.size(); ++i){
		cubes[i]->updateMatrix();
	}
}
Cube* BodyManager::createCube(glm::vec3 pos, glm::vec3 size, glm::vec3 rotation, float mass, glm::vec3 velocity){
	Cube* newCube = new Cube(pos, size, rotation, velocity, mass);
	cubes.push_back(newCube);
	return newCube;
}

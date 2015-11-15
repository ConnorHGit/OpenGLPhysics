#pragma once

#include "Cube.h"
class Cube;

class BodyManager
{
public:
	BodyManager();
	~BodyManager();
	Cube* addCube(Cube& newCube);
	Cube* createCube(glm::vec3 pos = glm::vec3(0), glm::vec3 size = glm::vec3(1), glm::vec3 rotation = glm::vec3(0), float mass = 1, glm::vec3 velocity = glm::vec3(0));
	void renderCubes();
	void updateCubes(float delta);
private:
	std::vector<Cube*> cubes;
};


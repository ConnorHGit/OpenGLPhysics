#pragma once
#include "Main.h"
class Cube
{
public:
	const static glm::vec4 cubeVerticies[];


	Cube(glm::vec3 position, glm::vec3 size, glm::vec3 rotation, glm::vec3 velocity, float mass);
	~Cube();
	
	float partialUpdate;

	void Cube::updateMatrix();
	void Cube::update(float delta);

	float mass,inverseMass;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 force;
	glm::vec3 velocity;
	glm::vec3 size;

	glm::vec3 instanceCubeVerticies[8];
	glm::mat4 cubeTransformMatrix;
};


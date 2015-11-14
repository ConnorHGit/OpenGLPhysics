#pragma once
#include "Main.h"
class Cube
{
public:
	const static glm::vec4 cubeVerticies[];

	Cube(glm::vec3 position, glm::vec3 size, glm::vec3 rotation, glm::vec3 velocity, float mass);
	~Cube();
	void Cube::updateMatrix();

	float mass,inverseMass;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 acceleration;
	glm::vec3 velocity;
	glm::vec3 size;

	glm::mat4 cubeTransformMatrix;
};


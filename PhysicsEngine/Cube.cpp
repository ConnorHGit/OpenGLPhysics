#include "Cube.h"
const glm::vec4 Cube::cubeVerticies[] = {
	glm::vec4(-0.5f, 0.5f, 0.5f,1),
	glm::vec4(0.5f, 0.5f, 0.5f,1),
	glm::vec4(0.5f, -0.5f, 0.5f,1),
	glm::vec4(-0.5f, -0.5f, 0.5f,1),
	glm::vec4(-0.5f, 0.5f, -0.5f,1),
	glm::vec4(0.5f, 0.5f, -0.5f,1),
	glm::vec4(0.5f, -0.5f, -0.5f,1),
	glm::vec4(-0.5f, -0.5f, -0.5f,1) };

Cube::Cube(glm::vec3 position = glm::vec3(0), glm::vec3 size = glm::vec3(1), glm::vec3 rotation = glm::vec3(0), glm::vec3 velocity = glm::vec3(0), float mass = 1){
	Cube::mass = mass;
	Cube::inverseMass = 1 / mass;
	Cube::position = position;
	Cube::rotation = rotation;
	Cube::velocity = velocity;
	Cube::size = size;
	partialUpdate = 0;
	updateMatrix();
}

Cube::~Cube()
{
}
void Cube::update(float delta){
	position += velocity * (delta - partialUpdate);
	if (position.y > 20)position.y = 20;
	velocity += force * inverseMass * (delta - partialUpdate);
	updateMatrix();
	partialUpdate += delta;
}
void Cube::updateMatrix(){
	Cube::cubeTransformMatrix = glm::translate(glm::mat4(1), glm::vec3(position.x,position.y,position.z)) * Render::createRotationMatrix(rotation) * glm::scale(glm::mat4(1), size);
	for (int i = 0; i < 8; i++)
		instanceCubeVerticies[i] = glm::vec3(cubeTransformMatrix * cubeVerticies[i]);
}
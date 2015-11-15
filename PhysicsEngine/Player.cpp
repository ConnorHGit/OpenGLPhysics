#include "Player.h"
#include "Terrain.h"
class Camera;
Camera Player::playerView = Camera();
glm::vec2 cursorPosition();

bool keydown[512];
void Player::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (action == GLFW_PRESS){
		keydown[key] = true;
	}
	else if (action == GLFW_RELEASE){
		keydown[key] = false;
	}
}
void Player::update(float delta){
	float speed = 2.f;
	float lookSpeed = 0.01f;

	float minVertAngle = -4.71f;
	float maxVertAngle = -1.57f;

	glm::vec2 curPos = cursorPosition();

	playerView.rotation.y += (curPos.x - 960) * -lookSpeed;
	playerView.rotation.x += (curPos.y - 540) * lookSpeed;

	playerView.rotation.x = Main::clip(playerView.rotation.x,minVertAngle, maxVertAngle);
	
	glfwSetCursorPos(GW::window, 960, 540);

	playerView.updateRotationMatrix();

	glm::mat4 rot = playerView.rotationMatrix;
	glm::vec3 dirlook = glm::vec3(rot[0][2], rot[1][2], rot[2][2]);
	glm::vec3 dirsidelook = glm::vec3(rot[0][0], rot[1][0], rot[2][0]);

	if (keydown[GLFW_KEY_W]) playerView.position += dirlook * speed * delta;
	if (keydown[GLFW_KEY_S]) playerView.position += dirlook * -speed * delta;
	if (keydown[GLFW_KEY_A]) playerView.position += dirsidelook * speed * delta;
	if (keydown[GLFW_KEY_D]) playerView.position += dirsidelook * -speed * delta;

	playerView.position.y = -Terrain::getElevation(glm::vec2(playerView.position.x * -1, playerView.position.z * -1)) - 1;

	if (keydown[GLFW_KEY_ESCAPE])glfwSetWindowShouldClose(GW::window, true);
	
 }
glm::vec2 cursorPosition(){
	double x, y;
	glfwGetCursorPos(GW::window, &x, &y);
	return glm::vec2(x, y);
}

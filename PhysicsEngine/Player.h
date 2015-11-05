#include "Camera.h"
class Camera;
namespace Player{
	extern Camera playerView;
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void update(float delta);
}
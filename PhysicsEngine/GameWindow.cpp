#include "GameWindow.h"
namespace GW{
	GLFWwindow* GW::window;
	int GW::initWindow(){

		window = glfwCreateWindow(1920, 1080, "Physics", NULL, NULL);
		if (!window) return 1;
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);
		glfwSetKeyCallback(window, Player::key_callback);
		//glfwSetMouseButtonCallback(window, MousePressed);
		return 0;
	}
}
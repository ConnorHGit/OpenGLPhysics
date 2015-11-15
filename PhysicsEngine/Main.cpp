#include "Main.h"
#include "Render.h"
#include "Model.h"
#include "Terrain.h"
#include <stdio.h>
#include "Cube.h"
GLuint Main::program;
std::chrono::milliseconds elapsedTime;
BodyManager Main::bodyManager;

std::chrono::milliseconds getTime(){
	return std::chrono::time_point_cast<std::chrono::milliseconds>(Clock::now()).time_since_epoch();
}
void initGL(){
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader_Loader sl;
	Main::program = sl.CreateProgram("Shaders\\Vertex_Shader.glsl", "Shaders\\Fragment_Shader.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_ELEMENT_ARRAY_BUFFER);
	
}

void gameLoop(){

	Cube* a = Main::bodyManager.createCube(glm::vec3(4, 19.3, 2.6), glm::vec3(1, 1, 1), glm::vec3(1, 0, 0));
	Cube* b = Main::bodyManager.createCube(glm::vec3(4, 18.3, 2.9), glm::vec3(1, 1, 1), glm::vec3(0.3, 0, 0));
	
	int i = 0;
	std::chrono::milliseconds sinceLast;
	while (!glfwWindowShouldClose(GW::window)){
		unsigned int delta = (getTime() - elapsedTime).count();

		elapsedTime = getTime();

		Player::update(delta);
		Main::bodyManager.updateCubes(delta);

		Render::renderScene();

		glfwPollEvents();

		i++;
		if (sinceLast.count() > 1000){
			std::cout << "FPS" << i << std::endl;
			i = 0;
			sinceLast = std::chrono::milliseconds();
		}

		if (Collision::intersecting(a, b))std::cout << "COLLIDING" << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds((long)fmax(16 - (getTime() - elapsedTime).count(),0)));

		sinceLast += getTime() - elapsedTime;
	}

}

int main(){
	srand(time(NULL));
	
	if (!glfwInit())
		return 0;

	if (GW::initWindow()){
		glfwTerminate();
		return 0;
	}

	glewInit();
	initGL();

	Texture::loadTexture("brick","C:\\Users\\Connor\\Documents\\Visual Studio 2013\\Projects\\Brick.png");
	Texture::loadTexture("wood", "C:\\Users\\Connor\\Documents\\Visual Studio 2013\\Projects\\Wood.png");

	Mod::createSquareModel("square");
	Mod::createCubeModel("cube");

	Terrain::initTerrain();
	
	gameLoop();

	glfwTerminate();

	return 0;
}

float Main::clip(float n, float lower, float upper) {
	return std::max(lower, std::min(n, upper));
}
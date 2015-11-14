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
	int i = 0;
	std::chrono::milliseconds sinceLast;
	while (!glfwWindowShouldClose(GW::window)){
		elapsedTime = getTime();
		Player::update(16.f);
		Main::bodyManager.updateCubes();
		Render::renderScene();
		glfwPollEvents();
		i++;
		if (sinceLast.count() > 1000){
			std::cout << "FPS" << i << std::endl;
			i = 0;
			sinceLast = std::chrono::milliseconds();
		}
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

	Mod::createSquareModel("square");
	Mod::createCubeModel("cube");

	Terrain::initTerrain();

	Cube* a = Main::bodyManager.createCube(glm::vec3(4, 19.3, 2.6), glm::vec3(1,2,1),glm::vec3(0.15,0,0));
	Cube* b = Main::bodyManager.createCube(glm::vec3(4, 17.8, 2.9),glm::vec3(1,1,1),glm::vec3(0.3,0,0));

	std::cout << "Colliding" << Collision::intersecting(a, b) << std::endl;

	gameLoop();

	glfwTerminate();

	return 0;
}

float Main::clip(float n, float lower, float upper) {
	return std::max(lower, std::min(n, upper));
}
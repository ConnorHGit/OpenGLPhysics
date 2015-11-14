#pragma once
#define NOMINMAX
#include "GL/glew.h"
#include "GameWindow.h"
#include <thread>
#include "Shader_Loader.h"
#include <chrono>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/norm.hpp"
#include "Player.h"
#include <algorithm>
#include "Texture.h"
#include "LodePNG\lodepng.h"
#include "Collision.h"

#include "BodyManager.h"

#pragma comment(lib, "opengl32.lib")

typedef std::chrono::high_resolution_clock Clock;

class Cube;
class BodyManager;

namespace Main{
	extern GLuint program;
	extern std::chrono::milliseconds elapsedTime;
	extern BodyManager bodyManager;
	float clip(float n, float lower, float upper);
};


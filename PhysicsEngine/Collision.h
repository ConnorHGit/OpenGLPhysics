#pragma once
#include "Cube.h"
class Cube;
namespace Collision{
	bool intersecting(Cube* a, Cube* b,glm::vec3* leastOverlapAxis = 0, float* overlap = 0);
}
#pragma once
#include "Cube.h"
class Cube;
namespace Collision{
	struct intersectingAxis{
		glm::vec3 axis;
		float overlapL;
		float overlapR;
		bool side;
		float time;
		float velAlong;
	};
	struct manifold{
		intersectingAxis collisionAxis;
		Cube* a;
		Cube* b;
	};
	std::vector<Collision::intersectingAxis> intersecting(Cube* a, Cube* b);
	bool detectCollision(Cube* a, Cube* b, float delta,Collision::intersectingAxis* collisionAxis);
	void handleCollisions(std::vector<Cube*> bodies,float delta);
}
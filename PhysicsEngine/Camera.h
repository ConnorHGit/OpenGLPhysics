#pragma once
#include "Main.h"
#include "Render.h"
	class Camera
	{
	public:
		Camera();
		~Camera();
		void updateRotationMatrix();
		glm::mat4 rotationMatrix;
		glm::vec3 position;
		glm::vec3 rotation;
	};



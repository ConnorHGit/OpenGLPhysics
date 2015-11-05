#include "Camera.h"


Camera::Camera()
{
	
}


Camera::~Camera()
{
}

void Camera::updateRotationMatrix(){
	rotationMatrix = Render::createRotationMatrix(Camera::rotation);
}
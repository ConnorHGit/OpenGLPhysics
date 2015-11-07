#version 430 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in float slope;
uniform mat4 matrix;

out vec3 pos;
out float s;

void main(void){
	gl_Position = matrix * vec4(in_position,1);
	pos = in_position;
	s = slope;
}
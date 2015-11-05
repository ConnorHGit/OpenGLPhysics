#version 430 core
layout(location = 0) in vec3 in_position;

uniform mat4 matrix;

out vec3 pos;

void main(void){
	gl_Position = matrix * vec4(in_position,1);
	pos = in_position;
}
#version 430 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_uv;

uniform mat4 matrix;

out vec2 UV;
void main(void){
	UV = in_uv;
	gl_Position = matrix * vec4(in_position.x,in_position.y,in_position.z, 1);
}
#version 430 core
layout(location = 0) out vec4 out_color;
 in vec3 pos;

void main(void){
	out_color = vec4(0,pos[1] / -50.f,0,1);
}

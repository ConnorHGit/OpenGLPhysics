#version 430 core
layout(location = 0) out vec4 out_color;

in vec2 UV;

uniform sampler2D textSamp;
 
void main(void){
	out_color = texture(textSamp,UV).rgba;
}

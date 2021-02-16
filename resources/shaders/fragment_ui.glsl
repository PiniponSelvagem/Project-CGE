#version 440

in vec2 texcoord;

out vec4 color;

uniform sampler2D uiTexture;

void main(void){
	color = texture(uiTexture, texcoord);
}
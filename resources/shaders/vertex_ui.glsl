#version 440

in vec2 position;

out vec2 texcoord;

uniform mat4 ModelMatrix;

void main() {
	texcoord = vec2((position.x + 1.f)/2.f, 1 - (position.y + 1.f)/2.f);
	gl_Position = ModelMatrix * vec4(position, 0.f, 1.f);
}
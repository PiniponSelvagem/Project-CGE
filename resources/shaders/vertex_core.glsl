#version 330

layout (location = 0) in vec3 vx_position;
layout (location = 1) in vec3 vx_color;
layout (location = 2) in vec2 vx_texcoord;

out vec3 vs_position;
out vec3 vs_color;
out vec2 vs_texcoord;

void main() {
	vs_position = vx_position;
	vs_color    = vx_color;
	vs_texcoord = vec2(vx_texcoord.x, vx_texcoord.y * -1.f);

	gl_Position = vec4(vx_position, 1.f);
}
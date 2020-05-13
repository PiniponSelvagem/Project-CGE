#version 440

layout (location = 0) in vec3 vx_position;
layout (location = 1) in vec2 vx_texcoord;
layout (location = 2) in vec3 vx_normal;

out vec3 vs_position;
out vec2 vs_texcoord;
out vec3 vs_normal;


uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform float vertexCount;

void main() {
	vs_position = vec4(ModelMatrix * vec4(vx_position, 1.f)).xyz;
	vs_texcoord = vec2(vx_texcoord.x, vx_texcoord.y * -1.f) * vertexCount;
	vs_normal	= mat3(ModelMatrix) * vx_normal;

	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vx_position, 1.f);
}
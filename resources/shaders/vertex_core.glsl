#version 440

layout (location = 0) in vec3 vx_position;
layout (location = 1) in vec3 vx_color;
layout (location = 2) in vec2 vx_texcoord;
layout (location = 3) in vec3 vx_normal;

out vec3 vs_position;
out vec3 vs_color;
out vec2 vs_texcoord;
out vec3 vs_normal;
out float visibility;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

struct Fog {
	float density;
	float gradient;
};

uniform Fog fog;

void main() {
	vs_position = vec4(ModelMatrix * vec4(vx_position, 1.f)).xyz;
	vs_color    = vx_color;
	vs_texcoord = vec2(vx_texcoord.x, vx_texcoord.y * -1.f);
	vs_normal	= mat3(ModelMatrix) * vx_normal;
	
	// Fog position calculation
	vec4 posRelativeToCam = ViewMatrix * vec4(vs_position, 1.f);
	float dist = length(posRelativeToCam.xyz);
	visibility = exp(-pow((dist*fog.density), fog.gradient));
	visibility = clamp(visibility, 0.0, 1.0);

	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vx_position, 1.f);
}
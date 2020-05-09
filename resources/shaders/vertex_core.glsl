#version 440

layout (location = 0) in vec3 vx_position;
layout (location = 1) in vec2 vx_texcoord;
layout (location = 2) in vec3 vx_normal;
layout (location = 3) in vec3 vx_color;

out vec3 vs_position;
out vec2 vs_texcoord;
out vec3 vs_normal;
out vec3 vs_color;


uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

/* 
//Simple Fog, might be less resource intensive (not a performance impact that could be noticable atm),
//but poor results specially, with large objects compared to fragment fog calculation.

out float visibility;
struct Fog {
	float density;
	float gradient;
};
uniform Fog fog;
*/

void main() {
	vs_position = vec4(ModelMatrix * vec4(vx_position, 1.f)).xyz;
	vs_color    = vx_color;
	vs_texcoord = vec2(vx_texcoord.x, vx_texcoord.y * -1.f);
	vs_normal	= mat3(ModelMatrix) * vx_normal;
	
	/*
	//Simple Fog, less resource intensive (not a performance impact that could be noticable atm),
	//but poor results specially, with large objects compared to fragment fog calculation.
	//Example: large floor plane with high density fog.

	// Fog position calculation
	vec4 posRelativeToCam = ViewMatrix * vec4(vs_position, 1.f);
	float dist = length(posRelativeToCam.xyz);
	visibility = exp(-pow((dist*fog.density), fog.gradient));
	visibility = clamp(visibility, 0.0, 1.0);
	*/

	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vx_position, 1.f);
}
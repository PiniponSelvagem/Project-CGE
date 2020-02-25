#version 440

struct Material {
	vec3 color;
	sampler2D diffuseTex;
	sampler2D maskTex;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform Material material;



vec4 calculateMask() {
	return texture(material.diffuseTex, vs_texcoord) * (1-texture(material.maskTex, vs_texcoord));
}

vec4 calculateColorTint() {
	return texture(material.diffuseTex, vs_texcoord) * texture(material.maskTex, vs_texcoord) * vec4(material.color, 1.f);
}

void main() {
	fs_color = calculateMask() + calculateColorTint();
}

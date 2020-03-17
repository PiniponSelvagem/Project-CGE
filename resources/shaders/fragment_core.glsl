#version 440

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

struct Light {
	vec3 position;
	vec3 color;
	float attenuation;
	float falloffNear;
	float falloffFar;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform Material material;
uniform Light light[4];
uniform vec3 cameraPos;


vec3 calculateAmbient(Material material) {
	return material.ambient;
}

vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 vs_normal, Light light) {
	vec3 posToLightDirVec = normalize(light.position - vs_position);
	float diffuse		  = clamp(dot(posToLightDirVec, vs_normal), 0, 1);
	vec3 diffuseFinal	  = material.diffuse * diffuse;

	return diffuseFinal * light.color;
}

vec3 calculateSpecular(Material material, vec3 vs_position, vec3 vs_normal, Light light, vec3 cameraPos) {
	vec3 lightToPosDirVec = normalize(vs_position - light.position);
	vec3 reflectDirVec	  = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
	vec3 posToViewDirVec  = normalize(cameraPos - vs_position);
	float specularConst	  = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 30);
	vec3 specularFinal	  = material.specular * specularConst * texture(material.specularTex, vs_texcoord).rgb;

	return specularFinal * light.color;
}

float calculateAttenuation(vec3 vs_position, vec3 vs_normal, Light light) {
	// http://learnwebgl.brown37.net/09_lights/lights_attenuation.html
	vec3 posToLightDirVec = light.position - vs_position;
	float dist			  = length(posToLightDirVec);
	float falloffNear = 0;
	float falloffFar  = 1;
	float attenuationFinal = 1.0 / (1.0 + falloffNear * dist + falloffFar * dist * dist);
	
	return attenuationFinal;
}


void main() {
	//fs_color = vec4(vs_color, 1.f);
	//fs_color = texture(texture0, vs_texcoord) * texture(texture1, vs_texcoord) * vec4(vs_color, 1.f);
	
	//Ambient Light
	vec3 ambientFinal = calculateAmbient(material);

	//Diffuse Light
	vec3 diffuseFinal = vec3(0.f);

	//Specular Light
	vec3 specularFinal = vec3(0.f);

	//Attenuation
	float attenuationFinal = 0.f;

	
	//for (int i=0; i<2; ++i) {
		attenuationFinal = attenuationFinal + calculateAttenuation(vs_position, vs_normal, light[0]);
		diffuseFinal = calculateDiffuse(material, vs_position, vs_normal, light[0]);
		specularFinal = calculateSpecular(material, vs_position, vs_normal, light[0], cameraPos);
		
		//fs_color = fs_color + attenuationFinal * (vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f));
	//}

	//fs_color = (fs_color + texture(material.diffuseTex, vs_texcoord)) * vec4(ambientFinal, 1.f);
	

	//Final Color / Light	
	fs_color = texture(material.diffuseTex, vs_texcoord)
		//* vec4(vs_color, 1.f)	//rainbow effect
		* (vec4(ambientFinal, 1.f)
			+ attenuationFinal * (vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f))
		);
}
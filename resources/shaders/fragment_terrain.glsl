#version 440

struct Fog {
	float density;
	float gradient;
};

struct LightPoint {
	vec3 position;
	vec3 color;
	float intensity;
	float attenuation;	// constant
	float falloffNear;	// linear
	float falloffFar;	// quadratic
};

in vec3 vs_position;
in vec2 vs_texcoord;
in vec3 vs_normal;
in float visibility;

out vec4 fs_color;

uniform sampler2D backgroundTex;
uniform sampler2D rTex;
uniform sampler2D gTex;
uniform sampler2D bTex;
uniform sampler2D blendMap;

uniform Fog fog;
uniform LightPoint lightPoint[4];
uniform vec3 ambient;
uniform vec3 cameraPos;
uniform float vertexCount;
//uniform vec3 skyColor;


vec3 calculateDiffuse(vec4 diffuseTex, vec3 vs_position, vec3 vs_normal, LightPoint lightPoint) {
	vec3 posToLightDirVec = normalize(lightPoint.position - vs_position);
	float diffuse		  = clamp(dot(posToLightDirVec, normalize(vs_normal)), 0, 1);
	vec3 diffuseFinal	  = vec3(1.f) * diffuse;

	return diffuseFinal * lightPoint.color;
}

vec3 calculateSpecular(vec4 diffuseTex, vec3 vs_position, vec3 vs_normal, LightPoint lightPoint, vec3 cameraPos) {
	vec3 lightToPosDirVec = normalize(vs_position - lightPoint.position);
	vec3 reflectDirVec	  = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
	vec3 posToViewDirVec  = normalize(cameraPos - vs_position);
	float specularConst	  = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 30);
	//vec3 specularFinal	  = material.specular * specularConst * texture(material.specularTex, vs_texcoord).rgb;
	vec3 specularFinal	  = vec3(1.f) * specularConst;

	return specularFinal * lightPoint.color;
}

float calculateAttenuation(vec3 vs_position, vec3 vs_normal, LightPoint lightPoint) {
	// http://learnwebgl.brown37.net/09_lights/lights_attenuation.html
	float dist			   = length(lightPoint.position - vs_position);
	float attenuationFinal = lightPoint.attenuation + (lightPoint.falloffNear * dist) + (lightPoint.falloffFar * dist * dist);

	return attenuationFinal / lightPoint.intensity;
}

float calculateFogVisibility() {
	vec3 posRelativeToCam  = cameraPos - vs_position;
	float dist = length(posRelativeToCam);
	float visibility = exp(-pow((dist*fog.density), fog.gradient));
	visibility = clamp(visibility, 0.0, 1.0);

	return visibility;
}



void main() {
	vec4 blendMapColor = texture(blendMap, vs_texcoord);
	
	float backTextureAmount = 1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);
	vec2 tiledCoords = vs_texcoord * vertexCount;
	vec4 backgroundTextureColor = texture(backgroundTex, tiledCoords) * backTextureAmount;
	vec4 rTexColor = texture(rTex, tiledCoords) * blendMapColor.r;
	vec4 gTexColor = texture(gTex, tiledCoords) * blendMapColor.g;
	vec4 bTexColor = texture(bTex, tiledCoords) * blendMapColor.b;

	vec4 totalColor = backgroundTextureColor + rTexColor + gTexColor + bTexColor;


	//Diffuse Light
	vec3 diffuseFinal = vec3(0.f);

	//Specular Light
	vec3 specularFinal = vec3(0.f);

	//Attenuation
	float attenuationFinal = 0.f;

	
	for (int i=0; i<4; ++i) {
		attenuationFinal = calculateAttenuation(vs_position, vs_normal, lightPoint[i]);
		diffuseFinal += calculateDiffuse(totalColor, vs_position, vs_normal, lightPoint[i]) / attenuationFinal;
		specularFinal += calculateSpecular(totalColor, vs_position, vs_normal, lightPoint[i], cameraPos) / attenuationFinal;
	}

	diffuseFinal = clamp(diffuseFinal, 0.0, 1.0);
	specularFinal = clamp(specularFinal, 0.0, 1.0);

	//Final Color / lightPoint
	fs_color = totalColor
		* (vec4(ambient, 1.f)
			+ (vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f))
		);
	
	// Fog calculation
	//fs_color = mix(vec4(vec3(0.0, 0.0, 0.0), 1.0), fs_color, calculateFogVisibility());
	//fs_color = mix(vec4(skyColor, 1.0), fs_color, visibility);
}
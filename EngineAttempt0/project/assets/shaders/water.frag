#version 420 core
in vec4 clipSpace;
in vec2 TexCoords;
in vec3 toCamVector;

const vec3 lightDirection = vec3(1,1,0);

uniform sampler2D reflectTexture;
uniform sampler2D refractTexture;
uniform sampler2D dudvMap;
uniform sampler2D dudvNMap;
uniform float time;

out vec4 FragColor;
void main()
{
	float movFactor = time * 0.02;
	vec2 distortion1 = (texture(dudvMap, vec2(TexCoords.x + movFactor, TexCoords.y) * 2).rg * 2 -1) * 0.02;
	vec2 distortion2 = (texture(dudvMap, vec2(-TexCoords.x - movFactor, TexCoords.y + movFactor) * 2).rg * 2 -1) * 0.02;
	vec2 totalDist = distortion1 + distortion2;

	vec2 ndc = (clipSpace.xy/clipSpace.w) /2  + 0.5;
	ndc += totalDist;
	ndc = clamp(ndc, 0.001, 0.999);
	vec4 reflectColor = texture(reflectTexture,vec2(ndc.x, -ndc.y));
	vec4 refractColor = texture(refractTexture, ndc);

	vec4 nmapValue = texture(dudvNMap, totalDist);
	vec3 normal = vec3(nmapValue.r * 2 -1, nmapValue.b, nmapValue.g * 2 -1);
	normal = normalize(normal);

	vec3 viewVector = normalize(toCamVector);
	float reflectiveVector = dot(viewVector, vec3(0, 1,0));
	reflectiveVector = pow(reflectiveVector, 0.5);

	vec4 BaseColor = mix(reflectColor, refractColor, reflectiveVector);
	BaseColor = mix(BaseColor, vec4(0.1, 0.1, 0.5, 1), 0.2);
	FragColor = BaseColor * max(dot(normalize(lightDirection), normal), 0.4);
}
#version 420 core
in vec2 TexCoords;

uniform sampler2D image;

const vec3 lightDir = vec3(0.5, 1, 0);
const float ambient = 0.1;

in vec3 norm;
in vec3 FragPos;

out vec4 FragColor;
void main()
{
	vec4 color = texture(image, TexCoords);
	float diffuse = max(dot(norm, lightDir), 0);
	vec4 result = (ambient + diffuse) * color;

	FragColor =  result;
}
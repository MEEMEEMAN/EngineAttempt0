#version 420 core

in vec3 uvs;
uniform samplerCube cube;
out vec4 FragColor;

void main()
{
	vec4 cube1 = texture(cube, uvs);

	FragColor = cube1;
}
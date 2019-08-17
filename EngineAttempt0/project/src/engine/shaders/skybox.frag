#version 420 core

in vec3 uvs;
uniform samplerCube cube;
out vec4 FragColor;

uniform float time;

void main()
{
	vec4 cube1 = texture(cube, uvs);
	vec4 color = mix(cube1, vec4(0), (sin(time * 0.2) + 1) * 0.5 * 0.5);

	FragColor = color;
}
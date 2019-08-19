#version 420 core

uniform sampler2D otis;
uniform sampler2D perhaps;

in vec2 TexCoords;
out vec4 FragColor;
void main()
{
	vec4 texOneColor = texture(otis, TexCoords);
	vec4 texTwoColor = texture(perhaps, TexCoords);

	FragColor = mix(texOneColor, texTwoColor, 0.5);
}
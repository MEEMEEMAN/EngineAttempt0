#version 420 core

in vec2 texCoords;
uniform sampler2D image;

out vec4 FragColor;
void main()
{
	FragColor = texture(image, texCoords);
}

#version 420 core
in vec2 TexCoords;

uniform sampler2D image;

out vec4 FragColor;
void main()
{
	vec4 color = texture(image, TexCoords);
	FragColor =  color;
}
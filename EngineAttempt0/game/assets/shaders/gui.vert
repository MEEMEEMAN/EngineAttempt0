#version 420 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexcoords;

uniform mat4 model;
out vec2 texCoords;

void main()
{
	gl_Position =  model * vec4(aPos, 1);

	texCoords = aTexcoords;
}
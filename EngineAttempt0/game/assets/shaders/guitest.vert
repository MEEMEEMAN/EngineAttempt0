#version 420 core
layout(location = 0) in vec3 positions;
layout(location = 1) in vec2 uvs;

uniform mat4 model;

out vec2 TexCoords;

void main()
{
	gl_Position = model * vec4(positions,1);
	TexCoords = uvs;
}
#version 420 core
layout(location = 0) in vec3 positions;
layout(location = 1) in vec2 uvs;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 camPos;

out vec4 clipSpace;
out vec2 TexCoords;
out vec3 toCamVector;

void main()
{
	vec4 worldPos =  model * vec4(positions,1);
	clipSpace = projection * view * worldPos;
	gl_Position = clipSpace;
	TexCoords = uvs;
	toCamVector = camPos - worldPos.xyz;
}
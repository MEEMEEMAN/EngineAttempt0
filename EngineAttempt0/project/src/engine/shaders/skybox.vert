#version 420 core
in vec3 position;

out vec3 uvs;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * vec4(position,1);

	uvs = position;
}
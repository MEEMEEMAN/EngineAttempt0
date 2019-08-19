#version 420 core
in vec3 position;

out vec3 uvs;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 pos =  projection * view * model * vec4(position,1);
	gl_Position = pos.xyww;
	uvs = position;
}
#version 420 core
layout(location = 0) in vec3 positions;
layout(location = 1) in vec2 uvs;
layout(location = 2) in vec3 normals;

out vec2 TexCoords;
out vec3 norm;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(positions, 1);
	FragPos = vec3(model * vec4(positions, 1));
	TexCoords = uvs;
	norm = mat3(transpose(inverse(model))) * normals;
	//norm = vec3(model * vec4(normals,1));
}
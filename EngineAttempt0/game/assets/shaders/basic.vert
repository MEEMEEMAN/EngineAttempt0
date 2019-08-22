#version 420 core
layout(location = 0) in vec3 positions;
layout(location = 1) in vec2 uvs;
layout(location = 2) in vec3 normals;

out vec2 TexCoords;
out vec3 norm;
out vec3 FragPos;

uniform vec4 plane;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 worldPosition = model * vec4(positions,1);
	gl_ClipDistance[0] = dot(worldPosition, plane);

	gl_Position = projection * view * worldPosition;
	FragPos = vec3(worldPosition);
	TexCoords = uvs;
	norm = normalize(mat3(transpose(inverse(model))) * normals);
}
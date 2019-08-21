#pragma once
#include "pch.h"

std::ostream& operator <<(std::ostream& os, const vec2& vector)
{
	os << " X: " << vector.x << " Y: " << vector.y;
	return os;
}


std::ostream& operator <<(std::ostream& os, const vec3& vector)
{
	os << " X: " << vector.x << " Y: " << vector.y << " Z: " << vector.z;
	return os;
}

std::ostream& operator <<(std::ostream& os, const vec4& vector)
{
	os << " X: " << vector.x << " Y: " << vector.y << " Z: " << vector.z << " W: " << vector.w;
	return os;
}

std::ostream& operator <<(std::ostream& os, const mat2& matrix)
{
	os << matrix[0][0];
	return os;
}


std::ostream& operator <<(std::ostream& os, const mat4& matrix)
{
	os << "[00]:" << matrix[0][0] << "|[01]:" << matrix[0][1] << "|[02]:" << matrix[0][2] << "|[03]:" << matrix[0][3] << "\n";
	os << "[10]:" << matrix[1][0] << "|[11]:" << matrix[1][1] << "|[12]:" << matrix[1][2] << "|[13]:" << matrix[1][3] << "\n";
	os << "[20]:" << matrix[2][0] << "|[21]:" << matrix[2][1] << "|[22]:" << matrix[2][2] << "|[23]:" << matrix[2][3] << "\n";
	os << "[30]:" << matrix[3][0] << "|[31]:" << matrix[3][1] << "|[32]:" << matrix[3][2] << "|[33]:" << matrix[3][3] << "\n";
	return os;
}

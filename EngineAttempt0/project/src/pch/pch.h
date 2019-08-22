#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <ostream>
#include <stack>
#include <thread>
#include <mutex>
#include <atomic>


#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

#include "stb/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat2 mat2;
typedef glm::mat3 mat3;
typedef glm::mat4 mat4;


std::ostream& operator <<(std::ostream& os, const vec2& vector);
std::ostream& operator <<(std::ostream& os, const vec3& vector);
std::ostream& operator <<(std::ostream& os, const vec4& vector);

std::ostream& operator <<(std::ostream& os, const mat2& matrix);
std::ostream& operator <<(std::ostream& os, const mat3& matrix);
std::ostream& operator <<(std::ostream& os, const mat4& matrix);

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "fmod.hpp"
#include "fmod_errors.h"

typedef FMOD_VECTOR fmodvec;

#include "json.h"
#include "reader.h"
#include "writer.h"

#define conlog(x) std::cout << x << "\n"
#define quote(x) #x
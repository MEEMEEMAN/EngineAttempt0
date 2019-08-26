#pragma once
#include "Material.h"

std::unordered_map<std::string, Material*> Material::matPool;
std::vector<std::string> Material::ids;
Material* Material::currentMaterial = nullptr;
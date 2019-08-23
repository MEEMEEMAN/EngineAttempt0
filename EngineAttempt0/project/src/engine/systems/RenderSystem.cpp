#include "RenderSystem.h"
#include "Renderable.h"

Camera* RenderSystem::mRenderCam = nullptr;
std::unordered_map<Material*, std::vector<Renderable>> RenderSystem::renderBuffer;
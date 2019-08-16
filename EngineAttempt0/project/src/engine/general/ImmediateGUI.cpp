#include "ImmediateGUI.h"
#include "Context.h"

void GUI::Initialize(std::string GLSL_VERSION)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsLight();
	ImGui_ImplGlfw_InitForOpenGL(Context::GetMainWindow(), true);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION.c_str());
}

void GUI::BeginFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GUI::EndFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

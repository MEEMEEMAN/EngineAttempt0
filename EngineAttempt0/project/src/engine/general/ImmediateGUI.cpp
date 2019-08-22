#include "ImmediateGUI.h"
#include "Context.h"

bool ImmediateGUI::toggle = false, ImmediateGUI::toggleWireFrame = false, ImmediateGUI::vsyncBtn = false;

void ImmediateGUI::Initialize(std::string GLSL_VERSION)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsLight();
	ImGui_ImplGlfw_InitForOpenGL(Context::GetMainWindow(), true);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION.c_str());
}

void ImmediateGUI::BeginFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImmediateGUI::EndFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

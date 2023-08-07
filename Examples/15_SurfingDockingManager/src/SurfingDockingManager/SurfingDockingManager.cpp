#include "SurfingDockingManager.h"

SurfingDockingManager::SurfingDockingManager()
{
	ofLogNotice(__FUNCTION__);
}

SurfingDockingManager::~SurfingDockingManager()
{
	ofLogNotice(__FUNCTION__);
}

void SurfingDockingManager::setup(ofxImGui::Gui& ui)
{
	if (bDoneSetup) return;

	ofLogNotice(__FUNCTION__);

	mainFrame.Init();

	bDoneSetup = 1;
}

void SurfingDockingManager::init()
{
	if (bDoneInit) return;

	ofLogNotice(__FUNCTION__);

#if 0
	//ImGuiViewport* viewport = ImGui::GetMainViewport();
	//if (viewport)
	//{
	//	size = viewport->WorkSize;
	//}
	//size = ImVec2(ofGetWindowSize());

	ImGuiIO& io = ImGui::GetIO(); 
	//(void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Viewport
	//io.FontAllowUserScaling = true; // activate zoom feature with ctrl + mousewheel
	 
	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
#endif

	bDoneInit = 1;
}

void SurfingDockingManager::draw() 
{
	size = ImVec2(ofGetWindowSize());
	mainFrame.Display(size);
}

void SurfingDockingManager::exit() 
{
	mainFrame.Unit();
}

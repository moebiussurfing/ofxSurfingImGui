#pragma once

// based on main.cpp

#include "ofxImGui.h"	
#include "imgui_internal.h"

#include "MainFrame.h"

#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>

class App_LayoutManager
{

public:

	MainFrame mainFrame;

	void setup()
	{
		mainFrame.Init();
	}

	void draw()
	{
		int display_w, display_h;
		ImVec2 size;

		//while (!glfwWindowShouldClose(window))
		//{
		//// maintain active, prevent user change via imgui dialog
		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		 //  

		//TODO: should get ofWindow size..
		display_w = 1280;
		display_h = 720;

		ImGuiIO& io = ImGui::GetIO();

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			if (viewport)
			{
				size = viewport->WorkSize;
			}
		}
		else
		{
			size = ImVec2((float)display_w, (float)display_h);
		}

		mainFrame.Display(ImVec2(display_w, display_h));
	}

	void exit()
	{
		mainFrame.Unit();
	}

};

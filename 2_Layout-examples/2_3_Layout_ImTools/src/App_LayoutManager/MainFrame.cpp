// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

/*
MIT License

Copyright (c) 2021 Stephane Cuillerdier (aka Aiekick)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "MainFrame.h"

#include <GLFW/glfw3.h>
#include <LayoutManager/LayoutManager.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

#include "LeftPane.h"
#include "RightPane.h"
#include "BottomPane.h"
#include "TopPane.h"
#include "CentralPane.h"
#include <LayoutManager/SamplePane.h>

void MainFrame::Init()
{
	LoadConfigFile("config.xml");
	
	LayoutManager::Instance()->Init("Layouts", "Default Layout");
	LayoutManager::Instance()->AddPane(LeftPane::Instance(), "Left", (1 << 0), PaneDisposal::LEFT, true, true);
	LayoutManager::Instance()->AddPane(RightPane::Instance(), "Right", (1 << 1), PaneDisposal::RIGHT, true, true);
	LayoutManager::Instance()->AddPane(BottomPane::Instance(), "Bottom", (1 << 2), PaneDisposal::BOTTOM, true, true);
	LayoutManager::Instance()->AddPane(TopPane::Instance(), "Top", (1 << 3), PaneDisposal::TOP, true, true);
	LayoutManager::Instance()->AddPane(CentralPane::Instance(), "Central", (1 << 4), PaneDisposal::CENTRAL, true, true);
	LayoutManager::Instance()->AddPane(SamplePane::Instance(), "Sample", (1 << 5), PaneDisposal::RIGHT, true, false);
}

void MainFrame::Unit()
{
	SaveConfigFile("config.xml");
}

//////////////////////////////////////////////////////////////////////////////
//// DRAW ////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
static int _widgetId = 8953;

void MainFrame::Display(ImVec2 vSize)
{
	if (ImGui::BeginMainMenuBar())
	{
		LayoutManager::Instance()->DisplayMenu(vSize);

		if (ImGui::BeginMenu("ImGui"))
		{
			ImGui::MenuItem("Show ImGui Demo", "", &m_ShowImGui);
			ImGui::MenuItem("Show ImGui Metric/Debug", "", &m_ShowMetric);

			ImGui::EndMenu();
		}

		// ImGui Infos
		auto io = ImGui::GetIO();
		const auto label = ct::toStr("Dear ImGui %s (Docking)", ImGui::GetVersion());
		const auto size = ImGui::CalcTextSize(label.c_str());
		ImGui::ItemSize(ImVec2(ImGui::GetContentRegionAvail().x - size.x - ImGui::GetStyle().FramePadding.x * 2.0f, 0));
		ImGui::Text("%s", label.c_str());

		ImGui::EndMainMenuBar();
	}

	if (LayoutManager::Instance()->BeginDockSpace(ImGuiDockNodeFlags_PassthruCentralNode))
	{
		//MainFrame::sCentralWindowHovered |= LayoutManager::Instance()->IsDockSpaceHoleHovered();

		LayoutManager::Instance()->EndDockSpace();
	}

	_widgetId = LayoutManager::Instance()->DisplayPanes(_widgetId);

	LayoutManager::Instance()->InitAfterFirstDisplay(vSize);

	LayoutManager::Instance()->DrawDialogsAndPopups();

	if (m_ShowImGui) ImGui::ShowDemoWindow(&m_ShowImGui);
	if (m_ShowMetric) ImGui::ShowMetricsWindow(&m_ShowMetric);
}

std::string MainFrame::getXml(const std::string& vOffset, const std::string& vUserDatas)
{
	UNUSED(vUserDatas);

	std::string str;

	str += LayoutManager::Instance()->getXml(vOffset, "app");
	
	return str;
}

bool MainFrame::setFromXml(tinyxml2::XMLElement* vElem, tinyxml2::XMLElement* vParent, const std::string& vUserDatas)
{
	UNUSED(vUserDatas);

	// The value of this child identifies the name of this element
	std::string strName;
	std::string strValue;
	std::string strParentName;

	strName = vElem->Value();
	if (vElem->GetText())
		strValue = vElem->GetText();
	if (vParent != 0)
		strParentName = vParent->Value();

	LayoutManager::Instance()->setFromXml(vElem, vParent, "app");
	
	return true;
}
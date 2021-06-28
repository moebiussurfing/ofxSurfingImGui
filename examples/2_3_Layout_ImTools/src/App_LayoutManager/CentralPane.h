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
#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxSurfingImGui.h"
#include "imgui_internal.h"


#include <LayoutManager/AbstractPane.h>
#include <ctools/ConfigAbstract.h>
#include <ctools/cTools.h>

#include <string>
#include <map>
#include <set>

class CentralPane : public AbstractPane
{
public:
	bool Init() override;
	void Unit() override;
	int DrawPanes(int vWidgetId, std::string vUserDatas) override;
	void DrawDialogsAndPopups(std::string vUserDatas) override;
	int DrawWidgets(int vWidgetId, std::string vUserDatas) override;

public: // configuration
	std::string getXml(const std::string& vOffset, const std::string& vUserDatas);
	bool setFromXml(tinyxml2::XMLElement* vElem, tinyxml2::XMLElement* vParent, const std::string& vUserDatas);

public: // singleton
	static CentralPane* Instance()
	{
		static CentralPane _instance;
		return &_instance;
	}

protected:
	CentralPane(); // Prevent construction
	CentralPane(const CentralPane&) = delete;
	CentralPane& operator =(const CentralPane&) = delete;
	~CentralPane(); // Prevent unwanted destruction};



public:
	ofParameterGroup params;
	void addParams(ofParameterGroup &group) {
		params = group;
	}
	void drawParams() {
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
		flags |= ImGuiTreeNodeFlags_Framed; // uncomment to draw dark tittle bar
		flags |= ImGuiTreeNodeFlags_DefaultOpen; // comment to start closed
		ofxImGuiSurfing::AddGroup(params, flags);
	}
};

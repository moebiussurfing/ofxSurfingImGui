#pragma once

#include "ofMain.h"

#include "surfingHelpers.h"
#include "ofHelpers.h"

class SurfingFiles
{
public:
	SurfingFiles() {
	};

	~SurfingFiles() {
	};

	void draw(bool bTreeFoldered = false)
	{
		ImGuiTreeNodeFlags flagst;
		flagst = ImGuiTreeNodeFlags_None;
		flagst |= ImGuiTreeNodeFlags_DefaultOpen;
		flagst |= ImGuiTreeNodeFlags_Framed;

		bool b;
		if (bTreeFoldered) b = ImGui::TreeNodeEx(label.c_str(), flagst);
		if (!bTreeFoldered || b)
		{
			float w = ofxImGuiSurfing::getWidgetsWidth();
			float h = ofxImGuiSurfing::getWidgetsHeightUnit();

			size_t sz = dir.size();
			for (size_t i = 0; i < sz; i++)
			{
				string n = dir[i].getBaseName();

				bool b = (i == index.get());
				ofxImGuiSurfing::BeginBlinkFrame(b);

				if (ImGui::Button(n.c_str(), ImVec2(w, h)))
				{
					index = ofClamp(i, index.getMin(), index.getMax());
				}

				ofxImGuiSurfing::EndBlinkFrame(b);
			}
		}
		if (bTreeFoldered && b) ImGui::TreePop();
	};

	string label = "Files";

	ofParameter<int> index{ "Theme", 0, 0, 0 };

private:
	ofDirectory dir;
	string pathFiles = "";
	string ext = "ini";
	bool bReady = false;

public:
	string getName(int i) const {
		if (dir.size() == 0) return string("");
		i = ofClamp(i, index.getMin(), index.getMax());
		return dir[i].getBaseName();
	};

	void refreshFiles() {
		if (pathFiles == "") return;

		bReady = ofFile(pathFiles).isDirectory();
		dir.open(pathFiles);
		dir.allowExt(ext);
		dir.listDir();

		index.setMin(0);
		index.setMax(dir.numFiles() - 1);

		size_t sz = dir.size();

		if (dir.numFiles() == 0) ofLogWarning("ofxSurfingImGui:SurfingFiles") << "Folder " << pathFiles << " is empty.";
		else ofLogNotice("ofxSurfingImGui:SurfingFiles") << "Folder " << pathFiles << " opened.";

		for (size_t i = 0; i < sz; i++)
		{
			string n = dir[i].getBaseName();
			ofLogNotice("ofxSurfingImGui:SurfingFiles") << "#" << i << " " << n << "." << ext;
		}
	};

	int getSize() const { return dir.size(); };

	vector<string> getNames() const {
		vector<string> ss;
		for (size_t i = 0; i < dir.size(); i++)
		{
			string n = dir[i].getBaseName();
			ss.push_back(n);
		}
		return ss;
	};

	void setPathDirectory(string path)
	{
		pathFiles = ofToDataPath(path);
		refreshFiles();
	};
};

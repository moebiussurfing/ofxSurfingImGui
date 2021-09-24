#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "ImGuiFileDialog.h"
#include "imgui_internal.h"

using namespace ImGui;

//------------------------------

namespace ofxImGuiSurfing
{
	static std::string filePathName = "-1";
	static std::string filePath = "-1";
	
	inline bool drawGui_FileDialog()
	{
		bool bReturn = false;

		ImVec2 pos;

		ImGui::Begin("File Browser", NULL, ImGuiWindowFlags_AlwaysAutoResize);
		{
			float w, h;
			w = getWidgetsWidth();
			h = getWidgetsHeightRelative() * 2;

			float posx;
			float posy;
			float wwidth;
			float hheight;

			// open Dialog Simple
			if (ImGui::Button("Open File Browser", ImVec2(w, h)))
				ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".xml\0.json\0.*\0\0", ".", 0);
			//,0 multiselection

			float pad = 2;
			posx = ImGui::GetWindowPos().x;
			posy = ImGui::GetWindowPos().y;
			wwidth = ImGui::GetWindowWidth();
			hheight = ImGui::GetWindowHeight();
			pos.x = posx + wwidth + pad;
			pos.y = posy;
		}
		ImGui::End();

		//-

		ImGui::SetNextWindowPos(pos, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(600, 600), ImGuiCond_FirstUseEver);

		// display
		if (ImGuiFileDialog::Instance()->FileDialog("ChooseFileDlgKey", ImGuiWindowFlags_None))
		{
			// action if OK
			if (ImGuiFileDialog::Instance()->IsOk == true)
			{
				filePathName = ImGuiFileDialog::Instance()->GetFilepathName();
				filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

				ofLogVerbose(__FUNCTION__) << "filePathName:" << filePathName;
				ofLogVerbose(__FUNCTION__) << "filePath:" << filePath;

				// action
				bReturn = true;
			}

			// close CANCEL
			ImGuiFileDialog::Instance()->CloseDialog("ChooseFileDlgKey");

			//TODO:
			//set folder (not file)
			if (ImGui::Button("Set Directory"))
			{
				//ImGuiFileDialog::Instance()->DirectoryNameBuffer();

				std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
				ofLogVerbose(__FUNCTION__) << "filePathName:" << filePathName;

				bReturn = true;
			}
		}

		// reset
		if (!bReturn) {
			filePathName = "-1";
			filePath = "-1";
		}

		return bReturn;
	}

	////static bool canValidateDialog = false;
	//bool canValidateDialog = false;

	//inline void InfosPane(std::string vFilter, bool *vCantContinue) // if vCantContinue is false, the user cant validate the dialog
	//{
	//	ImGui::TextColored(ImVec4(0, 1, 1, 1), "Infos Pane");
	//	ImGui::Text("Selected Filter : %s", vFilter.c_str());
	//	ImGui::Checkbox("if not checked you cant validate the dialog", &canValidateDialog);
	//	if (vCantContinue)
	//		*vCantContinue = canValidateDialog;
	//}

	//void drawGui_FileDialog()
	//{
	//	// open Dialog with Pane
	//	if (ImGui::Button("Open File Dialog with a custom pane"))
	//		ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".cpp\0.h\0.hpp\0\0",//?
	//			".", "", std::bind(&InfosPane, std::placeholders::_1, std::placeholders::_2), 350, "InfosPane");

	//	// display and action if ok
	//	if (ImGuiFileDialog::Instance()->FileDialog("ChooseFileDlgKey"))
	//	{
	//		if (ImGuiFileDialog::Instance()->IsOk == true)
	//		{
	//			std::string filePathName = ImGuiFileDialog::Instance()->GetFilepathName();
	//			std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
	//			// action
	//		}
	//		// close
	//		ImGuiFileDialog::Instance()->CloseDialog("ChooseFileDlgKey");
	//	}
	//}

}
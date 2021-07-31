
#pragma once

#include <fstream>
#include <streambuf>

#include "ofMain.h"

#include "imgui.h"
#include "TextEditor.h"


//--------------------------------------------------------------
class SurfingTextEditor
{

private:

	//std::string *textContent;

	//static const char* fileToEdit = "ImGuiColorTextEdit/TextEditor.cpp";
	char* fileToEdit;

	TextEditor editor;

	TextEditor::TextEditor::LanguageDefinition lang;

	std::string pathEditing = "-1"; // realted to data path

	bool bIntitiated = false;

	//-

public:

	//--------------------------------------------------------------
	void setup() {
	}

	//--

	//--------------------------------------------------------------
	void setText(string str, bool bResetPathSave = true) {
		editor.SetText(str);

		if (bResetPathSave) pathEditing = "-1";
	}

	//--------------------------------------------------------------
	void loadText(string path) {

		pathEditing = path;

		string p = ofFilePath::getAbsolutePath(path);
		fileToEdit = (char*)(p.c_str());

		//-

		ofLogNotice(__FUNCTION__) << "load ifstream fileToEdit: " << ofToString(fileToEdit);

		std::ifstream t(fileToEdit);
		if (t.good())
		{
			std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
			editor.SetText(str);
			ofLogNotice(__FUNCTION__) << "loaded file: " << ofToString(fileToEdit);
		}
		else {
			ofLogNotice(__FUNCTION__) << "file not found! " << ofToString(fileToEdit);
		}
	}

	//--

	//--------------------------------------------------------------
	void draw() {

		// initialize

		if (!bIntitiated)
		{
			bIntitiated = true;

			lang = TextEditor::LanguageDefinition::C();
			//lang = TextEditor::LanguageDefinition::Lua();
			editor.SetLanguageDefinition(lang);

			//editor.SetShowWhitespaces(true);

			//editor.SetPalette(TextEditor::GetLightPalette());
			editor.SetPalette(TextEditor::GetDarkPalette());
		}

		//--

		auto cpos = editor.GetCursorPosition();
		ImGui::Begin("Text Editor Demo", nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar);
		ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (pathEditing != "-1")
				{
					if (ImGui::MenuItem("Save"))
					{
						auto textToSave = editor.GetText();
						stringstream ssTextToSave;
						ssTextToSave << textToSave;

						// save text....
						TextToFile(ofFilePath::getAbsolutePath(pathEditing), ssTextToSave, false);
					}
				}
				else {
					if (ImGui::MenuItem("New!"))
					{
					}
				}

				if (ImGui::MenuItem("Clear"))
				{
					setText("");
					//break;
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				bool ro = editor.IsReadOnly();
				if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
					editor.SetReadOnly(ro);
				ImGui::Separator();

				if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && editor.CanUndo()))
					editor.Undo();
				if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && editor.CanRedo()))
					editor.Redo();

				ImGui::Separator();

				if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, editor.HasSelection()))
					editor.Copy();
				if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && editor.HasSelection()))
					editor.Cut();
				if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && editor.HasSelection()))
					editor.Delete();
				if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
					editor.Paste();

				ImGui::Separator();

				if (ImGui::MenuItem("Select all", nullptr, nullptr))
					editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(editor.GetTotalLines(), 0));

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View"))
			{
				if (ImGui::MenuItem("Dark palette"))
					editor.SetPalette(TextEditor::GetDarkPalette());
				if (ImGui::MenuItem("Light palette"))
					editor.SetPalette(TextEditor::GetLightPalette());
				if (ImGui::MenuItem("Retro blue palette"))
					editor.SetPalette(TextEditor::GetRetroBluePalette());
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		//std::filesystem::path filepath = ofFilePath::getAbsolutePath(pathEditing);
		//ofFilePath filepath = (ofFilePath::getAbsolutePath(pathEditing));
		//string name = filepath.getFileName();
		//string baseName = ofFilePath::getFileName(pathEditing);
		//static string baseName = ofFilePath::getFileName(ofFilePath::getAbsolutePath(pathEditing));

		ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s",
			cpos.mLine + 1,
			cpos.mColumn + 1,
			editor.GetTotalLines(),
			editor.IsOverwrite() ? "Ovr" : "Ins",
			editor.CanUndo() ? "*" : " ",
			editor.GetLanguageDefinition().mName.c_str(),
			pathEditing.c_str()
			//baseName.c_str()
		);

		editor.Render("TextEditor");
		ImGui::End();
	}

	//-

	// added
	//--------------------------------------------------------------
	bool TextToFile(const string& Path, const stringstream& Args, bool Append)
	{
		//ofFile f(path, ofFile::ReadWrite);
		//if (!f.exists()) f.create();

		filebuf fb;
		if (Append) fb.open(Path, ios::app);
		else fb.open(Path, ios::out);

		if (!fb.is_open()) return false;

		ostream os(&fb);
		stringstream ss(Args.str());

		if (ss.fail()) return false;

		string temp;
		while (getline(ss, temp))
		{
			if (temp != "")
			{
				os << temp << endl;
			}
		}

		fb.close();
		return true;
	}
};


//--

//TODO:
//load content:
//problems on char / string types... 

//std::string _name = "text.txt";
//ofLog()<<"(&ofToDataPath(_name)[0]):" << ofToString((&ofToDataPath(_name)[0]));

//string inputPath = ofFilePath::getAbsolutePath("input");
//ofStringReplace(inputPath, "/", "\\");

//fileToEdit = (&_name.c_str());

//TODO:
//this works on macOS
//fileToEdit = (&ofToDataPath(_name)[0]);

//-

////if (0)
//{
//	fileToEdit = (char*)(ofFilePath::getAbsolutePath("text1.txt").c_str());
//	ofLogNotice(__FUNCTION__) << "load ifstream fileToEdit: " << ofToString(fileToEdit);
//	//std::ifstream t("text.txt");
//	std::ifstream t(fileToEdit);
//	if (t.good())
//	{
//		std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
//		editor.SetText(str);
//		ofLogNotice(__FUNCTION__) << "loaded file: " << ofToString(fileToEdit);
//	}
//	else {
//		ofLogNotice(__FUNCTION__) << "file not found! " << ofToString(fileToEdit);
//	}
//}	
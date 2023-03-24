#pragma once

/*

More updated fork.
https://github.com/santaclose/ImGuiColorTextEdit

*/

#include "ofMain.h"

//#include <fstream>
//#include <streambuf>

#include "ofxSurfingImGui.h"
//#include "ofHelpers.h"
//#include "imgui.h"

#include "TextEditor.h"


//--------------------------------------------------------------
class SurfingTextEditor
{
public:
	SurfingTextEditor() {};
	~SurfingTextEditor() { exit(); };

	ofParameterGroup params{ "SurfingTextEditor" };
	ofParameter<bool> bGui{ "TextEditor", true };
	ofParameter<bool> bExtra{ "Extra", false };
	ofParameter<bool> bShowInfo{ "Info", false };
	ofParameter<bool> bMenus{ "Menus", false };
	ofParameter<int> sizeFont{ "Size", 0, 0, 3 };

private:
	string name = "Text Editor Demo";

	//std::string *textContent;

	//static const char* fileToEdit = "ImGuiColorTextEdit/TextEditor.cpp";
	char* fileToEdit;

	TextEditor editor;

	TextEditor::TextEditor::LanguageDefinition lang;

	std::string pathEditing = "-1"; // realted to data path

	bool bIntitiated = false;

	//-

public:

	void setName(string n) { name = n; }

	//--------------------------------------------------------------
	void setup(string name) {
		setName(name);
		setup();
	}

	//--------------------------------------------------------------
	void exit() {
		ofxSurfingHelpers::save(params);
	}

	//--------------------------------------------------------------
	void setup() {
		params.add(bGui);
		params.add(bExtra);
		params.add(bMenus);
		params.add(bShowInfo);
		params.add(sizeFont);

		ofxSurfingHelpers::load(params);
	}

	//--

	//--------------------------------------------------------------
	string getText() const {
		return editor.GetText();
	}

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

		ofLogNotice("ofxSurfingImGui::surfingTextEditor") << "load ifstream fileToEdit: " << ofToString(fileToEdit);

		std::ifstream t(fileToEdit);
		if (t.good())
		{
			std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
			editor.SetText(str);
			ofLogNotice("ofxSurfingImGui::surfingTextEditor") << "loaded file: " << ofToString(fileToEdit);
		}
		else {
			ofLogNotice("ofxSurfingImGui::surfingTextEditor") << "file not found! " << ofToString(fileToEdit);
		}
	}

	//--

	//--------------------------------------------------------------
	void drawImGuiMenus()
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Load"))
				{
					////TODO: open dialog
					//string path = ofToDataPath("text2.txt", true);
					//textEditor.loadText(path);
				}

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
	}

	//--------------------------------------------------------------
	void drawImGuiInternal() {
		ofxImGuiSurfing::AddParameter(bExtra);
		if (bExtra) {
			ofxImGuiSurfing::AddGroup(params);
		}
	}

	//--------------------------------------------------------------
	void draw() {
		if (!bGui) return;

		// initialize
		if (!bIntitiated)
		{
			bIntitiated = true;

			lang = TextEditor::LanguageDefinition::C();
			//lang = TextEditor::LanguageDefinition::Json();
			//lang = TextEditor::LanguageDefinition::Lua();

			editor.SetLanguageDefinition(lang);

			if (1) {
				editor.SetShowWhitespaces(true);
				editor.SetShowShortTabGlyphs(true);
				editor.SetColorizerEnable(true);
			}

			//editor.SetPalette(TextEditor::GetLightPalette());
			//editor.SetPalette(TextEditor::GetDarkPalette());
			editor.SetPalette(TextEditor::GetMarianaPalette());
		}

		//--

		auto cpos = editor.GetCursorPosition();

		ImGuiWindowFlags f = ImGuiWindowFlags_None;
		f += ImGuiWindowFlags_HorizontalScrollbar;
		if (bMenus) f += ImGuiWindowFlags_MenuBar;

		ImGui::SetWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);
		ImGui::Begin(name.c_str(), nullptr, f);

		if (bMenus) {
			drawImGuiMenus();
		}

		drawImGuiInternal();

		//std::filesystem::path filepath = ofFilePath::getAbsolutePath(pathEditing);
		//ofFilePath filepath = (ofFilePath::getAbsolutePath(pathEditing));
		//string name = filepath.getFileName();
		//string baseName = ofFilePath::getFileName(pathEditing);
		//static string baseName = ofFilePath::getFileName(ofFilePath::getAbsolutePath(pathEditing));

		if (bShowInfo) {
			//ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s",
			//	cpos.mLine + 1,
			//	cpos.mColumn + 1,
			//	editor.GetTotalLines(),
			//	editor.IsOverwrite() ? "Ovr" : "Ins",
			//	editor.CanUndo() ? "*" : " ",
			//	editor.GetLanguageDefinitionName(),
			//	//editor.GetLanguageDefinition().mName.c_str(),
			//	pathEditing.c_str()
			//	//baseName.c_str()
			//);

			ImGui::Text(pathEditing.c_str());

			ImGui::Text("%6d/%-6d %6d lines  | %s",
				cpos.mLine + 1,
				cpos.mColumn + 1,
				editor.GetTotalLines(),
				editor.IsOverwrite() ? "Ovr" : "Ins"
			);
		}

		editor.Render(name.c_str());
		//editor.Render("TextEditor");

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
//	ofLogNotice("ofxSurfingImGui::surfingTextEditor") << "load ifstream fileToEdit: " << ofToString(fileToEdit);
//	//std::ifstream t("text.txt");
//	std::ifstream t(fileToEdit);
//	if (t.good())
//	{
//		std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
//		editor.SetText(str);
//		ofLogNotice("ofxSurfingImGui::surfingTextEditor") << "loaded file: " << ofToString(fileToEdit);
//	}
//	else {
//		ofLogNotice("ofxSurfingImGui::surfingTextEditor") << "file not found! " << ofToString(fileToEdit);
//	}
//}	
#pragma once

/*

	Taken from a more updated fork!
	https://github.com/santaclose/ImGuiColorTextEdit

*/

#include "ofMain.h"

//#include "imgui.h"
//#include "ofHelpers.h"
#include "ofxSurfingImGui.h"

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
	ofParameter<bool> bAdvanced{ "Advanced", false };
	ofParameter<bool> bMenus{ "Menus", false };
	ofParameter<int> font{ "Font", 0, 0, 3 };
	ofParameter<int> theme{ "Theme", 0, 0, 3 };
	ofParameter<bool> bPath{ "Full Path" , false };

	void addKeyword(string keyword) {//call on setup
		keywords.push_back(keyword);

		//lang.mKeywords.insert("CPP");
		//lang.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("CPP", TextEditor::PaletteIndex::Identifier));
	}

private:
	void buildFontNames() {
		if (bs.size() != 0) bs.clear();
		for (size_t i = 0; i < customFonts.size(); i++) {
			string n = namesCustomFonts[i];
			ofParameter<bool> pb{ n, false };
			bs.emplace_back(pb);
			//bs.push_back(pb);
		}
	};
public:
	void setCustomFonts(vector<ImFont*> f, vector<string> names)
	{
		setCustomFontsNames(names);
		setCustomFonts(f);
	};
	void setCustomFontsNames(vector<string> names)
	{
		namesCustomFonts = names;
	};
	void setCustomFonts(vector<ImFont*> f)
	{
		customFonts = f;

		if (customFonts.size() == 0) {
			ofLogError("ofxSurfingImGui:SurfingLog") << "It looks that not any extra font styles are added!";

		}

		font.setMax(customFonts.size() - 1);

		buildFontNames();

		font = font;
	};

private:
	vector<ofParameter<bool>> bs;
	string pathEditingFileName;

private:

	vector<ImFont*> customFonts;
	vector<string> namesCustomFonts;

	vector<string> keywords;

	string name = "Text Editor Demo";

	char* fileToEdit;

	TextEditor editor;
	TextEditor::TextEditor::LanguageDefinition lang;

	std::string pathEditing = "-1"; // related to data path

	bool bIntitiated = false;

	//--

public:

	void setName(string n) {
		name = n;
		bGui.setName(n);
	}

	//--------------------------------------------------------------
	void setup(string name) {
		setName(name);
		setup();
	}

	//--------------------------------------------------------------
	void exit() {
		ofRemoveListener(params.parameterChangedE(), this, &SurfingTextEditor::Changed_Params); // exit()

		ofxImGuiSurfing::save(params);
	}

	//--------------------------------------------------------------
	void setup() {
		params.add(bGui);
		params.add(bExtra);
		params.add(bAdvanced);
		params.add(bMenus);
		params.add(bShowInfo);
		params.add(font);
		params.add(theme);
		params.add(bPath);

		ofAddListener(params.parameterChangedE(), this, &SurfingTextEditor::Changed_Params); // setup()

		ofxImGuiSurfing::load(params);
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

	void Changed_Params(ofAbstractParameter& e)
	{
		string name = e.getName();
		ofLogNotice() << __FUNCTION__ << name << " : " << e;

		if (name == theme.getName())
		{
			switch (theme)
			{
			case 0: editor.SetPalette(TextEditor::GetDarkPalette()); break;
			case 1: editor.SetPalette(TextEditor::GetLightPalette()); break;
			case 2: editor.SetPalette(TextEditor::GetRetroBluePalette()); break;
			case 3: editor.SetPalette(TextEditor::GetMarianaPalette()); break;
			}
			return;
		}

		if (name == font.getName())
		{
			for (size_t j = 0; j < bs.size(); j++) {
				bs[j] = (font.get() == j);
			}

			return;
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
				if (ImGui::MenuItem("New"))
				{
				}
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
				//else {
				//	if (ImGui::MenuItem("New!"))
				//	{
				//	}
				//}

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

				if (ImGui::MenuItem("Undo", "Ctrl-Z", nullptr, !ro && editor.CanUndo()))
					editor.Undo();
				if (ImGui::MenuItem("Redo", "Ctrl-Shift-Z", nullptr, !ro && editor.CanRedo()))
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
				ofxImGuiSurfing::MenuItemToggle(bExtra);
				ofxImGuiSurfing::MenuItemToggle(bAdvanced);
				ofxImGuiSurfing::MenuItemToggle(bShowInfo);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Font"))
			{
				for (size_t i = 0; i < customFonts.size(); i++) {
					if (ofxImGuiSurfing::MenuItemToggle(bs[i]))
					{
						if (bs[i]) font = i;

						bool bAllFalse = true;
						for (size_t j = 0; j < bs.size(); j++) {
							if (bs[j]) bAllFalse = false;
						}
						if (bAllFalse) { font = font; }//force true if has been disabled
					};
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Theme"))
			{
				if (ImGui::MenuItem("Dark palette", NULL, theme.get() == 0)) theme = 0;
				if (ImGui::MenuItem("Light palette", NULL, theme.get() == 1)) theme = 1;
				if (ImGui::MenuItem("Retro blue palette", NULL, theme.get() == 2)) theme = 2;
				if (ImGui::MenuItem("Mariana palette", NULL, theme.get() == 3)) theme = 3;

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
	}

	//--------------------------------------------------------------
	void drawImGuiInternal() {

		if (!bMenus) ofxImGuiSurfing::AddParameter(bExtra);
		if (bExtra)
		{
			//ofxImGuiSurfing::AddGroup(params);

			ofxImGuiSurfing::AddCheckBox(bMenus);
			ofxImGuiSurfing::SameLineIfAvailForWidht();
			ofxImGuiSurfing::AddCheckBox(bShowInfo);
			ofxImGuiSurfing::SameLineIfAvailForWidht();
			if (bShowInfo) {
				ofxImGuiSurfing::AddCheckBox(bPath);
				ofxImGuiSurfing::SameLineIfAvailForWidht();
			}
			ofxImGuiSurfing::AddCheckBox(bAdvanced);

			//make smaller if window is big
			float w = ofxImGuiSurfing::getWidgetsWidth();
			if (w > 500) {
				ImGuiOldColumnFlags fc = ImGuiOldColumnFlags_NoBorder;
				ImGui::BeginColumns("#cols", 2, fc);
				ImGui::SetColumnWidth(1, w / 2);
				ofxImGuiSurfing::AddComboButtonDualLefted(font, namesCustomFonts);
				ImGui::Columns(1);
			}
			else ofxImGuiSurfing::AddComboButtonDualLefted(font, namesCustomFonts);
		}

		ImGui::Spacing();
	}

	//--------------------------------------------------------------
	void draw() {
		if (!bGui) return;

		// initialize
		if (!bIntitiated)
		{
			bIntitiated = true;

			//TODO: 
			// Language
			lang = TextEditor::LanguageDefinition::C();
			//lang = TextEditor::LanguageDefinition::Json();
			//lang = TextEditor::LanguageDefinition::Lua();

			// Custom tags
			for (auto& k : keywords) {
				lang.mKeywords.insert(k);
			}

			editor.SetLanguageDefinition(lang);
		}

		//----

		static bool bAdvanced_ = !bAdvanced.get();
		if (bAdvanced_ != bAdvanced.get())
		{
			bAdvanced_ = bAdvanced.get();

			editor.SetShowWhitespaces(bAdvanced.get());
			editor.SetShowShortTabGlyphs(bAdvanced.get());
			editor.SetColorizerEnable(bAdvanced.get());
		}

		//--

		auto cpos = editor.GetCursorPosition();

		ImGuiWindowFlags f = ImGuiWindowFlags_None;
		f += ImGuiWindowFlags_HorizontalScrollbar;
		if (bMenus) f += ImGuiWindowFlags_MenuBar;

		//fix 
		//if (!bMenus && !bExtra)bExtra = 1;

		//ImGui::Begin(name.c_str(), nullptr, f);

		auto& p = bGui;
		bool tmp = p.get();
		if (tmp) ImGui::SetWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);
		ImGui::Begin(p.getName().c_str(), (bool*)&tmp, f);
		if (p.get() != tmp) p.set(tmp);

		{
			if (bMenus) drawImGuiMenus();

			drawImGuiInternal();

			if (bShowInfo)
			{
				if (bPath) {
					ImGui::Text(pathEditing.c_str());
				}
				else {
					pathEditingFileName = ofFilePath::getFileName(pathEditing);
					ImGui::Text(pathEditingFileName.c_str());
				}

				ImGui::Text("%4d/%-4d %4d lines | %s | %s",
					cpos.mLine + 1,
					cpos.mColumn + 1,
					editor.GetTotalLines(),
					editor.IsOverwrite() ? "Ovr" : "Ins",
					editor.GetLanguageDefinitionName());
			}

			if (font < customFonts.size()) if (customFonts[font] != nullptr) ImGui::PushFont(customFonts[font]);
			{
				// Draw Text content
				editor.Render(name.c_str());
				ImGui::Spacing();
			}
			if (font < customFonts.size()) if (customFonts[font] != nullptr) ImGui::PopFont();
		}
		ImGui::End();
	}

	//--

	//TODO: add open/save dialog

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
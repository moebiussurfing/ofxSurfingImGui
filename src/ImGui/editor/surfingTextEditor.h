#pragma once

/*

	Taken from a more updated fork!
	https://github.com/santaclose/ImGuiColorTextEdit

	Other ideas:
	https://github.com/mekhontsev/imgui_md
	https://github.com/juliettef/imgui_markdown

*/

#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "TextEditor.h"
//#include "ImGuiDebugPanel.cpp"

#include <functional>
using callback_t = std::function<void()>;

//--

//TODO: break lines for text formatting
//https://stackoverflow.com/questions/6891652/formatting-a-string-into-multiple-lines-of-a-specific-length-in-c-c

//#include <iostream>
//#include <string>
namespace ofxImGuiSurfing
{
	inline string splitInLines(string source, std::size_t width, string whitespace = " \t\r")
	{
		std::size_t  currIndex = width - 1;
		std::size_t  sizeToElim;
		while (currIndex < source.length())
		{
			currIndex = source.find_last_of(whitespace, currIndex + 1);
			if (currIndex == string::npos)
				break;
			currIndex = source.find_last_not_of(whitespace, currIndex);
			if (currIndex == string::npos)
				break;
			sizeToElim = source.find_first_not_of(whitespace, currIndex + 1) - currIndex - 1;
			source.replace(currIndex + 1, sizeToElim, "\n");
			currIndex += (width + 1); //due to the recently inserted "\n"
		}
		return source;
	}

	/*
	int main() {
		string source = "Shankle drumstick corned beef, chuck turkey chicken pork chop venison beef strip steak cow sausage. Tail short loin shoulder ball tip, jowl drumstick rump. Tail tongue ball tip meatloaf, bresaola short loin tri-tip fatback pork loin sirloin shank flank biltong. Venison short loin andouille.";
		string result = splitInLines(source, 60);
		std::cout << result;
		return 0;
	}
	*/
}


//--------------------------------------------------------------
class SurfingTextEditor
{
public:
	SurfingTextEditor() { };
	~SurfingTextEditor() { exit(); };

	ofParameterGroup params{ "SurfingTextEditor" };
	ofParameter<bool> bGui{ "TextEditor", true };
	ofParameter<bool> bExtra{ "Extra", false };
	ofParameter<bool> bShowInfo{ "Info", false };
	ofParameter<bool> bLangStyled{ "LangStyled", false };
	ofParameter<bool> bMenus{ "Menus", false };
	ofParameter<int> fontIndex{ "Font", 0, 0, 3 };
	ofParameter<int> themeIndex{ "Theme", 0, 0, 3 };
	ofParameter<bool> bPath{ "Path" , false };
	ofParameter<bool> bName{ "Name" , false };
	ofParameter<bool> bBreakLines{ "BreakLines" , true };
	ofParameter<int> lineWidth{ "LineWidth", 30, 10, 120 };//in chars
	ofParameter<bool> bNumberLines{ "NumberLines", false };

	void addKeyword(string keyword) {//call on setup
		keywords.push_back(keyword);

		//lang.mKeywords.insert("CPP");
		//lang.mTokenRegexStrings.push_back(std::make_pair<string, TextEditor::PaletteIndex>("CPP", TextEditor::PaletteIndex::Identifier));
	};

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

		fontIndex.setMax(customFonts.size() - 1);

		buildFontNames();

		fontIndex = fontIndex;
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

	string pathEditing = "-1"; // related to data path

	string textRaw = "";

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
	};

	//--------------------------------------------------------------
	void exit() {
		ofRemoveListener(params.parameterChangedE(), this, &SurfingTextEditor::Changed_Params); // exit()

		string p = params.getName() + "_" + name + ".json";
		ofxImGuiSurfing::saveGroup(params, p);
	};

	//--------------------------------------------------------------
	void setup() {
		params.add(bGui);
		params.add(bExtra);
		params.add(bLangStyled);
		params.add(bMenus);
		params.add(bShowInfo);
		params.add(fontIndex);
		params.add(themeIndex);
		params.add(bPath);
		params.add(bName);
		params.add(lineWidth);
		params.add(bBreakLines);
		params.add(bNumberLines);

		ofAddListener(params.parameterChangedE(), this, &SurfingTextEditor::Changed_Params); // setup()

		string p = params.getName() + "_" + name + ".json";
		ofxImGuiSurfing::loadGroup(params, p);
	};

	//--

	//--------------------------------------------------------------
	string getTextRaw() const {
		return textRaw;
	}

	//--------------------------------------------------------------
	string getText() const { // get editor text 
		return editor.GetText();
	};

	//--------------------------------------------------------------
	void setTextBreakLines(string s, int widthInChars) {
		//textRaw = s;

		string ss = ofxImGuiSurfing::splitInLines(s, widthInChars);
		editor.SetText(ss);
	};

	//--------------------------------------------------------------
	void addText(string s) {
		textRaw += s;

		if (bBreakLines) setTextBreakLines(textRaw, lineWidth);//split lines
		else editor.SetText(textRaw);
	};

	//--------------------------------------------------------------
	void setText(string s) {
		textRaw = s;

		if (bBreakLines) setTextBreakLines(s, lineWidth);//split lines
		else editor.SetText(s);

		//pathEditing = "-1";
	};

	/*
	//--------------------------------------------------------------
	void setText(string s, bool bResetPathSave = true) {
		textRaw = s;

		if (bBreakLines) setTextBreakLines(s, lineWidth);//split lines
		else editor.SetText(s);

		if (bResetPathSave) pathEditing = "-1";
	};
	*/

	//--------------------------------------------------------------
	void clearText() {
		textRaw = "";
		setText(textRaw);
	};

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
			string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

			textRaw = str;
			this->setText(str);

			ofLogNotice("ofxSurfingImGui::surfingTextEditor") << "loaded file: " << ofToString(fileToEdit);
		}
		else {
			ofLogNotice("ofxSurfingImGui::surfingTextEditor") << "file not found! " << ofToString(fileToEdit);
		}
	};

	void Changed_Params(ofAbstractParameter& e)
	{
		string name = e.getName();
		ofLogNotice() << __FUNCTION__ << name << " : " << e;

		if (name == themeIndex.getName())
		{
			switch (themeIndex)
			{
			case 0: editor.SetPalette(TextEditor::GetDarkPalette()); break;
			case 1: editor.SetPalette(TextEditor::GetLightPalette()); break;
			case 2: editor.SetPalette(TextEditor::GetRetroBluePalette()); break;
			case 3: editor.SetPalette(TextEditor::GetMarianaPalette()); break;
			}
			return;
		}

		if (name == fontIndex.getName())
		{
			for (size_t j = 0; j < bs.size(); j++) {
				bs[j] = (fontIndex.get() == j);
			}

			return;
		}

		if (name == lineWidth.getName())
		{
			static int i = -1;
			if (lineWidth != i) {
				i = lineWidth;

				textRaw = this->getTextRaw();//get the edited on runtime 
				this->setText(textRaw);
			}

			return;
		}

		if (name == bBreakLines.getName())
		{
			static bool b = !bBreakLines;
			if (bBreakLines != b) {
				b = bBreakLines;

				this->setText(textRaw);
			}

			return;
		}

		if (name == bNumberLines.getName())
		{
			editor.bShowLineNumbers = bNumberLines;

			return;
		}
	};

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
					setText("");
				}

				if (ImGui::MenuItem("Load"))
				{
					////TODO: open dialog
					//string path = ofToDataPath("text2.txt", true);
					//textEditor.loadText(path);
				}

				//if (pathEditing != "-1")
				{
					if (ImGui::MenuItem("Save"))
					{
						////TODO: open dialog

						auto textToSave = editor.GetText();
						stringstream ssTextToSave;
						ssTextToSave << textToSave;

						// save text....
						TextToFile(ofFilePath::getAbsolutePath(pathEditing), ssTextToSave, false);
					}
				}

				//if (ImGui::MenuItem("Clear"))
				//{
				//	setText("");
				//}

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
				ofxImGuiSurfing::MenuItemToggle(bLangStyled);
				ofxImGuiSurfing::MenuItemToggle(bShowInfo);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Font"))
			{
				for (size_t i = 0; i < customFonts.size(); i++) {
					if (ofxImGuiSurfing::MenuItemToggle(bs[i]))
					{
						if (bs[i]) fontIndex = i;

						bool bAllFalse = true;
						for (size_t j = 0; j < bs.size(); j++) {
							if (bs[j]) bAllFalse = false;
						}
						if (bAllFalse) { fontIndex = fontIndex; }//force true if has been disabled
					};
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Theme"))
			{
				if (ImGui::MenuItem("Dark palette", NULL, themeIndex.get() == 0)) themeIndex = 0;
				if (ImGui::MenuItem("Light palette", NULL, themeIndex.get() == 1)) themeIndex = 1;
				if (ImGui::MenuItem("Retro blue palette", NULL, themeIndex.get() == 2)) themeIndex = 2;
				if (ImGui::MenuItem("Mariana palette", NULL, themeIndex.get() == 3)) themeIndex = 3;

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
	};

	//--

	//TODO; advanced feature to help integrate the text editor / prompt
	// in other modules. 
	// ie: insert a QUERY button to pass the text to some API / method.

private:
	callback_t functionDraw = nullptr;
	//std::function<void()> functionDraw = nullptr;

public:
	//--------------------------------------------------------------
	void setDrawWidgetsFunction(callback_t f = nullptr) {
		functionDraw = f;
	};

	//--

	//--------------------------------------------------------------
	void drawImGuiInternal() {

		if (!bMenus) ofxImGuiSurfing::AddParameter(bExtra);

		if (bExtra)
		{
			//ofxImGuiSurfing::AddGroup(params);

			if (!bMenus) ofxImGuiSurfing::SameLineIfAvailForWidth();

			ofxImGuiSurfing::AddCheckBox(bMenus);
			ofxImGuiSurfing::SameLineIfAvailForWidth();
			ofxImGuiSurfing::AddCheckBox(bShowInfo);
			ofxImGuiSurfing::SameLineIfAvailForWidth();
			if (bShowInfo) {
				ofxImGuiSurfing::AddCheckBox(bName);
				ofxImGuiSurfing::SameLineIfAvailForWidth();
				ofxImGuiSurfing::AddCheckBox(bPath);
				ofxImGuiSurfing::SameLineIfAvailForWidth();
				ofxImGuiSurfing::AddCheckBox(bNumberLines);
				ofxImGuiSurfing::SameLineIfAvailForWidth();
			}
			ofxImGuiSurfing::AddCheckBox(bLangStyled);

			//ofxImGuiSurfing::SameLineIfAvailForWidth();
			//ofxImGuiSurfing::AddSeparatorVertical();
			//ofxImGuiSurfing::SameLineIfAvailForWidth();
			ofxImGuiSurfing::AddCheckBox(bBreakLines);
			if (bBreakLines) {
				ofxImGuiSurfing::SameLine();
				ImGui::PushItemWidth(90);
				ofxImGuiSurfing::AddStepper(lineWidth, true);
				ImGui::PopItemWidth();
				ofxImGuiSurfing::SameLine();
				ImGui::PushItemWidth(70);
				ofxImGuiSurfing::AddParameter(lineWidth);
				ImGui::PopItemWidth();
			}

			drawImGuiWidgetsFonts();
		}

		ImGui::Spacing();
	};

	//--------------------------------------------------------------
	void drawImGuiWidgetsFonts() {

		//font size
		if (customFonts.size() != 0)
		{
			//make smaller if window is big
			float w = ofxImGuiSurfing::getWidgetsWidth();
			if (w > 500) {
				ImGuiOldColumnFlags fc = ImGuiOldColumnFlags_NoBorder;
				ImGui::BeginColumns("#cols", 2, fc);
				ImGui::SetColumnWidth(1, w / 2);
				ofxImGuiSurfing::AddComboButtonDualLefted(fontIndex, namesCustomFonts);
				ImGui::Columns(1);
			}
			else ofxImGuiSurfing::AddComboButtonDualLefted(fontIndex, namesCustomFonts);
		}
	};

	//--------------------------------------------------------------
	void draw() {
		if (!bGui) return;

		// initialize
		if (!bIntitiated)
		{
			bIntitiated = true;

			//TODO: customizable
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

		static bool bLangStyled_ = !bLangStyled.get();
		if (bLangStyled_ != bLangStyled.get())
		{
			bLangStyled_ = bLangStyled.get();

			editor.SetShowWhitespaces(bLangStyled.get());
			editor.SetShowShortTabGlyphs(bLangStyled.get());
			editor.SetColorizerEnable(bLangStyled.get());
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
				if (bPath)
				{
					ImGui::Text(pathEditing.c_str());
				}
				if (bName)
				{
					pathEditingFileName = ofFilePath::getFileName(pathEditing);

					if (0) {
						auto sz = ImGui::CalcTextSize(pathEditingFileName.c_str());
						ofxImGuiSurfing::AddSpacingRightAlign(sz.x);
					}

					ImGui::Text(pathEditingFileName.c_str());
				}

				ImGui::Text("%4d/%-4d %4d lines | %s | %s",
					cpos.mLine + 1,
					cpos.mColumn + 1,
					editor.GetTotalLines(),
					editor.IsOverwrite() ? "Ovr" : "Ins",
					editor.GetLanguageDefinitionName());
			}

			//--

			// Insert external widgets if already settled!
			if (functionDraw != nullptr) functionDraw();

			//--

			// Main Text
			//ImGui::Spacing();
			if (fontIndex < customFonts.size() && customFonts[fontIndex] != nullptr) ImGui::PushFont(customFonts[fontIndex]);
			{
				// Draw Text content
				//editor.Render(name.c_str());

				bool aParentIsFocused = false;
				const ImVec2& aSize = ImVec2();
				bool aBorder = 0;

				editor.Render(name.c_str(), aParentIsFocused, aSize, aBorder);
			}
			if (fontIndex < customFonts.size() && customFonts[fontIndex] != nullptr) ImGui::PopFont();
			ImGui::Spacing();
		}

		ImGui::End();

		//--

		//editor.ImGuiDebugPanel("DebugPanel");
	};

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
	};
};


//--

//TODO:
//load content:
//problems on char / string types... 

//string _name = "text.txt";
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
//		string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
//		editor.SetText(str);
//		ofLogNotice("ofxSurfingImGui::surfingTextEditor") << "loaded file: " << ofToString(fileToEdit);
//	}
//	else {
//		ofLogNotice("ofxSurfingImGui::surfingTextEditor") << "file not found! " << ofToString(fileToEdit);
//	}
//}	
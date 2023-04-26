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
	//ofParameter<bool> bExtra{ "Extra", false };
	ofParameter<bool> bShowInfo{ "Info", false };
	ofParameter<bool> bLangStyled{ "LangStyled", false };
	ofParameter<bool> bMenus{ "Menus", false };
	ofParameter<int> fontIndex{ "Font", 0, 0, 3 };
	ofParameter<int> themeIndex{ "Theme", 0, 0, 3 };
	ofParameter<bool> bPath{ "Path" , false };
	ofParameter<bool> bName{ "Name" , false };
	ofParameter<bool> bBreakLines{ "BreakLines" , true };
	ofParameter<int> amountCharsLineWidth{ "nChars", 30, 10, 100 };//in chars
	ofParameter<bool> bNumberLines{ "NumberLines", false };
	ofParameter<bool> bMinimize{ "Minimize", false };
	ofParameter<bool> bFitWidth{ "FitW" ,false };
	ofParameter<bool> bFitHeight{ "FitH" ,false };
	ofParameter<bool> bAutoFit{ "AutoFit" ,false };

	void addKeyword(string keyword) {//call on setup
		keywords.push_back(keyword);

		//lang.mKeywords.insert("CPP");
		//lang.mTokenRegexStrings.push_back(std::make_pair<string, TextEditor::PaletteIndex>("CPP", TextEditor::PaletteIndex::Identifier));
	};

private:

	float charWidth = 0;
	float charHeight = 0;

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
	void keyPressed(int key) {

		//TODO: add args to allow modifier key (ctrl key)
		//add bKey toggle
		//add isOverEditor to bypass

		if (key == '`') bMinimize = !bMinimize;
		if (key == 'f') bFitWidth = bFitHeight = true;
		if (key == 'w') bFitWidth = true;
		if (key == 'h') bFitHeight = true;
	};

	//--------------------------------------------------------------
	void exit() {
		ofRemoveListener(params.parameterChangedE(), this, &SurfingTextEditor::Changed_Params); // exit()

		string p = params.getName() + "_" + name + ".json";
		ofxImGuiSurfing::saveGroup(params, p);
	};

	//--------------------------------------------------------------
	void setup()
	{
		bFitWidth.setSerializable(false);
		bFitHeight.setSerializable(false);

		params.add(bGui);
		//params.add(bExtra);
		params.add(bLangStyled);
		params.add(bMenus);
		params.add(bShowInfo);
		params.add(fontIndex);
		params.add(themeIndex);
		params.add(bPath);
		params.add(bName);
		params.add(amountCharsLineWidth);
		params.add(bBreakLines);
		params.add(bNumberLines);
		params.add(bMinimize);
		params.add(bFitWidth);
		params.add(bFitHeight);
		//params.add(bAutoFit);

		ofAddListener(params.parameterChangedE(), this, &SurfingTextEditor::Changed_Params); // setup()

		string p = params.getName() + "_" + name + ".json";
		ofxImGuiSurfing::loadGroup(params, p);
	};

	//--

	ImVec2 szWindow = ImVec2(0, 0);
	bool bIsWindowResizing = false;

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

		if (bBreakLines) setTextBreakLines(textRaw, amountCharsLineWidth);//split lines
		else editor.SetText(textRaw);
	};

	//--------------------------------------------------------------
	void setText(string s) {
		textRaw = s;

		if (bBreakLines) setTextBreakLines(s, amountCharsLineWidth);//split lines
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
		ofLogNotice() << __FUNCTION__ << " : " << name << " : " << e;

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

			//if (bAutoFit) 
			{
				if (!bFitWidth) bFitWidth = true;
			}

			return;
		}

		if (name == amountCharsLineWidth.getName())
		{
			static int i = -1;
			if (amountCharsLineWidth != i) {
				i = amountCharsLineWidth;

				textRaw = this->getTextRaw();//get the edited on runtime 
				this->setText(textRaw);
			}

			//if (bAutoFit) 
			{
				if (!bFitWidth) bFitWidth = true;
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
				ofxImGuiSurfing::AddTooltip("Not implemented");

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

					//TODO: make dialog to confirm ok or cancel.
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
				//ofxImGuiSurfing::MenuItemToggle(bExtra);
				ofxImGuiSurfing::MenuItemToggle(bLangStyled);
				ofxImGuiSurfing::MenuItemToggle(bShowInfo);
				ofxImGuiSurfing::MenuItemToggle(bFitWidth);
				ofxImGuiSurfing::MenuItemToggle(bFitHeight);
				//ofxImGuiSurfing::MenuItemToggle(bAutoFit);
				ofxImGuiSurfing::MenuItemToggle(bMenus);

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
	void drawImGuiInternalControls() {

		ofxImGuiSurfing::AddToggleRoundedMiniXsRightAligned(bMinimize);
		ofxImGuiSurfing::AddSpacing();
		float h = ofxImGuiSurfing::getWidgetsHeightUnit();

		if (bMinimize) return;

		//if (!bMenus || (bExtra && bMenus) || (!bExtra && bMenus)) ofxImGuiSurfing::AddSpacingY(-h);
		ofxImGuiSurfing::AddSpacingY(-h);

		//--

		//ofxImGuiSurfing::AddParameter(bExtra);
		//if (bExtra)
		{
			//ofxImGuiSurfing::AddGroup(params);

			ofxImGuiSurfing::AddCheckBox(bMenus);
			//ofxImGuiSurfing::SameLineIfAvailForWidth();

			ofxImGuiSurfing::AddCheckBox(bShowInfo);

			if (bShowInfo) {
				ofxImGuiSurfing::SameLine();
				ofxImGuiSurfing::AddCheckBox(bName);
				ofxImGuiSurfing::SameLineIfAvailForWidth();
				ofxImGuiSurfing::AddCheckBox(bPath);
				ofxImGuiSurfing::SameLineIfAvailForWidth();
				ofxImGuiSurfing::AddCheckBox(bNumberLines);
				ofxImGuiSurfing::SameLineIfAvailForWidth();
				ofxImGuiSurfing::AddCheckBox(bLangStyled);
			}

			ofxImGuiSurfing::AddCheckBox(bBreakLines);
			if (bBreakLines) {
				ofxImGuiSurfing::SameLine();
				ImGui::PushItemWidth(50);
				ofxImGuiSurfing::AddParameter(amountCharsLineWidth);
				ImGui::PopItemWidth();
				ImGui::PushItemWidth(86);
				ofxImGuiSurfing::AddStepper(amountCharsLineWidth, true);
				ImGui::PopItemWidth();
				ofxImGuiSurfing::SameLine();

				ofxImGuiSurfing::SameLineIfAvailForWidth(600);
				if (ImGui::Button("Fit")) {
					bFitWidth = true;
					bFitHeight = true;
				}
				ofxImGuiSurfing::SameLine();
				if (ImGui::Button("FitW")) {
					bFitWidth = true;
				}
				ofxImGuiSurfing::SameLine();
				if (ImGui::Button("FitH")) {
					bFitHeight = true;
				}
				//ofxImGuiSurfing::SameLine();
				//ofxImGuiSurfing::AddCheckBox(bAutoFit);
			}

			drawImGuiWidgetsFonts();
		}

		ImGui::Spacing();
	};

	//--------------------------------------------------------------
	void drawImGuiWindowContent()
	{
		auto cpos = editor.GetCursorPosition();

		// Menus
		if (!bMinimize)
		{
			if (bMenus) drawImGuiMenus();
		}

		// Controls
		drawImGuiInternalControls();

		// Info
		if (!bMinimize)
		{
			if (bShowInfo)
			{
				if (bPath)
				{
					ImGui::Text(pathEditing.c_str());
				}

				if (bName)
				{
					pathEditingFileName = ofFilePath::getFileName(pathEditing);

					//right align
					//if (0) {
					//	auto sz = ImGui::CalcTextSize(pathEditingFileName.c_str());
					//	ofxImGuiSurfing::AddSpacingRightAlign(sz.x);
					//}

					ImGui::Text(pathEditingFileName.c_str());
				}

				ImGui::Text("%4d/%-4d %4d lines | %s | %s",
					cpos.mLine + 1,
					cpos.mColumn + 1,
					editor.GetTotalLines(),
					editor.IsOverwrite() ? "Ovr" : "Ins",
					editor.GetLanguageDefinitionName());
			}
		}

		// Editor
		drawImGuiEditor();

		ImGui::Spacing();
	}

	//--------------------------------------------------------------
	void drawImGuiEditor() {

		// Insert external widgets 
		// if it's already settled!
		if (functionDraw != nullptr) functionDraw();

		//--

		// Editor Main Text

		//ImGui::Spacing();
		if (fontIndex < customFonts.size() && customFonts[fontIndex] != nullptr) ImGui::PushFont(customFonts[fontIndex]);
		{
			// Draw Text content
			//editor.Render(name.c_str());

			bool aParentIsFocused = false;
			const ImVec2& aSize = ImVec2();
			bool aBorder = 0;

			editor.Render(name.c_str(), aParentIsFocused, aSize, aBorder);

			//--			

			//TODO:
			//if (bBreakLines) 
			{
				//customFonts[fontIndex]
				ImFont* font = ImGui::GetFont();
				auto bb = font->CalcTextSizeA(font->FontSize, FLT_MAX, 0, "x");
				charWidth = bb.x;
				charHeight = bb.y;
			}
		}
		if (fontIndex < customFonts.size() && customFonts[fontIndex] != nullptr) ImGui::PopFont();
	}

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

	// Legacy. Deprecated
	//--------------------------------------------------------------
	void draw() {
		drawImGui();
	};

	//--------------------------------------------------------------
	void drawImGui() {
		if (!bGui) return;

		//TODO:
		/*
		if (bAutoFit)
			if (bIsWindowResizing && ofGetFrameNum() > 0) {

				ImGuiStyle& style = ImGui::GetStyle();

				szWindow = ImGui::GetWindowSize();

				//available space for chars
				float w = szWindow.x;
				w -= 2 * style.ItemSpacing.x;
				w -= 2 * style.WindowPadding.x;
				w -= style.ScrollbarSize;
				w -= 5;
				if (bNumberLines) w -= 4 * charWidth;

				amountCharsLineWidth = w / charWidth;

				bFitWidth = true;
			}
		*/

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

		//auto cpos = editor.GetCursorPosition();

		ImGuiWindowFlags f = ImGuiWindowFlags_None;
		f += ImGuiWindowFlags_HorizontalScrollbar;
		if (bMenus && !bMinimize) f += ImGuiWindowFlags_MenuBar;

		//fix 
		//if (!bMenus && !bExtra)bExtra = 1;

		//ImGui::Begin(name.c_str(), nullptr, f);

		ofParameter<bool>& p = bGui;
		bool tmp = p.get();

		static float w = 600.f;
		static float h = -1;

		if (tmp && !bFitWidth) {
			h = 400.f;
			ImGui::SetNextWindowSize(ImVec2{ w, h }, ImGuiCond_FirstUseEver);
		}

		if (ofGetFrameNum() > 0)//window must be updated on the first frame!
		{
			if (tmp && (bFitWidth || bFitHeight))
			{
				h = -1;

				if (bFitHeight) {
					bFitHeight = false;

					h = charHeight;
					h += editor.GetTotalLines() * charHeight;

					//add spacing
					ImGuiStyle& style = ImGui::GetStyle();
					h += 2 * style.ItemSpacing.y;
					h += 2 * style.WindowPadding.y;
					h += ofxImGuiSurfing::getWidgetsHeightUnit();//offset

					if (bMenus && !bMinimize) h += 2 * charHeight;
				}

				if (bFitWidth) {
					bFitWidth = false;

					//if (bBreakLines) 
					{
						//calculate chars width
						w = amountCharsLineWidth * charWidth;

						//add spacing
						ImGuiStyle& style = ImGui::GetStyle();
						w += 2 * style.ItemSpacing.x;
						w += 2 * style.WindowPadding.x;
						w += style.ScrollbarSize;
						w += 5;

						if (bNumberLines) w += 4 * charWidth;
					}
				}

				ImGui::SetNextWindowSize(ImVec2{ w, h }, ImGuiCond_Always);
			}
		}

		//--

		ImGui::Begin(p.getName().c_str(), (bool*)&tmp, f);
		{
			if (p.get() != tmp) p.set(tmp);

			drawImGuiWindowContent();

			//--

			h = ImGui::GetWindowHeight();

			//if (bAutoFit) 
			{
				static ImVec2 szWindow_(-1, -1);
				szWindow = ImGui::GetWindowSize();
				if (szWindow.x != szWindow_.x || szWindow.y != szWindow_.y)//changed
				{
					szWindow_ = szWindow;

					//if (!bFitWidth) bFitWidth = true;

					bIsWindowResizing = true;
				}
				else
				{
					bIsWindowResizing = false;
				}
			}
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
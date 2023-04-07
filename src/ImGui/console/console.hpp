#pragma once
#include <string>
#include <array>
#include <sstream>
#include <deque>
#include <iostream>
#include <unordered_map>
#include <functional>

#include "imgui.h"

template <typename T>
class console
{
private:
	bool bScrollToBottom = false;
	bool bPressedEnter = false;

public:
	void setScroll() { bScrollToBottom = true; }

public:
	console(bool redir = false) {
		if (redir) {
			_oldStdout = std::cout.rdbuf();
			std::cout.rdbuf(_stdout.rdbuf());
		}
		std::fill(_textEntryBuffer.begin(), _textEntryBuffer.end(), '\0');
	};

	~console() {
		if (_oldStdout) {
			std::cout.rdbuf(_oldStdout);
			_oldStdout = nullptr;
		}
	};

	void show(T data) {

		// Redirect std::cout
		if (_oldStdout) {
			std::string text("");
			std::getline(_stdout, text);
			while (text != "")
			{
				_terminalBuffer += text + '\n';
				text = "";
				std::getline(_stdout, text);
			}
			_stdout.clear();
		}

		// Get text input
		if (_terminalBuffer.size() > _terminalSizeLimit) {
			_terminalBuffer = _terminalBuffer.substr(_terminalBuffer.size() - _terminalSizeLimit, _terminalSizeLimit);
			int todel = _terminalBuffer.find('\n') + 1;
			_terminalBuffer = _terminalBuffer.substr(todel, _terminalBuffer.size() - todel);
		}

		//--


		ImGui::Begin("Debug Console", nullptr, 0);

		float windowWidth = ImGui::GetWindowWidth();
		float windowHeight = ImGui::GetWindowHeight();
		float w0 = ofxImGuiSurfing::getWidgetsWidth(1);
		float spx = ofxImGuiSurfing::getWidgetsSpacingX();
		float spy = ofxImGuiSurfing::getWidgetsSpacingY();

		int wbutton = 200;
		int hInput = ofxImGuiSurfing::getWidgetsHeightUnit();

		float wchild = windowWidth - 2 * spx - 5;
		float hchild = windowHeight - 2 * spy - hInput - spy - 47;

		ImGui::BeginChild("Console", ImVec2(wchild, hchild), true);

		ImGui::Text(_terminalBuffer.c_str());

		if (bScrollToBottom) {
			ImGui::SetKeyboardFocusHere(-1);
			ImGui::SetScrollHereY(1);
			bScrollToBottom = false;
		}
		if (bPressedEnter) {
			processCommand(data);
			bScrollToBottom = true;
		}

		ImGui::EndChild();

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		//--

		ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
		flags += ImGuiInputTextFlags_EnterReturnsTrue;
		flags += ImGuiInputTextFlags_AllowTabInput;


		//ImGui::InputTextMultiline("##Input", searchTermChar, IM_ARRAYSIZE(searchTermChar), ImVec2(windowWidth - 127.0f, -1), ImGuiInputTextFlags_AllowTabInput);
		//inputText = searchTermChar;

		//bool bPressedEnter = ImGui::InputTextMultiline("##Input", &_textEntryBuffer.front(), _textEntryBuffer.size() - 1, ImVec2(windowWidth - 127.0f, -1), flags);

		ImGui::PushItemWidth(w0);
		bPressedEnter = ImGui::InputText("##Input", &_textEntryBuffer.front(), _textEntryBuffer.size() - 1, flags);
		ImGui::PopItemWidth();


		/*
		ImGui::Text(_terminalBuffer.c_str());

		bool bPressedEnter = ImGui::InputText("Input", &_textEntryBuffer.front(), _textEntryBuffer.size() - 1, ImGuiInputTextFlags_EnterReturnsTrue);
		*/


		//ImGui::SameLine(windowWidth - wbutton);

		//static bool waiting = false;

		//if (waiting)
		//{
		//	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
		//}

		/*
		if (ImGui::Button("Submit", ImVec2(-1, -1)) && !waiting)
		{
			//if (apiKey != "")
			//{
			//	std::thread t(SendRequest);
			//	t.detach();
			//}
			//else
			//{
			//	logEditor.InsertText("[-] Please ensure that you fill out the API field, as it appears to be empty or incomplete\n");
			//}
		}
		*/

		//ImGui::PopStyleVar();

		ImGui::End();
	};

protected:
	std::unordered_map<std::string, std::function<void(std::stringstream args, T data)>> _commandList;

private:
	std::array<char, 240> _textEntryBuffer;
	std::streambuf* _oldStdout = nullptr;
	std::stringstream _stdout;

	std::deque<std::string> _commandHistory;
	std::string _terminalBuffer;

	const unsigned _maxHistoryLines = 200;
	const unsigned _terminalSizeLimit = 1000;


	void processCommand(T data) {
		std::string command(_textEntryBuffer.data());
		std::fill(_textEntryBuffer.begin(), _textEntryBuffer.end(), '\0');

		_commandHistory.emplace_back(command);
		while (_commandHistory.size() > _maxHistoryLines) {
			_commandHistory.pop_front();
		}

		std::cout << command << std::endl;

		auto cmdName = command.substr(0, command.find(' '));
		auto cmd = _commandList.find(cmdName);
		if (cmd != _commandList.end()) {
			cmd->second(std::stringstream(command.substr(command.find(' ') + 1, command.size() - command.find(' ') - 1)), data);
		}


		//TODO:?
		//addLine((string)(command));
	};


	//TODO:?
public:
	void addLine(string s) {
		_terminalBuffer += s;
		_terminalBuffer += "\n";
	};
	void clearLines(T data) {
		_terminalBuffer = "";
	};

	void addLineCommnand(string s, T data) {

		std::string command = s;

		_commandHistory.emplace_back(command);
		while (_commandHistory.size() > _maxHistoryLines) {
			_commandHistory.pop_front();
		}

		std::cout << command << std::endl;

		auto cmdName = command.substr(0, command.find(' '));
		auto cmd = _commandList.find(cmdName);
		if (cmd != _commandList.end()) {
			cmd->second(std::stringstream(command.substr(command.find(' ') + 1, command.size() - command.find(' ') - 1)), data);
		}

		//data->lastCommand= "addLineCommnand";
	};
};


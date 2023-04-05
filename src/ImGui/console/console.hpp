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
class console {
private:
	bool scrollToBottom = false;
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
		if (_terminalBuffer.size() > _terminalSizeLimit) {
			_terminalBuffer = _terminalBuffer.substr(_terminalBuffer.size() - _terminalSizeLimit, _terminalSizeLimit);
			int todel = _terminalBuffer.find('\n') + 1;
			_terminalBuffer = _terminalBuffer.substr(todel, _terminalBuffer.size() - todel);
		}

		ImGui::Begin("Debug terminal", nullptr, 0);

		ImGui::Text(_terminalBuffer.c_str());

		//bool pressedEnter = ImGui::InputText("", &_textEntryBuffer.front(), _textEntryBuffer.size()-1, ImGuiInputTextFlags_EnterReturnsTrue);

		bool pressedEnter = ImGui::InputText("Input", &_textEntryBuffer.front(), _textEntryBuffer.size()-1, ImGuiInputTextFlags_EnterReturnsTrue);

		//ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
		//bool pressedEnter = ImGui::InputText("##input", &_textEntryBuffer.front(), _textEntryBuffer.size() - 1, ImGuiInputTextFlags_EnterReturnsTrue);
		//ImGui::PopItemWidth();

		if (scrollToBottom) {
			ImGui::SetKeyboardFocusHere(-1);

			//ImGui::SetScrollHere();//error
			ImGui::SetScrollHereY();//?

			scrollToBottom = false;
		}
		if (pressedEnter) {
			processCommand(data);
			scrollToBottom = true;
		}

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

	const unsigned _maxHistoryLines = 100;
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

		data->someString = "addLineCommnand";
	};
};


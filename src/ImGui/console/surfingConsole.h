
/*

	This is a basic console module/example.
	Pass your data to a console,
	Call methods from your data by typing commands with arguments.

	TODO

	improve workflow:
		remove some cout stuff.
		more console feel
	split text input box. submit button.
	add params to show/integrate in our ofApp's.
	up arrow to browser previous history
	some helpers to add custom commands.
	separate dataCustom.
	get the typed text.

*/

//--

// Original code from @theKlanc:
// https://github.com/theKlanc/YAIC
// https://gitea.ledgedash.com/klanc/Spaceworks/src/branch/master/source/gameConsole.cpp

/*
Other interesting console/terminal 3rd party libs:
https://github.com/Organic-Code/ImTerm (C++17)
https://github.com/rmxbalanque/imgui-console (C++17)
*/


/*
*
*
* myCustomConsole.hpp
*
*
	//Header only C++ ImGui console,
	//with support for stdout redirection into itself.

	//Then just initialize an object myCustomConsole wherever you want,
	//and call its myCustomConsoleObject.show(data) method inside an ImGui context.

	//EXAMPLE

	#pragma once
	#include <functional>
	#include "console.hpp"

	struct customType{
	  int someVar;
	};

	using namespace std::placeholders;
	#define BIND(name) _commandList.emplace(std::make_pair<std::string, std::function<void(std::stringstream args, customType data)>>(#name, std::bind(&myCustomConsole::name, this, _1, _2)))

	class myCustomConsole : public console<customType>{
		public:
			myCustomConsole(bool redir = false): console(redir){
				BIND(myCommand);
			}
		private:
			void myCommand(std::stringstream args, customType data){
				doWhatev(data->someVar);
			}
	};
*/

//--

#pragma once
#include "ofMain.h"
#include "ofxSurfingImGui.h"

#include <functional>
#include "console.hpp"

//--

// This struct could be into a header filer from your app.
// Use it here as example for the Examples/08_ConsoleSystem.
// frameNum will be updated in ofApp on update.
// color will be settled thought the console commands
// then lastCommand will be named with some test, as what command is called.

struct dataCustom
{
	ofColor color{ 0,0,0,0 };
	int frameNum = 0;
	string lastCommand = "";
};

//--

using namespace std::placeholders;

#define BIND(name) _commandList.emplace(std::make_pair<std::string, std::function<void(std::stringstream args, dataCustom* data)>>(#name, std::bind(&surfingConsole::name, this, _1, _2)))

//--

// Example: extends console
class surfingConsole : public console<dataCustom*>
{
public:
	surfingConsole(bool redir = false) : console(redir)
	{
		std::cout << "> surfingConsole()" << " redirect:" << redir << endl;

		addCommands();
	};

	void addCommands()
	{
		BIND(myCommand);
		BIND(help);
		BIND(colorRandom);
		BIND(setColor);
		BIND(clear);
		BIND(printArgs);

		std::cout << "> addCommands:" << endl;
		help_();
	};

private:
	void myCommand(std::stringstream args, dataCustom* data)
	{
		//doWhatev(data);

		std::cout << "> myCommand" << endl;
		std::cout << endl;

		if (args.tellg() != -1) {
			std::string argument;
			args >> argument;

			// Example some catchers
			//unsigned id = std::strtol(argument.c_str(), nullptr, 10);
			//config::zoom = std::stoi(argument);
			//unsigned childID = std::stoi(argument);
			/*
			if (args.tellg() != -1) {
					args >> argument;
					if(argument == "_")
					{}
					else if(argument[0] == '-'){
						pos.pos.z -= std::strtol(&argument.c_str()[1], nullptr, 10);
					}
					else if(argument[0] == '+'){
						pos.pos.z += std::strtol(&argument.c_str()[1], nullptr, 10);
					}
					else{
						pos.pos.z = std::strtol(&argument.c_str()[1], nullptr, 10);
					}
				}
			*/

			if (argument == "reset") {
				data->lastCommand = "Just reseted by myCommand";
				data->color = ofColor::yellow;
			}
			else if (argument == "default") {
				data->lastCommand = "Just defaulted by myCommand";
				data->color = ofColor::black;
			}
			else {
				data->frameNum = -1;
				data->lastCommand = "Unknown argument for myCommand";

				addLine(data->lastCommand);
			}
		}

		setScroll();
	};

private:
	void help(std::stringstream args, dataCustom* data)
	{
		data->lastCommand = "just called help";

		std::cout << "> help" << endl;
		std::cout << "  data" << endl;
		std::cout << "  data->frameNum:" << data->frameNum << endl;
		std::cout << "  data->lastCommand:" << data->lastCommand << endl;
		std::cout << "  data->color:" << data->color << endl;
		std::cout << endl;

		help_();

		setScroll();
	};

	void clear(std::stringstream args, dataCustom* data)
	{
		clearLines(data);

		data->lastCommand = "just clear";

		setScroll();
	};

	void printArgs(std::stringstream args, dataCustom* data)
	{
		data->lastCommand = "just printArgs";

		std::cout << "  args:" << args << endl;
		std::cout << endl;

		setScroll();
	};

	void colorRandom(std::stringstream args, dataCustom* data)
	{
		data->color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 255);
		data->lastCommand = "randomized color";
		
		std::cout << "  data->color:" << data->color << endl;
		std::cout << endl;

		setScroll();
	};

	void setColor(std::stringstream args, dataCustom* data)
	{
		//TODO: catch/filter args
		string s = args.str();

		ofColor c;
		if (s == "red") c = ofColor(ofColor::red);
		else if (s == "green") c = ofColor(ofColor::green);
		else if (s == "blue") c = ofColor(ofColor::blue);

		data->color = c;
		data->lastCommand = "color settled";

		std::cout << "  data->color:" << data->color << endl;
		std::cout << endl;

		setScroll();
	};

public:
	void help_()
	{
		std::cout << "> help" << endl;
		std::cout << endl;
		std::cout << "  help        :  list commands" << std::endl;
		std::cout << "  myCommand   :  + arg: reset or default" << std::endl;
		std::cout << "  setColor    :  + arg: blue, green or red" << std::endl;
		std::cout << "  colorRandom :  random color" << std::endl;
		std::cout << "  printArgs   :  print passed args" << std::endl;
		std::cout << "  clear       :  clear console" << std::endl;
		std::cout << endl;

		setScroll();
	};

	void clear_()
	{
		clearLines(NULL);

		setScroll();
	};
};

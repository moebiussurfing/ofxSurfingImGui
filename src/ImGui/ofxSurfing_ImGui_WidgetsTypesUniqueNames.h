
#pragma once

#include "ofMain.h"
#include "ofxImGui.h" 

//TODO: enabled (commented) to enforce unique names engine...
//#define DISABLE_ID_PUSH_POP

namespace ofxImGuiSurfing
{
	struct ofParamUniqueName
	{

	private:

		int index = 0;
		int treeLevel = 0;

		//TODO:
		vector <ofParameter<bool>> bOpenGroups;

		//--

	public:

		//--------------------------------------------------------------
		void setOpen(bool b) {
			if (bOpenGroups.size() == 0) return;

			bOpenGroups[treeLevel].set(b);
			//bOpenGroups[treeLevel - 1].set(b);
		}
		//--------------------------------------------------------------
		bool isOpen(int _treeLevel) {
			if (bOpenGroups.size() == 0) return -1;
			if (_treeLevel >= bOpenGroups.size()) return -1;

			return bOpenGroups[_treeLevel].get();
		}

	public:

		//--------------------------------------------------------------
		void pushGroup() {
			ofParameter<bool> bOpenGroup{ "_open_" + ofToString(treeLevel), false };
			bOpenGroups.emplace_back(bOpenGroup);
			treeLevel++;
		}

		//--------------------------------------------------------------
		int getLevel() const {
			return treeLevel;
		}

		//--------------------------------------------------------------
		void reset() {
			index = 0;
			treeLevel = 0;
			bOpenGroups.clear();
		}

	private:

		//--------------------------------------------------------------
		void inc() {
			index++;
		}

	public:

		//--------------------------------------------------------------
		void push() {
			inc();

#ifndef DISABLE_ID_PUSH_POP
			ImGui::PushID(ofToString(index).c_str());
#endif
		}

		//--------------------------------------------------------------
		void pop() {
#ifndef DISABLE_ID_PUSH_POP
			ImGui::PopID();
#endif
		}
	};

	//-

	//TODO:
	// a getUniqueName alternative
	//public:
	//	int index = 0;
	//	void resetIndex() {
	//		index = 0;
	//	}
	//	std::string getTag(ofAbstractParameter& aparam) {
	//		string tag = aparam.getName() + ofToString(index++);
	//		return tag;
	//	}
}

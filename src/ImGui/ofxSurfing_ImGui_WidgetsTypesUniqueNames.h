
#pragma once

#include "ofMain.h"
#include "ofxImGui.h" 

namespace ofxImGuiSurfing
{
	struct ofParamUniqueName
	{
		int index = 0;
	
		void reset() {
			//ofLogNotice() << (__FUNCTION__) << "amount index:" << index;
			index = 0;
		}

		void inc() {
			index++;
		}

		void push() {
			inc();
			ImGui::PushID(ofToString(index).c_str());
		}

		void pop() {
			ImGui::PopID();
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

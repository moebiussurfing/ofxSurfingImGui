
#pragma once

#include "ofMain.h"
#include "ofxImGui.h" 

namespace ofxImGuiSurfing
{
	struct ofParamUniqueName
	{
		int index = 0;
	
		void reset() {
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
}

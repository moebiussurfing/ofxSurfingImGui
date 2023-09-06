#pragma once

#include "ofMain.h"

#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"

#include "LayoutHelpers.h"
#include "ofHelpers.h"

using namespace ofxImGuiSurfing;

//----

namespace ofxImGuiSurfing
{
	// One Window
		//--------------------------------------------------------------
	class WindowPanel {

	public:

		//--------------------------------------------------------------
		WindowPanel() {
		}

		//--------------------------------------------------------------
		~WindowPanel() {
		}

		//--------------------------------------------------------------
		void getShapeState()
		{
			rShape = ofRectangle(
				ImGui::GetWindowPos().x,
				ImGui::GetWindowPos().y,
				ImGui::GetWindowWidth(),
				ImGui::GetWindowHeight());
		}

	public:

		ofParameter<bool> bGui{ "bGui", true };

		ofParameter<ofRectangle> rShape{ "rShape",
			ofRectangle(0,0,0,0), ofRectangle(0,0,0,0), ofRectangle(1920,1080,1920,1080) };

		ofParameter<int> indexPos{ "IndexPos", -1, -1, 0 };

		int id = -1; // -1 is for not visible ?. or its position on the queue / window from left to right

	public:

		//--------------------------------------------------------------
		ofRectangle getShape() const
		{
			return rShape.get();
		}

		//--------------------------------------------------------------
		ofRectangle getRectangle() const
		{
			return rShape.get();
		}

		//--------------------------------------------------------------
		glm::vec2 getPosition() const
		{
			return glm::vec2(rShape->x, rShape->y);
		}

		//--------------------------------------------------------------
		float getWidth() const
		{
			return rShape->getWidth();
		}

		//--------------------------------------------------------------
		float getHeight() const
		{
			return rShape->getHeight();
		}

		//--------------------------------------------------------------
		void setPosition(glm::vec2 pos)
		{
			rShape->x = pos.x;
			rShape->y = pos.y;
		}

		//--------------------------------------------------------------
		void setRectangle(ofRectangle r)
		{
			rShape = r;
		}
	};
}
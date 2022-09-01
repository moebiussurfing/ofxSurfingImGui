#pragma once

#include "ofMain.h"


//TODO:
// derivate form a SurfingGui or pass as a pointer

// - Class to handle a video preview window with some extra features
// - Floating Fbo ImGui Window
// - Draw on windows space

// Some stuff taken from ofxMyUtil from https://github.com/Iwanaka

//----

#include "ofxImGui.h"
//#include "ofHelpers.h"
//#include "ofxSurfingImGui.h"//can't be enabled bc it's recursive, as WindowFbo.h is included too inside it!

#include "ofxSurfingHelpers.h"

#include "ofxInteractiveRect.h"
//#include "ofxSurfingBox.h"

namespace ofxImGuiSurfing
{
	/*

	//TODO:
	//https://github.com/d3cod3/ofxMosaicPlugin/blob/master/src/core/imgui_profiler.h

	//TODO:
	// Taken from here:
	https://github.com/d3cod3/ofxMosaicPlugin/blob/master/src/core/imgui_helpers.h

	//--------------------------------------------------------------
	inline void drawOFTexture(ofTexture* tex, float& _tw, float& _th, float& posX, float& posY, float& drawW, float& drawH ){
	  if(tex->isAllocated()){
		if(tex->getWidth()/tex->getHeight() >= _tw/_th){
		  if(tex->getWidth() > tex->getHeight()){   // horizontal texture
			drawW           = _tw;
			drawH           = (_tw/tex->getWidth())*tex->getHeight();
			posX            = 0;
			posY            = (_th-drawH)/2.0f;
		  }else{ // vertical texture
			drawW           = (tex->getWidth()*_th)/tex->getHeight();
			drawH           = _th;
			posX            = (_tw-drawW)/2.0f;
			posY            = 0;
		  }
		}else{ // always considered vertical texture
		  drawW           = (tex->getWidth()*_th)/tex->getHeight();
		  drawH           = _th;
		  posX            = (_tw-drawW)/2.0f;
		  posY            = 0;
		}

		ImVec2 cursor_pos = ImGui::GetCursorPos();
		ImGui::SetCursorPos(ImVec2(posX,posY+IMGUI_EX_NODE_HEADER_HEIGHT));

		ofxImGui::AddImage(*tex, ofVec2f(drawW, drawH));

		ImGui::SetCursorPos(cursor_pos);

	  }
	}

	//--------------------------------------------------------------
	inline void drawOFTextureFromImGui(ofTexture* tex, float& _tw, float& _th, float& posX, float& posY, float& drawW, float& drawH , void (*drawTexture)(ofTexture*,float&,float&,float&,float&,float&,float&)){
		drawTexture(tex,_tw,_th,posX,posY,drawW,drawH);
	}

	*/


	/*
	void DrawFbo(const ofFbo &fbo, GLuint &sourceID,
		std::string name = "fbo", ImGuiWindowFlags flag = 0);

	void DrawImage(const ofImage &img, GLuint &sourceID, float scale = 1.0f,
		std::string name = "image", ImGuiWindowFlags flag = 0);

	void DrawImageButton(const ofImage &img, GLuint &sourceID, void(*fn)(), float scale = 1.0f,
		std::string name = "image button", ImGuiWindowFlags flag = 0);

	void DrawImageButton(const ofImage &img, GLuint &sourceID, std::function<void()> fn, float scale = 1.0f,
		std::string name = "image button",
		ImGuiWindowFlags flag = 0);
	*/


	//--------------------------------------------------------------
	inline void BasicInfosWindow()
	{
		string str1 = "Size " + ofToString(ImGui::GetWindowSize().x, 0) + "," + ofToString(ImGui::GetWindowSize().y, 0);
		string str2 = "Pos  " + ofToString(ImGui::GetWindowPos().x, 0) + "," + ofToString(ImGui::GetWindowPos().y, 0);
		ImGui::Text(str2.c_str());
		ImGui::Text(str1.c_str());
	}

	//--------------------------------------------------------------
	inline GLuint loadTextureImage2D(unsigned char* pix, int width, int height)
	{
		GLint last_texture;
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
		GLuint new_texture;

		glGenTextures(1, &new_texture);

		glBindTexture(GL_TEXTURE_2D, new_texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(
			GL_TEXTURE_2D, 0,
			GL_RGBA, width, height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, pix
		);

		glBindTexture(GL_TEXTURE_2D, last_texture);
		return new_texture;
	}

	//--------------------------------------------------------------
	inline void DrawFboPreview(const ofFbo& fbo)
	{
		if (!fbo.isAllocated()) return;

		ImTextureID textureID = (ImTextureID)(uintptr_t)fbo.getTexture().getTextureData().textureID;

		ImVec2 szWin = ImGui::GetContentRegionAvail(); // for example
		ImVec2 szOut;

		float w = fbo.getWidth();
		float h = fbo.getHeight();
		float ratio = h / w;
		float pad = 0;
		float ww;
		float hh;
		ww = szWin.x - pad;
		hh = ww * ratio;

		szOut = ImVec2(ww, hh);
		ImGui::Image(textureID, szOut);
	}


	/*
	//--------------------------------------------------------------
	inline void DrawFbo(const ofFbo &fbo, GLuint &sourceID, string name, ImGuiWindowFlags flag = ImGuiWindowFlags_None, bool bResizeable = false)
	{
		if (!fbo.isAllocated()) return;

		//TODO:
		//static bool bDebug = true;

		////TODO: try to scale..
		//ImVec2 sz = ImVec2(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);

		//ofPixels pix;
		//pix.clear();

		//fbo.readToPixels(pix);
		//pix.setImageType(OF_IMAGE_COLOR_ALPHA);

		//// clear source
		//glDeleteTextures(1, &sourceID);

		//-

		ImTextureID textureID = (ImTextureID)(uintptr_t)fbo.getTexture().getTextureData().textureID;
		auto size = ImGui::GetContentRegionAvail(); // for example
		ImGui::Image(textureID, size);


		//// set source
		//if (bResizeable) {
		//	sourceID = loadTextureImage2D(pix.getData(), sz.x, sz.y);
		//	//sourceID = fbo.getTexture(0).getTextureData().textureID;

		//	float w = sz.x;
		//	float h = sz.y;

		//	//float w = fbo.getWidth();
		//	//float h = fbo.getHeight();

		//	float ratio = h / w;
		//	float ww;
		//	float hh;
		//	ww = (sz.x - 20);
		//	//ww = (sz.x - 20) * ofxSurfingHelpers::Bounce(10);
		//	hh = ww * ratio;

		//	//ImGui::Begin(name.c_str(), 0, flag);
		//	//ImGui::Begin(name.c_str(), 0, ImVec2(fbo.getWidth() * 1.1, fbo.getHeight()* 1.1f), .5f, flag);
		//	ImGui::Begin(name.c_str(), 0, flag);
		//	{
		//		ImGui::Image((ImTextureID)(uintptr_t)sourceID, sz);
		//		//ImGui::Image((ImTextureID)(uintptr_t)sourceID, ImVec2(ww, ww * ratio));
		//		//ImGui::Image((ImTextureID)(uintptr_t)fbo.getTexture(0).getTextureData().textureID, ImVec2(ww, ww * ratio));

		//		if (bDebug) BasicInfosWindow();
		//	}
		//	ImGui::End();
		//}
		//else {
		//	sourceID = loadTextureImage2D(pix.getData(), fbo.getWidth(), fbo.getHeight());

		//	//ImGui::Begin(name.c_str(), 0, ImVec2(fbo.getWidth() * 1.1, fbo.getHeight()* 1.1f), .5f, flag);
		//	ImGui::Begin(name.c_str(), 0, flag);
		//	{
		//		ImGui::Image((ImTextureID)(uintptr_t)sourceID, ImVec2(fbo.getWidth(), fbo.getHeight()));

		//		if (bDebug) BasicInfosWindow();
		//	}
		//	ImGui::End();
		//}


		//-


		////TODO:
		//sourceID = loadTextureImage2D(pix.getData(), sz.x, sz.y);
		////https://gamedev.stackexchange.com/questions/140693/how-can-i-render-an-opengl-scene-into-an-imgui-window
		////ImGui::Begin("GameWindow");
		//ImGui::Begin(name.c_str());
		//{
		//	// Using a Child allow to fill all the space of the window.
		//	// It also alows customization
		//	ImGui::BeginChild("GameRender");
		//	// Get the size of the child (i.e. the whole draw size of the windows).
		//	ImVec2 wsize = ImGui::GetWindowSize();
		//	// Because I use the texture from OpenGL, I need to invert the V from the UV.
		//	ImGui::Image((ImTextureID)(uintptr_t)sourceID, wsize);
		//	//ImGui::Image((ImTextureID)tex, wsize, ImVec2(0, 1), ImVec2(1, 0));
		//	//ImGui::Image((ImTextureID)tex, wsize, ImVec2(0, 1), ImVec2(1, 0));
		//	ImGui::EndChild();
		//}
	}
	*/


	/*
	//--------------------------------------------------------------
	void Im::DrawImage(const ofImage &img, GLuint &sourceID, float scale, string name, ImGuiWindowFlags flag)
	{
		if (!img.isAllocated()) return;

		ofPixels pix = img.getPixels();
		pix.setImageType(OF_IMAGE_COLOR_ALPHA);

		glDeleteTextures(1, &sourceID);
		sourceID = ofxMyUtil::GL::loadTextureImage2D(pix.getData(), img.getWidth(), img.getHeight());

		ImGui::Begin(name.c_str(), 0, flag);
		//ImGui::Begin(name.c_str(), 0, ImVec2(img.getWidth() * scale * 1.1f, img.getHeight() * scale * 1.3f), .0f, flag);
		{
			ImGui::Image((ImTextureID)(uintptr_t)sourceID, ImVec2(img.getWidth()* scale, img.getHeight()* scale));
		}
		ImGui::End();
	}

	//--------------------------------------------------------------
	void Im::DrawImageButton(const ofImage &img, GLuint &sourceID, void(*fn)(), float scale, string name, ImGuiWindowFlags flag)
	{
		if (!img.isAllocated()) return;

		ofPixels pix = img.getPixels();
		pix.setImageType(OF_IMAGE_COLOR_ALPHA);

		glDeleteTextures(1, &sourceID);
		sourceID = ofxMyUtil::GL::loadTextureImage2D(pix.getData(), img.getWidth(), img.getHeight());

		ImGui::Begin(name.c_str(), 0, flag);
		//ImGui::Begin(name.c_str(), 0, ImVec2(img.getWidth() *scale * 1.1f, img.getHeight() * scale * 1.3f), .0f, flag);
		{
			if (ImGui::ImageButton((ImTextureID)(uintptr_t)sourceID, ImVec2(img.getWidth()* scale, img.getHeight()* scale)))
			{
				fn();
			}
		}
		ImGui::End();
	}

	//--------------------------------------------------------------
	void Im::DrawImageButton(const ofImage &img, GLuint &sourceID, function<void()> fn, float scale, string name, ImGuiWindowFlags flag)
	{
		glDeleteTextures(1, &sourceID);
		ofPixels pix = img.getPixels();
		pix.setImageType(OF_IMAGE_COLOR_ALPHA);
		sourceID = ofxMyUtil::GL::loadTextureImage2D(pix.getData(), img.getWidth(), img.getHeight());

		ImGui::Begin(name.c_str(), 0, flag);
		//ImGui::Begin(name.c_str(), 0, ImVec2(img.getWidth() *scale * 1.1f, img.getHeight() * scale * 1.3f), .0f, flag);
		{
			if (ImGui::ImageButton((ImTextureID)(uintptr_t)sourceID, ImVec2(img.getWidth()* scale, img.getHeight()* scale))) {
				fn();
			}
		}
		ImGui::End();

	}*/
}

//----

class SurfingPreview
{
public:

	SurfingPreview()
	{
		setup();
	};

	~SurfingPreview()
	{
		//ofxSurfingHelpers::saveGroup(params);

		ofRemoveListener(params.parameterChangedE(), this, &SurfingPreview::Changed_Params); // exit()
	};

public:

	ofParameter<bool> bGui_MiniPreview{ "MINI PREVIEW", true };
	ofParameter<bool> bGui_Extra{ "PREVIEW EXTRA", false };//extra window for settings
	ofParameter<bool> bGui_PreviewBig{ "BIG", true };//big preview can be full screen, docked or draggable.

	ofParameter<bool> bFullScreen{ "Full Screen", true };//big preview will be drawn on the full screen
	ofParameter<bool> bInDocked{ "Docked", false };//will occupy the space between docking panels

	ofParameter<ofColor> colorBg{ "Bg", ofColor(0), ofColor(0), ofColor(255) };

	ofxInteractiveRect rectDraggable = { "rectDraggable" };

	ofFbo fboPreview;

private:

	// Fbo

	ofFboSettings fboSettings;
	ofParameter<bool> bGui_Preview;
	GLuint sourceID;

	string path;

public:

	ofParameterGroup& getParameters() {
		return params;
	}

	//private:

	ofParameterGroup params;

	ofParameter<bool> bAutoResize{ "Auto Resize", true };
	ofParameter<bool> bAutoResize_Preview{ "Auto Resize", true };
	ofParameter<bool> bDebug{ "Debug", false };

	std::vector<std::string> scaleModenames =
	{ "Fill", "Fit", "Center", "Stretch To Fill" };
	ofParameter<int> scaleModeIndex{ "Scale Mode", 0, 0, 3 };

public:

	ofScaleMode scaleMode;//what is applied to the viewport

public:

	void setup()
	{
		// Params
		params.setName("SurfingPreview");
		params.add(bGui_MiniPreview);
		params.add(bGui_PreviewBig);
		params.add(bGui_Extra);
		params.add(bAutoResize_Preview);
		params.add(bFullScreen);
		params.add(scaleModeIndex);
		params.add(bInDocked);
		params.add(colorBg);
		params.add(rectDraggable.getParameterRectangle());
		params.add(rectDraggable.bEditMode);

		ofAddListener(params.parameterChangedE(), this, &SurfingPreview::Changed_Params); // setup()

		//-

		// Fbo settings

		fboSettings.width = 1920;
		fboSettings.height = 1080;

		fboSettings.internalformat = GL_RGBA;
		fboSettings.textureTarget = GL_TEXTURE_2D;

		//fboSettings.internalformat = GL_RGBA32F_ARB;

		//fboSettings.useDepth = true;
		//fboSettings.useStencil = true;
		//fboSettings.depthStencilAsTexture = true;

		//ofEnableArbTex();
		//ofDisableeArbTex();

		fboPreview.allocate(fboSettings);
		fboPreview.begin();
		{
			ofClear(0, 255);
		}
		fboPreview.end();

		//-

		// Draggable viewport rectangle

		rectDraggable.bEditMode.setName("Edit Viewport");
		rectDraggable.setTransparent();
		rectDraggable.setAutoSave(true);

		//-

		// Startup

		//ofxSurfingHelpers::loadGroup(params);
	};

	void updateRectDraggable(ofRectangle r)
	{
		rectDraggable.setX(r.getX());
		rectDraggable.setY(r.getY());
		rectDraggable.setWidth(r.getWidth());
		rectDraggable.setHeight(r.getHeight());
	};

	void draw_Rectangle()//TODO:remove
	{
		rectDraggable.draw();
	};

	void begin()
	{
		fboPreview.begin();
		ofClear(0, 255);
	};

	void end()
	{
		fboPreview.end();
	};

	void Changed_Params(ofAbstractParameter& e)
	{
		string name = e.getName();
		ofLogNotice() << __FUNCTION__ << name << " : " << e;

		if (0) {}

		else if (name == scaleModeIndex.getName())
		{
			scaleMode = ofScaleMode(scaleModeIndex.get());
		}
	};

	/*
	void draw_ImGui_Preview(bool _bMinimize = false, string label = "") // minimized hides extra window
	{
		//--

		// 1. Preview Floating window

		if (bGui_MiniPreview)
		{
			ImGuiCond flagsCond = ImGuiCond_None;
			flagsCond |= ImGuiCond_Appearing;

			ImGuiWindowFlags flagsw = ImGuiWindowFlags_None;
			if (bAutoResize_Preview) flagsw |= ImGuiWindowFlags_AlwaysAutoResize;

			string n = bGui_MiniPreview.getName();

			//if (label != "") n += (" | " + label);
			// Notice that if we change the window name on runtime. ini settings store one layout position for each used name...

			ImGui::Begin(n.c_str(), (bool*)&bGui_MiniPreview.get(), flagsw);
			{
				ofxImGuiSurfing::DrawFboPreview(fboPreview);

				if (label != "") ImGui::Text(label.c_str());
			}
			ImGui::End();
		}

		//--

		// 2. Preview Extra stuff window

		if (!_bMinimize)
			if (bGui_Extra)
			{
				ImGuiCond flagsCond = ImGuiCond_None;
				flagsCond |= ImGuiCond_Appearing;

				ImGuiWindowFlags flagsw = ImGuiWindowFlags_None;
				if (bAutoResize) flagsw |= ImGuiWindowFlags_AlwaysAutoResize;

				ImGui::Begin(bGui_Extra.getName().c_str(), (bool*)&bGui_Extra.get(), flagsw);
				{
					ImGui::Indent();
					{
						// Preview Big

						ofxImGuiSurfing::AddToggleRounded(bGui_PreviewBig);
						if (bGui_PreviewBig)
						{
							ImGui::Indent();
							{
								//ofxImGuiSurfing::VectorCombo2(scaleModeIndex, scaleModenames);//TODO: fix

								float w = 0.5 * ofxImGuiSurfing::getWidgetsWidth();
								ImGui::PushItemWidth(w);
								ofxImGui::AddParameter(scaleModeIndex);//TODO: fix
								ImGui::PopItemWidth();

								if (scaleModeIndex <= scaleModenames.size() - 1)
								{
									string s = scaleModenames[scaleModeIndex.get()];
									ImGui::Text(s.c_str());
								}

								//-

								ofxImGuiSurfing::AddToggleRounded(bFullScreen);
								if (!bFullScreen)
								{
									ofxImGuiSurfing::AddToggleRounded(bInDocked);
									if (!bInDocked) ofxImGuiSurfing::AddToggleRounded(rectDraggable.bEditMode);
								}

								//TODO:
								//ofxImGuiSurfing::AddParameter(colorBg);//TODO: fix
							}
							ImGui::Unindent();
						}

						//--

						// Preview Floating

						ofxImGuiSurfing::AddToggleRounded(bGui_MiniPreview);
						if (bGui_MiniPreview)
						{
							ImGui::Indent();
							ofxImGuiSurfing::AddToggleRounded(bAutoResize_Preview);
							ImGui::Unindent();
						}

						// Debug only for floating window active
						if (bGui_MiniPreview)
						{
							ImGui::Separator();

							ofxImGuiSurfing::AddToggleRounded(bDebug);
							if (bDebug)
							{
								ImGui::Indent();
								ofxImGuiSurfing::BasicInfosWindow();
								ImGui::Unindent();
							}
						}
					}
					ImGui::Unindent();
				}
				ImGui::End();
			}
	};
	*/
};

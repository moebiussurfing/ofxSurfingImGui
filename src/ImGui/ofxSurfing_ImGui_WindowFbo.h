#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "ofxSurfing_ImGui_ofHelpers.h"
#include "ofxInteractiveRect.h"

// Class to handle a video preview window with some extra features

// Fbo ImGui Window
// Some stuff from ofxMyUtil from https://github.com/Iwanaka

namespace ofxImGuiSurfing
{
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
		string str1 = "Size: " + ofToString(ImGui::GetWindowSize().x, 0) + "," + ofToString(ImGui::GetWindowSize().y, 0);
		string str2 = "Pos:  " + ofToString(ImGui::GetWindowPos().x, 0) + "," + ofToString(ImGui::GetWindowPos().y, 0);
		ImGui::Text(str1.c_str());
		ImGui::Text(str2.c_str());
	}

	//--------------------------------------------------------------
	inline GLuint loadTextureImage2D(unsigned char * pix, int width, int height)
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
	inline void DrawFboPreview(const ofFbo &fbo)
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

//--

class SurfingPreview
{
public:

	SurfingPreview::SurfingPreview()
	{
		setup();
	}

	SurfingPreview::~SurfingPreview()
	{
		ofRemoveListener(params.parameterChangedE(), this, &SurfingPreview::Changed_Params); // exit()
	}

private:

	// fbo
	ofFbo fboPreview;
	ofFboSettings fboSettings;
	ofParameter<bool> bGui_Preview;
	GLuint sourceID;

public:

	ofParameter<bool> bGui{ "Preview", true };
	ofParameter<bool> bFullScreen{ "Full Screen", false };
	ofParameter<bool> bBigScreen{ "Big Screen", true };
	ofScaleMode scaleMode;
	ofxInteractiveRect myRect = { "myRect" };

	ofParameterGroup & getParameters() {
		return params;
	}

private:

	ofParameter<bool> bAutoResize{ "Auto Resize", true };
	ofParameter<bool> bDebug{ "Debug", true };
	ofParameter<bool> bExtra{ "Extra", false };

	std::vector<std::string> scaleModenames={ "FILL", "FIT", "CENTER", "STRETCH_TO_FILL" };
	ofParameter<int> scaleModeIndex{ "Scale Mode", 0, 0, 3 };

	ofParameterGroup params;

public:

	void setup()
	{
		params.setName("SurfingPreview");
		params.add(bGui);
		params.add(bExtra);
		params.add(bAutoResize);
		params.add(bFullScreen);
		params.add(scaleModeIndex);
		params.add(bBigScreen);
		params.add(myRect.getParameter());

		ofAddListener(params.parameterChangedE(), this, &SurfingPreview::Changed_Params); // setup()

		// fbo settings
		fboSettings.width = 1920;
		fboSettings.height = 1080;

		fboSettings.internalformat = GL_RGBA;
		fboSettings.textureTarget = GL_TEXTURE_2D;
		//fboSettings.internalformat = GL_RGBA32F_ARB;

		//fboSettings.useDepth = true;
		//fboSettings.useStencil = true;
		//fboSettings.depthStencilAsTexture = true;

		// fbo 
		//ofEnableArbTex();
		//ofDisableeArbTex();
		fboPreview.allocate(fboSettings);
		fboPreview.begin();
		{
			ofClear(0, 255);
		}
		fboPreview.end();

		//-

		myRect.bEditMode.setName("Edit Viewport");
		//myRect.enableEdit();
		//myRect.setRect(200, 200, 200, 400);
		myRect.setTransparent();
		myRect.setAutoSave(true);
		//myRect.loadSettings();
	};

	void updateRect(ofRectangle r)
	{
		myRect.setX(r.getX());
		myRect.setY(r.getY());
		myRect.setWidth(r.getWidth());
		myRect.setHeight(r.getHeight());
	};

	void draw()
	{
		myRect.draw();
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

	void draw_ImGuiPreview()
	{
		if (!bGui) return;

		ImGuiCond flagsCond = ImGuiCond_None;
		flagsCond |= ImGuiCond_Appearing;

		ImGuiWindowFlags flagsw = ImGuiWindowFlags_None;
		if (bAutoResize) flagsw |= ImGuiWindowFlags_AlwaysAutoResize;

		ImGui::Begin(bGui.getName().c_str(), (bool*)&bGui.get(), flagsw);
		{
			ofxImGuiSurfing::DrawFboPreview(fboPreview);

			ofxImGuiSurfing::AddToggleRounded(bExtra);
			if (bExtra)
			{
				ofxImGuiSurfing::AddToggleRounded(bBigScreen);
				if (bBigScreen) {
					ImGui::Indent();
					ofxImGuiSurfing::AddToggleRounded(myRect.bEditMode);
					//ofxImGuiSurfing::AddCombo(scaleModeIndex, scaleModenames);
					ofxImGuiSurfing::AddToggleRounded(bFullScreen);
					ImGui::Unindent();
				}
				ofxImGuiSurfing::AddToggleRounded(bDebug);
				if (bDebug)
				{
					ImGui::Indent();
					ofxImGuiSurfing::BasicInfosWindow();
					ImGui::Unindent();
				}
				ofxImGuiSurfing::AddToggleRounded(bAutoResize);
			}
		}
		ImGui::End();
	};

	void Changed_Params(ofAbstractParameter &e)
	{
		string name = e.getName();
		ofLogNotice() << __FUNCTION__ << name << " : " << e;

		if (0) {}

		else if (name == scaleModeIndex.getName())
		{
			scaleMode = ofScaleMode(scaleModeIndex.get());
		}
	};
};
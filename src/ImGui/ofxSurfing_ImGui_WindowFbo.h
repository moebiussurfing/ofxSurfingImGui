#pragma once

#include "ofMain.h"

#include "ofxImGui.h"

// Fbo ImGui Window
// from ofxMyUtil from https://github.com/Iwanaka

namespace ofxImGuiSurfing {

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
		ImGui::Text("Window size : x %f, y %f", ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
		ImGui::Text("Window position : x %f, y %f", ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);
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
	inline void DrawFbo(const ofFbo &fbo, GLuint &sourceID, string name, ImGuiWindowFlags flag = ImGuiWindowFlags_None, bool bResizeable = false)
	{
		if (!fbo.isAllocated()) return;

		static bool bDebug = true;

		//TODO: try to scale..
		ImVec2 sz = ImVec2(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);

		ofPixels pix;
		pix.clear();

		fbo.readToPixels(pix);
		pix.setImageType(OF_IMAGE_COLOR_ALPHA);

		// clear source
		glDeleteTextures(1, &sourceID);

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

		sourceID = loadTextureImage2D(pix.getData(), sz.x, sz.y);
		//https://gamedev.stackexchange.com/questions/140693/how-can-i-render-an-opengl-scene-into-an-imgui-window
		//ImGui::Begin("GameWindow");
		ImGui::Begin(name.c_str());
		{
			// Using a Child allow to fill all the space of the window.
			// It also alows customization
			ImGui::BeginChild("GameRender");
			// Get the size of the child (i.e. the whole draw size of the windows).
			ImVec2 wsize = ImGui::GetWindowSize();
			// Because I use the texture from OpenGL, I need to invert the V from the UV.
			ImGui::Image((ImTextureID)(uintptr_t)sourceID, wsize);
			//ImGui::Image((ImTextureID)tex, wsize, ImVec2(0, 1), ImVec2(1, 0));
			//ImGui::Image((ImTextureID)tex, wsize, ImVec2(0, 1), ImVec2(1, 0));
			ImGui::EndChild();
		}
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
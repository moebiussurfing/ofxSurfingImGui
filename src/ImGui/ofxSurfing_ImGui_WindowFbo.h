#pragma once

#include "ofMain.h"

#include "ofxImGui.h"

// Fbo ImGui Window
// from ofxMyUtil from https://github.com/Iwanaka

namespace ofxImGuiSurfing {

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
	inline void DrawFbo(const ofFbo &fbo, GLuint &sourceID, string name, ImGuiWindowFlags flag)
	{
		if (!fbo.isAllocated()) return;

		ofPixels pix;
		pix.clear();

		fbo.readToPixels(pix);
		pix.setImageType(OF_IMAGE_COLOR_ALPHA);

		// clear source
		glDeleteTextures(1, &sourceID);

		// set source
		sourceID = loadTextureImage2D(pix.getData(), fbo.getWidth(), fbo.getHeight());

		ImGui::Begin(name.c_str(), 0, flag);
		//ImGui::Begin(name.c_str(), 0, ImVec2(fbo.getWidth() * 1.1, fbo.getHeight()* 1.1f), .5f, flag);
		{
			ImGui::Image((ImTextureID)(uintptr_t)sourceID, ImVec2(fbo.getWidth(), fbo.getHeight()));
		}
		ImGui::End();
	}
}
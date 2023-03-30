#pragma once
#include "ofMain.h"

#include "imgInspect.h"
#include "ofxSurfingImGui.h"
#include "ofxSurfingHelpers.h"

class SurfImageInspect
{
private:
	ofxSurfingGui* ui = nullptr;
public:
	void setUiPtr(ofxSurfingGui* _ui) {
		ui = _ui;
	}

private:
	ofPixels pixels;
	ofImage image;
	ofTexture texture;
	GLuint textureID;
	//ofFbo fbo;

public:
	ofParameter<bool> bGui{ "ImageInspect", true };
	ofParameter<ofColor> colorPtr{ "ColorPicked", ofColor(128, 128) };

private:
	ofParameter<bool> bGui_Image{ "Window Image", true };
	ofParameter<bool> bDebugAdvanced{ "DebugAdvanced", false };
	ofParameter<bool> bEnableInspector{ "Inspector",true };
	ofParameter<bool> bEnablePicker{ "Picker",false };
	ofParameter<int> zoomSize{ "ZoomOut", 40, 1, 50 };
	ofParameter<int> zoomRectangleWidth{ "BoxSize", 100, 50, 1000 };
	ofParameterGroup params{ "Image Inspector" };

	bool bLoaded = false;

	string path = "";//file name
	//string pathImages = "images";//file path

	ofColor c = 0;

	//--

public:
	SurfImageInspect() {
	};

	~SurfImageInspect() {
		exit();
	};

	void setup()
	{
		params.add(bGui);
		params.add(bGui_Image);
		params.add(bDebugAdvanced);
		params.add(bEnableInspector);
		params.add(bEnablePicker);
		params.add(zoomSize);
		params.add(zoomRectangleWidth);

		ofxSurfingHelpers::load(params);
	};

	void loadTexture(string path_)
	{
		ofLogNotice("SurfImageInspect") << "loadTexture()";

		path = path_;

		bLoaded = image.load(path);
		if (bLoaded)
		{
			ofLogNotice("SurfImageInspect") << "Loaded image on path: " << path;
		}
		else
		{
			ofLogError("SurfImageInspect") << "Not found image on path: " << path;
			return;
		}


		/*
		ofLogNotice("SurfImageInspect") << "loadTexture()";
		if (_image.isAllocated()) {
			bLoaded = true;
		}

		if (bLoaded) {
			image = _image;
			ofLogNotice("SurfImageInspect") << "Image received.";
		}
		else
		{
			ofLogError("SurfImageInspect") << "Image not received.";
			return;
		}
		*/

		//-

		/*
		// push
		bool b = ofGetUsingArbTex();
		ofDisableArbTex();
		*/

		ofLoadImage(texture, path);

		/*
		float w = texture.getWidth();
		float h = texture.getHeight();
		fbo.allocate(w, h);

		fbo.createAndAttachTexture(GL_RGB, 0); //position
		fbo.createAndAttachTexture(GL_RGBA32F, 1); //velocity
		fbo.createAndAttachRenderbuffer(GL_DEPTH_COMPONENT, GL_DEPTH_ATTACHMENT);
		fbo.checkStatus();

		fbo.begin();
		ofClear(0);
		fbo.end();

		// pop/restore
		if (b) ofEnableArbTex();

		// draw texture once
		fbo.begin();
		ofClear(0, 0, 0, 0);
		texture.draw(0, 0);
		fbo.end();
		*/

		//--

		// pre load on ui
		if (ui != nullptr) textureID = ui->getGuiPtr()->loadTexture(texture, path);
	};

	void drawImGui(bool bWindowed = true)
	{
		if (ui == nullptr) return;
		if (!bGui) return;

		{
			// Locks moving window when mouse over image.	
			static bool bOver = false;
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
			if (ui->bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
			if (bOver) window_flags |= ImGuiWindowFlags_NoMove;

			//if (bGui) IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL;

			bool b = true;
			if (bWindowed) b = ui->BeginWindow(bGui, window_flags);
			if (b)
			{
				bool bDebug = ui->bDebug;

				//--

				float _w100 = ui->getWidgetsWidth(1);
				float _spcx = ui->getWidgetsSpacingX();
				float _hb = ui->getWidgetsHeightUnit();

				//--

				float wSrc = texture.getWidth();
				float hSrc = texture.getHeight();
				float ratioSrc = hSrc / wSrc;

				float wDisplay = _w100;
				float hDisplay = wDisplay * ratioSrc;

				ui->AddMinimizerToggle();
				ui->AddSpacing();

				if (ui->isMaximized())
				{
					ui->AddDebugToggle();
					if (bDebug) ui->Add(bDebugAdvanced, OFX_IM_TOGGLE_ROUNDED_MINI);
					ui->AddSpacing();

					ui->AddAutoResizeToggle();

					ui->AddSpacingSeparated();
				}

				// Raw data
				if (bLoaded)
				{
					texture.readToPixels(pixels);
				}

				const unsigned char* data = pixels.getData();
				auto nBits = pixels.getBitsPerPixel();

				//--

				// Image

				if (bLoaded)
				{
					ui->AddSpacing();

					//// 1. Fbo
					//if (ImGui::ImageButton(
					//	(ImTextureID)(uintptr_t)fbo.getTexture(0).getTextureData().textureID,
					//	ImVec2(wDisplay)))
					//{
					//	ofLogNotice("SurfImageInspect") << "Image clicked";
					//}

					// 2. Texture
					ImGui::Image((ImTextureID)(uintptr_t)textureID, ImVec2(wDisplay, hDisplay));

					//--

					// Catch from previous widget
					ImGuiIO& io = ImGui::GetIO();
					bOver = ImGui::IsItemHovered();
					bool bMouseLeft = io.MouseClicked[0];
					bool bMouseRight = io.MouseClicked[1];
					bool bShift = io.KeyShift;

					ImRect rc = ImRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
					ImVec2 mouseUVCoord_ = (io.MousePos - rc.Min) / rc.GetSize();
					//mouseUVCoord_.y = 1.f - mouseUVCoord_.y; // flip y

					// clamp mouse
					ImVec2 mouseUVCoord = ImVec2(ofClamp(mouseUVCoord_.x, 0, 1), ofClamp(mouseUVCoord_.y, 0, 1));

					// clamp display zone
					ImVec2 displayedTextureSize_ = ImVec2(wDisplay, hDisplay);
					ImVec2 displayedTextureSize = ImVec2(ofClamp(displayedTextureSize_.x, 0, wSrc), ofClamp(displayedTextureSize_.y, 0, hSrc));

					//--

					bool b24bits = (nBits == 24);

					//--

					if (bOver)
					{
						if (bEnableInspector)
						{
							ImageInspect::inspect(wSrc, hSrc, data, mouseUVCoord, displayedTextureSize, zoomSize, zoomRectangleWidth, b24bits, bDebug, bDebugAdvanced, &c);
						}
						if (bEnablePicker && bMouseLeft)
						{
							c = ImageInspect::getColor(wSrc, hSrc, data, mouseUVCoord, displayedTextureSize, b24bits, &c);
							ofLogNotice("SurfImageInspect") << "Click color: " << c;
							colorPtr.set(c);
						}

						if (bEnableInspector && bMouseLeft)
						{
							ofLogNotice("SurfImageInspect") << "Click color: " << c;
							colorPtr.set(c);
						}

						if (bMouseRight)
						{
							bEnableInspector = !bEnableInspector;
						}
					}

					//--

					if (ui->isMaximized())
					{
						ui->AddSpacing();
						ui->AddSpacing();
						ui->Add(bEnableInspector, OFX_IM_TOGGLE_BIG, 2, true);
						ui->Add(bEnablePicker, OFX_IM_TOGGLE_BIG, 2);
						ui->AddSpacing();

						//--

						if (bEnableInspector)
						{
							ui->Add(zoomSize);
							ui->Add(zoomRectangleWidth);

							if (ImGui::Button("Mini")) {
								zoomSize = 1;
								zoomRectangleWidth = 60;
							}
							ImGui::SameLine();
							if (ImGui::Button("Small")) {
								zoomSize = 40;
								zoomRectangleWidth = 100;
							}
							ImGui::SameLine();
							if (ImGui::Button("Medium")) {
								zoomSize = 5;
								zoomRectangleWidth = 160;
							}
							if (ofxImGuiSurfing::getWindowWidthAvail() > 120)
								ImGui::SameLine();
							if (ImGui::Button("Big")) {
								zoomSize = 30;
								zoomRectangleWidth = 500;
							}
							ImGui::SameLine();
							if (ImGui::Button("Huge")) {
								zoomSize = 50;
								zoomRectangleWidth = 1000;
							}
						}


						//--

						/*
						if (ui->AddButton("Reset Original"))
						{
							wDisplay = image.getWidth();
							hDisplay = image.getHeight();
						}
						*/
					}
				}


				//--

				// Debug

				if (bLoaded)
				{
					if (ui->isDebug() && bDebugAdvanced && ui->isMaximized())
					{
						ui->AddSpacingBigSeparated();

						//size_t dsz = sizeof(((unsigned char*)data)) / sizeof(((unsigned char*)data)[0]);
						//ui->AddLabel("nData: " + ofToString(dsz));

						ui->AddLabel("nBits: " + ofToString(nBits));
						ui->AddSpacing();
						ui->BeginColumns(2, "##cols", true);
						ui->AddLabelBig("FILE:");
						ui->AddLabel("size: " + ofToString(wSrc) + "," + ofToString(hSrc));
						ui->AddLabel("nPix: " + ofToString(wSrc * hSrc));
						ui->NextColumn();
						ui->AddLabelBig("DRAWN:");
						ui->AddLabel("size: " + ofToString(wDisplay, 0) + "," + ofToString(hDisplay, 0));
						ui->AddLabel("nPix: " + ofToString(wDisplay * hDisplay, 0));
						ui->EndColumns();
						ui->AddSpacingBigSeparated();

						ui->AddLabelBig("MOUSE App:");
						ui->AddLabel("x,y: " + ofToString(ofGetMouseX()) + "," + ofToString(ofGetMouseY()));
						ui->AddSpacing();

						static bool bInside;
						ui->AddLabelBig(bInside ? "MOUSE Window:" : "");
						auto pm = ImGui::GetMousePos();
						auto pw = ImGui::GetWindowPos();
						ImVec2 p = pm - pw;
						ofRectangle r(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
						bInside = r.inside(ofGetMouseX(), ofGetMouseY());
						string s = " ";
						if (bInside) s = "x,y: " + ofToString(p.x) + "," + ofToString(p.y);
						ui->AddLabel(s);

						ui->AddSpacingBigSeparated();
					}
				}

				//--

				if (ui->isMaximized()) {
					ui->AddLabel(path);
					ui->AddSpacing();

					if (bLoaded)
					{
						ui->Add(bGui_Image, OFX_IM_TOGGLE_ROUNDED);
					}
				}

				if (bWindowed && b) ui->EndWindow();
			}
		}

		//--

		if (bLoaded)
		{
			if (bGui_Image)
			{
				if (ui->BeginWindow(bGui_Image, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImVec2 sz = ImVec2(image.getWidth(), image.getHeight());

					// 2. Texture
					ImGui::Image((ImTextureID)(uintptr_t)textureID, sz);

					// 3. Pixels
					//ImGui::Image(GetImTextureID(pixelsButtonID), sz);

					ui->EndWindow();
				}
			}
		}
	};

private:
	void exit() {
		ofxSurfingHelpers::save(params);
	};
};
//#include "ofApp.h"
//
////--------------------------------------------------------------
//void ofApp::setup()
//{
//	ofSetWindowPosition(1920, 25);
//
//	ui.setup();
//	ui.bNotifier = false;
//
//	//path = path1;
//	//loadTexture();
//
//	event = index.newListener([&](int& value)
//		{
//			switch (value)
//			{
//			case 0: path = path1; break;
//			case 1: path = path2; break;
//			case 2: path = path3; break;
//			}
//
//	ofLogNotice() << "path: " << path;
//
//	loadTexture();
//
//		});
//
//	//startup
//	index = 0;
//}
//
////--------------------------------------------------------------
//void ofApp::loadTexture()
//{
//	ofLogNotice() << "loadTexture()";
//
//	bool bLoaded = image.load(path);
//	if (bLoaded) ofLogNotice() << "Loaded image on path: " << path;
//	else ofLogError() << "Not found image on path: " << path;
//
//	imageFloat.load(path);
//
//
//	// push
//	bool b = ofGetUsingArbTex();
//	ofDisableArbTex();
//
//	//ofImageLoadSettings s = ;
//
//	ofLoadImage(texture, path);
//
//	float w = texture.getWidth();
//	float h = texture.getHeight();
//	fbo.allocate(w, h);
//
//	fbo.createAndAttachTexture(GL_RGB, 0); //position
//	fbo.createAndAttachTexture(GL_RGBA32F, 1); //velocity
//	fbo.createAndAttachRenderbuffer(GL_DEPTH_COMPONENT, GL_DEPTH_ATTACHMENT);
//	fbo.checkStatus();
//
//	fbo.begin();
//	ofClear(0);
//	fbo.end();
//
//	// pop/restore
//	if (b) ofEnableArbTex();
//
//	// draw texture once
//	fbo.begin();
//	ofClear(0, 0, 0, 0);
//	texture.draw(0, 0);
//	fbo.end();
//
//	//--
//
//	// "preload" on ui
//	textureID = ui.getGuiPtr()->loadTexture(texture, path);
//
//}
//
////--------------------------------------------------------------
//void ofApp::draw()
//{
//	ofClear(cBg);
//
//	ofRectangle rr(0, 0, imageFloat.getWidth(), imageFloat.getHeight());
//	rr.scaleTo(ofGetCurrentViewport(), OF_SCALEMODE_FIT);
//	imageFloat.draw(rr.x, rr.y, rr.width, rr.height);
//
//	//int p = 50;
//	//imageFloat.draw(p, p, ofGetWidth() - p * 2, ofGetHeight() - p * 2);
//
//	drawImGui();
//}
//
////--------------------------------------------------------------
//void ofApp::drawImGui()
//{
//	ui.Begin();
//
//	{
//		//if (bGui) IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL;
//
//		if (ui.BeginWindow(bGui))
//		{
//			//TODO: expose
//			static int zoomSize = 3;
//			static int zoomRectangleWidth = 200;
//			bool bdebug = ui.bDebug;
//
//			//--
//
//			float _w100 = ui.getWidgetsWidth(1);
//			float _spcx = ui.getWidgetsSpacingX();
//			float _hb = ui.getWidgetsHeightUnit();
//
//			//--
//
//			static bool bEnable = 1;
//
//			float wsrc = texture.getWidth();
//			float hsrc = texture.getHeight();
//			float ratio = hsrc / wsrc;
//
//			float ww;
//			float hh;
//
//			ww = _w100;
//			hh = ww * ratio;
//
//			ui.AddMinimizerToggle();
//
//			if (ui.isMaximized()) {
//				ui.AddNotifierToggle();
//				ui.AddLogToggle();
//				ui.AddAutoResizeToggle();
//				ui.AddSpacingBigSeparated();
//
//				ui.AddSpacing();
//				ui.Add(bDrawImg2, OFX_IM_TOGGLE_ROUNDED);
//
//				ui.AddDebugToggle();
//				ui.AddSpacing();
//			}
//
//			// mode
//			//pixels.allocate(image.getWidth(), image.getHeight(), OF_IMAGE_COLOR_ALPHA);
//			//pixels.setImageType(OF_IMAGE_COLOR_ALPHA);
//
//			//TODO:
//			// raw data
//
//			texture.readToPixels(pixels);
//			const unsigned char* data = pixels.getData();
//
//			auto nBits = pixels.getBitsPerPixel(); // 24 for RGB, 32 for RGBA
//
//
//			if (ui.isDebug())
//			{
//				//size_t dsz = sizeof(((uint32_t*)data)) / sizeof(((uint32_t*)data)[0]);
//				size_t dsz = sizeof(((unsigned char*)data)) / sizeof(((unsigned char*)data)[0]);
//				//ui.AddLabel("nData: " + ofToString(dsz));
//				ui.AddLabel("nBits: " + ofToString(nBits));
//				ui.AddSpacing();
//
//				ui.BeginColumns(2, "##cols", true);
//				ui.AddLabelBig("FILE:");
//				ui.AddLabel(ofToString(wsrc) + "," + ofToString(hsrc));
//				ui.AddLabel("nPixels: " + ofToString(wsrc * hsrc));
//				ui.NextColumn();
//				ui.AddLabelBig("DRAWN:");
//				ui.AddLabel(ofToString(ww, 0) + "," + ofToString(hh, 0));
//				ui.AddLabel("nPixels: " + ofToString(ww * hh));
//				ui.EndColumns();
//
//				ui.AddSpacingBigSeparated();
//
//				ui.AddLabelBig("MOUSE App:");
//				ui.AddLabel("x,y: " + ofToString(ofGetMouseX()) + "," + ofToString(ofGetMouseY()));
//
//				auto pm = ImGui::GetMousePos();
//				auto pw = ImGui::GetWindowPos();
//				ImVec2 p = pm - pw;
//				ui.AddLabelBig("MOUSE Window:");
//				ofRectangle r(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
//				bool bInside = r.inside(ofGetMouseX(), ofGetMouseY());
//				string s = " ";
//				if (bInside)
//				{
//					s = "x,y: " + ofToString(p.x) + "," + ofToString(p.y);
//				}
//				ui.AddLabel(s);
//				ui.AddSpacingBigSeparated();
//			}
//
//			//--
//
//			ui.AddToggle("Enable", bEnable, OFX_IM_TOGGLE_BIG);
//			ui.AddSpacing();
//
//			//// 1. Fbo
//			//if (ImGui::ImageButton(
//			//	(ImTextureID)(uintptr_t)fbo.getTexture(0).getTextureData().textureID,
//			//	ImVec2(ww, hh)))
//			//{
//			//	ofLogNotice() << "Image clicked";
//			//}
//
//			// 2. Texture
//			ImGui::Image((ImTextureID)(uintptr_t)textureID, ImVec2(ww, hh));
//
//			// over
//			bool bOver = 0;
//			bOver = ImGui::IsItemHovered();
//
//			//--
//
//			ImGuiIO& io = ImGui::GetIO();
//			ImRect rc = ImRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
//			ImVec2 mouseUVCoord_ = (io.MousePos - rc.Min) / rc.GetSize();
//			//mouseUVCoord_.y = 1.f - mouseUVCoord_.y; // flip y
//
//			// clamp
//			ImVec2 mouseUVCoord = ImVec2(
//				ofClamp(mouseUVCoord_.x, 0, 1),
//				ofClamp(mouseUVCoord_.y, 0, 1));
//
//			ImVec2 displayedTextureSize_ = ImVec2(ww, hh);
//			ImVec2 displayedTextureSize = ImVec2(
//				ofClamp(displayedTextureSize_.x, 0, wsrc),
//				ofClamp(displayedTextureSize_.y, 0, hsrc));
//
//			ui.AddSpacing();
//
//			//TODO: make ofParams
//			ImGui::SliderInt("zoomSize", &zoomSize, 1, 50);
//			ImGui::SliderInt("zoomRect", &zoomRectangleWidth, 50, 1000);
//
//			if (ImGui::Button("Reset")) {
//				zoomSize = 3;
//				zoomRectangleWidth = 200;
//			}
//
//			bool b24bits = (nBits == 24);
//
//			if (bOver && bEnable)
//			{
//				ImageInspect::inspect(wsrc, hsrc, data, mouseUVCoord, displayedTextureSize,
//					b24bits, bdebug, &zoomSize, &zoomRectangleWidth, &c);
//			}
//
//			//if (io.KeyShift && io.MouseDown[0])
//			if (bOver && bEnable && io.MouseDown[0])
//			{
//				ofLog() << "CLICK color: " << c;
//				cBg.set(c);
//			}
//
//			if (bOver && io.KeyShift && io.MouseDown[1])
//			{
//				bEnable = !bEnable;
//
//				ofLog() << "CLICK enable: " << bEnable;
//
//				//// swap
//				//static bool bEnable_ = !bEnable;
//
//				//if (bEnable != bEnable_) {
//				//	bEnable_ = bEnable;
//				//	bEnable = !bEnable;
//				//}
//			}
//
//			if (ui.isDebug())
//			{
//				ui.AddSpacingBigSeparated();
//				ui.AddToggle("OverImg", bOver);
//			}
//
//			//----
//
//			//if (ui.AddButton("Reset Original"))
//			//{
//			//	ww = image.getWidth();
//			//	hh = image.getHeight();
//			//}
//
//			ui.EndWindow();
//		}
//
//		//--
//
//		if (ui.BeginWindow(bDrawImg2, ImGuiWindowFlags_AlwaysAutoResize))
//		{
//			ui.Add(index);
//			ui.AddLabelBig(path);
//			ui.AddSpacing();
//
//			ImVec2 sz = ImVec2(image.getWidth(), image.getHeight());
//
//			// 2. Texture
//			ImGui::Image((ImTextureID)(uintptr_t)textureID, sz);
//
//			// 3. Pixels
//			//ImGui::Image(GetImTextureID(pixelsButtonID), sz);
//
//			ui.EndWindow();
//		}
//
//	}
//
//	ui.End();
//}
//
////--------------------------------------------------------------
//void ofApp::keyPressed(int key)
//{
//	if (key == ' ') bGui = !bGui;
//}

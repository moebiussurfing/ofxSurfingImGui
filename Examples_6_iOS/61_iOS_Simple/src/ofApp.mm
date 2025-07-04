#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ui.setup();
	
	//TODO: Not working. Must fix bc overloaded.
//	ui.setGlobalScale(3);
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			ui.AddLabelBig("Hello iOS World");
			ui.AddSpacing();
			
			ui.Add(bEnable, OFX_IM_TOGGLE_BIG_BORDER_BLINK);
			ui.Add(speed, OFX_IM_HSLIDER);
			ui.Add(value, OFX_IM_HSLIDER);
			ui.Add(index, OFX_IM_HSLIDER);
			ui.AddSpacingSeparated();
			
			ui.AddGroup(params);
			ui.AddSpacingSeparated();
			
			ui.AddMinimizeToggle();
			if(ui.isMaximized()) ui.DrawWidgetsGlobalScale();
			else ui.DrawWidgetsGlobalScaleMini();
			
			//--
			
#ifdef OFXIMGUI_DEBUG
			ui.AddDebugToggle();
			if(ui.isDebug()) {
				drawDebug();
				// DemoWindow
				static bool showDemo = false;
				ImGui::Checkbox("Show demo window", &showDemo);
				if( showDemo ){
					ImGui::ShowDemoWindow();
				}
				static bool showMetrics = false;
				ImGui::Checkbox("Show metrics window", &showMetrics);
				if( showMetrics ){
					ImGui::ShowMetricsWindow();
				}
			}
#endif
			
			ui.EndWindow();
		}
		
#ifdef OFXIMGUI_DEBUG
		if(ui.isDebug()) ui.getImGuiPtr()->drawOfxImGuiDebugWindow();
#endif
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::drawDebug(){
	//TODO: Test fix bin/data/ file settings persistence...
	if(ui.AddButton("Save UI Settings"))
		ui.saveSettings();
	
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_IsTouchScreen)
		ImGui::Text("Touch screen mode enabled");
}

//--------------------------------------------------------------
void ofApp::exit(){
}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){
	
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){
	
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){
	
}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){
	
}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch){
	
}

//--------------------------------------------------------------
void ofApp::lostFocus(){
	
}

//--------------------------------------------------------------
void ofApp::gotFocus(){
	
}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning(){
	
}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){
	
}

//--------------------------------------------------------------
void ofApp::launchedWithURL(std::string url){
	
}

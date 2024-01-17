
/*
* SurfingTransformNode.h
* 
	A class derived from ofNode, 
	but adding ofParameters for 
	position, rotation, scale and other useful params (draw, debug...etc)
	Ready to be exposed to a UI.
	Handles the transforms for an object.
	To be applied easily and to store to JSON settings
*/

/*
	TODO
	- add refreshGui by passing transfromGroup. like presets groups
	- allow mode for linked or independent scale for xyz
		- fix lock all axis to x 
	- add simple example?
	- add bbox for selected model
*/

//--

#pragma once

#include "ofMain.h"

//TODO: add settings
#include "ofxSurfingHelpersLite.h"

//----

//OPTIONAL: comment the below line
// if you are using this class standalone,
// without the whole ofxSurfingPBR!
//#include "ofxSurfingPBRConstants.h"

#ifndef SURFING__PBR__SCENE_SIZE_UNIT
	#define SURFING__PBR__SCENE_SIZE_UNIT 1000.f
#endif

// Range for rotate
#define SURFING__MAX_DEGREE 360
//#define SURFING__MAX_DEGREE 180

//----

class TransformNode : public ofNode {

	//--

	//some constants
	const float scaleNormalizedRatio = 10.f;
	const int scaleNormalizedPowMax = 100;
	//const float scaleNormalizedUnit = scaleNormalizedPowMax;
	float scaleNormalizedUnit = scaleNormalizedRatio * scaleNormalizedPowMax;
	const float unitSize = SURFING__PBR__SCENE_SIZE_UNIT * 1.f;

	//--

	// Main controls
	// Exposed to gui and "redirected" to ofNode!
public:
	ofParameter<glm::vec3> position { "Position", glm::vec3(0),
		glm::vec3(-unitSize), glm::vec3(unitSize) };

	ofParameter<glm::vec3> scale { "Scale", glm::vec3(1),
		glm::vec3(1), glm::vec3(scaleNormalizedUnit) };

	ofParameter<glm::vec3> rotationEuler { "Rotation Euler", glm::vec3(0),
		glm::vec3(-(float)SURFING__MAX_DEGREE), glm::vec3((float)SURFING__MAX_DEGREE) };

	// Normalized controls
	ofParameter<float> scaleNormalized { "Scale Norm", 0, -1.f, 1.f };
	ofParameter<int> scaleNormalizedPow { "Scale Pow", scaleNormalizedPowMax / 2, 1, scaleNormalizedPowMax };
	ofParameter<bool> bScaleLinkAxis { "ScaleLinkAxis", true }; //TODO
	ofParameter<glm::vec3> positionNormalized { "Position Normalized", glm::vec3(0), glm::vec3(-1), glm::vec3(1) };

	ofParameterGroup parameters; //exposed to the gui
	ofParameterGroup paramsScaleNormalized;
	ofParameterGroup paramsOfNode;
	ofParameterGroup paramsResets;

public:
	ofParameter<void> vReset { "Reset" };
	ofParameter<void> vResetScale { "Reset Scale" };
	ofParameter<void> vResetPosition { "Reset Position" };
	ofParameter<void> vResetRotation { "Reset Rotation" };

	ofParameter<bool> bDraw { "Draw", true };
	ofParameter<bool> bDebug { "Debug", false };

private:
	SurfingAutoSaver autoSaver;
	string name = "";
	string pathSuffix = "_Transform.json";
	string path = "";
	bool bDoneSetup = false;

	bool bAttendingScale = false;

public:
	ofxPanel gui;
	ofParameter<bool> bGui;
	ofParameterGroup paramsPreset;

	void setName(string name_) { //caall before setup
		ofLogNotice("TransformNode") << "setName(" << name_ << ")";
		name = name_;
	}

private:
	void setupSettings() {
		ofLogNotice("TransformNode") << "setupSettings()";

		// build preset group
		if (name == "") name = "Transform";
		//name = "UI " + name; 
		bGui.set(name, true);

		paramsPreset.setName(name);
		paramsPreset.add(positionNormalized);
		paramsPreset.add(paramsScaleNormalized);
		paramsPreset.add(paramsOfNode);
		paramsPreset.add(paramsResets);

		path = name + pathSuffix;

		gui.setup(paramsPreset);

		if (bEnableSettings) {
			callback_t f = std::bind(&TransformNode::save, this);
			autoSaver.setFunctionSaver(f);

			load();
		}
	}

	void save() {
		ofLogNotice("TransformNode") << "save -> " << path;
		ofxSurfing::saveSettings(parameters, path);
	}

	bool load() {
		ofLogNotice("TransformNode") << "load -> " << path;
		if (bEnableSettings) autoSaver.pause();
		bool b = ofxSurfing::loadSettings(parameters, path);
		if (bEnableSettings) autoSaver.start();
		return b;
	}

	void update(ofEventArgs & args) {
		update();
	}

	void update() {
		if (!bDoneSetup) {
			setup();
		}
	}

	void Changed(ofAbstractParameter & e) {

		std::string name = e.getName();

		ofLogVerbose("TransformNode") << "Changed: " << name << ": " << e;

		if (bEnableSettings)
			if (e.isSerializable()) {
				autoSaver.saveSoon();
			}
	}

	//----

public:
	TransformNode() {
		ofLogNotice("TransformNode") << "Constructor";
		//setup();

		ofAddListener(ofEvents().update, this, &TransformNode::update);
		ofAddListener(parameters.parameterChangedE(), this, &TransformNode::Changed);
	}

	//TransformNode(const TransformNode & other)
	//	: bDraw(other.bDraw)
	//	, scaleNormalizedPow(other.scaleNormalizedPow)
	//	, scaleNormalized(other.scaleNormalized)
	//	, positionNormalized(other.positionNormalized)
	//	, rotationEuler(other.rotationEuler)
	//	, vReset(other.vReset)
	//	, vResetScale(other.vResetScale)
	//	, vResetPosition(other.vResetPosition)
	//	, vResetRotation(other.vResetRotation)
	//	, parameters(other.parameters)
	//{
	//	setup();
	//}

	TransformNode(const TransformNode & other) {
		ofLogNotice("TransformNode") << "Constructor";

		ofAddListener(ofEvents().update, this, &TransformNode::update);
		ofAddListener(parameters.parameterChangedE(), this, &TransformNode::Changed);
	}

	~TransformNode() {
		ofLogNotice("TransformNode") << "Destructor";

		ofRemoveListener(ofEvents().update, this, &TransformNode::update);
		ofRemoveListener(parameters.parameterChangedE(), this, &TransformNode::Changed);
	}

	//--

	void refreshGui() {
		ofLogNotice("TransformNode") << "refreshGui()";

		gui.getGroup(paramsOfNode.getName()).getGroup(scale.getName()).minimize();
		gui.getGroup(paramsOfNode.getName()).getGroup(position.getName()).minimize();
		gui.getGroup(paramsResets.getName()).minimize();
	}

	void refreshGuiUserParams(ofxPanel & gui_, ofxGuiGroup & group_) {
		ofLogNotice("TransformNode") << "refreshGui(ofxPanel,ofxGuiGroup)";

		group_.getGroup(paramsOfNode.getName()).getGroup(scale.getName()).minimize();
		group_.getGroup(paramsOfNode.getName()).getGroup(position.getName()).minimize();
		group_.getGroup(paramsResets.getName()).minimize();
	}

	//--

private:
	bool bEnableSettings = true;

public:
	void setEnableSettings(bool b) { //use to disable when settings are handled externaly. as when using a transform vector for multiple objects..
		bEnableSettings = b;
	}

private:
	std::unique_ptr<ofEventListener> e_vResetScale;
	std::unique_ptr<ofEventListener> e_vResetPosition;
	std::unique_ptr<ofEventListener> e_vResetRotation;
	std::unique_ptr<ofEventListener> e_vReset;

	std::unique_ptr<ofEventListener> e_positionNormalizedChanged;
	std::unique_ptr<ofEventListener> e_scaleNormalized;
	std::unique_ptr<ofEventListener> e_scaleNormalizedPow;
	std::unique_ptr<ofEventListener> e_rotatioEulerChanged; //TODO

	//--

public:
	void setup() {

		// parameters

		parameters.setName("TRANSFORM");

		paramsOfNode.setName("ofNode");
		paramsOfNode.add(scale);
		paramsOfNode.add(position);
		paramsOfNode.add(rotationEuler);

		paramsScaleNormalized.setName("Scale Normalized");
		paramsScaleNormalized.add(scaleNormalizedPow);
		paramsScaleNormalized.add(scaleNormalized);
		paramsScaleNormalized.add(bScaleLinkAxis); //TODO

		parameters.add(bDraw);
		parameters.add(bDebug);
		parameters.add(paramsOfNode);
		parameters.add(paramsScaleNormalized);
		parameters.add(positionNormalized);

		paramsResets.setName("Resets");
		paramsResets.add(vResetScale);
		paramsResets.add(vResetPosition);
		paramsResets.add(vResetRotation);
		paramsResets.add(vReset);
		paramsResets.setSerializable(false);
		parameters.add(paramsResets);

		setupCallbacks();

		//--

		setupSettings();

		bDoneSetup = true;
	}

	//--

	// Get the transforms for each model
	// passing the model index as argument:

public:
	bool isEnabled() const {
		return bDraw;
	}
	bool isDebug() const {
		return bDebug;
	}

	float getScaleNormalized() const {
		return scaleNormalized;
	}

	float getScalePow() const {
		return scaleNormalizedPow;
	}

	glm::vec3 getPositionNormalized() const {
		return positionNormalized;
	}

	glm::vec3 getRotationDeg() const {
		return rotationEuler;
	}

	//--

	void reset() {
		resetScale();
		resetPosition();
		resetRotation();
	}
	void resetScale() {
		scaleNormalized = 0;
		//scaleNormalizedPow = scaleNormalizedPowMax/2;
	}
	void resetPosition() {
		positionNormalized = glm::vec3(0);
	}
	void resetRotation() {
		rotationEuler = glm::vec3(0);
	}

	//--

	//https://forum.openframeworks.cc/t/ofnode-and-ofparameter/24436/2

public:
	void setupCallbacks() {
		position.addListener(this, &TransformNode::_setPosition);
		scale.addListener(this, &TransformNode::_setScale);
		rotationEuler.addListener(this, &TransformNode::_setRotation);

		//--

		// Transform

		e_positionNormalizedChanged = std::make_unique<ofEventListener>(positionNormalized.newListener([this](glm::vec3) {
			ofLogNotice(__FUNCTION__);

			refreshPositionFromNormalized();
		}));

		e_scaleNormalizedPow = std::make_unique<ofEventListener>(scaleNormalizedPow.newListener([this](float) {
			ofLogNotice(__FUNCTION__);

			//adapt param range
			scaleNormalizedUnit = scaleNormalizedRatio * scaleNormalizedPow;
			scale.setMax(glm::vec3(scaleNormalizedUnit, scaleNormalizedUnit, scaleNormalizedUnit));

			refreshScaleFromNormalized();
		}));

		e_scaleNormalized = std::make_unique<ofEventListener>(scaleNormalized.newListener([this](float) {
			ofLogNotice(__FUNCTION__);

			refreshScaleFromNormalized();
		}));

		e_rotatioEulerChanged = std::make_unique<ofEventListener>(rotationEuler.newListener([this](glm::vec3) {
		}));

		//--

		// Resets

		e_vReset = std::make_unique<ofEventListener>(vReset.newListener([this](void) {
			reset();
		}));

		e_vResetScale = std::make_unique<ofEventListener>(vResetScale.newListener([this](void) {
			resetScale();
		}));

		e_vResetPosition = std::make_unique<ofEventListener>(vResetPosition.newListener([this](void) {
			resetPosition();
		}));

		e_vResetRotation = std::make_unique<ofEventListener>(vResetRotation.newListener([this](void) {
			resetRotation();
		}));
	}

	//--

	// Update ofNode

	void _setPosition(glm::vec3 & v) {
		ofLogNotice(__FUNCTION__);

		setPosition(v);

		refreshPositionToNormalized();
	}

	void _setScale(glm::vec3 & v) {
		if (bAttendingScale) return;
		ofLogNotice(__FUNCTION__) << v;

		if (bScaleLinkAxis) {
			bAttendingScale = true;

			//TODO: fix lock all axis to x
			glm::vec3 s = glm::vec3(scale.get().x);

			//glm::vec3 s = glm::vec3(v.x, v.x, v.x);
			scale.set(s);
//v = s;
#if 0
			ofLogNotice(__FUNCTION__) << "s:" << s;
			ofLogNotice(__FUNCTION__) << "v:" << v;
			ofLogNotice(__FUNCTION__) << "scale:" << scale;
#endif

			bAttendingScale = false;

			setScale(s);
			return;
		}

		setScale(v);
	}

	void _setRotation(glm::vec3 & v) {
		ofLogNotice(__FUNCTION__);

		setOrientation(v);
	}

	//--

	// Update params from ofNode

	void onPositionChanged() override {
		if (position.get() != getPosition()) {
			ofLogNotice(__FUNCTION__);

			position.set(getPosition());
			//position.setWithoutEventNotifications(getPosition());

			refreshPositionToNormalized();
		}
	}

	void onOrientationChanged() override {
		// compare the two objects with an epsilon of 0.001
		bool bEqual = glm::all(glm::epsilonEqual(rotationEuler.get(), getOrientationEuler(), 0.001f));

		if (!bEqual) {
			ofLogNotice(__FUNCTION__);

			//ofLogNotice() << "rotationEuler:" << rotationEuler;
			//ofLogNotice() << "getOrientationEuler():" << getOrientationEuler();

			//TODO
			//refreshEulerRotationFromOfNodeOrientation();
		}
	}

	void onScaleChanged() override {
		if (bAttendingScale) return;

		if (scale.get() != getScale()) {
			ofLogNotice(__FUNCTION__);

			scale.set(getScale());
		}
		//TODO: apply to normalized scale
	}

	//--

	void refreshPositionFromNormalized() {
		ofLogNotice(__FUNCTION__);

		const float u = unitSize; //distance unit
		float x = ofMap(positionNormalized.get().x, -1, 1, -u, u, true);
		float y = ofMap(positionNormalized.get().y, -1, 1, -u, u, true);
		float z = ofMap(positionNormalized.get().z, -1, 1, -u, u, true);
		setPosition(glm::vec3(x, y, z));
		_setPosition(glm::vec3(x, y, z));
	}

	void refreshPositionToNormalized() {
		ofLogNotice(__FUNCTION__);

		//apply to normalized
		const float u = position.getMax().x; //distance unit assumed the same for the three axis
		float x = ofMap(position.get().x, -u, u, -1, 1, true);
		float y = ofMap(position.get().y, -u, u, -1, 1, true);
		float z = ofMap(position.get().z, -u, u, -1, 1, true);

		float px = positionNormalized.get().x;
		float py = positionNormalized.get().y;
		float pz = positionNormalized.get().z;
		if (px != x || py != y || pz != z) //update only if changed/differs to reduce callbacks
		{
			positionNormalized.set(glm::vec3(x, y, z));
		}
	}

	void refreshScaleFromNormalized() {
		ofLogNotice(__FUNCTION__);

		float s = 1;
		if (scaleNormalized == 0) {
			s = scaleNormalizedPow;
		} else if (scaleNormalized > 0) {
			s = ofMap(scaleNormalized, 0, 1, scaleNormalizedPow, scaleNormalizedPow * scaleNormalizedRatio, true);
		} else if (scaleNormalized < 0) {
			s = ofMap(scaleNormalized, 0, -1, scaleNormalizedPow, scaleNormalizedPow / scaleNormalizedRatio, true);
		}
		setScale(s, s, s);
		_setScale(glm::vec3(s, s, s));
	}

	void refreshEulerRotationFromOfNodeOrientation() {
		ofLogNotice(__FUNCTION__);

		glm::vec3 r = rotationEuler.get();
		_setRotation(r);
	}

	//--

public:
	ofNode & getNode() { return *this; }
	// Exposed to use push/popp matrix:
	// myObject.getNode().transformGL();
	// draw your "transformed" scene
	// myObject.getNode().restoreTransformGL();
};
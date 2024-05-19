#include "mySurfingAppGui.h"
#include "ofxSurfingImGui.h"
#include "ofApp.h"

namespace mySurfingApp
{
	//------------------------------------------------------------------------------------------
	Gui::Gui(ofApp* app) : mainApp(app)
	{
	}

	//------------------------------------------------------------------------------------------
	Gui::~Gui()
	{
	}

	//------------------------------------------------------------------------------------------
	void Gui::setup()
	{
		setupImGui();

		//A.setup();
	}

	//------------------------------------------------------------------------------------------
	void Gui::setupImGui()
	{
		ui = make_unique<SurfingGuiManager>();

		ui->setName("mySurfingAppGui");

		ui->setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);

		ui->addWindowSpecial(bGuiCameras);
		ui->addWindowSpecial(bGuiOutput);
		ui->addWindowSpecial(bGuiSync);
		ui->addWindowSpecial(bGuiTrackerData);
		ui->addWindowSpecial(bGuiTrackerInputs);
		ui->addWindowSpecial(bGuiData);

		ui->setup();

		ui->startup();
	}

	//------------------------------------------------------------------------------------------
	void Gui::draw()
	{
		if (!ui) return;
		if (!bGui) return;
		if (!mainApp) return;

		string s;

		ui->Begin();
		{
			if (ui->BeginWindow(bGui))
			{
				s = "An instantiated class object";
				ui->AddLabelBig(s);
				ui->Add(A.bGui, OFX_IM_TOGGLE);
				ui->AddSpacingBigSeparated();

				s = "Added Special Windows";
				ui->AddLabelBig(s);
				ui->Add(ui->bLinked, OFX_IM_TOGGLE_ROUNDED);
				ui->Add(bGuiCameras);
				ui->Add(bGuiData);
				ui->Add(bGuiOutput);
				ui->Add(bGuiSync);
				ui->Add(bGuiTrackerData);
				ui->Add(bGuiTrackerInputs);

				s = "A Window";
				ui->AddLabelBig(s);
				ui->Add(bGuiSettings, OFX_IM_TOGGLE);
				ui->AddSpacingBigSeparated();

				s = "Parameters from ofApp scope";
				ui->AddLabelBig(s);
				ui->AddGroup(mainApp->parameters);

				ui->EndWindow();
			}

			//--

			if (bGuiSettings) ImGui::SetNextWindowSize({ 200,200 });
			if (ui->BeginWindow(bGuiSettings))
			{
				ui->AddLabel("bGuiSettings");
				ui->Add(mainApp->bEnable1);
				ui->EndWindow();
			}

			//--

			if (bGuiCameras) ImGui::SetNextWindowSize({ 200,200 });
			if (ui->BeginWindowSpecial(bGuiCameras))
			{
				ui->AddLabel("bGuiCameras");
				ui->Add(mainApp->bPrevious);
				ui->Add(mainApp->bNext);
				ui->EndWindowSpecial();
			}

			if (bGuiOutput) ImGui::SetNextWindowSize({ 200,200 });
			if (ui->BeginWindowSpecial(bGuiOutput))
			{
				ui->AddLabel("drawImGuiOutput");
				ui->Add(mainApp->separation, OFX_IM_HSLIDER);
				ui->EndWindowSpecial();
			}

			if (bGuiSync) ImGui::SetNextWindowSize({ 200,200 });
			if (ui->BeginWindowSpecial(bGuiSync))
			{
				ui->AddLabel("drawImGuiSync");
				ui->Add(mainApp->lineWidth, OFX_IM_HSLIDER);
				ui->EndWindowSpecial();
			}

			if (bGuiTrackerData) ImGui::SetNextWindowSize({ 200,200 });
			if (ui->BeginWindowSpecial(bGuiTrackerData))
			{
				ui->AddLabel("drawImGuiTrackerData");
				ui->Add(mainApp->separation, OFX_IM_HSLIDER);
				ui->EndWindowSpecial();
			}

			if (bGuiTrackerInputs) ImGui::SetNextWindowSize({ 200,200 });
			if (ui->BeginWindowSpecial(bGuiTrackerInputs))
			{
				ui->AddLabel("drawImGuiTrackerInputs");
				ui->Add(mainApp->amount, OFX_IM_HSLIDER);
				ui->EndWindowSpecial();
			}

			if (bGuiData) ImGui::SetNextWindowSize({ 200,200 });
			if (ui->BeginWindowSpecial(bGuiData))
			{
				ui->AddLabel("bGuiData");
				ui->Add(mainApp->size, OFX_IM_HSLIDER);
				ui->EndWindowSpecial();
			}
		}
		ui->End();

		//--

		A.drawImGui();
	}

	//------------------------------------------------------------------------------------------
	bool Gui::isMouseOverGui()
	{
		if (!ui) return false;
		return ui->isMouseOverGui();
	}

	//------------------------------------------------------------------------------------------
	bool Gui::isMouseOverInputText()
	{
		if (!ui) return false;
		return ui->isMouseOverInputText();
	}

} // namespace mySurfingApp

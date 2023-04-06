/*

	TODO

	PROFILER
	could be separated to another class

	By default we setup 4 cpu and 4 gpu tasks by default.
	not passed tasks are showed too...we should hide.
	But for now, we can initiate amount of measures on startup:
	T_CPU_SETUP(4);
	T_GPU_SETUP(3);

*/


#pragma once
#include "ofMain.h"

#define SURFING_MAX_FRAME_RATE 60.f

//#define DEBUG_INTERNAL_METRICS // to enable debug params
#define ENABLE_LIST_PLOT

//--

#include "imgui.h"

// Original code from:
// https://github.com/GameTechDev/MetricsGui
#include "metrics_gui.h"

#ifdef DEBUG_INTERNAL_METRICS
#include "surfingMetrics.h"
#endif

// Original code from @Raikiri: 
// https://github.com/Raikiri/LegitProfiler
#include "imgui_profiler.h"
#define PROFILER_DEMO_NUM_PASSES 5
//#define PROFILER_DEMO_NUM_PASSES 3

//-- 

class SurfingDebugger
{
public:
	ofParameter<bool> bGui{ "Debugger", true };
	ofParameter<bool> bGui_Mini{ "Mini", true };
	ofParameter<bool> bGui_Metrics{ "Metrics", true };
	ofParameter<bool> bGui_Profiler{ "Profiler", 1 };
	ofParameter<bool> bAutoResize{ "Auto Resize", true };
	ofParameter<bool> bList{ "List", 1 };
	ofParameter<bool> bFrameRate{ "FrameRate", true };
	ofParameter<bool> bFrameTime{ "FrameTime", false };
	ofParameter<bool> bGraphs{ "Graphs", 1 };
	ofParameter<bool> bProfilerDemo{ "ProfilerDemo", false };
	ofParameter<bool> bDebugMetrics{ "Debug Metrics", false };
	ofParameter<bool> bMinimized{ "bMinimized",false };
	ofParameterGroup params{ "Debugger Settings" };//to avoid repeat names

public:
	SurfingDebugger() {
		setup();
	};

private:
	void setup()
	{
		ofFloatColor c1 = ofColor(ofColor::turquoise, 255);
		ofFloatColor c2 = ofColor(ofColor::orange, 255);

		params.add(bAutoResize);
		params.add(bGui_Metrics);
		params.add(bGui_Profiler);
		params.add(bGui_Mini);
		params.add(bFrameRate);
		params.add(bFrameTime);
		params.add(bGraphs);
		params.add(bList);
		params.add(bDebugMetrics);
		params.add(bMinimized);

		//-

		// FrameTime
		frameTimeMetric.mDescription = "FrameTime";
		frameTimeMetric.mUnits = "s";
		//frameTimeMetric.mFlags = MetricsGuiMetric::USE_SI_UNIT_PREFIX;
		frameTimeMetric.mSelected = 0;
		frameTimeMetric.mColor[0] = c1.r;
		frameTimeMetric.mColor[1] = c1.g;
		frameTimeMetric.mColor[2] = c1.b;
		frameTimeMetric.mColor[3] = c1.a;

		//custom
		frameTimeMetric.mFlags = MetricsGuiMetric::USE_SI_UNIT_PREFIX;
		frameTimeMetric.mFlags |= MetricsGuiMetric::KNOWN_MIN_VALUE | MetricsGuiMetric::KNOWN_MAX_VALUE;
		frameTimeMetric.mKnownMinValue = 0.001f;
		frameTimeMetric.mKnownMaxValue = 0.10f;

		//-

		// FrameRate
		frameRateMetric.mDescription = "FrameRate";
		frameRateMetric.mUnits = "fps";
		//frameRateMetric.mFlags = MetricsGuiMetric::NONE;
		frameRateMetric.mSelected = 0;
		frameRateMetric.mColor[0] = c2.r;
		frameRateMetric.mColor[1] = c2.g;
		frameRateMetric.mColor[2] = c2.b;
		frameRateMetric.mColor[3] = c2.a;

		//custom
		frameRateMetric.mFlags = MetricsGuiMetric::KNOWN_MAX_VALUE;
		frameRateMetric.mFlags |= MetricsGuiMetric::KNOWN_MIN_VALUE;
		frameRateMetric.mKnownMaxValue = SURFING_MAX_FRAME_RATE;
		frameRateMetric.mKnownMinValue = 0.f;

		//-

		frameTimePlot.mShowAverage = 0;
		frameTimePlot.mShowLegendAverage = 0;
		//frameTimePlot.mShowLegendAverage = 1;//avg label is weird/wrong..
		frameTimePlot.mBarGraph = 0;
		frameTimePlot.mShowLegendColor = 0;
		frameTimePlot.mShowInlineGraphs = 0;
		frameTimePlot.mShowOnlyIfSelected = 0;

		frameRatePlot.mShowAverage = 0;
		frameRatePlot.mShowLegendAverage = 0;
		frameRatePlot.mBarGraph = 0;
		frameRatePlot.mShowLegendColor = 0;
		frameRatePlot.mShowInlineGraphs = true;
		frameRatePlot.mShowOnlyIfSelected = 0;

		//frameRatePlot.mMaxValue = 60;
		//frameRatePlot.mMinValue = 0;

		//--

		frameRatePlot.AddMetric(&frameRateMetric);
		frameTimePlot.AddMetric(&frameTimeMetric);

		frameTimePlot.LinkLegends(&frameRatePlot);

		//--

#ifdef ENABLE_LIST_PLOT
		listPlot.AddMetric(&frameRateMetric);
		listPlot.AddMetric(&frameTimeMetric);
		//listPlot.SortMetricsByName();

		listPlot.mShowInlineGraphs = 0;
#endif

		//--

		// Profiler (cpu/gpu)
		//customize max tasks. to improve aesthetics..
		setupProfileTasks(4, 4);
		//setupProfileTasks(3, 3);
		//setupProfileTasks();
	};

public:
	~SurfingDebugger() {
	};

	//--

	// Profiler

private:
	ImGuiEx::ProfilersWindow profiler;
	bool bProfilerActive = true;
	int PROFILER_DEMO_NUM_PASSES_CPU = PROFILER_DEMO_NUM_PASSES;
	int PROFILER_DEMO_NUM_PASSES_GPU = PROFILER_DEMO_NUM_PASSES;

	//--

private:
	//Debug settings
#ifdef DEBUG_INTERNAL_METRICS
	surfingMetrics metrics;
#endif

	MetricsGuiMetric frameTimeMetric;
	MetricsGuiMetric frameRateMetric;

	MetricsGuiPlot frameTimePlot;
	MetricsGuiPlot frameRatePlot;

#ifdef ENABLE_LIST_PLOT
	MetricsGuiPlot listPlot;
#endif

	//private:
public:
	void update()
	{
		if (!bGui) return;

		//--

		// Metrics

		frameRateMetric.AddNewValue(ofGetFrameRate());

		//float v = ((float)ofGetLastFrameTime());
		//float v = (1.f / ofGetFrameRate());
		float v = 1.f / (float)(ImGui::GetIO().Framerate);
		frameTimeMetric.AddNewValue(v);

		//--

		frameTimePlot.UpdateAxes();
		frameRatePlot.UpdateAxes();

#ifdef ENABLE_LIST_PLOT
		if (bList || bGui_Mini) listPlot.UpdateAxes();
#endif

		//--

		// Profiler

		if (bGui_Profiler)
		{
			//TODO:
			//updateProfileTasksCpu();

			// Demo
			if (bProfilerDemo) updateDemoProfiler();
		}
	};

public:
	//TODO; passing ui?
	//void draw(SurfingGuiManager *ui)
	//void draw(SurfingGuiManager *ui = nullptr)
	//void draw(ofxSurfingImGui *ui = nullptr)
	//void draw(ofxSurfingImGui ui)

	void drawImGui()
	{
		if (!bGui) return;

		if (!(bMinimized && bGui_Mini))
		{

#ifdef DEBUG_INTERNAL_METRICS
			metrics.draw();
#endif
			static bool p_open = true;

			float pd = 8;
			ImVec2 sz(500, 150);
			ImVec2 pos(ofGetWidth() - sz.x - pd, pd);
			ImGuiCond cond = ImGuiCond_FirstUseEver;
			if (p_open)
			{
				ImGui::SetNextWindowPos(pos, cond);
				ImGui::SetNextWindowSize(sz, cond);
			}

			ImGuiWindowFlags flags = ImGuiWindowFlags_None;
			if (bAutoResize) flags += ImGuiWindowFlags_AlwaysAutoResize;

			if (bGraphs) {
				ImVec2 szMin(300, 190);
				ImVec2 szMax(1000, 1000);
				ImGui::SetNextWindowSizeConstraints(szMin, szMax);
			}

			//p_open = bOpen;
			bool bOpen = ImGui::Begin("Debugger", &p_open, flags);
			//bool bOpen = ImGui::Begin("Debugger");

			//bool bOpen = true;
			//if (ui != nullptr) bOpen = ui->BeginWindow(bGui);
			//else bOpen = ImGui::Begin("Debugger");

			if (bOpen)
			{
				bool b = true;

				//if (ui != nullptr) {
				//	b = ui->isMaximized();
				//}

				if (b)
				{
					float w = 70;
					ImVec2 sz(w, ofxImGuiSurfing::getWidgetsHeightUnit());

					ofxImGuiSurfing::AddBigToggle(bGui_Metrics, sz);
					ImGui::SameLine();
					ofxImGuiSurfing::AddBigToggle(bGui_Profiler, sz);
					ImGui::SameLine();
					ofxImGuiSurfing::AddBigToggle(bGui_Mini, sz);
					ImGui::SameLine();
					ofxImGuiSurfing::AddParameter(bAutoResize);

					//ofxImGuiSurfing::AddParameter(bProfilerDemo);
					//ImGui::Checkbox("Controls", &profiler.bShowControls);
					//ofxImGuiSurfing::AddParameter(bDebugMetrics);

					if (bGui_Metrics) {
						//ImGui::SameLine();
						ofxImGuiSurfing::AddBigToggle(bList, sz);
						ImGui::SameLine();
						ofxImGuiSurfing::AddBigToggle(bGraphs, sz);
						if (bGraphs) {
							ImGui::SameLine();
							ofxImGuiSurfing::AddParameter(bFrameRate);
							ImGui::SameLine();
							ofxImGuiSurfing::AddParameter(bFrameTime);
						}
						//ImGui::SameLine();
					}
				}

				//--

#ifdef ENABLE_LIST_PLOT
				if (bList)
				{
					listPlot.DrawList();
					//listPlot.DrawHistory();
				}
#endif

				//--

				if (bGraphs)
				{
					if (bFrameRate) frameRatePlot.DrawHistory();
					if (bFrameTime) frameTimePlot.DrawHistory();
				}

			}

			//--

			ImGui::End();

			if (bDebugMetrics) ImGui::ShowMetricsWindow();

			//--

			if (bGui_Profiler)
			{
				drawImGuiProfiler();
			}
		}

		//--

		if (bGui_Mini)
		{
			drawImGuiMini();
		}
	};

	//--

	void drawImGuiMini()
	{
		static bool p_open = true;
		if (p_open != bGui_Mini) p_open = bGui_Mini;

		ImVec2 sz(260, 150);
		float pd = 8;
		ImVec2 pos(ofGetWidth() / 2 - sz.x / 2, ofGetHeight() / 2 - sz.y / 2);
		ImGuiCond cond = ImGuiCond_FirstUseEver;
		if (p_open)
		{
			ImGui::SetNextWindowPos(pos, cond);
			ImGui::SetNextWindowSize(sz, cond);

			ImVec2 szMin(300, 155);
			ImVec2 szMax(350, 300);
			ImGui::SetNextWindowSizeConstraints(szMin, szMax);
		}

		ImGuiWindowFlags flags = ImGuiWindowFlags_None;
		if (bAutoResize) flags += ImGuiWindowFlags_AlwaysAutoResize;
		//flags += ImGuiWindowFlags_AlwaysAutoResize;

		bool bOpen = ImGui::Begin("Debugger Mini", &p_open, flags);
		if (bOpen)
		{
			// super mini toggle
			// on top-right, mini, no label
			{
				//move up
				ImVec2 diff{ 0, -5 };
				auto pf = ImGui::GetCursorPos();
				auto pt = pf + diff;
				ImGui::SetCursorPos(pt);
				//set size
				const float hu = ImGui::GetFrameHeight();
				const float ht = 0.8f * hu;
				const float w = 1.55f * ht;
				//move right
				float wwidget = ImGui::GetContentRegionAvail().x - w;
				ImGui::Dummy(ImVec2{ wwidget,0 });
				ImGui::SameLine();
				ofxImGuiSurfing::AddToggleRoundedButton(bMinimized, ht, true, true);
			}

			listPlot.DrawList();
			ImGui::Spacing();
			ImGui::Separator();
			profiler.RenderMini();

		}
		ImGui::End();

		if (bGui_Mini != p_open) bGui_Mini = p_open;
	}

	void drawImGuiProfiler()
	{
		//updateProfileTasksGpu();

		// Demo
		if (bProfilerDemo) drawDemoProfiler();

		if (bProfilerActive != bGui_Profiler) bProfilerActive = bGui_Profiler;
		if (bProfilerActive)
		{
			profiler.Render(&bProfilerActive);

		}
		if (bGui_Profiler != bProfilerActive) bGui_Profiler = bProfilerActive;
	};

	//--

	// Cpu
	ImGuiEx::ProfilerTask* ptCpu;
	void startProfilerTaskCpu(int i, string name)
	{
		ptCpu[i].color = profiler.cpuGraph.colors[i];
		//ptCpu[i].color = profiler.cpuGraph.colors[static_cast<unsigned int>(8 + i % 8)];

		ptCpu[i].startTime = ofGetElapsedTimef();
		ptCpu[i].name = name + "_" + ofToString(i);
		//ptCpu[i].name = "CPU " + name + "_" + ofToString(i);
		//ptCpu[i].name = "cpuTask" + ofToString(i);
	};
	void endProfilerTaskCpu(int i)
	{
		ptCpu[i].endTime = ofGetElapsedTimef();
	};

	//--

	// Gpu
	ImGuiEx::ProfilerTask* ptGpu;
	void startProfilerTaskGpu(int i, string name)
	{
		ptGpu[i].color = profiler.gpuGraph.colors[i];
		//ptGpu[i].color = profiler.gpuGraph.colors[static_cast<unsigned int>(8 + i % 8)];

		ptGpu[i].startTime = ofGetElapsedTimef();
		ptGpu[i].name = name + "_" + ofToString(i);
		//ptGpu[i].name = "GPU " + name + "_" + ofToString(i);
		//ptGpu[i].name = "gpuTask" + ofToString(i);
	};
	void endProfilerTaskGpu(int i)
	{
		ptGpu[i].endTime = ofGetElapsedTimef();
	};

	//--

public:
	void setupProfileTasksCpu(size_t numCpuTasks)
	{
		PROFILER_DEMO_NUM_PASSES_CPU = numCpuTasks;
		setupProfileTasks();
	};
	void setupProfileTasksGpu(size_t numGpuTasks)
	{
		PROFILER_DEMO_NUM_PASSES_GPU = numGpuTasks;
		setupProfileTasks();
	};
private:
	void setupProfileTasks(size_t numCpuTasks, size_t numGpuTasks)
	{
		PROFILER_DEMO_NUM_PASSES_CPU = numCpuTasks;
		PROFILER_DEMO_NUM_PASSES_GPU = numGpuTasks;
		setupProfileTasks();
	};
	void setupProfileTasks()
	{
		ptCpu = new ImGuiEx::ProfilerTask[PROFILER_DEMO_NUM_PASSES_CPU];
		ptGpu = new ImGuiEx::ProfilerTask[PROFILER_DEMO_NUM_PASSES_GPU];
	};

	//TODO: could be auto called..
public:
	void updateProfileTasksCpu()//must call after all measurements done.call after update
	{
		profiler.cpuGraph.LoadFrameData(ptCpu, PROFILER_DEMO_NUM_PASSES_CPU);
	};
	void updateProfileTasksGpu()//must call after all measurements done. call after draw
	{
		profiler.gpuGraph.LoadFrameData(ptGpu, PROFILER_DEMO_NUM_PASSES_GPU);
	};

	//--

	// Macros

	// call on setup to define how much measurements we want to use
#define T_CPU_SETUP(x)		ui.debugger.setupProfileTasksCpu(x);
#define T_GPU_SETUP(x)		ui.debugger.setupProfileTasksGpu(x);

#define T_CPU_START(x,n)	ui.debugger.startProfilerTaskCpu(x, n);
#define T_CPU_END(x)		ui.debugger.endProfilerTaskCpu(x);

#define T_GPU_START(x,n)	ui.debugger.startProfilerTaskGpu(x, n);
#define T_GPU_END(x) 		ui.debugger.endProfilerTaskGpu(x);

//private:
//	bool bDoneUpdateProfileTasksCpu = false;
//	bool bDoneUpdateProfileTasksGpu = false;

//--

public:

	// Demo

	void updateDemoProfiler()
	{
		ImGuiEx::ProfilerTask* ptCpu_ = new ImGuiEx::ProfilerTask[PROFILER_DEMO_NUM_PASSES_CPU];

		for (size_t i = 0; i < PROFILER_DEMO_NUM_PASSES_CPU; i++)
		{
			ptCpu_[i].color = profiler.cpuGraph.colors[i];
			//ptCpu_[i].color = profiler.cpuGraph.colors[static_cast<unsigned int>(8 + i % 8)];

			ptCpu_[i].startTime = ofGetElapsedTimef();
			ptCpu_[i].name = "cpuTask" + ofToString(i);

			int t = ofRandom(9);
			ofSleepMillis(t);

			ptCpu_[i].endTime = ofGetElapsedTimef();
		}

		profiler.cpuGraph.LoadFrameData(ptCpu_, PROFILER_DEMO_NUM_PASSES_CPU);
	};

	void drawDemoProfiler()
	{
		ImGuiEx::ProfilerTask* ptGpu_ = new ImGuiEx::ProfilerTask[PROFILER_DEMO_NUM_PASSES_GPU];

		for (size_t i = 0; i < PROFILER_DEMO_NUM_PASSES_GPU; i++)
		{
			ptGpu_[i].color = profiler.gpuGraph.colors[i];
			//ptGpu_[i].color = profiler.gpuGraph.colors[static_cast<unsigned int>(i % 16)];

			ptGpu_[i].startTime = ofGetElapsedTimef();
			ptGpu_[i].name = "gpuTask" + ofToString(i);

			int t = ofRandom(i * 2);
			ofSleepMillis(t);

			ptGpu_[i].endTime = ofGetElapsedTimef();
		}

		profiler.gpuGraph.LoadFrameData(ptGpu_, PROFILER_DEMO_NUM_PASSES_GPU);
	};
};

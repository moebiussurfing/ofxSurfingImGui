// /*
// Copyright 2017-2018 Intel Corporation

// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// */

//     // Set up sample metrics frameTime and sine.
//     //
//     // Note: MetricsGuiPlot does not assume ownership over added metrics, so it
//     // is the users responsibility to manage the lifetime of MetricsGuiMetric
//     // instances.
//     MetricsGuiMetric frameTimeMetric("Frame time", "s", MetricsGuiMetric::USE_SI_UNIT_PREFIX);
//     frameTimeMetric.mSelected = true;

//     MetricsGuiMetric sineMetric("Sine", "", MetricsGuiMetric::KNOWN_MIN_VALUE | MetricsGuiMetric::KNOWN_MAX_VALUE);
//     sineMetric.mKnownMinValue = -1.f;
//     sineMetric.mKnownMaxValue = 1.f;
//     sineMetric.mSelected = true;

//     // Metrics are drawn using a MetricsGuiPlot.  MetricsGuiPlot holds pointers
//     // to one or more metrics, and maintains value extents for the metrics
//     // added to it.
//     MetricsGuiPlot frameTimePlot;
//     frameTimePlot.mShowAverage = true;
//     frameTimePlot.mShowLegendAverage = true;
//     frameTimePlot.mShowLegendColor = false;
//     frameTimePlot.AddMetric(&frameTimeMetric);

//     MetricsGuiPlot sinePlot;
//     sinePlot.mShowAverage = true;
//     sinePlot.mShowLegendAverage = true;
//     sinePlot.mShowLegendColor = false;
//     sinePlot.AddMetric(&sineMetric);

//     // If you link the legends of two or more plots, then their labels will all
//     // be aligned.
//     frameTimePlot.LinkLegends(&sinePlot);

//     MetricsGuiPlot listPlot;
//     listPlot.mShowInlineGraphs = true;
//     listPlot.mShowOnlyIfSelected = true;
//     listPlot.mShowLegendColor = false;
//     listPlot.mShowLegendDesc = false;
//     listPlot.mShowLegendMin = true;
//     listPlot.mShowLegendMax = true;
//     listPlot.AddMetric(&frameTimeMetric);
//     listPlot.AddMetric(&sineMetric);
//     listPlot.SortMetricsByName();

//     MetricsGuiPlot combinedPlot;
//     combinedPlot.mBarGraph = true;
//     combinedPlot.mStacked = true;
//     combinedPlot.mShowAverage = true;
//     combinedPlot.mShowLegendAverage = true;
//     combinedPlot.mShowLegendUnits = false;
//     combinedPlot.mPlotRowCount = 7;
//     combinedPlot.AddMetric(&frameTimeMetric);
//     combinedPlot.AddMetric(&sineMetric);

//     // Create D3D implementation instance
//     char title[1024] = {};
//     auto titleIdx = sprintf_s(title, "MetricsGui sample");


//         ImGui::NewFrame();

//         // Update metrics values
//         LARGE_INTEGER t;
//         QueryPerformanceCounter(&t);
//         frameTimeMetric.AddNewValue(1.f / ImGui::GetIO().Framerate);
//         sineMetric.AddNewValue((float) sin((double) (t.QuadPart - t0.QuadPart) / freq.QuadPart));

//         // After adding metric values, update all the plot axes.
//         frameTimePlot.UpdateAxes();
//         sinePlot.UpdateAxes();
//         listPlot.UpdateAxes();
//         combinedPlot.UpdateAxes();

//         // Create a ImGui window to display the metrics in.
//         if (ImGui::Begin("Metrics Window")) {

//             if (ImGui::CollapsingHeader("MetricsGuiPlot::DrawList()", ImGuiTreeNodeFlags_CollapsingHeader | ImGuiTreeNodeFlags_DefaultOpen)) {
//                 if (ImGui::TreeNode("Plot options")) {
//                     int plotRowCount = (int) listPlot.mInlinePlotRowCount;
//                     int vbarMinWidth = (int) listPlot.mVBarMinWidth;
//                     int vbarGapWidth = (int) listPlot.mVBarGapWidth;
//                     ImGui::SliderFloat("mBarRounding##0",      &listPlot.mBarRounding, 0.f, 0.5f * ImGui::GetTextLineHeight(), "%.1f");
//                     ImGui::SliderFloat("mRangeDampening##0",   &listPlot.mRangeDampening, 0.f, 1.f, "%.2f");
//                     ImGui::SliderInt("mInlinePlotRowCount##0", &plotRowCount, 1, 10);
//                     ImGui::SliderInt("mVBarMinWidth##0",       &vbarMinWidth, 1, 20);
//                     ImGui::SliderInt("mVBarGapWidth##0",       &vbarGapWidth, 0, 10);
//                     ImGui::Checkbox("mShowAverage##0",         &listPlot.mShowAverage);
//                     ImGui::Checkbox("mShowInlineGraphs##0",    &listPlot.mShowInlineGraphs);
//                     ImGui::Checkbox("mShowOnlyIfSelected##0",  &listPlot.mShowOnlyIfSelected);
//                     ImGui::Checkbox("mShowLegendDesc##0",      &listPlot.mShowLegendDesc);
//                     ImGui::Checkbox("mShowLegendColor##0",     &listPlot.mShowLegendColor);
//                     ImGui::Checkbox("mShowLegendUnits##0",     &listPlot.mShowLegendUnits);
//                     ImGui::Checkbox("mShowLegendAverage##0",   &listPlot.mShowLegendAverage);
//                     ImGui::Checkbox("mShowLegendMin##0",       &listPlot.mShowLegendMin);
//                     ImGui::Checkbox("mShowLegendMax##0",       &listPlot.mShowLegendMax);
//                     ImGui::Checkbox("mBarGraph##0",            &listPlot.mBarGraph);
//                     listPlot.mInlinePlotRowCount = (uint32_t) plotRowCount;
//                     listPlot.mVBarMinWidth       = (uint32_t) vbarMinWidth;
//                     listPlot.mVBarGapWidth       = (uint32_t) vbarGapWidth;
//                     ImGui::Spacing();
//                     ImGui::TreePop();
//                 }
//                 listPlot.DrawList();
//             }
//             ImGui::Spacing();

//             if (ImGui::CollapsingHeader("MetricsGuiPlot::DrawHistory()", ImGuiTreeNodeFlags_CollapsingHeader | ImGuiTreeNodeFlags_DefaultOpen)) {
//                 ImGui::Separator();
//                 ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_FirstUseEver);
//                 if (ImGui::TreeNode("Individual metrics")) {
//                     if (ImGui::TreeNode("Plot options")) {
//                         int plotRowCount = (int) frameTimePlot.mPlotRowCount;
//                         int vbarMinWidth = (int) frameTimePlot.mVBarMinWidth;
//                         int vbarGapWidth = (int) frameTimePlot.mVBarGapWidth;
//                         ImGui::SliderFloat("mBarRounding##1",     &frameTimePlot.mBarRounding, 0.f, 0.5f * ImGui::GetTextLineHeight(), "%.1f");
//                         ImGui::SliderFloat("mRangeDampening##1",  &frameTimePlot.mRangeDampening, 0.f, 1.f, "%.2f");
//                         ImGui::SliderInt("mPlotRowCount##1",      &plotRowCount, 1, 10);
//                         ImGui::SliderInt("mVBarMinWidth##1",      &vbarMinWidth, 1, 20);
//                         ImGui::SliderInt("mVBarGapWidth##1",      &vbarGapWidth, 0, 10);
//                         ImGui::Checkbox("mShowAverage##1",        &frameTimePlot.mShowAverage);
//                         ImGui::Checkbox("mShowOnlyIfSelected##1", &frameTimePlot.mShowOnlyIfSelected);
//                         ImGui::Checkbox("mShowLegendDesc##1",     &frameTimePlot.mShowLegendDesc);
//                         ImGui::Checkbox("mShowLegendColor##1",    &frameTimePlot.mShowLegendColor);
//                         ImGui::Checkbox("mShowLegendUnits##1",    &frameTimePlot.mShowLegendUnits);
//                         ImGui::Checkbox("mShowLegendAverage##1",  &frameTimePlot.mShowLegendAverage);
//                         ImGui::Checkbox("mShowLegendMin##1",      &frameTimePlot.mShowLegendMin);
//                         ImGui::Checkbox("mShowLegendMax##1",      &frameTimePlot.mShowLegendMax);
//                         ImGui::Checkbox("mBarGraph##1",           &frameTimePlot.mBarGraph);
//                         ImGui::Spacing();
//                         frameTimePlot.mPlotRowCount  = (uint32_t) plotRowCount;
//                         frameTimePlot.mVBarMinWidth  = (uint32_t) vbarMinWidth;
//                         frameTimePlot.mVBarGapWidth  = (uint32_t) vbarGapWidth;
//                         sinePlot.mBarRounding        = frameTimePlot.mBarRounding;
//                         sinePlot.mRangeDampening     = frameTimePlot.mRangeDampening;
//                         sinePlot.mPlotRowCount       = frameTimePlot.mPlotRowCount;
//                         sinePlot.mVBarMinWidth       = frameTimePlot.mVBarMinWidth;
//                         sinePlot.mVBarGapWidth       = frameTimePlot.mVBarGapWidth;
//                         sinePlot.mShowAverage        = frameTimePlot.mShowAverage;
//                         sinePlot.mShowOnlyIfSelected = frameTimePlot.mShowOnlyIfSelected;
//                         sinePlot.mShowLegendDesc     = frameTimePlot.mShowLegendDesc;
//                         sinePlot.mShowLegendColor    = frameTimePlot.mShowLegendColor;
//                         sinePlot.mShowLegendUnits    = frameTimePlot.mShowLegendUnits;
//                         sinePlot.mShowLegendAverage  = frameTimePlot.mShowLegendAverage;
//                         sinePlot.mShowLegendMin      = frameTimePlot.mShowLegendMin;
//                         sinePlot.mShowLegendMax      = frameTimePlot.mShowLegendMax;
//                         sinePlot.mBarGraph           = frameTimePlot.mBarGraph;
//                         ImGui::TreePop();
//                     }
//                     frameTimePlot.DrawHistory();
//                     sinePlot.DrawHistory();
//                     ImGui::TreePop();
//                 }

//                 ImGui::Separator();
//                 ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_FirstUseEver);
//                 if (ImGui::TreeNode("Combined metrics")) {
//                     if (ImGui::TreeNode("Plot options")) {
//                         int plotRowCount = (int) combinedPlot.mPlotRowCount;
//                         int vbarMinWidth = (int) combinedPlot.mVBarMinWidth;
//                         int vbarGapWidth = (int) combinedPlot.mVBarGapWidth;
//                         ImGui::SliderFloat("mBarRounding##2",     &combinedPlot.mBarRounding, 0.f, 0.5f * ImGui::GetTextLineHeight(), "%.1f");
//                         ImGui::SliderFloat("mRangeDampening##2",  &combinedPlot.mRangeDampening, 0.f, 1.f, "%.2f");
//                         ImGui::SliderInt("mPlotRowCount##2",      &plotRowCount, 1, 10);
//                         ImGui::SliderInt("mVBarMinWidth##2",      &vbarMinWidth, 1, 20);
//                         ImGui::SliderInt("mVBarGapWidth##2",      &vbarGapWidth, 0, 10);
//                         ImGui::Checkbox("mShowAverage##2",        &combinedPlot.mShowAverage);
//                         ImGui::Checkbox("mShowOnlyIfSelected##2", &combinedPlot.mShowOnlyIfSelected);
//                         ImGui::Checkbox("mShowLegendDesc##2",     &combinedPlot.mShowLegendDesc);
//                         ImGui::Checkbox("mShowLegendColor##2",    &combinedPlot.mShowLegendColor);
//                         ImGui::Checkbox("mShowLegendUnits##2",    &combinedPlot.mShowLegendUnits);
//                         ImGui::Checkbox("mShowLegendAverage##2",  &combinedPlot.mShowLegendAverage);
//                         ImGui::Checkbox("mShowLegendMin##2",      &combinedPlot.mShowLegendMin);
//                         ImGui::Checkbox("mShowLegendMax##2",      &combinedPlot.mShowLegendMax);
//                         ImGui::Checkbox("mBarGraph##2",           &combinedPlot.mBarGraph);
//                         ImGui::Checkbox("mStacked##2",            &combinedPlot.mStacked);
//                         ImGui::Spacing();
//                         combinedPlot.mPlotRowCount = (uint32_t) plotRowCount;
//                         combinedPlot.mVBarMinWidth = (uint32_t) vbarMinWidth;
//                         combinedPlot.mVBarGapWidth = (uint32_t) vbarGapWidth;
//                         ImGui::TreePop();
//                     }
//                     combinedPlot.DrawHistory();
//                     ImGui::TreePop();
//                 }
//             }
//             ImGui::Spacing();
//         }
//         ImGui::End();

//         ImGui::EndFrame();
//         ImGui::Render();

//         // Render the scene (a single triangle in this sample).
//         implD3D->Render(resourcesIndex);
//     }

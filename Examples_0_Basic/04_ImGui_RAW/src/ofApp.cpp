#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    data.reserve(20);
    data.resize(20);

    for (int i = 0; i < data.size(); ++i) {
        data[i] = { i + 1, "Name " + std::to_string(i + 1), i * 10.0f, i * 1.0e5, i * 100, "Description " + std::to_string(i + 1) };

        ofLogNotice() << data[i].id<<","<<data[i].name<<","<<data[i].value<<","<<data[i].largeValue<<","<<data[i].anotherInt<<","<<data[i].description;
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		/* Put windows here */

		if (ui.BeginWindow(bGui))
		{
            ui.AddAutoResizeToggle();
            ui.AddSpacing();

			/* Put RAW Dear ImGui widgets here. */
            /* No need to handle the window as we are using ofxSurfingImGui */

            ShowExampleTable();

			ui.EndWindow();
		}

        // RAW Dear ImGui with his window management
        ImGui::ShowDemoWindow();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == ' ') bGui = !bGui;
}

// Function to display a table with data
//--------------------------------------------------------------
void ofApp::ShowExampleTable() {
    //// Dear ImGui window also usable
    //// Begin the ImGui frame
    //ImGui::Begin("Example Table");

    // Create a table with 10 columns
    if (ImGui::BeginTable("MyTable", 10)) {
        // Setup the table columns
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Value");
        ImGui::TableSetupColumn("Large Value");
        ImGui::TableSetupColumn("Another Int");
        ImGui::TableSetupColumn("Description");
        // Add more columns as needed
        for (int col = 6; col < 10; ++col) {
            ImGui::TableSetupColumn(("Column " + std::to_string(col)).c_str());
        }

        // Display the headers
        ImGui::TableHeadersRow();

        // Display the data rows
        for (const auto& entry : data) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn(); ImGui::Text("%d", entry.id);
            ImGui::TableNextColumn(); ImGui::Text("%s", entry.name.c_str());
            ImGui::TableNextColumn(); ImGui::Text("%.1f", entry.value);
            ImGui::TableNextColumn(); ImGui::Text("%.2f", entry.largeValue);
            ImGui::TableNextColumn(); ImGui::Text("%d", entry.anotherInt);
            ImGui::TableNextColumn(); ImGui::Text("%s", entry.description.c_str());
            // Add more data columns if necessary
            for (int col = 6; col < 10; ++col) {
                ImGui::TableNextColumn(); ImGui::Text("Data %d", col);
            }
        }

        // End the table
        ImGui::EndTable();
    }

    //// Dear ImGui window also usable
    //// End the ImGui frame
    //ImGui::End();
}


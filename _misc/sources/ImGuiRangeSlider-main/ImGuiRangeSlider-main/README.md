# ImGuiRangeSlider
A range slider for imgui
<pre>
    int max = 10000;
    int min = 1;
    static int ilow = 1, ihigh = 5000;
    static int ilow1 = 1, ihigh1 = 5000;
    static int ilow2 = 2, ihigh2 = 5000;
    static float flow = 1, fhigh = 5000;
    static float flow1 = 1, fhigh1 = 5000;
    static float flow2 = 1, fhigh2 = 5000;
    ImGui::RangeSliderInt("CMDS", min, max, ilow, ihigh);
    ImGui::RangeSliderInt("CMDS1", min, max, ilow1, ihigh1);
    ImGui::RangeSliderInt("CMDS2", min, max, ilow2, ihigh2);
    ImGui::RangeSliderFloat("CMDS3f", min, max, flow2, fhigh2);
    ImGui::RangeSliderFloat("CMDS4f", min, max, flow1, fhigh1);
    ImGui::RangeSliderFloat("CMDS5f", min, max, flow, fhigh);
    
    basic sample usage
    </pre>
![range selector](https://user-images.githubusercontent.com/16273696/130307924-c78bb58e-19c0-4b39-a547-1c1d003efa09.png)

    

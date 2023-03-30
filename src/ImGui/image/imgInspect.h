/*

	A modified version by @moebiusSurfing

	Added 24 bits format.
	Added exposed public: bool bDebug, int* zoomSize_, int* zoomRectangleWidth_, ofColor* c
	..etc

*/


// https://github.com/CedricGuillemet/imgInspect
//
// The MIT License(MIT)
//
// Copyright(c) 2019 Cedric Guillemet
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


/*

	Example

	Image pickerImage;
	ImGui::ImageButton(pickerImage.textureID, ImVec2(pickerImage.mWidth, pickerImage.mHeight));

	ImGuiIO& io = ImGui::GetIO();
	ImRect rc = ImRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
	ImVec2 mouseUVCoord = (io.MousePos - rc.Min) / rc.GetSize();
	mouseUVCoord.y = 1.f - mouseUVCoord.y;


	if (io.KeyShift && io.MouseDown[0] && mouseUVCoord.x >= 0.f && mouseUVCoord.y >= 0.f)
	{
			int width = pickerImage.mWidth;
			int height = pickerImage.mHeight;

			imageInspect(width, height, pickerImage.GetBits(), mouseUVCoord, displayedTextureSize);
	}

*/


//--

#pragma once

#include "ofMain.h"

#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"

//#include <algorithm>

namespace ImageInspect
{
	inline float getFadeBlink(float min = 0.20, float max = 0.80, float freq = 0.15) {
		float a = ofMap(glm::sin(freq * ofGetFrameNum()), -1, 1, min, max);
		return a;
	}

	//--

	// draw inspector and pick the central color
	inline void inspect(const int width,
		const int height,
		const unsigned char* const bits,
		ImVec2 mouseUVCoord_,
		ImVec2 displayedTextureSize,
		int zoomSize_,
		int zoomRectangleWidth_,
		bool b24bits = false,//default is 32bit
		bool bDebug = false,
		bool bDebugAdvanced = false,
		ofColor* c = nullptr
	)
	{
		int zoomSize = zoomSize_;
		float zoomRectangleWidth = zoomRectangleWidth_;

		//--

		// clamp
		ImClamp(mouseUVCoord_, ImVec2{ 0,0 }, ImVec2{ 1,1 });
		ImVec2 mouseUVCoord = mouseUVCoord_;

		// clamp the zoom zone inside the image
		const int basex = ImClamp(int(mouseUVCoord.x * width), zoomSize, width - zoomSize);
		const int basey = ImClamp(int(mouseUVCoord.y * height), zoomSize, height - zoomSize);

		const float quadWidth = zoomRectangleWidth / float(zoomSize * 2 + 1);
		const ImVec2 quadSize(quadWidth, quadWidth);

		int npx = zoomRectangleWidth / quadWidth;
		int pixCenterRect = ((npx * npx) / 2) + 0;
		int pixCenter;
		static ImColor colorCenter;

		//--

		if (bDebug)
		{
			ImVec2 size_min{ zoomRectangleWidth + 150, -1 };
			ImVec2 size_max{ 1000,1000 };
			ImGui::SetNextWindowSizeConstraints(size_min, size_max);
		}

		//--

		ImGui::BeginTooltip();
		{
			if (!bDebug) {
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
				ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
				ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 0);
				ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0, 0));
			}
			{
				ImGui::BeginGroup();
				{
					ImDrawList* draw_list = ImGui::GetWindowDrawList();

					// 1. Magnifier

					// bitmap zoom
					ImGui::InvisibleButton("AnotherInvisibleMan", ImVec2(zoomRectangleWidth, zoomRectangleWidth));
					const ImRect pickRc(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());

					// bg box
					//ImU32 c = 0xFF000000;
					ImU32 c = ImColor(0, 0, 255, 255);//0xFF000000
					draw_list->AddRectFilled(pickRc.Min, pickRc.Max, c);

					// draw each big pixel
					int count = 0; // additional count rect pixels to get the center color
					pixCenter = pixCenterRect + basex * basey;

					for (int y = -zoomSize; y <= zoomSize; y++)
					{
						for (int x = -zoomSize; x <= zoomSize; x++)
						{
							// fix
							//uint32_t texel = ((uint32_t*)bits)[(basey - y) * width + x + basex];

							size_t i = (basey - y) * width + x + basex;

							// clamp index
							size_t sz = width * height;
							i = MIN(i, sz - 1);
							i = MAX(i, 0);

							// color
							//uint32_t texel = ((uint32_t*)bits)[i];
							uint32_t texel;

							if (b24bits) // 24 bits
							{
								const uint8_t* pixel = bits + i * 3;
								texel = (pixel[2] << 16) | (pixel[1] << 8) | pixel[0];
								const ImVec4 ct = ImColor(texel);
								texel = GetColorU32(ImVec4(ct.x, ct.y, ct.z, 1.f));//add alpha
							}
							else // 32 bits
							{
								texel = ((uint32_t*)bits)[i];
							}

							// Draw each big pixel as a rectangle

							ImVec2 pos;
							bool bflip = 1;
							if (bflip)
							{
								// mirror y 
								pos = ImVec2(pickRc.Min.x, pickRc.Max.y) + ImVec2(float(x + zoomSize), -1 + float(-y - zoomSize)) * quadSize;
							}
							else
							{
								// y flipped
								pos = pickRc.Min + ImVec2(float(x + zoomSize), float(y + zoomSize)) * quadSize;
							}

							draw_list->AddRectFilled(pos, pos + quadSize, texel);

							// Get this pixel! is the center one. the same over mouse pointer.
							if (count == pixCenterRect) {
								//pixCenter = count;
								colorCenter = ImColor(texel);
							}

							count++;
						}
					}

					// center quad
					if (1)
					{
						ImGui::SameLine();

						const ImVec2 pos = pickRc.Min + ImVec2(float(zoomSize), float(zoomSize)) * quadSize;

						//one color with blink alpha
						//int a = 255 * getFadeBlink();
						//ImU32 c;
						//if (0) c = ImColor(0, 0, 0, a);//black
						//else c = ImColor(255, 255, 255, a);//white
						////c = ImColor(255, 0, 0, a);//red

						//alternate b/w
						int v1 = 0;
						int v2 = 255;
						int v = ImLerp(v1, v2, getFadeBlink(0, 1, 0.15f * 1));
						float a = getFadeBlink(0.2, 0.8, 0.15f * 0.5f);
						a *= getFadeBlink(0, 0.8, 0.15f * 0.5f);
						ImU32 c = IM_COL32(v, v, v, 255 * a);

						draw_list->AddRect(pos, pos + quadSize, c, 0.f, 15, 2.f);
					}
				}
				ImGui::EndGroup();

				ImGui::SameLine();

				ImGui::BeginGroup();
				{
					// 2. Labels

					// fix
					//uint32_t texel = ((uint32_t*)bits)[(basey - zoomSize * 2 - 1) * width + basex];

					// TODO: Picked color seems is not being the one from the center pixel

					size_t i = (basey - zoomSize * 2 - 1) * width + basex;

					// clamp index
					size_t sz = width * height;
					i = MIN(i, sz - 1);
					i = MAX(i, 0);

					// color
					//uint32_t texel = ((uint32_t*)bits)[i];

					uint32_t texel;

					if (b24bits) // 24 bits
					{
						const uint8_t* pixel = bits + i * 3;
						texel = (pixel[2] << 16) | (pixel[1] << 8) | pixel[0];
					}
					else // 32 bits
					{
						texel = ((uint32_t*)bits)[i];
					}

					// Get to parent color Ptr
					ImVec4 color = ImColor(colorCenter);
					//ImVec4 color = ImColor(texel);

					if (c != nullptr) c->set(color);

					if (bDebug) {
						//ImGui::Text(" ");

						// uv	
						ImGui::Text("U,V:    %1.2f,%1.2f", mouseUVCoord.x, mouseUVCoord.y);

						// coord
						ImGui::Text("x,y:    %d,%d", int(mouseUVCoord.x * width), int(mouseUVCoord.y * height));

						// size
						ImGui::Text("w,h:    %d,%d", int(displayedTextureSize.x), int(displayedTextureSize.y));

						ImGui::Separator();

						// rgb
						ImGui::Text("R,G,B:  %d,%d,%d", int(color.x * 255.f), int(color.y * 255.f), int(color.z * 255.f));

						// alpha
						ImGui::Text("alpha:  %d", INT(color.w * 255.f));

						//--

						if (bDebugAdvanced)
						{
							// debug
							string s;
							ImGui::Separator();
							ImGui::Spacing();
							ImGui::Spacing();

							s = "DEBUG ADVANCED";
							ImGui::Text(s.c_str());
							ImGui::Spacing();

							s = "24 bits: " + ofToString(b24bits ? "TRUE" : "FALSE");
							ImGui::Text(s.c_str());

							s = "basex: " + ofToString(basex);
							ImGui::Text(s.c_str());

							s = "basey: " + ofToString(basey);
							ImGui::Text(s.c_str());

							s = "zoomSize: " + ofToString(zoomSize);
							ImGui::Text(s.c_str());

							s = "zoomRect: " + ofToString(zoomRectangleWidth);
							ImGui::Text(s.c_str());

							s = "quadWidth: " + ofToString(quadWidth, 1);
							ImGui::Text(s.c_str());

							s = "Pix: " + ofToString(npx) + "x" + ofToString(npx);
							ImGui::Text(s.c_str());

							s = "nPix: " + ofToString(npx * npx);
							ImGui::Text(s.c_str());

							s = "px center rect: " + ofToString(pixCenterRect);
							ImGui::Text(s.c_str());

							s = "px center: " + ofToString(pixCenter);
							ImGui::Text(s.c_str());

							ofFloatColor c = ofFloatColor(colorCenter.Value.x, colorCenter.Value.y, colorCenter.Value.z, colorCenter.Value.w);
							//s = "C center: " + ofToString(c);
							//ImGui::Text(s.c_str());

							ImVec4 cc = ImVec4(colorCenter);
							ImU32 ctexel = GetColorU32(cc);
							ImVec4 colorVec = ImGui::ColorConvertU32ToFloat4(ctexel);
							int r = (int)(colorVec.x * 255.0f + 0.5f);
							int g = (int)(colorVec.y * 255.0f + 0.5f);
							int b = (int)(colorVec.z * 255.0f + 0.5f);
							s = "r,g,b: " + ofToString(r) + "," + ofToString(g) + "," + ofToString(b);
							ImGui::Text(s.c_str());

							if (0) {
								ImDrawList* draw_list = ImGui::GetWindowDrawList();
								ImVec2 pos = ImGui::GetCursorPos();
								const ImRect rc(pos, pos + ImVec2{ 50, 50 });
								draw_list->AddRectFilled(rc.Min, rc.Max, ctexel);
								ImGui::Dummy(ImVec2(0, 20));
								//s = "GetColorU32: " + ofToString(ctexel);
							}
						}
					}
				}
				ImGui::EndGroup();
			}
			if (!bDebug) {
				ImGui::PopStyleVar();
				ImGui::PopStyleVar();
				ImGui::PopStyleVar();
				ImGui::PopStyleVar();
				ImGui::PopStyleVar();
				ImGui::PopStyleVar();
			}
		}
		ImGui::EndTooltip();
	};

	//--

	// Get picked color by mouse pointer.
	// (not the center of the zoom rectangle)
	inline ofColor getColor(const int width,
		const int height,
		const unsigned char* const bits,
		ImVec2 mouseUVCoord_,
		ImVec2 displayedTextureSize,
		bool b24bits = false,//default is 32bit
		ofColor* c = nullptr)
	{
		// clamp
		ImClamp(mouseUVCoord_, ImVec2{ 0,0 }, ImVec2{ 1,1 });
		ImVec2 mouseUVCoord = mouseUVCoord_;

		const int x = ImClamp(int(mouseUVCoord.x * width), 0, width);
		const int y = ImClamp(int(mouseUVCoord.y * height), 0, height);

		size_t i = y * width + x;

		// clamp index
		size_t sz = width * height;
		static bool b = 1;
		if (b) {
			i = MIN(i, sz - 1);
			i = MAX(i, 0);
		}

		// color
		//uint32_t texel = ((uint32_t*)bits)[i];
		uint32_t texel;

		if (b24bits) // 24 bits
		{
			const uint8_t* pixel = bits + i * 3;
			texel = (pixel[2] << 16) | (pixel[1] << 8) | pixel[0];
			const ImVec4 ct = ImColor(texel);
			texel = GetColorU32(ImVec4(ct.x, ct.y, ct.z, 1.f));//add alpha
		}
		else // 32 bits
		{
			texel = ((uint32_t*)bits)[i];
		}

		ImVec4 ct = ImColor(texel);

		if (c != nullptr)
		{
			c->set(ct);
		}

		return ofColor(ct);
	};

} // namespace ImageInspect

//--

//TODO: Extra widgets

namespace ImageInspect
{
	/*
	inline void histogram(const int width, const int height, const unsigned char* const bits)
	{
		unsigned int count[4][256] = { 0 };

		const unsigned char* ptrCols = bits;

		ImGui::InvisibleButton("histogram", ImVec2(512, 256));
		for (int l = 0; l < height * width; l++)
		{
			count[0][*ptrCols++]++;
			count[1][*ptrCols++]++;
			count[2][*ptrCols++]++;
			count[3][*ptrCols++]++;
		}

		unsigned int maxv = count[0][0];
		unsigned int* pCount = &count[0][0];
		for (int i = 0; i < 3 * 256; i++, pCount++)
		{
			maxv = (maxv > *pCount) ? maxv : *pCount;
		}

		ImDrawList* drawList = ImGui::GetWindowDrawList();
		const ImVec2 rmin = ImGui::GetItemRectMin();
		const ImVec2 rmax = ImGui::GetItemRectMax();
		const ImVec2 size = ImGui::GetItemRectSize();
		const float hFactor = size.y / float(maxv);

		for (int i = 0; i <= 10; i++)
		{
			float ax = rmin.x + (size.x / 10.f) * float(i);
			float ay = rmin.y + (size.y / 10.f) * float(i);
			drawList->AddLine(ImVec2(rmin.x, ay), ImVec2(rmax.x, ay), 0x80808080);
			drawList->AddLine(ImVec2(ax, rmin.y), ImVec2(ax, rmax.y), 0x80808080);
		}

		const float barWidth = (size.x / 256.f);
		for (int j = 0; j < 256; j++)
		{
			// pixel count << 2 + color index(on 2 bits)
			uint32_t cols[3] = { (count[0][j] << 2), (count[1][j] << 2) + 1, (count[2][j] << 2) + 2 };
			if (cols[0] > cols[1])
				ImSwap(cols[0], cols[1]);
			if (cols[1] > cols[2])
				ImSwap(cols[1], cols[2]);
			if (cols[0] > cols[1])
				ImSwap(cols[0], cols[1]);
			float heights[3];
			uint32_t colors[3];
			uint32_t currentColor = 0xFFFFFFFF;
			for (int i = 0; i < 3; i++)
			{
				heights[i] = rmax.y - (cols[i] >> 2) * hFactor;
				colors[i] = currentColor;
				currentColor -= 0xFF << ((cols[i] & 3) * 8);
			}

			float currentHeight = rmax.y;
			const float left = rmin.x + barWidth * float(j);
			const float right = left + barWidth;
			for (int i = 0; i < 3; i++)
			{
				if (heights[i] >= currentHeight)
				{
					continue;
				}
				drawList->AddRectFilled(ImVec2(left, currentHeight), ImVec2(right, heights[i]), colors[i]);
				currentHeight = heights[i];
			}
		}
	}
	*/

	/*
	inline void drawNormal(ImDrawList* draw_list, const ImRect& rc, float x, float y)
	{
		draw_list->AddCircle(rc.GetCenter(), rc.GetWidth() / 2.f, 0x20AAAAAA, 24, 1.f);
		draw_list->AddCircle(rc.GetCenter(), rc.GetWidth() / 4.f, 0x20AAAAAA, 24, 1.f);

		draw_list->AddLine(rc.GetCenter(), rc.GetCenter() + ImVec2(x, y) * rc.GetWidth() / 2.f, 0xFF0000FF, 2.f);
		//fix
		//draw_list->AddLine(rc.GetCenter(), rc.GetCenter() + ImVec2(x * (rc.GetWidth() / 2.f), y * (rc.GetWidth() / 2.f)) , 0xFF0000FF, 2.f);
	}
	*/
}

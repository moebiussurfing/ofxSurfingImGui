//// This is an open source non-commercial project. Dear PVS-Studio, please check it.
//// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
///*
//MIT License
//
//Copyright (c) 2010-2020 Stephane Cuillerdier (aka Aiekick)
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
//*/
//
//#include "GLVersionChecker.h"
//#include "Logger.h"
//#ifdef USE_IMGUI
//#include USE_IMGUI
//#endif
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//
//OpenglInfosStruct::OpenglInfosStruct()
//{
//	majorGLVersion = 0;
//	minorGLVersion = 0;
//
//	for (int i = 0; i < 3; i++)
//	{
//		workgroup_count[i] = 0;
//		workgroup_size[i] = 0;
//	}
//	workgroup_invocations = 0;
//
//	maxTextureSize = 0;
//	max3DTextureSize = 0;
//	maxCubeMapTextureSize = 0;
//	maxArrayTextureSize = 0;
//	maxColorTextureSize = 0;
//	maxDepthTextureSize = 0;
//	maxRectTextureSize = 0;
//	maxTextureBufferSize = 0;
//	maxTextureImageUnits = 0;
//	maxTextureLodBias = 0;
//
//	maxFramebufferWidth = 0;
//	maxFramebufferHeight = 0;
//	maxFramebufferLayers = 0;
//	maxFramebufferSampler = 0;
//
//	maxFragmentAtomicCounters = 0;
//	maxFragmentShaderStorageBlocks = 0;
//	maxFragmentInputComponents = 0;
//	maxFragmentUniformComponents = 0;
//	maxFragmentUniformVectors = 0;
//	maxFragmentUniformBlocks = 0;
//
//	maxGeometryAtomicCounters = 0;
//	maxGeometryShaderStorageBlocks = 0;
//	maxGeometryInputComponents = 0;
//	maxGeometryOutputComponents = 0;
//	maxGeometryTextureImageUnits = 0;
//	maxGeometryUniformBlocks = 0;
//	maxGeometryUniformComponent = 0;
//
//	maxTesselationControlAtomicCounters = 0;
//	maxTesselationControlShaderStorageBlocks = 0;
//	maxTesselationEvalAtomicCounters = 0;
//	maxTesselationEvalShaderStorageBlocks = 0;
//	maxPatchVertices = 0;
//
//	maxRenderbufferSize = 0;
//
//	maxShaderStorageBufferBindings = 0;
//
//	maxUniformBufferBindings = 0;
//	maxUniformBlockSize = 0;
//	maxUniformLocations = 0;
//
//	maxVaryingComponents = 0;
//	maxVaryingVectors = 0;
//	maxVaryingFloats = 0;
//
//	maxClipDistances = 0;
//
//	maxDrawBuffers = 0;
//	maxDualSourceDrawBuffers = 0;
//
//	maxElementsIndexs = 0;
//	maxElementsIndices = 0;
//	maxElementsVertices = 0;
//
//	maxVertexAtomicCounters = 0;
//	maxVertexAttribs = 0;
//	maxVertexShaderStorageBlocks = 0;
//	maxVertexTextureImageUnits = 0;
//	maxVertexUniformComponents = 0;
//	maxVertexUniformVectors = 0;
//	maxVertexOutputComponents = 0;
//	maxVertexUniformBlocks = 0;
//
//	maxTrasnformFeedbackInterleavedComponents = 0;
//	maxTrasnformFeedbackSeparateAttribs = 0;
//	maxTrasnformFeedbackSeparateComponents = 0;
//
//	maxViewports = 0;
//	for (int i = 0; i < 2; i++)
//	{
//		rangeViewportBounds[i] = 0;
//		maxViewportSize[i] = 0;
//	}
//}
//
//void OpenglInfosStruct::fill()
//{
//	// Oepngl Driver Infos
//	glGetIntegerv(GL_MAJOR_VERSION, &majorGLVersion);
//	glGetIntegerv(GL_MINOR_VERSION, &minorGLVersion);
//	driverVersion = getString(GL_VERSION);
//	driverVendor = getString(GL_VENDOR);
//	driverRenderer = getString(GL_RENDERER);
//	driverGlslsVer = getString(GL_SHADING_LANGUAGE_VERSION);
//
//	// compute
//	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &workgroup_count[0]);
//	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &workgroup_count[1]);
//	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &workgroup_count[2]);
//	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &workgroup_size[0]);
//	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &workgroup_size[1]);
//	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &workgroup_size[2]);
//	glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &workgroup_invocations);
//
//	// texture
//	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
//	glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &max3DTextureSize);
//	glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &maxCubeMapTextureSize);
//	glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &maxArrayTextureSize);
//	glGetIntegerv(GL_MAX_COLOR_TEXTURE_SAMPLES, &maxColorTextureSize);
//	glGetIntegerv(GL_MAX_DEPTH_TEXTURE_SAMPLES, &maxDepthTextureSize);
//	glGetIntegerv(GL_MAX_RECTANGLE_TEXTURE_SIZE, &maxRectTextureSize);
//	glGetIntegerv(GL_MAX_TEXTURE_BUFFER_SIZE, &maxTextureBufferSize);
//	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureImageUnits);
//	glGetIntegerv(GL_MAX_TEXTURE_LOD_BIAS, &maxTextureLodBias);
//
//	// clipping
//	glGetIntegerv(GL_MAX_CLIP_DISTANCES, &maxClipDistances);
//
//	// buffers
//	glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxDrawBuffers);
//	glGetIntegerv(GL_MAX_DUAL_SOURCE_DRAW_BUFFERS, &maxDualSourceDrawBuffers);
//
//	// elements
//	glGetIntegerv(GL_MAX_ELEMENT_INDEX, &maxElementsIndexs);
//	glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &maxElementsIndices);
//	glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &maxElementsVertices);
//
//	// fragment
//	glGetIntegerv(GL_MAX_FRAGMENT_ATOMIC_COUNTERS, &maxFragmentAtomicCounters);
//	glGetIntegerv(GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS, &maxFragmentShaderStorageBlocks);
//	glGetIntegerv(GL_MAX_FRAGMENT_INPUT_COMPONENTS, &maxFragmentInputComponents);
//	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &maxFragmentUniformComponents);
//	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &maxFragmentUniformVectors);
//	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS, &maxFragmentUniformBlocks);
//
//	// fbo
//	glGetIntegerv(GL_MAX_FRAMEBUFFER_WIDTH, &maxFramebufferWidth);
//	glGetIntegerv(GL_MAX_FRAMEBUFFER_HEIGHT, &maxFramebufferHeight);
//	glGetIntegerv(GL_MAX_FRAMEBUFFER_LAYERS, &maxFramebufferLayers);
//	glGetIntegerv(GL_MAX_FRAMEBUFFER_SAMPLES, &maxFramebufferSampler);
//
//	// geometry
//	glGetIntegerv(GL_MAX_GEOMETRY_ATOMIC_COUNTERS, &maxGeometryAtomicCounters);
//	glGetIntegerv(GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS, &maxGeometryShaderStorageBlocks);
//	glGetIntegerv(GL_MAX_GEOMETRY_INPUT_COMPONENTS, &maxGeometryInputComponents);
//	glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_COMPONENTS, &maxGeometryOutputComponents);
//	glGetIntegerv(GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS, &maxGeometryTextureImageUnits);
//	glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_BLOCKS, &maxGeometryUniformBlocks);
//	glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS, &maxGeometryUniformComponent);
//
//	// tesselation
//	glGetIntegerv(GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS, &maxTesselationControlAtomicCounters);
//	glGetIntegerv(GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS, &maxTesselationControlShaderStorageBlocks);
//	glGetIntegerv(GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS, &maxTesselationEvalAtomicCounters);
//	glGetIntegerv(GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS, &maxTesselationEvalShaderStorageBlocks);
//	glGetIntegerv(GL_MAX_PATCH_VERTICES, &maxPatchVertices);
//
//	// renderbuffer
//	glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxRenderbufferSize);
//
//	// shader storage
//	glGetIntegerv(GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, &maxShaderStorageBufferBindings);
//
//	// uniform
//	glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &maxUniformBufferBindings);
//	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &maxUniformBlockSize);
//	glGetIntegerv(GL_MAX_UNIFORM_LOCATIONS, &maxUniformLocations);
//
//	// varying
//	glGetIntegerv(GL_MAX_VARYING_COMPONENTS, &maxVaryingComponents);
//	glGetIntegerv(GL_MAX_VARYING_VECTORS, &maxVaryingVectors);
//	glGetIntegerv(GL_MAX_VARYING_FLOATS, &maxVaryingFloats);
//
//	// vertex
//	glGetIntegerv(GL_MAX_VERTEX_ATOMIC_COUNTERS, &maxVertexAtomicCounters);
//	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
//	glGetIntegerv(GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS, &maxVertexShaderStorageBlocks);
//	glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &maxVertexTextureImageUnits);
//	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &maxVertexUniformComponents);
//	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &maxVertexUniformVectors);
//	glGetIntegerv(GL_MAX_VERTEX_OUTPUT_COMPONENTS, &maxVertexOutputComponents);
//	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &maxVertexUniformBlocks);
//
//	//viewports
//	glGetIntegerv(GL_MAX_VIEWPORTS, &maxViewports);
//	glGetIntegerv(GL_VIEWPORT_BOUNDS_RANGE, &rangeViewportBounds[0]);
//	glGetIntegerv(GL_MAX_VIEWPORT_DIMS, &maxViewportSize[0]);
//
//	//transform feedback
//	glGetIntegerv(GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS, &maxTrasnformFeedbackInterleavedComponents);
//	glGetIntegerv(GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS, &maxTrasnformFeedbackSeparateAttribs);
//	glGetIntegerv(GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS, &maxTrasnformFeedbackSeparateComponents);
//
//	// extentions
//	glGetIntegerv(GL_NUM_EXTENSIONS, &maxExtentionCount);
//	for (int i = 0; i < maxExtentionCount; i++)
//	{
//		auto str = glGetStringi(GL_EXTENSIONS, i);
//		extentions[std::string((char*)str)] = i;
//	}
//}
//
//#ifdef USE_IMGUI
//void OpenglInfosStruct::drawImGui()
//{
//	if (ImGui::BeginMenu("Opengl Infos"))
//	{
//		ImGui::Text("Opengl Version %i.%i", majorGLVersion, minorGLVersion);
//		
//		if (ImGui::BeginMenu("Driver Infos"))
//		{
//			ImGui::Text("Version :      %s", driverVersion.c_str());
//			ImGui::Text("Vendor :       %s", driverVendor.c_str());
//			ImGui::Text("Renderer :     %s", driverRenderer.c_str());
//			ImGui::Text("GLSL Version : %s", driverGlslsVer.c_str());
//
//			ImGui::EndMenu(); 
//		}
//		
//		if (ImGui::BeginMenu("Shader Infos"))
//		{
//			if (ImGui::BeginMenu("Storage Infos"))
//			{
//				ImGui::Text("GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS : %i", maxShaderStorageBufferBindings);
//
//				ImGui::EndMenu();
//			}
//			
//			if (ImGui::BeginMenu("Uniform Infos"))
//			{
//				ImGui::Text("GL_MAX_UNIFORM_BUFFER_BINDINGS : %i", maxUniformBufferBindings);
//				ImGui::Text("GL_MAX_UNIFORM_BLOCK_SIZE :      %i", maxUniformBlockSize);
//				ImGui::Text("GL_MAX_UNIFORM_LOCATIONS :       %i", maxUniformLocations);
//
//				ImGui::EndMenu();
//			}
//			
//			if (ImGui::BeginMenu("Varying Infos"))
//			{
//				ImGui::Text("GL_MAX_VARYING_COMPONENTS : %i", maxVaryingComponents);
//				ImGui::Text("GL_MAX_VARYING_VECTORS :    %i", maxVaryingVectors);
//				ImGui::Text("GL_MAX_VARYING_FLOATS :     %i", maxVaryingFloats);
//
//				ImGui::EndMenu();
//			}
//			
//			if (ImGui::BeginMenu("Vertex Infos"))
//			{
//				ImGui::Text("GL_MAX_VERTEX_ATOMIC_COUNTERS :       %i", maxVertexAtomicCounters);
//				ImGui::Text("GL_MAX_VERTEX_ATTRIBS :               %i", maxVertexAttribs);
//				ImGui::Text("GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS : %i", maxVertexShaderStorageBlocks);
//				ImGui::Text("GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS :   %i", maxVertexTextureImageUnits);
//				ImGui::Text("GL_MAX_VERTEX_UNIFORM_COMPONENTS :    %i", maxVertexUniformComponents);
//				ImGui::Text("GL_MAX_VERTEX_UNIFORM_VECTORS :       %i", maxVertexUniformVectors);
//				ImGui::Text("GL_MAX_VERTEX_OUTPUT_COMPONENTS :     %i", maxVertexOutputComponents);
//				ImGui::Text("GL_MAX_VERTEX_UNIFORM_BLOCKS :        %i", maxVertexUniformBlocks);
//
//				ImGui::EndMenu();
//			}
//			
//			if (ImGui::BeginMenu("Geometry Infos"))
//			{
//				ImGui::Text("GL_MAX_GEOMETRY_ATOMIC_COUNTERS :       %i", maxGeometryAtomicCounters);
//				ImGui::Text("GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS : %i", maxGeometryShaderStorageBlocks);
//				ImGui::Text("GL_MAX_GEOMETRY_INPUT_COMPONENTS :      %i", maxGeometryInputComponents);
//				ImGui::Text("GL_MAX_GEOMETRY_OUTPUT_COMPONENTS :     %i", maxGeometryOutputComponents);
//				ImGui::Text("GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS :   %i", maxGeometryTextureImageUnits);
//				ImGui::Text("GL_MAX_GEOMETRY_UNIFORM_BLOCKS :        %i", maxGeometryUniformBlocks);
//				ImGui::Text("GL_MAX_GEOMETRY_UNIFORM_COMPONENTS :    %i", maxGeometryUniformComponent);
//
//				ImGui::EndMenu();
//			}
//			
//			if (ImGui::BeginMenu("Teseelation Infos"))
//			{
//				ImGui::Text("Control");
//				ImGui::Text("GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS :          %i", maxTesselationControlAtomicCounters);
//				ImGui::Text("GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS :    %i", maxTesselationControlShaderStorageBlocks);
//				ImGui::Text("Evaluation");
//				ImGui::Text("GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS :       %i", maxTesselationEvalAtomicCounters);
//				ImGui::Text("GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS : %i", maxTesselationEvalShaderStorageBlocks);
//				ImGui::Text("Patches");
//				ImGui::Text("GL_MAX_PATCH_VERTICES :                        %i", maxPatchVertices);
//				
//				ImGui::EndMenu();
//			}
//
//			if (ImGui::BeginMenu("Frament Infos"))
//			{
//				ImGui::Text("GL_MAX_FRAGMENT_ATOMIC_COUNTERS :       %i", maxFragmentAtomicCounters);
//				ImGui::Text("GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS : %i", maxFragmentShaderStorageBlocks);
//				ImGui::Text("GL_MAX_FRAGMENT_INPUT_COMPONENTS :      %i", maxFragmentInputComponents);
//				ImGui::Text("GL_MAX_FRAGMENT_UNIFORM_COMPONENTS :    %i", maxFragmentUniformComponents);
//				ImGui::Text("GL_MAX_FRAGMENT_UNIFORM_VECTORS :       %i", maxFragmentUniformVectors);
//				ImGui::Text("GL_MAX_FRAGMENT_UNIFORM_BLOCKS :        %i", maxFragmentUniformBlocks);
//
//				ImGui::EndMenu();
//			}
//			
//			if (ImGui::BeginMenu("Compute Infos"))
//			{
//				ImGui::Text("GL_MAX_COMPUTE_WORK_GROUP_COUNT :       x:%i y:%i z:%i", workgroup_count[0], workgroup_count[1], workgroup_count[2]);
//				ImGui::Text("GL_MAX_COMPUTE_WORK_GROUP_SIZE :        x:%i y:%i z:%i", workgroup_size[0], workgroup_size[1], workgroup_size[2]);
//				ImGui::Text("GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS : %i", workgroup_invocations);
//
//				ImGui::EndMenu();
//			}
//
//			ImGui::EndMenu();
//		}
//	
//		if (ImGui::BeginMenu("Texture Infos"))
//		{
//			ImGui::Text("GL_MAX_TEXTURE_SIZE :           %i", maxTextureSize);
//			ImGui::Text("GL_MAX_3D_TEXTURE_SIZE :        %i", max3DTextureSize);
//			ImGui::Text("GL_MAX_CUBE_MAP_TEXTURE_SIZE :  %i", maxCubeMapTextureSize);
//			ImGui::Text("GL_MAX_ARRAY_TEXTURE_LAYERS :   %i", maxArrayTextureSize);
//			ImGui::Text("GL_MAX_COLOR_TEXTURE_SAMPLES :  %i", maxColorTextureSize);
//			ImGui::Text("GL_MAX_DEPTH_TEXTURE_SAMPLES :  %i", maxDepthTextureSize);
//			ImGui::Text("GL_MAX_RECTANGLE_TEXTURE_SIZE : %i", maxRectTextureSize);
//			ImGui::Text("GL_MAX_TEXTURE_BUFFER_SIZE :    %i", maxTextureBufferSize);
//			ImGui::Text("GL_MAX_TEXTURE_IMAGE_UNITS :    %i", maxTextureImageUnits);
//			ImGui::Text("GL_MAX_TEXTURE_LOD_BIAS :       %i", maxTextureLodBias);
//
//			ImGui::EndMenu();
//		}
//	
//		if (ImGui::BeginMenu("FrameBuffer Infos"))
//		{
//			ImGui::Text("GL_MAX_FRAMEBUFFER_WIDTH :   %i", maxFramebufferWidth);
//			ImGui::Text("GL_MAX_FRAMEBUFFER_HEIGHT :  %i", maxFramebufferHeight);
//			ImGui::Text("GL_MAX_FRAMEBUFFER_LAYERS :  %i", maxFramebufferLayers);
//			ImGui::Text("GL_MAX_FRAMEBUFFER_SAMPLES : %i", maxFramebufferSampler);
//
//			ImGui::EndMenu();
//		}
//		
//		if (ImGui::BeginMenu("RenderBuffer Infos"))
//		{
//			ImGui::Text("GL_MAX_RENDERBUFFER_SIZE : %i", maxRenderbufferSize);
//
//			ImGui::EndMenu();
//		}
//		
//		if (ImGui::BeginMenu("Draw Buffers Infos"))
//		{
//			ImGui::Text("GL_MAX_DRAW_BUFFERS :             %i", maxDrawBuffers);
//			ImGui::Text("GL_MAX_DUAL_SOURCE_DRAW_BUFFERS : %i", maxDualSourceDrawBuffers);
//
//			ImGui::EndMenu();
//		}
//		
//		if (ImGui::BeginMenu("Clipping Infos"))
//		{
//			ImGui::Text("GL_MAX_CLIP_DISTANCES : %i", maxClipDistances);
//
//			ImGui::EndMenu();
//		}
//		
//		if (ImGui::BeginMenu("Elements Infos"))
//		{
//			ImGui::Text("GL_MAX_ELEMENTS_INDEXS :  %i", maxElementsIndexs);
//			ImGui::Text("GL_MAX_ELEMENTS_INDICES :  %i", maxElementsIndices);
//			ImGui::Text("GL_MAX_ELEMENTS_VERTICES : %i", maxElementsVertices);
//
//			ImGui::EndMenu();
//		}
//		
//		if (ImGui::BeginMenu("ViewPort Infos"))
//		{
//			ImGui::Text("GL_MAX_VIEWPORTS :         %i", maxViewports);
//			ImGui::Text("GL_VIEWPORT_BOUNDS_RANGE : x:%i y:%i", rangeViewportBounds[0], rangeViewportBounds[1]);
//			ImGui::Text("GL_MAX_VIEWPORT_DIMS :     x:%i y:%i", maxViewportSize[0], maxViewportSize[1]);
//
//			ImGui::EndMenu();
//		}
//
//		if (ImGui::BeginMenu("Transform Feedback Infos"))
//		{
//			ImGui::Text("GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS : %i", maxTrasnformFeedbackInterleavedComponents);
//			ImGui::Text("GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS :       %i", maxTrasnformFeedbackSeparateAttribs);
//			ImGui::Text("GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS :    %i", maxTrasnformFeedbackSeparateComponents);
//
//			ImGui::EndMenu();
//		}
//
//		if (ImGui::BeginMenu("Extentions Infos"))
//		{
//			ImGui::Text("Extention Count : %i", maxExtentionCount);
//
//			for (auto it = extentions.begin(); it != extentions.end(); ++it)
//			{
//				ImGui::Text("%s", it->first.c_str());
//			}
//		
//			ImGui::EndMenu();
//		}
//
//		ImGui::EndMenu();
//	}
//}
//#endif
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//
//GLVersionChecker::GLVersionChecker()
//{
//	InitSupportedVars();
//	FillOpenglVersionMap();
//	CheckVersions();
//	DisplaySupport();
//}
//
//GLVersionChecker::~GLVersionChecker()
//{
//
//}
//
//OpenGlVersionStruct* GLVersionChecker::GetOpenglVersionStruct(std::string vVersion)
//{
//	if (OpenGlVersionsMap.find(vVersion) != OpenGlVersionsMap.end())
//	{
//		return &(OpenGlVersionsMap[vVersion]);
//	}
//	return 0;
//}
//
//// PRIVATE
//
//void GLVersionChecker::InitSupportedVars()
//{
//	puGeometryShaderSupported = false;
//	puTesselationShaderSupported = false;
//	puComputeShaderSupported = false;
//	puAttribLayoutSupportedCore = false;
//	puAttribLayoutSupportedExtention = false;
//}
//
//void GLVersionChecker::DisplaySupport()
//{
//	auto glStruct = GetOpenglVersionStruct(puOpenglVersion);
//	if (glStruct)
//	{
//		LogVar("OpenGl version : %i.%i", glStruct->major, glStruct->minor);
//		if (puAttribLayoutSupportedCore)
//			LogVar("- Attrib Location Available in Core");
//		else if (puAttribLayoutSupportedExtention)
//			LogVar("- Attrib Location Available in Extension");
//		else
//			LogVar("- Attrib Location Not Available");
//		if (puGeometryShaderSupported)
//			LogVar("- Geometry Stage Available");
//		else
//			LogVar("- Geometry Stage Not Available");
//		if (puTesselationShaderSupported)
//			LogVar("- Tesselation Stage Available");
//		else
//			LogVar("- Tesselation Stage Not Available");
//		if (puComputeShaderSupported)
//			LogVar("- Compute Stage Available");
//		else
//			LogVar("- Compute Stage Not Available");
//	}
//	else
//	{
//		LogVar("OpenGl version : Not Found !");
//	}
//}
//
//void GLVersionChecker::FillOpenglVersionMap()
//{
//	//https://en.wikipedia.org/wiki/OpenGL_Shading_Language
//	/*
//	2.0 es #version 100
//	3.0 es #version 300 es
//	1.10.59[1] 	2.0 	April 2004 		#version 110
//	1.20.8[2] 	2.1 	September 2006 	#version 120
//	1.30.10[3] 	3.0 	August 2008 	#version 130
//	1.40.08[4] 	3.1 	March 2009 		#version 140
//	1.50.11[5] 	3.2 	August 2009 	#version 150
//	3.30.6[6] 	3.3 	February 2010 	#version 330
//	4.00.9[7] 	4.0 	March 2010 		#version 400
//	4.10.6[8] 	4.1 	July 2010 		#version 410
//	4.20.11[9] 	4.2 	August 2011 	#version 420
//	4.30.8[10] 	4.3 	August 2012 	#version 430
//	4.40[11] 	4.4 	July 2013 		#version 440
//	4.50[12] 	4.5 	August 2014 	#version 450
//	*/
//	OpenGlVersionsMap["2.0 ES"] =	OpenGlVersionStruct(2, -1,	"2.0 ES",	100, "#version 100",		false,	false,	false,	false,	false);
//	OpenGlVersionsMap["2.0"] =		OpenGlVersionStruct(2,	0,	"2.0",		110, "#version 110",		true,	false,	false,	false,	false);
//	OpenGlVersionsMap["2.1"] =		OpenGlVersionStruct(2,	1,	"2.1",		120, "#version 120",		true,	false,	false,	false,	false);
//	OpenGlVersionsMap["3.0 ES"] =	OpenGlVersionStruct(3, -1,	"3.0 ES",	300, "#version 300 es",		true,	false,	false,	false,	false);
//	OpenGlVersionsMap["3.0"] =		OpenGlVersionStruct(3,	0,	"3.0",		130, "#version 130",		true,	false,	false,	false,	false);
//	OpenGlVersionsMap["3.1"] =		OpenGlVersionStruct(3,	1,	"3.1",		140, "#version 140",		true,	false,	false,	false,	false);
//	OpenGlVersionsMap["3.2"] =		OpenGlVersionStruct(3,	2,	"3.2",		150, "#version 150",		true,	true,	false,	false,	false);
//	OpenGlVersionsMap["3.3"] =		OpenGlVersionStruct(3,	3,	"3.3",		330, "#version 330",		false,	true,	true,	false,	false);
//	OpenGlVersionsMap["4.0"] =		OpenGlVersionStruct(4,	0,	"4.0",		400, "#version 400",		false,	true,	true,	true,	false);
//	OpenGlVersionsMap["4.1"] =		OpenGlVersionStruct(4,	1,	"4.1",		410, "#version 410",		false,	true,	true,	false,	false);
//	OpenGlVersionsMap["4.2"] =		OpenGlVersionStruct(4,	2,	"4.2",		420, "#version 420",		false,	true,	true,	false,	false);
//	OpenGlVersionsMap["4.3"] =		OpenGlVersionStruct(4,	3,	"4.3",		430, "#version 430",		false,	true,	true,	true,	true);
//	OpenGlVersionsMap["4.4"] =		OpenGlVersionStruct(4,	4,	"4.4",		440, "#version 440",		false,	true,	true,	true,	true);
//	OpenGlVersionsMap["4.5"] =		OpenGlVersionStruct(4,	5,	"4.5",		450, "#version 450",		false,	true,	true,	true,	true);
//}
//
//bool GLVersionChecker::IsGlSupported(int vMajorGLVersion, int MinorGLVersion)
//{
//#ifdef GL3W
//	return gl3wIsSupported(vMajorGLVersion, MinorGLVersion);
//#endif
//#ifdef GLAD
//	if (GLVersion.major < 3)
//		return false;
//	if (GLVersion.major == vMajorGLVersion)
//		return GLVersion.minor >= MinorGLVersion;
//	return GLVersion.major >= vMajorGLVersion;
//#endif
//}
//
//bool GLVersionChecker::CheckVersion(int vMajorGLVersion, int MinorGLVersion)
//{
//	bool res = IsGlSupported(vMajorGLVersion, MinorGLVersion);
//	if (res)
//	{
//		puOpenglVersion = ct::toStr(vMajorGLVersion) + "." + ct::toStr(MinorGLVersion);
//		auto version = GetOpenglVersionStruct(puOpenglVersion);
//		if (version)
//		{
//			version->supported = true;
//			puDefaultGlslVersionInt = version->DefaultGlslVersionInt;
//			puDefaultGlslVersionHeader = version->DefineCode;
//
//			puAttribLayoutSupportedExtention = version->attribLayoutSupportedExtention;
//			puAttribLayoutSupportedCore = version->attribLayoutSupportedCore;
//			puGeometryShaderSupported = version->geometryShaderSupported;
//			puTesselationShaderSupported = version->tesselationShaderSupported;
//			puComputeShaderSupported = version->computeShaderSupported;
//		}
//	}
//	else
//	{
//		std::string vers = ct::toStr(vMajorGLVersion) + "." + ct::toStr(MinorGLVersion);
//		auto version = GetOpenglVersionStruct(vers);
//		if (version)
//		{
//			version->supported = false;
//		}
//	}
//	return res;
//}
//
//bool GLVersionChecker::CheckVersions()
//{
//	if (!CheckVersion(4, 5))
//		if (!CheckVersion(4, 4))
//			if (!CheckVersion(4, 3))
//				if (!CheckVersion(4, 2))
//					if (!CheckVersion(4, 1))
//						if (!CheckVersion(4, 0))
//							if (!CheckVersion(3, 3))
//								if (!CheckVersion(3, 2))
//									if (!CheckVersion(3, 1))
//										if (!CheckVersion(3, 0))
//											if (!CheckVersion(2, 1))
//												CheckVersion(2, 0);
//
//	puOpenglInfosStruct.fill();
//
//	return true;
//}
//

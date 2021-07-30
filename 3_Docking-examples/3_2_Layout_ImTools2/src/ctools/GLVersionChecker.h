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
//#pragma once
//
//#include "cTools.h"
//#include <glad/glad.h>
//
//#ifdef MSVC
//#include <Windows.h>
//#include <strsafe.h>
//#else
//#endif
//
//#include <string>
//#include <map>
//#include <memory>
//
//struct OpenglInfosStruct
//{
//	int majorGLVersion = 0;
//	int minorGLVersion = 0;
//	std::string driverVersion;
//	std::string driverVendor;
//	std::string driverRenderer;
//	std::string driverGlslsVer;
//
//	int workgroup_count[3] = { 0,0,0 };
//	int workgroup_size[3] = { 0,0,0 };
//	int workgroup_invocations = 0;
//
//	int maxTextureSize = 0;
//	int max3DTextureSize = 0;
//	int maxCubeMapTextureSize = 0;
//	int maxArrayTextureSize = 0;
//	int maxColorTextureSize = 0;
//	int maxDepthTextureSize = 0;
//	int maxRectTextureSize = 0;
//	int maxTextureBufferSize = 0;
//	int maxTextureImageUnits = 0;
//	int maxTextureLodBias = 0;
//
//	int maxFragmentAtomicCounters = 0;
//	int maxFragmentShaderStorageBlocks = 0;
//	int maxFragmentInputComponents = 0;
//	int maxFragmentUniformComponents = 0;
//	int maxFragmentUniformVectors = 0;
//	int maxFragmentUniformBlocks = 0;
//
//	int maxFramebufferWidth = 0;
//	int maxFramebufferHeight = 0;
//	int maxFramebufferLayers = 0;
//	int maxFramebufferSampler = 0;
//	
//	int maxGeometryAtomicCounters = 0;
//	int maxGeometryShaderStorageBlocks = 0;
//	int maxGeometryInputComponents = 0;
//	int maxGeometryOutputComponents = 0;
//	int maxGeometryTextureImageUnits = 0;
//	int maxGeometryUniformBlocks = 0;
//	int maxGeometryUniformComponent = 0;
//
//	int maxTesselationControlAtomicCounters = 0;
//	int maxTesselationControlShaderStorageBlocks = 0;
//	int maxTesselationEvalAtomicCounters = 0;
//	int maxTesselationEvalShaderStorageBlocks = 0;
//	int maxPatchVertices = 0;
//
//	int maxVertexAtomicCounters = 0;
//	int maxVertexAttribs = 0;
//	int maxVertexShaderStorageBlocks = 0;
//	int maxVertexTextureImageUnits = 0;
//	int maxVertexUniformComponents = 0;
//	int maxVertexUniformVectors = 0;
//	int maxVertexOutputComponents = 0;
//	int maxVertexUniformBlocks = 0;
//
//	int maxRenderbufferSize = 0;
//
//	int maxShaderStorageBufferBindings = 0;
//
//	int maxUniformBufferBindings = 0;
//	int maxUniformBlockSize = 0;
//	int maxUniformLocations = 0;
//
//	int maxVaryingComponents = 0;
//	int maxVaryingVectors = 0;
//	int maxVaryingFloats = 0;
//
//	int maxClipDistances = 0;
//
//	int maxDrawBuffers = 0;
//	int maxDualSourceDrawBuffers = 0;
//
//	int maxElementsIndexs = 0;
//	int maxElementsIndices = 0;
//	int maxElementsVertices = 0;
//
//	int maxViewports = 0;
//	int rangeViewportBounds[2] = { 0,0 };
//	int maxViewportSize[2] = { 0,0 };
//
//	int maxTrasnformFeedbackInterleavedComponents = 0;
//	int maxTrasnformFeedbackSeparateAttribs = 0;
//	int maxTrasnformFeedbackSeparateComponents = 0;
//
//	int maxExtentionCount = 0;
//	std::map<std::string, int> extentions;
//	
//	OpenglInfosStruct();
//
//	std::string getString(GLenum vGLenum)
//	{
//		const char* s = (const char*)glGetString(vGLenum);
//		if (s)
//			return std::string(s);
//		return "";
//	}
//
//	void fill();
//#ifdef USE_IMGUI
//	void drawImGui();
//#endif
//};
//
//struct OpenGlVersionStruct
//{
//	int major = 0;
//	int minor = 0;
//	std::string OpenglVersion;
//	int DefaultGlslVersionInt;
//	std::string DefineCode;
//	bool supported = true;
//	bool attribLayoutSupportedExtention = false;
//	bool geometryShaderSupported = false;
//	bool attribLayoutSupportedCore = false;
//	bool tesselationShaderSupported = false;
//	bool computeShaderSupported = false;
//	
//	OpenGlVersionStruct()
//	{
//		major = 0;
//		minor = 0;
//	}
//
//	OpenGlVersionStruct(int vMajor, int vMinor,
//		std::string vOpenglVersion,
//		int vDefaultGlslVersionInt,
//		std::string vDefineCode,
//		bool AttribLayoutSupportedByExt,
//		bool vGeomShaderSupported,
//		bool AttribLayoutSupportedInCore,
//		bool vTessShaderSupported, 
//		bool vCompShaderSupported)
//	{
//		major = vMajor;
//		minor = vMinor;
//		OpenglVersion = vOpenglVersion;
//		DefaultGlslVersionInt = vDefaultGlslVersionInt;
//		DefineCode = vDefineCode;
//		attribLayoutSupportedExtention = AttribLayoutSupportedByExt;
//		geometryShaderSupported = vGeomShaderSupported;
//		attribLayoutSupportedCore = AttribLayoutSupportedInCore;
//		tesselationShaderSupported = vTessShaderSupported;
//		computeShaderSupported = vCompShaderSupported;
//	}
//};
//
//class GLVersionChecker
//{
//private:
//	std::map<std::string, OpenGlVersionStruct> OpenGlVersionsMap;
//	std::map<std::string, std::string> ContextParamsMap;
//	std::string puDefaultGlslVersionHeader;
//	int puDefaultGlslVersionInt;
//	std::string puOpenglVersion;
//	
//public: //extention
//	bool puGeometryShaderSupported = false;
//	bool puTesselationShaderSupported = false;
//	bool puComputeShaderSupported = false;
//	bool puAttribLayoutSupportedCore = false;
//	bool puAttribLayoutSupportedExtention = false;
//
//public:
//	OpenglInfosStruct puOpenglInfosStruct;
//
//public:
//	static GLVersionChecker* Instance()
//	{
//		static GLVersionChecker _Instance;
//		return &_Instance;
//	}
//
//public:
//	GLVersionChecker(); // Prevent construction
//	GLVersionChecker(const GLVersionChecker&) {}; // Prevent construction by copying
//	GLVersionChecker& operator =(const GLVersionChecker&) { return *this; }; // Prevent assignment
//	~GLVersionChecker(); // Prevent unwanted destruction
//
//public:
//	OpenGlVersionStruct* GetOpenglVersionStruct(std::string vVersion);
//	std::map<std::string, OpenGlVersionStruct>* GetOpenglVersionMap() { return &OpenGlVersionsMap; }
//	std::string GetOpenglVersion() { return puOpenglVersion; }
//	int GetGlslVersionInt() { return puDefaultGlslVersionInt; }
//	std::string GetGlslVersionHeader() { return puDefaultGlslVersionHeader; }
//	bool CheckVersions();
//
//private:
//	void InitSupportedVars();
//	void FillOpenglVersionMap();
//	bool IsGlSupported(int vMajorGLVersion, int MinorGLVersion);
//	bool CheckVersion(int vMajorGLVersion, int MinorGLVersion);
//	void DisplaySupport();
//};
//

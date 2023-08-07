/////*
////MIT License
////
////Copyright (c) 2010-2020 Stephane Cuillerdier (aka Aiekick)
////
////Permission is hereby granted, free of charge, to any person obtaining a copy
////of this software and associated documentation files (the "Software"), to deal
////in the Software without restriction, including without limitation the rights
////to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
////copies of the Software, and to permit persons to whom the Software is
////furnished to do so, subject to the following conditions:
////
////The above copyright notice and this permission notice shall be included in all
////copies or substantial portions of the Software.
////
////THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
////IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
////FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
////AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
////LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
////OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
////SOFTWARE.
////*/
//
//#pragma once
//#include "ofMain.h"
//
//#include <string>
//#include <vector>
//#include <map>
//#include <memory>
//
//struct PathStruct
//{
//	std::string path;
//	std::string name;
//	std::string ext;
//
//	bool isOk = false;
//
//	PathStruct();
//	PathStruct(const std::string& vPath, const std::string& vName, const std::string& vExt);
//
//	// FPNE mean FilePathNameExt
//	std::string GetFPNE();
//	std::string GetFPNE_WithPathNameExt(std::string vPath, const std::string& vName, const std::string& vExt);
//	std::string GetFPNE_WithPath(const std::string& vPath);
//	std::string GetFPNE_WithPathName(const std::string& vPath, const std::string& vName);
//	std::string GetFPNE_WithPathExt(const std::string& vPath, const std::string& vExt);
//	std::string GetFPNE_WithName(const std::string& vName);
//	std::string GetFPNE_WithNameExt(const std::string& vName, const std::string& vExt);
//	std::string GetFPNE_WithExt(const std::string& vExt);
//};
//
//typedef int FileLocation;
//
//#ifdef USE_GLFW3
//struct GLFWwindow;
//#endif
//class FileHelper
//{
//public: // static
//	static std::string AppPath;
//
//public: // var
//	std::map<FileLocation, std::string> puRegisteredPaths;
//	std::string puSlashType;
//	std::string puAppFileName;
//	std::vector<std::string> puSearchPaths;
//
//public: // funcs
//	PathStruct ParsePathFileName(const std::string& vPathFileName) const;
//
//	void RegisterPath(FileLocation vLoc, const std::string& vPath);
//
//	std::string GetExistingFilePathForFile(const std::string& vFileName, bool vSilentMode = false);
//	std::string CorrectSlashTypeForFilePathName(const std::string& vFilePathName) const;
//#ifdef _DEBUG
//	void Test_GetRelativePathToPath();
//#endif
//	std::string GetRelativePathToPath(const std::string& vFilePathName, const std::string& vRootPath);
//	bool IsAbsolutePath(const std::string& vFilePathName);
//
//	void SetAppPath(const std::string& vPath);
//	std::string GetAppPath();
//	std::string GetPathRelativeToApp(const std::string& vFilePathName);
//
//	std::string GetCurDirectory() const;
//	bool SetCurDirectory(const std::string& vPath) const;
//
//	std::string ComposePath(const std::string& vPath, const std::string& vFileName, const std::string& vExt) const;
//
//	bool IsFileExist(const std::string& name, bool vSilentMode = false) const;
//	std::string GetID(const std::string& vPathFileName) const;
//
//	std::string SimplifyFilePath(const std::string& vFilePath) const;
//
//	std::string LoadFileToString(const std::string& vFilePathName, bool vSilentMode = false);
//	void SaveStringToFile(const std::string& vString, const std::string& vFilePathName);
//
//	std::vector<uint8_t> LoadFileToBytes(const std::string& vFilePathName, int* vError = nullptr);
//
//	void DestroyFile(const std::string& filePathName) const;
//
//	bool IsDirectoryExist(const std::string& name) const;
//	bool CreateDirectoryIfNotExist(const std::string& name) const;
//	bool CreatePathIfNotExist(const std::string& vPath) const;
//
//	void OpenFile(const std::string& vShaderToOpen) const;
//	void OpenUrl(const std::string& vUrl) const;
//	void SelectFile(const std::string& vFileToSelect) const;
//
//	std::vector<std::string> GetDrives() const;
//
//	std::string GetTimeStampToString(const std::string& vSeparator = "_") const;
//	size_t GetTimeStampToNumber() const;
//
//	std::vector<std::string> GetAbsolutePathForFileLocation(const std::vector<std::string>& vRelativeFilePathNames, FileLocation vFileType);
//	std::string GetAbsolutePathForFileLocation(const std::string& vRelativeFilePathName, FileLocation vFileType);
//
//	std::string LoadFile(const std::string& vFilePathName, FileLocation vFileType);
//	void SaveToFile(const std::string& vCode, const std::string& vFilePathName, FileLocation vFileType);
//
//	// specific function
//	std::string GetRelativePathToParent(const std::string& vFilePath, const std::string& vParentPath, bool vSilentMode = false) const;
//
//#ifdef USE_GLFW3
//public: /* clipboard */
//	void SaveInClipBoard(GLFWwindow* vWin, const std::string& vString);
//	std::string GetFromClipBoard(GLFWwindow* vWin);
//#endif
//
//public: // singleton
//	static FileHelper* Instance()
//	{
//		static FileHelper _Instance;
//		return &_Instance;
//	}
//
//public:
//	FileHelper(); // Prevent construction
//	FileHelper(const FileHelper&) {}; // Prevent construction by copying
//	FileHelper& operator =(const FileHelper&) { return *this; }; // Prevent assignment
//	~FileHelper(); // Prevent unwanted destruction
//};

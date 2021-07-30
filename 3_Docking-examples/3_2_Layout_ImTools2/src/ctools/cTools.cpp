// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

/*
MIT License

Copyright (c) 2010-2020 Stephane Cuillerdier (aka Aiekick)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "cTools.h"

#ifdef WIN32
#include <Windows.h>
#elif defined(LINUX) or defined(APPLE)
#endif

#include <cstdarg>  // For va_start, etc.

#include <cmath>
#include <list>
#include <string>
#include <map>
#include <vector>
#include <chrono>
#include <functional>
#include <algorithm> // ::std::reverse
#include <cstring>

#ifdef MSVC
#include <cwchar>
#endif

::std::string ct::toStr(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	char TempBuffer[3072 + 1];//3072 = 1024 * 3
	const int w = vsnprintf(TempBuffer, 3072, fmt, args);
	va_end(args);
	if (w)
	{
		return std::string(TempBuffer, w);
	}
	return std::string();
}

#ifdef USE_IMGUI
::std::string ct::toStrFromImVec2(ImVec2 v, char delimiter)
{
	return toStrFromArray(&v.x, 2, delimiter);
}
::std::string ct::toStrFromImVec4(ImVec4 v, char delimiter)
{
	return toStrFromArray(&v.x, 4, delimiter);
}
#endif

::std::list<::std::string> ct::splitStringToList(const ::std::string& text, const std::string& delimiters, bool pushEmpty, bool vInversion)
{
	::std::list<::std::string> arr;
	if (!text.empty())
	{
		::std::string::size_type start = 0;
		::std::string::size_type end = text.find_first_of(delimiters, start);
		while (end != ::std::string::npos)
		{
			::std::string token = text.substr(start, end - start);
			if (!token.empty() || (token.empty() && pushEmpty))
			{
				if (vInversion) arr.emplace_front(token);
				else arr.emplace_back(token);
			}
			start = end + 1;
			end = text.find_first_of(delimiters, start);
		}
		::std::string token = text.substr(start);
		if (!token.empty() || (token.empty() && pushEmpty))
		{
			if (vInversion)
				arr.emplace_front(token);
			else
				arr.emplace_back(token);
		}
	}
	return arr;
}

::std::vector<::std::string> ct::splitStringToVector(const ::std::string& text, const std::string& delimiters, bool pushEmpty)
{
	::std::vector<::std::string> arr;
	if (!text.empty())
	{
		::std::string::size_type start = 0;
		::std::string::size_type end = text.find_first_of(delimiters, start);
		while (end != ::std::string::npos)
		{
			::std::string token = text.substr(start, end - start);
			if (!token.empty() || (token.empty() && pushEmpty))
				arr.emplace_back(token);
			start = end + 1;
			end = text.find_first_of(delimiters, start);
		}
		::std::string token = text.substr(start);
		if (!token.empty() || (token.empty() && pushEmpty))
			arr.emplace_back(token);
	}
	return arr;
}

::std::set<::std::string> ct::splitStringToSet(const ::std::string& text, const std::string& delimiters, bool pushEmpty)
{
	::std::set<::std::string> arr;
	if (!text.empty())
	{
		::std::string::size_type start = 0;
		::std::string::size_type end = text.find_first_of(delimiters, start);
		while (end != ::std::string::npos)
		{
			::std::string token = text.substr(start, end - start);
			if (!token.empty() || (token.empty() && pushEmpty))
				arr.emplace(token);
			start = end + 1;
			end = text.find_first_of(delimiters, start);
		}
		::std::string token = text.substr(start);
		if (!token.empty() || (token.empty() && pushEmpty))
			arr.emplace(token);
	}
	return arr;
}

::std::list<::std::string> ct::splitStringToList(const ::std::string& text, char delimiter, bool pushEmpty, bool vInversion)
{
	::std::list<::std::string> arr;
	if (!text.empty())
	{
		::std::string::size_type start = 0;
		::std::string::size_type end = text.find(delimiter, start);
		while (end != ::std::string::npos)
		{
			::std::string token = text.substr(start, end - start);
			if (!token.empty() || (token.empty() && pushEmpty))
			{
				if (vInversion) arr.emplace_front(token);
				else arr.emplace_back(token);
			}
			start = end + 1;
			end = text.find(delimiter, start);
		}
		::std::string token = text.substr(start);
		if (!token.empty() || (token.empty() && pushEmpty))
		{
			if (vInversion)
				arr.emplace_front(token);
			else
				arr.emplace_back(token);
		}
	}
	return arr;
}

::std::vector<::std::string> ct::splitStringToVector(const ::std::string& text, char delimiter, bool pushEmpty)
{
	::std::vector<::std::string> arr;
	if (!text.empty())
	{
		::std::string::size_type start = 0;
		::std::string::size_type end = text.find(delimiter, start);
		while (end != ::std::string::npos)
		{
			::std::string token = text.substr(start, end - start);
			if (!token.empty() || (token.empty() && pushEmpty))
				arr.emplace_back(token);
			start = end + 1;
			end = text.find(delimiter, start);
		}
		::std::string token = text.substr(start);
		if (!token.empty() || (token.empty() && pushEmpty))
			arr.emplace_back(token);
	}
	return arr;
}

::std::set<::std::string> ct::splitStringToSet(const ::std::string& text, char delimiter, bool pushEmpty)
{
	::std::set<::std::string> arr;
	if (!text.empty())
	{
		::std::string::size_type start = 0;
		::std::string::size_type end = text.find(delimiter, start);
		while (end != ::std::string::npos)
		{
			::std::string token = text.substr(start, end - start);
			if (!token.empty() || (token.empty() && pushEmpty))
				arr.emplace(token);
			start = end + 1;
			end = text.find(delimiter, start);
		}
		::std::string token = text.substr(start);
		if (!token.empty() || (token.empty() && pushEmpty))
			arr.emplace(token);
	}
	return arr;
}

/////////////////////////////////////////////////////////////
///////// StringToVector ////////////////////////////////////
/////////////////////////////////////////////////////////////

/*
#ifndef MINGW32
bool ct::StringToFloat(const ::std::string &vWord, float *vFloat)
{
	::std::stringstream ss;
	float vUniform = 0.0f;
	if (vWord.find_first_not_of("-+0123456789.") == ::std::string::npos)
	{
		ss.
		IsItaFloat >> vUniform;
		if (IsItaFloat)
		{
			*vFloat = vUniform;
			return true;
		}
	}
	return false;
}
bool ct::StringToInt(::std::string vWord, int *vInt)
{
	int vUniform = 0;
	if (vWord.find_first_not_of("-+0123456789") == ::std::string::npos)
	{
		::std::stringstream IsItaInt = ::std::stringstream(vWord);
		IsItaInt >> vUniform;
		if (IsItaInt)
		{
			*vInt = vUniform;
			return true;
		}
	}
	return false;
}
#endif
*/

#ifdef WXWIDGETS
::std::wstring ct::s2ws(const ::std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	::std::wstring r(buf);
	delete[] buf;
	return r;
}
#endif

::std::vector<::std::string::size_type> ct::strContains(const ::std::string& text, const ::std::string& word)
{
	::std::vector<::std::string::size_type> result;

	::std::string::size_type loc = 0;
	while ((loc = text.find(word, loc)) != ::std::string::npos)
	{
		result.emplace_back(loc);
		loc += word.size();
	}

	return result;
}

/////////////////////////////////////////////////////////////
///////// replaceString ////////////////////////////////////
/////////////////////////////////////////////////////////////

bool ct::replaceString(::std::string& str, const ::std::string& oldStr, const ::std::string& newStr)
{
	bool found = false;
	size_t pos = 0;
	while ((pos = str.find(oldStr, pos)) != ::std::string::npos)
	{
		found = true;
		str.replace(pos, oldStr.length(), newStr);
		pos += newStr.length();
	}
	return found;
}

/////////////////////////////////////////////////////////////
///////// Count Occurence ///////////////////////////////////
/////////////////////////////////////////////////////////////

size_t ct::GetCountOccurence(const ::std::string& vSrcString, const ::std::string& vStringToCount)
{
	size_t count = 0;
	size_t pos = 0;
	const auto len = vStringToCount.length();
	while ((pos = vSrcString.find(vStringToCount, pos)) != ::std::string::npos)
	{
		++count;
		pos += len;
	}
	return count;
}
size_t ct::GetCountOccurenceInSection(const ::std::string& vSrcString, size_t vStartPos, size_t vEndpos, const ::std::string& vStringToCount)
{
	size_t count = 0;
	size_t pos = vStartPos;
	const auto len = vStringToCount.length();
	while (pos < vEndpos && (pos = vSrcString.find(vStringToCount, pos)) != ::std::string::npos)
	{
		if (pos < vEndpos)
		{
			++count;
			pos += len;
		}
	}
	return count;
}

// can be more fast if char is used
size_t ct::GetCountOccurence(const ::std::string& vSrcString, const char& vStringToCount)
{
	size_t count = 0;
	size_t pos = 0;
	while ((pos = vSrcString.find(vStringToCount, pos)) != ::std::string::npos)
	{
		++count;
		pos++;
	}
	return count;
}

// can be more fast if char is used
size_t ct::GetCountOccurenceInSection(const ::std::string& vSrcString, size_t vStartPos, size_t vEndpos, const char& vStringToCount)
{
	size_t count = 0;
	size_t pos = vStartPos;
	while (pos < vEndpos && (pos = vSrcString.find(vStringToCount, pos)) != ::std::string::npos)
	{
		if (pos < vEndpos)
		{
			++count;
			pos++;
		}
	}
	return count;
}
// std::wstring to std::string
// std::wstring(unicode/multibytes/char16/wchar_t) to std::string(char)
std::string ct::wstring_to_string(const std::wstring& wstr)
{
	std::mbstate_t state = std::mbstate_t();
	const std::size_t len = wstr.size();
	std::vector<char> mbstr(len);
	const wchar_t* wptr = wstr.c_str();
#ifdef MSVC
	size_t res = 0;
	/*errno_t err = */wcsrtombs_s(&res, &mbstr[0], len, &wptr, mbstr.size(), &state);
#else
	std::wcsrtombs(&mbstr[0], &wptr, mbstr.size(), &state);
#endif
	return std::string(mbstr.data(), mbstr.size());
}

// std::string to std::wstring
// std::string(char) to std::wstring(unicode/multibytes/char16/wchar_t)
std::wstring ct::string_to_wstring(const std::string& mbstr)
{
	std::mbstate_t state = std::mbstate_t();
	const std::size_t len = mbstr.size();
	std::vector<wchar_t> wstr(len);
	const char* ptr = mbstr.c_str();
#ifdef MSVC
	size_t res = 0;
	/*errno_t err = */mbsrtowcs_s(&res, &wstr[0], len, &ptr, wstr.size(), &state);
#else
	std::mbsrtowcs(&wstr[0], &ptr, wstr.size(), &state);
#endif
	return std::wstring(wstr.data(), wstr.size());
}

/////////////////////////////////////////////////////////////
///////// ct::ActionTime ////////////////////////////////////
/////////////////////////////////////////////////////////////

uint64_t ct::GetTicks()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::system_clock::now().time_since_epoch()).count();
}

static uint64_t lastTick = ct::GetTicks();

float ct::GetTimeInterval()
{
	const uint64_t ticks = GetTicks();
	static float secMult = 1.0f / 1000.0f;
	const float interval = (ticks - lastTick) * secMult;
	lastTick = ticks;
	return interval;
}

ct::ActionTime::ActionTime()
{
	lastTick = GetTicks();
}

void ct::ActionTime::Fix() // fixe les marqueur de temps
{
	lastTick = GetTicks();
	pauseTick = GetTicks();
	resumeTick = GetTicks();
}

void ct::ActionTime::FixTime(double vValue) // fixe les marqueur de temps
{
	Fix();
	setTime(vValue);
}

void ct::ActionTime::Pause()
{
	pauseTick = GetTicks();
	play = false;
}

void ct::ActionTime::Resume()
{
	resumeTick = GetTicks();
	lastTick += resumeTick - pauseTick;
	play = true;
}

uint64_t ct::ActionTime::Get() const
{
	return ct::GetTicks() - lastTick;
}

double ct::ActionTime::GetTime() const
{
	static double secMult = 1.0 / 1000.0;
	return (ct::GetTicks() - lastTick) * secMult;
}

void ct::ActionTime::setTime(double vValue)
{
	const auto v = (uint64_t)(((double)vValue) * 1000.0);
	lastTick = ct::GetTicks() - v;
}

bool ct::ActionTime::IsTimeToAct(long vMs, bool vFix)
{
	if (Get() > (uint64_t)vMs)
	{
		if (vFix)
			Fix();
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////
///// ct::texture //////////////////////////////////////////////
/////////////////////////////////////////////////////////////
#ifdef USE_OPENGL
::std::string ct::texture::GetString() const
{
	::std::string res;

	res += "----------------------------------------------\n";

	if (glTextureType == GL_TEXTURE_1D)					res += "type = GL_TEXTURE_1D\n";
	else if (glTextureType == GL_TEXTURE_2D)			res += "type = GL_TEXTURE_2D\n";
	else if (glTextureType == GL_TEXTURE_3D)			res += "type = GL_TEXTURE_3D\n";

	if (glformat == GL_RGBA)							res += "format = GL_RGBA\n";
	else if (glformat == GL_RGB)						res += "format = GL_RGB\n";

	if (glinternalformat == GL_RGBA)					res += "internal format = GL_RGBA\n";
	else if (glinternalformat == GL_RGBA32F)			res += "internal format = GL_RGBA32F\n";

	if (gldatatype == GL_FLOAT)							res += "Data Type = GL_FLOAT\n";
	else if (gldatatype == GL_UNSIGNED_BYTE)			res += "Data Type = GL_UNSIGNED_BYTE\n";

	if (glWrapS == GL_CLAMP_TO_EDGE)					res += "Wrap S = GL_CLAMP_TO_EDGE\n";
	else if (glWrapS == GL_REPEAT)						res += "Wrap S = GL_REPEAT\n";
	else if (glWrapS == GL_MIRRORED_REPEAT)				res += "Wrap S = GL_MIRRORED_REPEAT\n";

	if (glWrapT == GL_CLAMP_TO_EDGE)					res += "Wrap T = GL_CLAMP_TO_EDGE\n";
	else if (glWrapT == GL_REPEAT)						res += "Wrap T = GL_REPEAT\n";
	else if (glWrapT == GL_MIRRORED_REPEAT)				res += "Wrap T = GL_MIRRORED_REPEAT\n";

	if (glWrapR == GL_CLAMP_TO_EDGE)					res += "Wrap R = GL_CLAMP_TO_EDGE\n";
	else if (glWrapR == GL_REPEAT)						res += "Wrap R = GL_REPEAT\n";
	else if (glWrapR == GL_MIRRORED_REPEAT)				res += "Wrap R = GL_MIRRORED_REPEAT\n";

	if (useMipMap)										res += "Use MipMap = True\n";
	else												res += "Use MipMap = False\n";

	res += "MipMap Max Level = " + ct::toStr(maxMipMapLvl) + "\n";

	if (glMinFilter == GL_LINEAR)						res += "Min Filter = GL_LINEAR\n";
	else if (glMinFilter == GL_NEAREST)					res += "Min Filter = GL_NEAREST\n";
	else if (glMinFilter == GL_NEAREST_MIPMAP_NEAREST)	res += "Min Filter = GL_NEAREST_MIPMAP_NEAREST\n";
	else if (glMinFilter == GL_LINEAR_MIPMAP_NEAREST)	res += "Min Filter = GL_LINEAR_MIPMAP_NEAREST\n";
	else if (glMinFilter == GL_NEAREST_MIPMAP_LINEAR)	res += "Min Filter = GL_NEAREST_MIPMAP_LINEAR\n";
	else if (glMinFilter == GL_LINEAR_MIPMAP_LINEAR)	res += "Min Filter = GL_LINEAR_MIPMAP_LINEAR\n";

	if (glMagFilter == GL_LINEAR)						res += "Mag Filter = GL_LINEAR\n";
	else if (glMagFilter == GL_NEAREST)					res += "Mag Filter = GL_NEAREST\n";

	res += "Size = " + ct::toStr(w) + "," + ct::toStr(h) + "," + ct::toStr(d) + "\n";

	res += "----------------------------------------------\n";

	return res;
}
#endif
/////////////////////////////////////////////////////////////
///////// BUFFERS ///////////////////////////////////////////
/////////////////////////////////////////////////////////////

void ct::AppendToBuffer(char* vBuffer, size_t vBufferLen, const ::std::string& vStr)
{
	::std::string st = vStr;
	if (!st.empty() && st != "\n")
	{
		ct::replaceString(st, "\r", "");
		ct::replaceString(st, "\n", "");
		//LogVar(st);
	}

	const size_t slen = strlen(vBuffer);
	vBuffer[slen] = '\0';
	::std::string str = ::std::string(vBuffer);
	if (!str.empty()) str += "\n";
	str += vStr;
	const auto len = ct::mini<size_t>(vBufferLen - 1, str.size());

#ifdef MSVC
	strncpy_s(vBuffer, vBufferLen, str.c_str(), len);
#else
	strncpy(vBuffer, str.c_str(), len);
#endif

	vBuffer[len] = '\0';
}

void ct::ResetBuffer(char* vBuffer)
{
	vBuffer[0] = '\0';
}

/////////////////////////////////////////////////////////////
///////// GetNewBufferFromList //////////////////////////////
/////////////////////////////////////////////////////////////

// Buffer a destroy apres utilisationBufferSize
// in : lst, offset
// out : return, BufferSize
template<typename T>
T* ct::GetNewBufferFromList(::std::list<T>& lst, int offsetBefore, int offsetAfter, int* BufferSize)
{
	const int count = (int)lst.size();
	if (count > 0)
	{
		*BufferSize = count + offsetBefore + offsetAfter;
		T* Buffer = new T[(*BufferSize)]; size_t idx = offsetBefore;
		// before init
		for (size_t i = 0; i < (size_t)offsetBefore; ++i)
		{
			Buffer[i] = T();
		}
		// content
		for (typename ::std::list<T>::iterator it = lst.begin(); it != lst.end(); ++it)
		{
			T obj = *it;
			Buffer[idx++] = obj;
		}
		// after init
		for (size_t i = 0; i < (size_t)offsetAfter; ++i)
		{
			Buffer[idx + i] = T();
		}
		return Buffer;
	}
	return nullptr;
}

/////////////////////////////////////////////////////////////
///////// GetNewBufferFromMap ///////////////////////////////
/////////////////////////////////////////////////////////////

// Buffer a destroy apres utilisationBufferSize
// in : lst, offset
// out : return, BufferSize
template<typename T, typename P>
P* ct::GetNewBufferFromMap(::std::map<T, P>& mp, int offsetBefore, int offsetAfter, int* BufferSize)
{
	const int count = (int)mp.size();
	if (count > 0)
	{
		*BufferSize = count + offsetBefore + offsetAfter;
		P* Buffer = new P[(*BufferSize)]; int idx = offsetBefore;
		// before init
		for (size_t i = 0; i < (size_t)offsetBefore; ++i)
		{
			Buffer[i] = P();
		}
		// content
		for (typename ::std::map<T, P>::iterator it = mp.begin(); it != mp.end(); ++it)
		{
			//			T key = it->first;
			P obj = it->second;

			Buffer[idx++] = obj;
		}
		// after init
		for (size_t i = 0; i < (size_t)offsetAfter; ++i)
		{
			Buffer[idx + i] = P();
		}
		return Buffer;
	}
	return nullptr;
}

/////////////////////////////////////////////////////////////
///////// DeleteObjectsAndClearPointerList //////////////////
/////////////////////////////////////////////////////////////

template<typename T>
void ct::DeleteObjectsAndClearPointerList(::std::list<T*>& lst)
{
	if (!lst.empty())
	{
		for (typename ::std::list<T*>::iterator it = lst.begin(); it != lst.end(); ++it)
		{
			T* type = nullptr;
			type = *it;
			if (type != nullptr)
			{
				delete type;
				*it = 0;
			}
		}
		lst.clear();
	}
}

template<typename T>
void ct::DeleteObjectsAndClearPointerVector(::std::vector<T*>& vec)
{
	if (!vec.empty())
	{
		for (typename ::std::vector<T*>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			T* type = nullptr;
			type = *it;
			if (type != nullptr)
			{
				delete type;
				*it = 0;
			}
		}

		vec.clear();
	}
}

template<typename T>
::std::string ct::VectorToString(::std::vector<T>& vec, char vCharDelimiter)
{
	::std::string res;

	if (!vec.empty())
	{
		for (auto it = vec.begin(); it != vec.end(); ++it)
		{
			if (it != vec.begin())
				res += vCharDelimiter;
			res += ct::toStr(*it);
		}
	}

	return res;
}

template<typename T>
::std::string ct::VectorVec2ToString(::std::vector<ct::vec2<T>>& vec, char vCharDelimiter)
{
	::std::string res;

	if (!vec.empty())
	{
		for (auto it = vec.begin(); it != vec.end(); ++it)
		{
			if (it != vec.begin())
				res += vCharDelimiter;
			res += (*it).string();
		}
	}

	return res;
}

template<typename T>
::std::string ct::VectorVec3ToString(::std::vector<ct::vec3<T>>& vec, char vCharDelimiter)
{
	::std::string res;

	if (!vec.empty())
	{
		for (auto it = vec.begin(); it != vec.end(); ++it)
		{
			if (it != vec.begin())
				res += vCharDelimiter;
			res += (*it).string();
		}
	}

	return res;
}

template<typename T>
::std::string ct::VectorVec4ToString(::std::vector<ct::vec4<T>>& vec, char vCharDelimiter)
{
	::std::string res;

	if (!vec.empty())
	{
		for (auto it = vec.begin(); it != vec.end(); ++it)
		{
			if (it != vec.begin())
				res += vCharDelimiter;
			res += (*it).string();
		}
	}

	return res;
}

// return "vParamName=\"" + ct::toStr(vValue) + "\";
template<typename T>
::std::string ct::ParamToXMLString(::std::string vParamName, T vValue)
{
	return " " + vParamName + "=\"" + ct::toStr(vValue) + "\"";
}

// return "vParamName=\"" + ct::toStr(vValue) + "\" si vValue est different de vValueDiff;
template<typename T>
::std::string ct::ParamToXMLStringDiff(::std::string vParamName, T vValue, T vValueDiff)
{
	if (vValue != vValueDiff)
		return " " + vParamName + "=\"" + ct::toStr(vValue) + "\"";
	return "";
}
/// Mix : Get value based on ratio and inf and sup limit // https://www.opengl.org/sdk/docs/man/html/mix.xhtml
// ex : ct::mix(2.0f, 6.0f, 0.5f) => 4.0f

template<typename T>
ct::vec2<T> ct::mix(const ct::vec2<T>& vInf, const ct::vec2<T>& vSup, const ct::vec2<T>& vRatio)
{
	return vInf * (1.0f - vRatio) + vSup * vRatio;
}

template<typename T>
ct::vec3<T> ct::mix(const ct::vec3<T>& vInf, const ct::vec3<T>& vSup, const ct::vec3<T>& vRatio)
{
	return vInf * (1.0f - vRatio) + vSup * vRatio;
}

template<typename T>
ct::vec4<T> ct::mix(const ct::vec4<T>& vInf, const ct::vec4<T>& vSup, const ct::vec4<T>& vRatio)
{
	return vInf * (1.0f - vRatio) + vSup * vRatio;
}

/// Get ratio based on value and inf and sup limit
// ex : cRatio(2.0f, 6.0f, 4.0f) => 0.5f
template<typename T>
ct::vec2<T> ct::invMix(const ct::vec2<T>& vInf, const ct::vec2<T>& vSup, const ct::vec2<T>& vValue)
{
	return (vValue - vInf) / (vSup - vInf);
}

template<typename T>
ct::vec3<T> ct::invMix(const ct::vec3<T>& vInf, const ct::vec3<T>& vSup, const ct::vec3<T>& vValue)
{
	return (vValue - vInf) / (vSup - vInf);
}

template<typename T>
ct::vec4<T> ct::invMix(const ct::vec4<T>& vInf, const ct::vec4<T>& vSup, const ct::vec4<T>& vValue)
{
	return (vValue - vInf) / (vSup - vInf);
}

/// clamp

template<typename T>
ct::vec2<T> ct::clamp(const ct::vec2<T>& vValue, const ct::vec2<T>& vInf, const ct::vec2<T>& vSup)
{
	ct::vec2<T> vUniform = vValue;
	vUniform.x = ct::clamp(vUniform.x, vInf.x, vSup.x);
	vUniform.y = ct::clamp(vUniform.y, vInf.y, vSup.y);
	return vUniform;
}

template<typename T>
ct::vec3<T> ct::clamp(const ct::vec3<T>& vValue, const ct::vec3<T>& vInf, const ct::vec3<T>& vSup)
{
	ct::vec3<T> vUniform = vValue;
	vUniform.x = ct::clamp(vUniform.x, vInf.x, vSup.x);
	vUniform.y = ct::clamp(vUniform.y, vInf.y, vSup.y);
	vUniform.z = ct::clamp(vUniform.z, vInf.z, vSup.z);
	return vUniform;
}

template<typename T>
ct::vec4<T> ct::clamp(const ct::vec4<T>& vValue, const ct::vec4<T>& vInf, const ct::vec4<T>& vSup)
{
	ct::vec4<T> vUniform = vValue;
	vUniform.x = ct::clamp(vUniform.x, vInf.x, vSup.x);
	vUniform.y = ct::clamp(vUniform.y, vInf.y, vSup.y);
	vUniform.z = ct::clamp(vUniform.z, vInf.z, vSup.z);
	vUniform.w = ct::clamp(vUniform.w, vInf.w, vSup.w);
	return vUniform;
}

/*template<typename T>
ct::vec2<T> ct::clamp(const ct::vec2<T>& vValue, T vInf, T vSup)
{
	ct::vec2<T> vUniform = vValue;
	vUniform.x = ct::clamp(vUniform.x, vInf, vSup);
	vUniform.y = ct::clamp(vUniform.y, vInf, vSup);
	return vUniform;
}*/

template<typename T>
ct::vec3<T> ct::clamp(const ct::vec3<T>& vValue, T vInf, T vSup)
{
	ct::vec3<T> vUniform = vValue;
	vUniform.x = ct::clamp(vUniform.x, vInf, vSup);
	vUniform.y = ct::clamp(vUniform.y, vInf, vSup);
	vUniform.z = ct::clamp(vUniform.z, vInf, vSup);
	return vUniform;
}

template<typename T>
ct::vec4<T> ct::clamp(const ct::vec4<T>& vValue, T vInf, T vSup)
{
	ct::vec4<T> vUniform = vValue;
	vUniform.x = ct::clamp(vUniform.x, vInf, vSup);
	vUniform.y = ct::clamp(vUniform.y, vInf, vSup);
	vUniform.z = ct::clamp(vUniform.z, vInf, vSup);
	vUniform.w = ct::clamp(vUniform.w, vInf, vSup);
	return vUniform;
}

template<typename T>
ct::vec2<T> ct::clamp(const ct::vec2<T>& vValue)
{
	ct::vec2<T> vUniform = vValue;
	vUniform.x = ct::clamp(vUniform.x);
	vUniform.y = ct::clamp(vUniform.y);
	return vUniform;
}

template<typename T>
ct::vec3<T> ct::clamp(const ct::vec3<T>& vValue)
{
	ct::vec3<T> vUniform = vValue;
	vUniform.x = ct::clamp(vUniform.x);
	vUniform.y = ct::clamp(vUniform.y);
	vUniform.z = ct::clamp(vUniform.z);
	return vUniform;
}

template<typename T>
ct::vec4<T> ct::clamp(const ct::vec4<T>& vValue)
{
	ct::vec4<T> vUniform = vValue;
	vUniform.x = ct::clamp(vUniform.x);
	vUniform.y = ct::clamp(vUniform.y);
	vUniform.z = ct::clamp(vUniform.z);
	vUniform.w = ct::clamp(vUniform.w);
	return vUniform;
}

// ct::mod

template<typename T>
ct::vec2<T> ct::mod(const ct::vec2<T>& vValue, const ct::vec2<T>& vLim)
{
	ct::vec2<T> vUniform = vValue;
	vUniform.x = ct::mod(vUniform.x, vLim.x);
	vUniform.y = ct::mod(vUniform.y, vLim.y);
	return vUniform;
}

template<typename T>
ct::vec3<T> ct::mod(const ct::vec3<T>& vValue, const ct::vec3<T>& vLim)
{
	ct::vec3<T> vUniform = vValue;
	vUniform.x = ct::mod(vUniform.x, vLim.x);
	vUniform.y = ct::mod(vUniform.y, vLim.y);
	vUniform.z = ct::mod(vUniform.z, vLim.z);
	return vUniform;
}

template<typename T>
ct::vec4<T> ct::mod(const ct::vec4<T>& vValue, const ct::vec4<T>& vLim)
{
	ct::vec4<T> vUniform = vValue;
	vUniform.x = ct::mod(vUniform.x, vLim.x);
	vUniform.y = ct::mod(vUniform.y, vLim.y);
	vUniform.z = ct::mod(vUniform.z, vLim.z);
	vUniform.w = ct::mod(vUniform.w, vLim.w);
	return vUniform;
}

template<typename T>
ct::vec2<T> ct::mod(const ct::vec2<T>& vValue, T vLim)
{
	ct::vec2<T> vUniform = vValue;
	vUniform.x = ct::mod(vUniform.x, vLim);
	vUniform.y = ct::mod(vUniform.y, vLim);
	return vUniform;
}

template<typename T>
ct::vec3<T> ct::mod(const ct::vec3<T>& vValue, T vLim)
{
	ct::vec3<T> vUniform = vValue;
	vUniform.x = ct::mod(vUniform.x, vLim);
	vUniform.y = ct::mod(vUniform.y, vLim);
	vUniform.z = ct::mod(vUniform.z, vLim);
	return vUniform;
}

template<typename T>
ct::vec4<T> ct::mod(const ct::vec4<T>& vValue, T vLim)
{
	ct::vec4<T> vUniform = vValue;
	vUniform.x = ct::mod(vUniform.x, vLim);
	vUniform.y = ct::mod(vUniform.y, vLim);
	vUniform.z = ct::mod(vUniform.z, vLim);
	vUniform.w = ct::mod(vUniform.w, vLim);
	return vUniform;
}
// ReRange value from range 0-MaxRange to range Sup-Inf and return new value
// 0 ----- Inf ----- value ---- Sup ---- MaxRange
template<typename T>
T ct::cReRange(T vMaxRange,
	T vNewRangeInf, T vNewRangeSup,
	T vValue)
{
	return (vValue - vNewRangeInf) * vMaxRange / (vNewRangeSup - vNewRangeInf);
}

/// Returns 1 for non-negative values and -1 for negative values.
size_t ct::ratioOfSizeT(size_t t, double r)
{
	return (size_t)(t * r);
}

/////////////////////////////////////////////////////////////////////////////////////////

//https://stackoverflow.com/questions/2685911/is-there-a-way-to-round-numbers-into-a-reader-friendly-format-e-g-1-1k?noredirect=1&lq=1
std::string ct::FormatNum(size_t vNum, int vDecimalCount)
{
	// 2 decimal places => 100, 3 => 1000, etc
	const auto decimalCount = (size_t)std::pow(10, vDecimalCount);

	// Enumerate number abbreviations
	char abbrev[] = { 'k', 'M', 'G', 'T' };
	const int abbrevLength = 4;

	// Go through the array backwards, so we do the largest first
	for (int i = abbrevLength - 1; i >= 0; i--)
	{
		// Convert array index to "1000", "1000000", etc
		const auto size = (size_t)std::pow(10, (i + 1) * 3);

		// If the number is bigger or equal do the abbreviation
		if (size <= vNum)
		{
			// Here, we multiply by decPlaces, round, and then divide by decPlaces.
			// This gives us nice rounding to a particular decimal place.
			vNum = (size_t)std::round(vNum * decimalCount / size) / decimalCount;

			// Handle special case where we round up to the next abbreviation
			if ((vNum == 1000) && (i < abbrevLength - 1)) {
				vNum = 1;
				++i;
			}

			// Add the letter for the abbreviation
			return ct::toStr(vNum) + " " + abbrev[i];

			// We are done... stop
			break;
		}
	}

	return ct::toStr(vNum);
}
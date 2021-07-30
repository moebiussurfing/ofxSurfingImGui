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

#pragma once

#include <tinyxml2/tinyxml2.h>

#include <fstream> // ifstream
#include <sstream> // stringstream
#include <string>
#include <map>

namespace conf
{
	class ConfigAbstract
	{
	public:
		virtual std::string getXml(const std::string& vOffset, const std::string& vUserDatas = "") = 0;
		// return true for continue xml parsing of childs in this node or false for interupt the child exploration
		virtual bool setFromXml(tinyxml2::XMLElement* vElem, tinyxml2::XMLElement* vParent, const std::string& vUserDatas = "") = 0;

	public:
		// replace patterns (who can break a xml code) by corresponding escaped pattern
		std::string escapeXmlCode(std::string vDatas)
		{
			// escape some patterns
			// https://stackoverflow.com/questions/1091945/what-characters-do-i-need-to-escape-in-xml-documents/46637835#46637835
			replaceString(vDatas, "&", "&amp;"); // do that in first :) else it will modify the others code who are starting by &
			replaceString(vDatas, "<", "&lt;");
			replaceString(vDatas, "\"", "&quot;");
			replaceString(vDatas, "'", "&apos;");
			replaceString(vDatas, ">", "&gt;");
			return vDatas;
		}

		// replace xml excaped pattern by corresponding good pattern
		std::string unEscapeXmlCode(std::string vDatas)
		{
			// unescape some patterns
			// https://stackoverflow.com/questions/1091945/what-characters-do-i-need-to-escape-in-xml-documents/46637835#46637835
			replaceString(vDatas, "&lt;", "<");
			replaceString(vDatas, "&amp;", "&");
			replaceString(vDatas, "&quot;", "\"");
			replaceString(vDatas, "&apos;", "'");
			replaceString(vDatas, "&gt;", ">");
			return vDatas;
		}

		tinyxml2::XMLError LoadConfigString(const std::string& vConfigString, const std::string& vUserDatas = "", const std::string& vFirstElement = "config")
		{
			return parseConfigDatas(vConfigString, vUserDatas, vFirstElement);
		}

		std::string SaveConfigString(const std::string& vUserDatas = "", const std::string& vFirstElement = "config")
		{
			return "<" + vFirstElement + ">\n" + getXml("\t", vUserDatas) + "</" + vFirstElement + ">\n";
		}

		tinyxml2::XMLError LoadConfigFile(const std::string& vFilePathName, const std::string& vUserDatas = "", const std::string& vFirstElement = "config")
		{
			tinyxml2::XMLError res = tinyxml2::XMLError::XML_CAN_NOT_CONVERT_TEXT;

			std::ifstream docFile(vFilePathName, std::ios::in);
			if (docFile.is_open())
			{
				std::stringstream strStream;

				strStream << docFile.rdbuf();//read the file

				res = LoadConfigString(strStream.str(), vUserDatas, vFirstElement);

				docFile.close();
			}
			else
			{
				res = tinyxml2::XMLError::XML_ERROR_FILE_COULD_NOT_BE_OPENED;
			}

			return res;
		}

		bool SaveConfigFile(const std::string& vFilePathName, const std::string& vUserDatas = "")
		{
			bool res = false;

			std::string data = SaveConfigString(vUserDatas);
			std::ofstream configFileWriter(vFilePathName, std::ios::out);
			if (!configFileWriter.bad())
			{
				configFileWriter << data;
				configFileWriter.close();
				res = true;
			}

			return res;
		}

		tinyxml2::XMLError parseConfigDatas(std::string vDatas, const std::string& vUserDatas = "", const std::string& vFirstElement = "config")
		{
			tinyxml2::XMLError res = tinyxml2::XMLError::XML_CAN_NOT_CONVERT_TEXT;

			try
			{
				replaceString(vDatas, "\r\n", "\n");

				tinyxml2::XMLDocument doc;
				res = doc.Parse(vDatas.c_str(), vDatas.size());

				if (res == tinyxml2::XMLError::XML_SUCCESS)
				{
					RecursParsingConfig(doc.FirstChildElement(vFirstElement.c_str()), 0, vUserDatas);
				}
				else
				{
					doc.PrintError();
				}
			}
			catch (std::exception& ex)
			{
				printf("parse error => %s", std::string(ex.what()).c_str());
			}

			return res;
		}

		void RecursParsingConfig(tinyxml2::XMLElement* vElem, tinyxml2::XMLElement* vParent, const std::string& vUserDatas = "")
		{
			if (setFromXml(vElem, vParent, vUserDatas))
			{
				// CHILDS
				// parse through all childs elements
				for (tinyxml2::XMLElement* child = vElem->FirstChildElement(); child != 0; child = child->NextSiblingElement())
				{
					RecursParsingConfig(child->ToElement(), vElem, vUserDatas);
				}
			}
		}

		std::string getTinyXml2ErrorMessage(tinyxml2::XMLError vErrorCode)
		{
			tinyxml2::XMLDocument doc;
			return std::string(doc.ErrorIDToName(vErrorCode));
		}

	private:
		bool replaceString(::std::string& str, const ::std::string& oldStr, const ::std::string& newStr)
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
	};
}

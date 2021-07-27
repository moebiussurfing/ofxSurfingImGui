#pragma once
#include "ofGLUtils.h"

//--------------------------------------------------------------
// ofxMyUtil GL
//--------------------------------------------------------------
namespace ofxMyUtil 
{
	namespace GL 
	{

		// OpenGLで使うテクスチャ読み込み
		GLuint loadTextureImage2D(unsigned char * pix, int width, int height);

	}
}
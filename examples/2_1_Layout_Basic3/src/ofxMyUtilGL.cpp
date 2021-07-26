#include "ofxMyUtilGL.h"

//--------------------------------------------------------------
// ofxMyUtil GL
//--------------------------------------------------------------
using namespace ofxMyUtil;

//--------------------------------------------------------------
GLuint GL::loadTextureImage2D(unsigned char * pix, int width, int height) 
{

	GLint last_texture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
	GLuint new_texture;
	// 作成
	glGenTextures(1, &new_texture);
	// バインド
	glBindTexture(GL_TEXTURE_2D, new_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(
		GL_TEXTURE_2D, 0,
		GL_RGBA, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, pix
	);

	// バインド
	glBindTexture(GL_TEXTURE_2D, last_texture);
	return new_texture;

}

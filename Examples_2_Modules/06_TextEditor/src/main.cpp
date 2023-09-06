#include "ofMain.h"
#include "ofApp.h"

int main()
{

#if defined(TARGET_OPENGLES)
  ofGLESWindowSettings settings;
  settings.setSize(1920, 1080);
  settings.setGLESVersion(2);
  ofCreateWindow(settings);
#else
  ofSetupOpenGL(1920, 1080, OF_WINDOW);
#endif

ofRunApp( new ofApp());

}

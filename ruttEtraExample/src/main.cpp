#include "ofMain.h"
#include "testApp.h"

//========================================================================
int main( ){

	// If we want shaders on the Pi, we need to set the renderer to the programmable renderer
#ifdef TARGET_OPENGLES
	ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
#endif

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp( new testApp());
}

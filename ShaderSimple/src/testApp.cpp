#include "testApp.h"

// ---------------------------------------------------------------------------------------------------------------------------------------------------
//
void testApp::setup()
{
	ofBackground( 0, 0, 0 );
	
	fontSmall.loadFont("Fonts/DIN.otf", 8 );
	
	// We need to load different shaders for mobile (or Pi) and desktop.
#ifdef TARGET_OPENGLES
	shader.load("Shaders/ShaderGLES");
#else
	shader.load("Shaders/ShaderDesktop");
#endif
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------
//
void testApp::update()
{

}

// ---------------------------------------------------------------------------------------------------------------------------------------------------
//
void testApp::draw()
{
	ofSetColor(255);
	
	shader.begin();
		shader.setUniform1f("time", ofGetElapsedTimef() );

		// we need to draw something for the shader to run on those pixels 
		ofRect(0, 0, ofGetWidth(), ofGetHeight() );
	
	shader.end();

		
	ofSetColor( 128, 128, 128 );
	fontSmall.drawString( "fps: " + ofToString( ofGetFrameRate(), 1), 5, ofGetHeight() - 10 );
}
// ---------------------------------------------------------------------------------------------------------------------------------------------------
//
void testApp::keyPressed(int key)
{
}

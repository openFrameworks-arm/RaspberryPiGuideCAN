#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetVerticalSync(false);
	
	string videoPath = ofToDataPath("../../../videos/720p.mov", true);
	
	// this will just set videoPath to the first video in the videos folder, if any.
	ofDirectory currentVideoDirectory(ofToDataPath("videos", true));
	if (currentVideoDirectory.exists()) 
	{
		currentVideoDirectory.listDir();
		vector<ofFile> files = currentVideoDirectory.getFiles();
		if (files.size()>0) 
		{
			videoPath = files[0].path();
		}		
	}
	
	//Somewhat like ofFboSettings we may have a lot of options so this is the current model
	ofxOMXPlayerSettings settings;
	settings.videoPath = videoPath;
	settings.useHDMIForAudio = true;	//default true
	settings.enableTexture = false;		//default true
	settings.enableLooping = true;		//default true

	omxPlayer.setup(settings);
}

//--------------------------------------------------------------
void testApp::update() {
	//update background tasks here
}

//--------------------------------------------------------------
void testApp::draw(){
	//not used as the non-textured player takes over the screen
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key) { }

//--------------------------------------------------------------
void testApp::keyReleased(int key) { }

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) { }

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) {}


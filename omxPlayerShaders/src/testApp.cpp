#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetVerticalSync(false);
	
	string videoPath = ofToDataPath("../../../videos/big_buck_bunny_MpegStreamclip_720p_h264_50Quality_48K_256k_AAC.mov", true);
	
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
	
	shader.load("PostProcessing.vert", "PostProcessing.frag" );
	
	//Somewhat like ofFboSettings we may have a lot of options so this is the current model
	ofxOMXPlayerSettings settings;
	settings.videoPath = videoPath;
	settings.useHDMIForAudio = true;	//default true
	settings.enableTexture = true;		//default true
	settings.enableLooping = true;		//default true

	omxPlayer.setup(settings);
}

//--------------------------------------------------------------
void testApp::update()
{
}

//--------------------------------------------------------------
void testApp::draw(){
	
	shader.begin();
		shader.setUniformTexture("tex0", omxPlayer.getTextureReference(), omxPlayer.getTextureID());
		shader.setUniform1f("time", ofGetElapsedTimef());
		shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
		omxPlayer.draw(0,0);
	shader.end();
	
	//draw a smaller version in the lower right
	int scaledHeight = omxPlayer.getHeight()/4;
	int scaledWidth = omxPlayer.getWidth()/4;
	//omxPlayer.draw(ofGetWidth()-scaledWidth, ofGetHeight()-scaledHeight, scaledWidth, scaledHeight);
	
	// and osme info
	stringstream info;
	info << "APP FPS: "+ ofToString(ofGetFrameRate());
	/*info <<"\n" <<	"MEDIA TIME: "			<< omxPlayer.getMediaTime();
	info <<"\n" <<	"DIMENSIONS: "			<< omxPlayer.getWidth()<<"x"<<omxPlayer.getHeight();
	info <<"\n" <<	"DURATION: "			<< omxPlayer.getDuration();
	info <<"\n" <<	"TOTAL FRAMES: "		<< omxPlayer.getTotalNumFrames();
	info <<"\n" <<	"CURRENT FRAME: "		<< omxPlayer.getCurrentFrame();
	info <<"\n" <<	"REMAINING FRAMES: "	<< omxPlayer.getTotalNumFrames() - omxPlayer.getCurrentFrame();
	info <<"\n" <<	"CURRENT VOLUME: "		<< omxPlayer.getVolume();*/

	ofDrawBitmapStringHighlight(info.str(), 60, 60, ofColor(ofColor::black, 90), ofColor::yellow);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ }

//--------------------------------------------------------------
void testApp::keyReleased(int key){ }

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){ }

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


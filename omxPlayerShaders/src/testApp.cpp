#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	//When using shaders on the Pi is a good idea to use an FBO 
	//in order to isolate the shader
	
	fbo.allocate(ofGetWidth(), ofGetHeight());
	
	
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
	
	/*
		To load shaders in OF you have a couple of options
		The simplest is to name your shaders *.vert and *frag
		In our case the file names are shaderExample.vert and shaderExample.frag
		and are located in the bin/data folder

		We can then use:
	*/
	
	shader.load("shaderExample");
	
	/*
		You also can be more explict which is useful if you are swapping around different 
		.frag implementations. In that case you could do something like
		shader.load("shaderExample.vert", "someOtherShaderExample.frag" );
	 */
	
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
	/*
		Due to some current OF quirks if you use
		an FBO/Shader combo on the RPi
		you must do it in update()
	 */
	
	fbo.begin();
		shader.begin();
			//Here we tell pass our shader some changing values
			
			//We pass our texture id 
			shader.setUniformTexture("tex0", omxPlayer.getTextureReference(), omxPlayer.getTextureID());
			
			//We give it an incrementing value to use
			shader.setUniform1f("time", ofGetElapsedTimef());
			
			//And a resolution
			shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	
			//We then send our texture that kicks it off
			omxPlayer.draw(0,0);
		shader.end();
	fbo.end();
}

//--------------------------------------------------------------
void testApp::draw(){
	
	
	fbo.draw(0, 0);
	
	//draw a smaller version in the lower right
	int scaledHeight = fbo.getHeight()/4;
	int scaledWidth = fbo.getWidth()/4;
	fbo.draw(ofGetWidth()-scaledWidth, ofGetHeight()-scaledHeight, scaledWidth, scaledHeight);
	
	// and some info
	stringstream info;
	info << "APP FPS: "+ ofToString(ofGetFrameRate());
	info <<"\n" <<	"MEDIA TIME: "			<< omxPlayer.getMediaTime();
	info <<"\n" <<	"DIMENSIONS: "			<< omxPlayer.getWidth()<<"x"<<omxPlayer.getHeight();
	info <<"\n" <<	"DURATION: "			<< omxPlayer.getDuration();
	info <<"\n" <<	"TOTAL FRAMES: "		<< omxPlayer.getTotalNumFrames();
	info <<"\n" <<	"CURRENT FRAME: "		<< omxPlayer.getCurrentFrame();
	info <<"\n" <<	"REMAINING FRAMES: "	<< omxPlayer.getTotalNumFrames() - omxPlayer.getCurrentFrame();
	info <<"\n" <<	"CURRENT VOLUME: "		<< omxPlayer.getVolume();

	ofDrawBitmapStringHighlight(info.str(), 60, 60, ofColor(ofColor::black, 90), ofColor::yellow);
}



#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	#ifdef TARGET_OPENGLES
		ofHideCursor();
	#endif
	
	#ifdef _USE_LIVE_VIDEO
        vidGrabber.setVerbose(true);
        vidGrabber.initGrabber(320,240);
	#else
        vidPlayer.loadMovie("movies/fingers.mp4");
        vidPlayer.play();
	#endif

    colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	

	// We need to load different shaders for mobile (or Pi) and desktop.
#ifdef TARGET_OPENGLES
	colorFromHeightShader.load("shaders/ColorFromHeightGLES");
#else
	colorFromHeightShader.load("shaders/ColorFromHeight");
#endif
	
	camera.setFov( 60.0f );
	camera.setNearClip( 0.01f );
	camera.setFarClip( 1024.0f );
	camera.setAutoDistance( false );
	camera.orbit(10.0f, -60.0f, 250.0f );
	
	// load all the png images in the folder data/palettes
	ofDirectory tmpDir;
	tmpDir.allowExt( "png" );
	int numFiles = tmpDir.listDir( "palettes" );
	for( int i = 0; i < numFiles; i++ )
	{
		ofImage tmpImage;
		tmpImage.loadImage( tmpDir.getPath(i) );
		palettes.push_back( tmpImage );
	}

	currPalette = NULL;
	if( palettes.size() > 0 ) currPalette = &palettes.at(0);
	
	linesHeight = 20.0f;

	lineSkip = 10;
	
	lastClickTime = -9999.0f;
}

//--------------------------------------------------------------
void testApp::update()
{
	ofBackground(0,0,0);

	// grab new frame and update colorImg with it.
    bool bNewFrame = false;

	#ifdef _USE_LIVE_VIDEO
       vidGrabber.update();
	   bNewFrame = vidGrabber.isFrameNew();
    #else
        vidPlayer.update();
        bNewFrame = vidPlayer.isFrameNew();
	#endif

	if (bNewFrame){
		
		#ifdef _USE_LIVE_VIDEO
            colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
	    #else
            colorImg.setFromPixels(vidPlayer.getPixels(), 320,240);
        #endif

        grayImage = colorImg; // converts from color to greyscale
	}

	float time = ofGetElapsedTimef();

	// Update mesh from grayImage's pixels
	updateMesh();
	
	// update a few variables based on time
	float timeToChangePalettes = 10.0f;
	int paletteIndex = (int) ((ofWrap( time, 0.0f, timeToChangePalettes ) / timeToChangePalettes ) * palettes.size());
	if( palettes.size() > 0 && paletteIndex < palettes.size())  currPalette = &palettes.at(paletteIndex);
		
	linesHeight = 80.0f;
	
	lineSkip = 4; //ofMap( cos(time * 1.1f), -1.0f, 1.0f, 2, 25 );
	
	// if we click, wait a bit until we auto orbit the camera
	if( (time - lastClickTime) > 4.0 )
	{
		float orbitLong = ofMap( ofNoise(time*0.2f), 0.0f, 1.0f, -50.0f, 50.0f ) ;
		float orbitLat = ofMap( ofNoise( (time+111.0f)*0.3f), 0.0f, 1.0f, 0.0f, -100.0f ) ;
		float orbitRadius = ofMap( ofNoise( (time-123.0f)*0.45f), 0.0f, 1.0f, 100.0f, 250.0f ) ;
		camera.orbit(orbitLong, orbitLat, orbitRadius );
	}

	if( ofGetFrameNum() % 30 == 0 ) ofLogNotice() <<  "fps: " << ofToString( ofGetFrameRate(), 1); 
}

//--------------------------------------------------------------
void testApp::draw(){

	grayImage.draw(0,0);
	
	ofEnableDepthTest();
	
	camera.begin();

		ofTranslate( (grayImage.getWidth() * -0.5f) * imageToSpaceScaling.x, 0.0f, (grayImage.getHeight() * -0.5f) * imageToSpaceScaling.z );
	
		ofSetColor( ofColor::white );
	
		colorFromHeightShader.begin();
			
			if( currPalette != NULL ) colorFromHeightShader.setUniformTexture( "u_paletteSampler", currPalette->getTextureReference(), 1 );
			colorFromHeightShader.setUniform1f("u_maxHeight", linesHeight );
	
			vbo.draw();
	
		colorFromHeightShader.end();
	
	camera.end();
	
	ofDisableDepthTest();
	
	if( currPalette != NULL ) currPalette->draw(0, ofGetHeight() - 20, 256, 20 );

}

//--------------------------------------------------------------
void testApp::updateMesh()
{	
	imageToSpaceScaling.set(1.0f,linesHeight,1.0f);
	
	ofPixelsRef tmpPixels = grayImage.getPixelsRef();
	
	vbo.clear();
	vbo.setMode( OF_PRIMITIVE_LINES );
	
	int tmpIndex = 0;
	for( int y = 0; y < grayImage.getHeight(); y += lineSkip )
	{
		tmpIndex = y * grayImage.getWidth();
		
		for( int x = 0; x < grayImage.getWidth(); x++ )
		{
			ofVec3f tmpVert(x, tmpPixels[tmpIndex]/255.0f, y);
			tmpVert *= imageToSpaceScaling;
			
			vbo.addVertex( tmpVert );
			
			tmpIndex++;
		}
	}
	
	int tmpY = 0;
	for( int y = 0; y < grayImage.getHeight(); y += lineSkip )
	{
		tmpIndex = tmpY * grayImage.getWidth();
		tmpY++;
		
		for( int x = 0; x < grayImage.getWidth()-1; x++ )
		{
			vbo.addIndex( tmpIndex );
			vbo.addIndex( tmpIndex + 1 );
			
			tmpIndex++;
		}
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	switch (key){
		case ' ':

			break;
		case '+':

			break;
		case '-':

			break;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	lastClickTime = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	lastClickTime = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	lastClickTime = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofEnableAlphaBlending();
	#ifdef TARGET_OPENGLES
		ofHideCursor();
	#endif
	
	#ifdef _USE_LIVE_VIDEO
        vidGrabber.setVerbose(true);
        vidGrabber.initGrabber(320,240);
	#else
        vidPlayer.loadMovie("movies/fingers.mp4");
		vidPlayer.setLoopState(OF_LOOP_NORMAL);//Quirk, This must be set on the Pi after loadMovie
        vidPlayer.play();
	#endif

    colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
		ofClear(0, 0, 0, 0);
	fbo.end();

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
	ofBackground(ofColor::black);

	// grab new frame and update colorImg with it.
    bool bNewFrame = false;

	#ifdef _USE_LIVE_VIDEO
       vidGrabber.update();
	   bNewFrame = vidGrabber.isFrameNew();
    #else
        vidPlayer.update();
        bNewFrame = vidPlayer.isFrameNew();
	#endif

	if (bNewFrame)
	{
		
		#ifdef _USE_LIVE_VIDEO
            colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
	    #else
            colorImg.setFromPixels(vidPlayer.getPixels(), 320,240);
        #endif

        grayImage = colorImg; // converts from color to greyscale

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
		
		fbo.begin();
			ofClear(0, 0, 0, 0); //clear our Fbo memory
			ofEnableDepthTest(); //enable 3d
				camera.begin(); //start our camera viewpoint
					ofTranslate( 
								(grayImage.getWidth() * -0.5f) * imageToSpaceScaling.x, //move x
								0.0f,													//move y
								(grayImage.getHeight() * -0.5f) * imageToSpaceScaling.z //move z
								);
			
					ofSetColor( ofColor::white );	//start with a white mesh
					colorFromHeightShader.begin();	//begin our shader
						if( currPalette != NULL )	//make sure we have a palette
						{
							//we pass our palette to the shader
							colorFromHeightShader.setUniformTexture( "u_paletteSampler", currPalette->getTextureReference(), 1 ); 
						}
						//we pass our linesHeight to the shader
						colorFromHeightShader.setUniform1f("u_maxHeight", linesHeight );
		
						//we draw our mesh (currently in OF_PRIMITIVE_LINES mode)
						mesh.draw();
					colorFromHeightShader.end();	//stop our shader operation
				camera.end();						//end our camera view
			ofDisableDepthTest();					//ending 3d
		fbo.end();									//stop drawing inside the fbo
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
	grayImage.draw(0,0);
	fbo.draw(0, 0);
		
	if( currPalette != NULL ) currPalette->draw(0, ofGetHeight() - 20, 256, 20 );
	//ofDrawBitmapStringHighlight("FPS: " + ofToString( ofGetFrameRate(), 1), 320, 50, ofColor::black, ofColor::yellow);

}

//--------------------------------------------------------------
void testApp::updateMesh()
{	
	imageToSpaceScaling.set(1.0f,linesHeight,1.0f);
	
	ofPixelsRef tmpPixels = grayImage.getPixelsRef();
	
	mesh.clear();
	mesh.setMode( OF_PRIMITIVE_LINES );
	
	int tmpIndex = 0;
	for( int y = 0; y < grayImage.getHeight(); y += lineSkip )
	{
		tmpIndex = y * grayImage.getWidth();
		
		for( int x = 0; x < grayImage.getWidth(); x++ )
		{
			ofVec3f tmpVert(x, tmpPixels[tmpIndex]/255.0f, y);
			tmpVert *= imageToSpaceScaling;
			
			mesh.addVertex( tmpVert );
			
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
			mesh.addIndex( tmpIndex );
			mesh.addIndex( tmpIndex + 1 );
			
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

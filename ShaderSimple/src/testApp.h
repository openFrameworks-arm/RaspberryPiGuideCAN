#pragma once

#include "ofMain.h"


// ---------------------------------------------------------------------------------------------------------------------------------------------------
//
class testApp : public ofBaseApp
{

	public:

		void				setup();
		void				update();
		void				draw();
		
		void				keyPressed(int key);
	
		ofTrueTypeFont		fontSmall;
	
		ofShader			shader;


};

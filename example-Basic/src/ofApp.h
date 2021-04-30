#pragma once
#include "ofMain.h"

#include "ofxSCENE-SVG.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void draw();
		void keyPressed(int key);

		void randomizePalette();
		vector<ofColor> palette;

		DEMO_Svg demoScene;
};

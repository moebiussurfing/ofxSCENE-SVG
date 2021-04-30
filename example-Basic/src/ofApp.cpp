#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() 
{
	demoScene.setLinkPalette(palette);
	demoScene.setEnable(true); //hidden by default

	randomizePalette();
}

//--------------------------------------------------------------
void ofApp::draw() 
{
	if (palette.size() > 0) ofClear(palette[0]);

	demoScene.draw();

	string s;
	s += "KEYS \n";
	s += "SPACE     : RANDOMIZE PALETTE COLORS FROM SVG FILE \n";
	s += "BACKSPACE : RANDOMIZE RECTANGLE CONTAINER";
	ofDrawBitmapStringHighlight(s, 10, ofGetHeight() - 3 * 15);
}

//--------------------------------------------------------------
void ofApp::randomizePalette() 
{
	palette.clear();
	palette.resize(demoScene.getNumColors());// same amount of colors of the SVG file 

	for (auto &c : palette) {
		c.set(ofRandom(255), ofRandom(255), ofRandom(255));
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') demoScene.setVisibleToggle();
	if (key == ' ') randomizePalette();
	if (key == 'e'|| key == 'E') demoScene.setToggleEdit();
	if (key == 'r'|| key == 'R') demoScene.reset();
	if (key == OF_KEY_BACKSPACE)//randomize a rect
	{
		ofRectangle r(ofRandom(100, 500), ofRandom(100, 500), ofRandom(400, 1000), -1);
		demoScene.setRect(r);
	}

}

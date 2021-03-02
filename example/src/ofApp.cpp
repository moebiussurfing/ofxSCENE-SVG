#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	demoSVG.setLinkPalette(palette);

	randomizePalette();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	demoSVG.draw();

	ofDrawBitmapStringHighlight("PRESS SPACE TO RANDOMIZE PALETTE COLORS FROM SVG FILE", 10, ofGetHeight() - 15);
}

//--------------------------------------------------------------
void ofApp::randomizePalette() {
	palette.clear();
	palette.resize(demoSVG.getNumColors());//same amount of colors of the SVG file 

	for (auto &c : palette) {
		c.set(ofRandom(255), ofRandom(255), ofRandom(255));
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'g') demoSVG.setVisibleToggle();
	if (key == ' ') randomizePalette();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

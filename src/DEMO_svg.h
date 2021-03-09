#pragma once

#include "ofMain.h"

//
// TODO:
//
// * must sync/reference mouse drag/rectangle etc. Now is no referenced to the mouse point


/*

For the momment we need to set manually the expected number of groups on the SVG.
We must remember to name the the groups as:
group1, group2, group3... on Illustrator
Use SVG 1.1 Tiny file format.
All the elements inside the group are paths
Do not include hidden layers or mask, can be problematic.

*/


// OPTIONAL
#define USE_MASK


#include "ofxSvgLoader.h"
#include "ofxPSBlend.h"
#include "ofxInteractiveRect.h" 
#include "ofxGui.h"
#include "ofxSurfingHelpers.h"
#ifdef USE_MASK
#include "ofxAlphaMask.h"
#endif

#define MAX_PALETTE_COLORS 20

class DEMO_Svg
{
	//--

#ifdef USE_MASK
public:
	ofParameter<bool> enable_Mask{ "Enable Mask", false };
private:
	ofFbo srcFbo;
	ofFbo maskFbo;
	ofxAlphaMask alphaMask;
	void update_Mask();
	void draw_Mask();
#endif

	//-

public:
	DEMO_Svg()
	{
		setup();
		ofAddListener(ofEvents().mouseDragged, this, &DEMO_Svg::mouseDragged);
		ofAddListener(ofEvents().mouseScrolled, this, &DEMO_Svg::mouseScrolled);
		ofAddListener(ofEvents().keyPressed, this, &DEMO_Svg::keyPressed);
	};

	~DEMO_Svg()
	{
		ofRemoveListener(params.parameterChangedE(), this, &DEMO_Svg::Changed_Controls);
		rSvg.saveSettings(path_Name, path_Layout, false);
		ofxSurfingHelpers::saveGroup(params, path_AppSettings);
		ofRemoveListener(ofEvents().mouseDragged, this, &DEMO_Svg::mouseDragged);
		ofRemoveListener(ofEvents().mouseScrolled, this, &DEMO_Svg::mouseScrolled);
		ofRemoveListener(ofEvents().keyPressed, this, &DEMO_Svg::keyPressed);
	};

	//--

public:
	void setEnableKeys(bool b) {
		//keys = b;
		if (b)ofAddListener(ofEvents().keyPressed, this, &DEMO_Svg::keyPressed);
		else ofRemoveListener(ofEvents().keyPressed, this, &DEMO_Svg::keyPressed);
	};

public:
	void setup();
	void startup();
	void update();

	void draw_SVG();

	void draw();//use draggable rectangle
	//void draw(glm::vec2 _pos);//force pos

public:
	//void keyPressed(int key);
	void keyPressed(ofKeyEventArgs &eventArgs);
	void mouseScrolled(ofMouseEventArgs &eventArgs);
	void mouseDragged(ofMouseEventArgs &eventArgs);
	//void mousePressed(ofMouseEventArgs &eventArgs);

	//--

private:
	float w, h;
	float w2, h2;
	float x2, y2;
	//window
	float ww;
	float hh;

private:
	std::string path_AppSettings;
	std::string path_Global;

private:
	std::string path_Name = "_DEMO_Svg";
	ofxInteractiveRect rSvg = { "_DEMO_Svg" };
	std::string path_Layout;

private:
	std::vector<ofFile> files;
	std::vector<std::string> files_Names;
	void refresh_Files(std::string path);
	void load_SVG(std::string name);

public:
	ofParameter<bool> keys{ "Enable Keys", true };
	ofParameter<bool> ShowGui{ "Show Gui", true };
	ofParameter<bool> DEMO2_Enable{ "Enable DEMO Svg", false };
	ofParameter<bool> DEMO2_Edit{ "Edit DEMO Svg", false };
	ofParameter<float> DEMO2_Scale{ "Scale", 1, 0.1, 2.0f };
	ofParameter<float> DEMO2_Alpha{ "Alpha", 1.0f, 0, 1.0f };
	ofParameter<int> blendMode{ "Blend Type", 1, 0, 24 };
	ofParameter<std::string> blendModeName{ "Blend Name", "" };
	ofParameter<int> fileIndex{ "SVG File", 0, 0, 0 };
	ofParameter<std::string> fileIndexName{ "File Name", "" };
	//ofParameter<glm::vec2> position;

	ofParameterGroup getParams() { return params; }

private:
	ofParameterGroup params{ "ofxSCENE-SVG" };
	void Changed_Controls(ofAbstractParameter &e);

	void setEdit(bool b)
	{
		if (b) rSvg.enableEdit();
		else rSvg.disableEdit();
	}

private:
	float scale;
	float alpha;
	float ratio;
	ofRectangle rSvgBounds;

	ofxPanel gui;
public:
	void setVisible(bool b) {
		ShowGui = b;
	}
	void setVisibleToggle() {
		ShowGui = !ShowGui;
	}

	glm::vec2 getPositionTittle()
	{
		ofRectangle r = rSvg.getRect();
		glm::vec2 p = glm::vec2(r.x + r.getWidth() / 2.0, r.y);
		return p;
	}

public:
	void setAlpha(float f)
	{
		alpha = f;
	}
	void setScale(float f)
	{
		scale = f;

		rSvg.setWidth(rSvgBounds.getWidth() * scale);
		rSvg.setHeight(rSvgBounds.getHeight() * scale);
	}

	//--

	float getWidth() {
		return shape.x;
	}
	float getHeight() {
		return shape.y;
	}
	int getNumColors() {
		return maxNumSvgGroupColors;
	}
	void setPaletteColors(vector<ofColor> &palette);//to be used on manual updating mode

	//pointer
	void setLinkPalette(vector<ofColor> &p);
	vector<ofColor> *palette_TARGET = NULL;

	//----

private:
	ofxSvgLoader svg;
	ofImage img;
	ofImage img_Mask;

	ofxPSBlend psBlend;

	vector<ofColor> paletteSvg;
	ofParameter<int> maxNumSvgGroupColors{ "Amount Colors", 0, 0, MAX_PALETTE_COLORS };

	glm::vec2 pos{ 0,0 };
	glm::vec2 shape;

	//--------------------------------------------------------------
	void refresh_Gui_Layout()
	{
		int _pad1 = 20;
		int _pad2 = 3;
		int _xx, _yy, _ww, _hh;
		_xx = rSvg.getX() + _pad1;
		_yy = rSvg.getY() + _pad1;

		rSvg.setWidth(_ww);
		rSvg.setHeight(_hh);
	}
};
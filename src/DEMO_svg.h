#pragma once

#include "ofMain.h"


/*

For the momment we need to set manually the num of groups.
We must remember to name the the groups as: 
group1, group2, group3... on Illustrator
Use SVG 1.1 Tiny file format.
All the elements inside the group are paths

*/


#include "ofxSvgLoader.h"
#include "ofxPSBlend.h"
#include "ofxInteractiveRect.h" 
#include "ofxGui.h"
#include "ofxSurfingHelpers.h"

class DEMO_Svg
{
	//--

public:
	DEMO_Svg()
	{
		setup();
		ofAddListener(ofEvents().mouseScrolled, this, &DEMO_Svg::mouseScrolled);
	};

	~DEMO_Svg()
	{
		ofRemoveListener(params.parameterChangedE(), this, &DEMO_Svg::Changed_Controls);
		rectDgSvg.saveSettings(path_Name, path_Layout, false);
		ofxSurfingHelpers::saveGroup(params, path_AppSettings);
		ofRemoveListener(ofEvents().mouseScrolled, this, &DEMO_Svg::mouseScrolled);
	};

	//--

public:
	void setup();
	void update();

	void draw();//use draggable rectangle
	void draw(glm::vec2 _pos);//force pos

public:
	void keyPressed(int key);
	void mouseScrolled(ofMouseEventArgs &eventArgs);

	//--

private:
	std::string path_AppSettings;
	std::string path_Global;

private:
	std::string path_Name = "_DEMO_Svg";
	ofxInteractiveRect rectDgSvg = { "_DEMO_Svg" };
	std::string path_Layout;

public:
	ofParameter<bool> ShowGui{ "Show Gui", true };
	ofParameter<bool> DEMO2_Test{ "Enable DEMO2", false };
	ofParameter<bool> DEMO2_Edit{ "Edit DEMO2", false };
	ofParameter<float> DEMO2_Scale{ "Scale", 1, 0.1, 2.0f };
	ofParameter<float> DEMO2_Alpha{ "Alpha", 1.0f, 0, 1.0f };
	ofParameterGroup getParams() { return params; }

private:
	ofParameterGroup params{ "ofxSCENE-SVG" };
	void Changed_Controls(ofAbstractParameter &e);

	void setEdit(bool b)
	{
		if (b) rectDgSvg.enableEdit();
		else rectDgSvg.disableEdit();
	}

private:
	float scale;
	float alpha;
	float ratio;
	ofRectangle rSvgBounds;

public:
	ofxPanel gui;
	void setVisible(bool b) {
		ShowGui = b;
	}
	void setVisibleToggle() {
		ShowGui = !ShowGui;
	}

public:
	void setAlpha(float f)
	{
		alpha = f;
	}
	void setScale(float f)
	{
		scale = f;

		rectDgSvg.setWidth(rSvgBounds.getWidth() * scale);
		rectDgSvg.setHeight(rSvgBounds.getHeight() * scale);
	}

	//--

	float getWidth() {
		return shape.x;
	}
	float getHeight() {
		return shape.y;
	}
	void setPaletteColors(vector<ofColor> &palette);//to be used on manual updating mode

	//pointer
	void setLinkPalette(vector<ofColor> &p);
	vector<ofColor> *palette_TARGET = NULL;

	//----

private:
	ofxSvgLoader svg;
	ofImage img;

	ofxPSBlend psBlend;

	int blendMode;

	vector<ofColor> paletteSvg;
	int maxNumSvgGroupColors = 2;

	glm::vec2 pos{ 0,0 };
	glm::vec2 shape;

	//--------------------------------------------------------------
	void refresh_Gui_Layout()
	{
		int _pad1 = 20;
		int _pad2 = 3;
		int _xx, _yy, _ww, _hh;
		_xx = rectDgSvg.getX() + _pad1;
		_yy = rectDgSvg.getY() + _pad1;

		rectDgSvg.setWidth(_ww);
		rectDgSvg.setHeight(_hh);
	}
};
#pragma once

#include "ofMain.h"

//
// TODO:
//
// + fix. mask mode is displaced to the non maksed mode..
// + mask looks worst image quality/resolution
// + use fbo to custom draw position/size ??


/*

IMPORTANT

For the momment we need to set manually the expected number of groups/colors on the SVG.
We must remember to name the the groups as:
group1, group2, group3... on Illustrator.
Use SVG 1.1 Tiny file format.
All the elements inside the group are paths
Do not include hidden layers or mask, can be problematic.
Look to the image captures in /readme_images/

*/


//--------------------------------------------------------------
//
// OPTIONAL
#define USE_IMGUI // to easy populate control widgets on other projects. Disable if you do not needs ImGui helper.
//#define USE_MASK // to allow transparent background on the inforunt image... TODO: WIP
//
//--------------------------------------------------------------


#include "ofxSvgLoader.h"
#include "ofxPSBlend.h"
#include "ofxInteractiveRect.h" 
#include "ofxGui.h"
#include "ofxSurfingHelpers.h"
#include "ofxSurfing_Timers.h"
#ifdef USE_MASK
#include "ofxAlphaMask.h"
#endif
#ifdef USE_IMGUI
#include "ofxImGui.h"
#include "ofxSurfing_ImGui.h"
#endif

#define MAX_PALETTE_COLORS 20
#define DRAG_STEP 0.025f // mouse speed

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

	//--------------------------------------------------------------
	DEMO_Svg()
	{
		setup();

		ofAddListener(ofEvents().mouseScrolled, this, &DEMO_Svg::mouseScrolled);
		ofAddListener(ofEvents().keyPressed, this, &DEMO_Svg::keyPressed);
		ofAddListener(ofEvents().keyReleased, this, &DEMO_Svg::keyReleased);
	};

	//--------------------------------------------------------------
	~DEMO_Svg()
	{
		ofRemoveListener(ofEvents().mouseScrolled, this, &DEMO_Svg::mouseScrolled);
		ofRemoveListener(ofEvents().keyPressed, this, &DEMO_Svg::keyPressed);
		ofRemoveListener(ofEvents().keyReleased, this, &DEMO_Svg::keyReleased);

		ofRemoveListener(params.parameterChangedE(), this, &DEMO_Svg::Changed_Controls);
		ofRemoveListener(params_Rectangle.parameterChangedE(), this, &DEMO_Svg::Changed_Rectangle);

		rectangle_SVG.saveSettings(path_Name, path_Layout, false);
		ofxSurfingHelpers::saveGroup(params, path_AppSettings);
	};

	//--

public:
	//--------------------------------------------------------------
	void setEnable(bool b) {
		bEnable = b;
	}

	//--------------------------------------------------------------
	void setEnableKeys(bool b) {
		bKeys = b;
		if (b) {
			ofAddListener(ofEvents().keyPressed, this, &DEMO_Svg::keyPressed);
			ofAddListener(ofEvents().keyReleased, this, &DEMO_Svg::keyReleased);
		}
		else
		{
			ofRemoveListener(ofEvents().keyPressed, this, &DEMO_Svg::keyPressed);
			ofRemoveListener(ofEvents().keyReleased, this, &DEMO_Svg::keyReleased);
		}
	};

public:
	//--------------------------------------------------------------
	void save() {
		rectangle_SVG.saveSettings(path_Name, path_Layout, false);
		ofxSurfingHelpers::saveGroup(params, path_AppSettings);
	};
	//--------------------------------------------------------------
	void load() {
		reset();
		rectangle_SVG.loadSettings(path_Name, path_Layout, false);
		ofxSurfingHelpers::loadGroup(params, path_AppSettings);
	};

	//--

public:
	void setup();
	void startup();
	void update();
	void draw();
	void draw_SVG();

public:
	void keyPressed(ofKeyEventArgs &eventArgs);
	void keyReleased(ofKeyEventArgs &eventArgs);
	void mouseScrolled(ofMouseEventArgs &eventArgs);

	//--

private:
	float wSource, hSource, ratioSource;

	ofParameterGroup params_Box{ "Box" };

	ofParameter<int> xRect{ "Position x", 0,0,1920 };
	ofParameter<int> yRect{ "Position y", 0,0,1080 };
	ofParameter<int> wRect{ "Width", 0,0,1920 };
	ofParameter<int> hRect{ "Height", 0,0,1080 };
	ofParameterGroup params_Rectangle{ "Rectangle" };

	void Changed_Rectangle(ofAbstractParameter &e);

private:
	std::string path_AppSettings;
	std::string path_Global;
public:
	ofxInteractiveRect rectangle_SVG = { "_DEMO_Svg" };
private:
	std::string path_Name = "_DEMO_Svg";
	std::string path_Layout;

private:
	std::vector<ofFile> files;
	std::vector<std::string> files_Names;
	void refresh_Files(std::string path);
	void load_SVG(std::string name);

public:
	ofParameter<bool> bDrawBorder{ "Draw Border", false };
	ofParameter<bool> bReset{ "Reset", false };
	ofParameter<bool> bKeys{ "Enable Keys", true };
	ofParameter<bool> bShowGui{ "Show Gui", true };
	ofParameter<bool> bEnable{ "Enable DEMO Svg", false};
	ofParameter<bool> bEdit{ "MOUSE EDIT", false };
	ofParameter<float> scaleSvg{ "Scale", 1, 0.1, 2.0f };
	ofParameter<float> alphaSvg{ "Alpha", 1.0f, 0, 1.0f };
	ofParameter<int> blendMode{ "Blend Type", 1, 0, 24 };
	ofParameter<int> fileIndex{ "SVG File", 0, 0, 0 };
	ofParameter<bool> bBgWhite{ "Bg White", false };
	ofParameter<std::string> blendModeName{ "Blend Name", "" };
	ofParameter<std::string> fileIndexName{ "File Name", "" };

	ofParameterGroup getParams() { return params; }

	//--

private:

	ofParameterGroup params{ "ofxSCENE-SVG" };
	void Changed_Controls(ofAbstractParameter &e);

public:

	//--------------------------------------------------------------
	void setEdit(bool b)
	{
		if (b) rectangle_SVG.enableEdit();
		else rectangle_SVG.disableEdit();

		// workflow
		if (bEdit != b) bEdit = b;
		//if (bEdit != b) bEdit.setWithoutEventNotifications(b);
	}

	//--------------------------------------------------------------
	void setToggleEdit() {
		setEdit(!bEdit);
	}

private:
	float alphaBlend;
	//float ratio;
	
	float scaleSource;
	ofRectangle rectangle_SVG_Bounds;

public:

	ofxPanel gui;

public:

	void reset();

	//--------------------------------------------------------------
	void setVisible(bool b) {
		bShowGui = b;
	}
	//--------------------------------------------------------------
	void setVisibleToggle() {
		bShowGui = !bShowGui;
		if (!bEnable && bShowGui) bEnable = true;

	}

	//--------------------------------------------------------------
	glm::vec2 getPositionTittle()
	{
		ofRectangle r = rectangle_SVG.getRect();
		glm::vec2 p = glm::vec2(r.x + r.getWidth() / 2.0, r.y);
		return p;
	}

public:

	//--------------------------------------------------------------
	void setAlpha(float f)
	{
		alphaBlend = f;
	}
	//--------------------------------------------------------------
	void setScale(float f)
	{
		//TODO:
		//this other scale is redundant... should remove.. ??
		scaleSource = f;

		rectangle_SVG.setWidth(rectangle_SVG_Bounds.getWidth() * scaleSource);
		rectangle_SVG.setHeight(rectangle_SVG_Bounds.getHeight() * scaleSource);

		wRect = rectangle_SVG_Bounds.getWidth() * scaleSource;
		hRect = rectangle_SVG_Bounds.getHeight() * scaleSource;
	}

	//--------------------------------------------------------------
	void setRect(ofRectangle r)
	{
		xRect = r.x;
		yRect = r.y;
		hRect = r.getHeight();
		wRect = r.getWidth();//priority
	}

	//--------------------------------------------------------------
	void setX(float x)
	{
		xRect = x;
	}
	//--------------------------------------------------------------
	void setY(float y)
	{
		yRect = y;
	}
	//--------------------------------------------------------------
	void setWidth(float w)
	{
		wRect = w;
	}
	//--------------------------------------------------------------
	void setHeight(float h)
	{
		hRect = h;
	}

	//--------------------------------------------------------------
	float getRatio()
	{
		//return hRect / wRect;
		return ratioSource;
	}

	//--------------------------------------------------------------
	ofRectangle getRect()
	{
		return ofRectangle(xRect, yRect, wRect, hRect);
	}

	//--

	//--------------------------------------------------------------
	float getWidth() {
		return wRect;
	}
	//--------------------------------------------------------------
	float getHeight() {
		return hRect;
	}

	//----

	// colors

	//--------------------------------------------------------------
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
	glm::vec2 shapeImg;

	bool bModKey = false;

	//--------------------------------------------------------------
	void refresh_Gui_Layout()
	{
		int _pad1 = 20;
		int _pad2 = 3;
		int _xx, _yy, _ww, _hh;
		_xx = rectangle_SVG.getX() + _pad1;
		_yy = rectangle_SVG.getY() + _pad1;

		rectangle_SVG.setWidth(_ww);
		rectangle_SVG.setHeight(_hh);
	}

	//--

public:
#ifdef USE_IMGUI
	//--------------------------------------------------------------
	void drawImGuiControls(float _w100, float _w99, float _w50, float _w33, float _h) {
		if (bEnable)
		{
			if (ImGui::CollapsingHeader("SCENE-SVG"))
			{
				ImGui::PushItemWidth(_w33);

				ofxSurfingHelpers::AddBigToggle(bEdit, _w100, _h / 2);
				//ofxImGui::AddParameter(bEdit);

				if (bEdit) {
					ofxImGui::AddParameter(scaleSvg);
					ofxImGui::AddParameter(bDrawBorder);
					ofxImGui::AddParameter(alphaSvg);
					ofxImGui::AddParameter(xRect);
					ofxImGui::AddParameter(yRect);
					ofxImGui::AddParameter(wRect);
					ofxImGui::AddParameter(hRect);
				}

				if (ImGui::CollapsingHeader("IMAGE")) {
					ofxImGui::AddStepper(blendMode);
					ofxImGui::AddParameter(blendModeName);
					ofxImGui::AddStepper(fileIndex);
					ofxImGui::AddParameter(fileIndexName);
#ifdef USE_SVG_MASK
					ofxImGui::AddParameter(enable_Mask);
					ofxImGui::AddParameter(bBgWhite);
#endif		
				}

				ofxImGui::AddParameter(bKeys);
				ImGui::PopItemWidth();

				if (ImGui::Button("Reset SVG", ImVec2(_w100, _h / 2))) {
					reset();
				}

				if (bEdit) {
					if (ImGui::Button("Load", ImVec2(_w50, _h / 2))) {
						load();
					}
					ImGui::SameLine();
					if (ImGui::Button("Save", ImVec2(_w50, _h / 2))) {
						save();
					}
				}
			}
		}
	}
#endif
};
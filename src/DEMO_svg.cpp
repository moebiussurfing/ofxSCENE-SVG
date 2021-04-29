#include "DEMO_Svg.h"

//--------------------------------------------------------------
void DEMO_Svg::setup() {
	ofLogNotice(__FUNCTION__);

	path_Global = "ofxSCENE-SVG/";
	path_AppSettings = path_Global + "DEMO_Svg.xml";

	// b. load settings
	//rectangle_SVG.disableEdit();
	path_Layout = path_Global;
	//rectangle_SVG.loadSettings(path_Name, path_Layout, false);
	rectangle_SVG.setAllScreenMouse(true);

	//ww = ofGetWidth();
	//hh = ofGetHeight();
	//position.set("Positon", glm::vec2(ww / 2, hh / 2), glm::vec2(0, 0), glm::vec2(ww, hh));

	//--

	refresh_Files(path_Global);

	//--

	//blendMode.setSerializable(false);
	//fileIndex.setSerializable(false);
	blendModeName.setSerializable(false);
	fileIndexName.setSerializable(false);
	maxNumSvgGroupColors.setSerializable(false);

	//positionCanvas.set("Position", glm::vec2(30, 30), glm::vec2(0, 0), glm::vec2(1920, 1080));
	//shapeCanvas.set("Shape", glm::vec2(30, 30), glm::vec2(0, 0), glm::vec2(1920, 1080));

	//--

	// control params for callback

	bEdit.setSerializable(false);
	bReset.setSerializable(false);

	//params.add(positionCanvas);
	//params.add(shapeCanvas);
	params.add(bEnable);
	params.add(alphaSvg);
	params.add(blendMode);
	params.add(blendModeName);
	params.add(fileIndex);
	params.add(fileIndexName);
	params.add(maxNumSvgGroupColors);
#ifdef USE_MASK
	params.add(enable_Mask);
	params.add(bBgWhite);
#endif

	params_Box.add(bEdit);
	params_Box.add(scaleSvg);
	params_Rectangle.add(xRect);
	params_Rectangle.add(yRect);
	params_Rectangle.add(wRect);
	params_Rectangle.add(hRect);
	params_Box.add(params_Rectangle);
	params_Box.add(bDrawBorder);
	params.add(params_Box);

	params.add(bKeys);
	params.add(bReset);
	//params.add(position);

	ofAddListener(params.parameterChangedE(), this, &DEMO_Svg::Changed_Controls);
	ofAddListener(params_Rectangle.parameterChangedE(), this, &DEMO_Svg::Changed_Rectangle);

	//--

	gui.setup("ofxSCENE-SVG");
	gui.add(params);

	//--

	startup();
}

//--------------------------------------------------------------
void DEMO_Svg::startup() {
	ofLogNotice(__FUNCTION__);

	reset();

	rectangle_SVG.loadSettings(path_Name, path_Layout, false);
	ofxSurfingHelpers::loadGroup(params, path_AppSettings);

	rectangle_SVG.disableEdit();
}

//--------------------------------------------------------------
void DEMO_Svg::setPaletteColors(vector<ofColor> &_palette) {
	ofLogNotice(__FUNCTION__);

	if (_palette.size() > 0)
	{
		int _max = MAX(paletteSvg.size(), _palette.size());

		//TODO:
		//manual mode to call every frame

		if (paletteSvg.size() < _palette.size())
		{
			for (int i = 0; i < _max; i++)
			{
				int i2 = i % paletteSvg.size();
				paletteSvg[i] = _palette[i2];

			}
		}
		else if (_palette.size() < paletteSvg.size())
		{
			for (int i = 0; i < _max; i++)
			{
				int i2 = i % _palette.size();
				paletteSvg[i] = _palette[i2];
			}
		}
	}
}

//--------------------------------------------------------------
void DEMO_Svg::mouseScrolled(ofMouseEventArgs &eventArgs)
{
	const int &x = eventArgs.x;
	const int &y = eventArgs.y;
	const float &scrollX = eventArgs.scrollX;
	const float &scrollY = eventArgs.scrollY;

	ofLogVerbose(__FUNCTION__) << "scrollX: " << scrollX << "  scrollY: " << scrollY;

	if (bEdit)
	{
		// zoom 
		//if (rectangle_SVG.inside(glm::vec2(x, y))) // inside only but translated when rescaled
		{
			if (scrollY == 1) scaleSvg += 0.025f;
			else if (scrollY == -1) scaleSvg -= 0.025f;
		}
	}
}

//--------------------------------------------------------------
void DEMO_Svg::mouseDragged(ofMouseEventArgs &eventArgs)
{
	//const int &x = eventArgs.x;
	//const int &y = eventArgs.y;
	//ofLogNotice(__FUNCTION__) << x << ", " << y;

	//float xx = x;
	//float yy = y;

	//////xx = x + rectangle_SVG.getWidth() * scale * 1.0;
	//////yy = y + rectangle_SVG.getHeight() * scale * 1.0;

	//if (bEdit)
	//{
	//	float xpre;
	//	float ypre;
	//	xpre = rectangle_SVG.getRectX();
	//	ypre = rectangle_SVG.getRectY();

	//	//rectangle_SVG.setPosition(-xx + xpre, -yy + ypre);

	//	//position = glm::vec2(xx, yy);
	//}
}

//--------------------------------------------------------------
void DEMO_Svg::Changed_Rectangle(ofAbstractParameter &e)
{
	std::string name = e.getName();

	ofLogNotice(__FUNCTION__) << name << " : " << e;

	//----

	if (false) {}

	//----

	else if (name == xRect.getName())
	{
		rectangle_SVG.setX(xRect);
	}
	else if (name == yRect.getName())
	{
		rectangle_SVG.setY(yRect);
	}

	else if (name == wRect.getName())
	{
		rectangle_SVG.setWidth(wRect);

		hRect = wRect * ratioSource;

		scaleSvg = wRect / rSvgBounds.getWidth();
	}
	else if (name == hRect.getName())
	{
		rectangle_SVG.setHeight(hRect);
		//can be controlled by height!
	}
}

//--------------------------------------------------------------
void DEMO_Svg::Changed_Controls(ofAbstractParameter &e)
{
	std::string name = e.getName();

	if (name != bEnable.getName()) { // ??
		ofLogNotice(__FUNCTION__) << name << " : " << e;
	}

	//----

	if (false) {}

	//----

	// demo2 svg
	else if (name == bEnable.getName())
	{
		// workflow
		if (!bEnable)
		{
			bEdit = false;
			//setEdit(bEdit);
		}
	}
	else if (name == bEdit.getName())
	{
		setEdit(bEdit);
	}

	else if (name == scaleSvg.getName())
	{
		setScale(scaleSvg);
	}

	else if (name == bReset.getName() && bReset)
	{
		bReset = false;
		reset();
	}

	//else if (name == positionCanvas.getName())
	//{
	//	rectangle_SVG.setPosition(positionCanvas.get().x, positionCanvas.get().y);
	//}
	//else if (name == shapeCanvas.getName())
	//{
	//	rSvgBounds.setWidth(shapeCanvas.get().x);
	//	rSvgBounds.setHeight(shapeCanvas.get().y);
	//	//TODO:
	//	wRect = rSvgBounds.getWidth() * scale;
	//	hRect = rSvgBounds.getHeight() * scale;
	//}

	else if (name == alphaSvg.getName())
	{
		setAlpha(alphaSvg);
	}

	// blend
	else if (name == blendMode.getName())
	{
		blendMode = ofClamp(blendMode, 0, 24);
		blendModeName = psBlend.getBlendMode(blendMode);
	}

	// file
	else if (name == fileIndex.getName())
	{
		fileIndex = ofClamp(fileIndex, 0, 1);
		//if (fileIndex.get() > files_Names.size() - 1) return;

		fileIndexName = files_Names[fileIndex];

		ofLogNotice(__FUNCTION__) << fileIndexName;

		load_SVG(fileIndexName);
	}
}

//--------------------------------------------------------------
void DEMO_Svg::update() {

	// update colors
	{
		//// a. manually update every on frame

		//int szp = paletteSvg.size();
		//for (int i = 0; i < maxNumSvgGroupColors; i++)
		//{
		//	ofColor c = ofColor(paletteSvg[i % szp], alpha * 255.0);
		//}

		//-

		// b. update referenced palette

		if (palette_TARGET != nullptr)
		{
			int szp = palette_TARGET->size();

			for (int i = 0; i < maxNumSvgGroupColors && szp > 0; i++)
			{
				paletteSvg[i] = (*palette_TARGET)[i % szp];
			}
		}

		//--

		// assign fill color to svg groups
		// svg file must be named corrently as group1, group2, group3,...

		if (paletteSvg.size() != 0)
		{
			for (int i = 0; i < maxNumSvgGroupColors; i++)
			{
				std::string name = "group" + ofToString(i);

				shared_ptr<ofxSvgGroup> bGroup = svg.get< ofxSvgGroup>(name.c_str());
				if (bGroup && i < paletteSvg.size())
				{
					ofColor c = ofColor(paletteSvg[i], alpha * 255.0);

					for (int e = 0; e < bGroup->getElements().size(); e++)
					{
						shared_ptr< ofxSvgElement > te = dynamic_pointer_cast<ofxSvgElement>(bGroup->getElements()[e]);

						te->path.setFillColor(c);
					}
				}
			}
		}
	}

	//--

#ifdef USE_MASK
	update_Mask();
#endif

	//--

	// edit draggable scale object

	if (rectangle_SVG.isEditing())
	{
		refreshEdited();
	}
}

#ifdef USE_MASK
//--------------------------------------------------------------
		//float _ratio = rectangle_SVG.getHeight() / rectangle_SVG.getHeight();
		//scale = rectangle_SVG.getY() / rSvgBounds.getY();
void DEMO_Svg::update_Mask()

{
	//if (enable_Mask)
	{
		srcFbo.begin();
		{
			ofClear(0);
			draw_SVG();
		}
		srcFbo.end();

		maskFbo.begin();
		{
			ofClear(0);
			ofFill();
			img_Mask.draw(xRect, yRect, wRect, hRect);
		}
		maskFbo.end();
	}
}

//--------------------------------------------------------------
void DEMO_Svg::draw_Mask()
{
	ofPushStyle();
	//ofPushMatrix();
	//ofTranslate(-position.get().x, -position.get().y);

	// srcFbo/maskFbo
	ofSetColor(255, 255);
	alphaMask.begin(maskFbo.getTexture());
	{
		float ratio = wSource / hSource;
		srcFbo.draw(0, 0, ofGetWidth(), ofGetWidth() / ratio);
		//srcFbo.draw(-position.get().x, -position.get().y, ofGetWidth(), ofGetWidth() / ratio);
	}
	alphaMask.end();

	//ofPopMatrix();
	ofPopStyle();
}

#endif

//--------------------------------------------------------------
void DEMO_Svg::draw_SVG()
{
	ofPushStyle();

	psBlend.begin();
	svg.draw();
	psBlend.end();

	//--

	//TODO:
	// nike
	if (fileIndex == 1) ofClear(255);//white bg

	//-

	//blend types
	//string str;
	//str += "Press UP/DOWN key\n";
	//str += "Blend Mode: [" + ofToString(blendMode) + "] " + psBlend.getBlendMode(blendMode);
	//ofDrawBitmapStringHighlight(str, 20, 30);

	ofPushMatrix();

	ofTranslate(rectangle_SVG.getX(), rectangle_SVG.getY());

	//ofPushMatrix();
	//ofTranslate(rectangle_SVG.getWidth() / 2.f, rectangle_SVG.getHeight()/2.0f);
	ofScale(scale);
	{
		psBlend.draw(img.getTextureReference(), blendMode);
	}
	//ofPopMatrix();

	ofPopMatrix();
	ofPopStyle();
}

//--------------------------------------------------------------
void DEMO_Svg::draw()
{
	if (bEnable)
	{
		update();

		//----

#ifndef USE_MASK
		draw_SVG();
#endif

#ifdef USE_MASK
		if (enable_Mask)
		{
			draw_Mask();
		}
		else
		{
			draw_SVG();
		}
#endif
	}

	//debug border
	if (bDrawBorder)
	{
		ofPushStyle();
		ofNoFill();

		//blink on editing
		ofSetLineWidth(2);
		ofSetColor(128, (bEdit ? ofxSurfingHelpers::Bounce(0.5) + 0.25 : 1) * 128);
		ofDrawRectangle(rectangle_SVG);

		//ofSetColor(128, 32);
		//ofDrawRectangle(rSvgBounds);
		
		ofPopStyle();
	}

	//----

	if (bShowGui) gui.draw();
}

//--------------------------------------------------------------
void DEMO_Svg::setLinkPalette(vector<ofColor> &p)
{
	ofLogNotice(__FUNCTION__);

	palette_TARGET = &p;
}

//--------------------------------------------------------------
void DEMO_Svg::keyPressed(ofKeyEventArgs &eventArgs)
{
	if (!bKeys) { return; }

	const int key = eventArgs.key;

	// modifiers
	bool mod_COMMAND = eventArgs.hasModifier(OF_KEY_COMMAND);
	bool mod_CONTROL = eventArgs.hasModifier(OF_KEY_CONTROL);
	bool mod_ALT = eventArgs.hasModifier(OF_KEY_ALT);
	bool mod_SHIFT = eventArgs.hasModifier(OF_KEY_SHIFT);

	ofLogNotice(__FUNCTION__) << key;

	if (/*key == OF_KEY_UP ||*/ key == '+')
	{
		if (blendMode >= 24)
		{
			blendMode = 0;
		}
		else
		{
			blendMode++;
		}
	}

	else if (/*key == OF_KEY_DOWN || key == ' ' ||*/ key == '-')
	{
		if (blendMode <= 0)
		{
			blendMode = 24;
		}
		else
		{
			blendMode--;
		}
	}

	//else if (key == OF_KEY_CONTROL)
	//{
	//	bModKey = true;
	//	setEdit(bModKey);
	//}
}
//--------------------------------------------------------------
void DEMO_Svg::keyReleased(ofKeyEventArgs &eventArgs)
{
	//const int key = eventArgs.key;

	//if (key == OF_KEY_CONTROL)
	//{
	//	bModKey = false;
	//	setEdit(bModKey);
	//}
}

//--------------------------------------------------------------
void DEMO_Svg::refresh_Files(std::string path)
{
	ofLogNotice(__FUNCTION__) << path;
	ofxSurfingHelpers::CheckFolder(path);

	ofDirectory dataDirectory(ofToDataPath(path, true));

	//-

	// clear files and filenames vectors
	files.clear();
	files_Names.clear();
	//dataDirectory.allowExt("");

	// load all folder files in one call
	files = dataDirectory.getFiles();

	if (files.size() < 1)
	{
		ofLogError(__FUNCTION__) << "PATH DIRECTORY EMPTY!";
		return;
	}

	//-

	for (size_t i = 0; i < files.size(); i++)
	{
		auto _nName = files[i].getBaseName();
		auto _nFolder = files[i].getAbsolutePath();

		if (std::filesystem::is_directory(_nFolder))
		{
			files_Names.push_back(_nName);
			//ofLogNotice(__FUNCTION__) << files_Names.back();
		}
	}

	if (files_Names.size() < 1)
	{
		ofLogError(__FUNCTION__) << "PATH DIRECTORY FORMAT NOT COMPATIBLE!";
		return;
	}

	fileIndex.setMax(files_Names.size() - 1);
	if (fileIndex > files_Names.size() - 1) fileIndex = -1;

	//-

	// workflow

	//TODO:
	//void to go to 1st...
	fileIndex = 0;

	// 1. load same position preset
	// if preset is deleted goes to nextone..
	// should check names because sorting changes..
	if (files_Names.size() > 0)
	{
		if (fileIndex > files_Names.size() - 1) fileIndex = files_Names.size() - 1;
		fileIndexName = files_Names[fileIndex];
		ofLogNotice(__FUNCTION__) << fileIndexName;

		load_SVG(fileIndexName);
	}
	else
	{
		ofLogError(__FUNCTION__) << "FILE PRESET NOT FOUND!";
	}
}

//--------------------------------------------------------------
void DEMO_Svg::load_SVG(std::string name)
{
	// initiate
	svg = ofxSvgLoader();
	img.clear();

	//--

	// nike.svg
	svg.load(path_Global + name + "/" + name + ".svg");
#ifdef USE_MASK
	img_Mask.load(path_Global + name + "/" + name + "_Mask.jpg");
	//img_Mask.load(path_Global + name + "/" + name + "-Mask.jpg");
#endif
	img.load(path_Global + name + "/" + name + ".jpg");
	shape = glm::vec2(img.getWidth(), img.getHeight());

	//TODO: count svg groups/layers
	//hardcoded workaround
	if (name == "nike")
	{
		maxNumSvgGroupColors = 8;//nike
	}
	else if (name == "moebius")
	{
		maxNumSvgGroupColors = 7;//moebius
#ifdef USE_MASK
		enable_Mask = false;//no mask for this svg
#endif
	}
	else
	{
		maxNumSvgGroupColors = 4;//default
	}

	//--

	//TODO:
	//could add svg file selector

	//TODO:
	//should auto get the num of groups
	//for the momment we need to set manualy the num of groups.
	//remember to name the the groups as: group1, group2, group3... on Illustrator
	//use SVG 1.1 tiny file format.
	//shared_ptr<ofxSvgGroup> bGroup = svg.get< ofxSvgGroup>(name.c_str());

	//----

	ofLogNotice(__FUNCTION__) << endl << endl << svg.toString();

	rSvgBounds = svg.getBounds();

	wSource = rSvgBounds.getWidth();
	hSource = rSvgBounds.getHeight();
	ratioSource = hSource / wSource;

	//TODO:
	//scale
	//svg.getTransformFromSvgMatrix
	//getTransformFromSvgMatrix(string matrix, ofVec2f& apos, float & scaleX, float & scaleY, float & arotation)
	//vector< shared_ptr<ofxSvgImage> > trees = svg.getElementsForType< ofxSvgImage>("trees");

	shape = glm::vec2(wSource, hSource);
	//ratio = shape.x / shape.y;

	img.resize(wSource, hSource);

#ifdef USE_MASK
	img_Mask.resize(wSource, hSource);
#endif

	//psBlend.setup(wSource, hSource);
	psBlend.setup(img.getWidth(), img.getHeight());

	//blendMode = 1;//multiply

	paletteSvg.clear();
	paletteSvg.resize(maxNumSvgGroupColors);

	// draggable rect
	rectangle_SVG.setRect(rSvgBounds.getX(), rSvgBounds.getY(), wSource, hSource);//default init
	rectangle_SVG.setLockResize(false);
	//rectangle_SVG.setLockResize(true);

	// b. load settings
	//rectangle_SVG.loadSettings();
	//path_Layout = path_Global;
	//rectangle_SVG.loadSettings(path_Name, path_Layout, false);

	//--

#ifdef USE_MASK
	//if (enable_Mask)
	{
		//srcFbo.allocate(1920, 1080, GL_RGBA);
		srcFbo.allocate(wSource, hSource, GL_RGBA);
		srcFbo.begin();
		{
			ofClear(0);
		}
		srcFbo.end();

		//maskFbo.allocate(1920, 1080, GL_RGBA);
		maskFbo.allocate(wSource, hSource, GL_RGBA);
		maskFbo.begin();
		{
			ofClear(0);
		}
		maskFbo.end();
	}
#endif

	//--

	// load layout
	rectangle_SVG.loadSettings(path_Name, path_Layout, false);
	//setEdit(bEdit);

	//fix workaround for startup bug
	wRect = (rSvgBounds.getWidth() * scale);
	hRect = (rSvgBounds.getHeight() * scale);
	xRect = rectangle_SVG.getX();
	yRect = rectangle_SVG.getY();

	rectangle_SVG.setWidth(wRect);
	rectangle_SVG.setHeight(hRect);
}

//--------------------------------------------------------------
void DEMO_Svg::refreshEdited() {

	////highlight
	//ofFill();
	//int fr = ofGetFrameNum() % 60;
	//ofSetColor(fr < 30 ? ofColor(255, 16) : (ofColor(0, 16)));
	//ofDrawRectangle(rectangle_SVG);

	//-

	wRect = rSvgBounds.getWidth() * scale;
	hRect = rSvgBounds.getHeight() * scale;
	xRect = rectangle_SVG.getX();
	yRect = rectangle_SVG.getY();

	rectangle_SVG.setWidth(wRect);
	rectangle_SVG.setHeight(hRect);

	//positionCanvas = glm::vec2(xRect, yRect);
	//shapeCanvas = glm::vec2(rSvgBounds.getWidth(), rSvgBounds.getHeight());
}

//--------------------------------------------------------------
void DEMO_Svg::reset() {
	bEdit = false;
	fileIndex = 1;
	scaleSvg = 1;
	alphaSvg = 0.5f;
	blendMode = 4;

	//--

	// layout

	wRect = wSource;//original size
	//wRect = 1000;
	hRect = wRect * ratioSource;

	xRect = ofGetWidth() / 2 - wRect / 2;
	yRect = ofGetHeight() / 2 - hRect / 2;

	//rectangle_SVG.loadSettings(path_Name, path_Layout, false);
	//rectangle_SVG.setRestore();
	//rectangle_SVG.set(glm::vec2(200, 200), 800, 400);

	//refreshEdited();


	rectangle_SVG.setWidth(wRect);
	rectangle_SVG.setHeight(hRect);

	scale = wRect / rSvgBounds.getWidth();

}
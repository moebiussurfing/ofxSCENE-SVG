#include "DEMO_Svg.h"

//--------------------------------------------------------------
void DEMO_Svg::setup() {
	ofLogNotice(__FUNCTION__);

	path_Global = "ofxSCENE-SVG/";
	path_AppSettings = path_Global + "DEMO_Svg.xml";

	//--

	// set the svg file and jpg lines

	// moebius.svg
	//svg.load(path_Global + "moebius/moebius-giraud.svg");
	//img.load(path_Global + "moebius/moebius-lines.jpg");
	//shape = glm::vec2(838, 1080);
	//maxNumSvgGroupColors = 7;

	// nike.svg
	svg.load(path_Global + "nike/nike.svg");
#ifdef USE_MASK
	img_Mask.load(path_Global + "nike/nike-Mask.jpg");
#endif
	img.load(path_Global + "nike/nike.jpg");
	shape = glm::vec2(1024, 666);
	maxNumSvgGroupColors = 8;

	//--

	//TODO:
	//could add svg file selector
	
	//TODO:
	//should auto get the num of groups
	//for the momment we need to set manualy the num of groups.
	//remember to name the the groups as: group1, group2, group3... on Illustrator
	//use SVG 1.1 tiny file format.
	//shared_ptr<ofxSvgGroup> bGroup = svg.get< ofxSvgGroup>(name.c_str());

	//--

	ofLogNotice(__FUNCTION__) << svg.toString();

	rSvgBounds = svg.getBounds();

	w = rSvgBounds.getWidth();
	h = rSvgBounds.getHeight();

	//TODO:
	//scale
	//svg.getTransformFromSvgMatrix
	//getTransformFromSvgMatrix(string matrix, ofVec2f& apos, float & scaleX, float & scaleY, float & arotation)
	//vector< shared_ptr<ofxSvgImage> > trees = svg.getElementsForType< ofxSvgImage>("trees");

	shape = glm::vec2(w, h);
	//ratio = shape.x / shape.y;

	img.resize(w, h);

#ifdef USE_MASK
	img_Mask.resize(w, h);
#endif

	//psBlend.setup(w, h);
	psBlend.setup(img.getWidth(), img.getHeight());

	//blendMode = 1;//multiply

	paletteSvg.clear();
	paletteSvg.resize(maxNumSvgGroupColors);

	// draggable rect
	rSvg.setRect(rSvgBounds.getX(), rSvgBounds.getY(), w, h);//default init
	rSvg.setLockResize(false);
	//rSvg.setLockResize(true);

	// b. load settings
	//rSvg.loadSettings();
	path_Layout = path_Global;
	rSvg.loadSettings(path_Name, path_Layout, false);
	rSvg.disableEdit();

	//rSvg.enableEdit();

	//_xx = rSvg.getX() + _pad1;
	//_yy = rSvg.getY() + _pad1;

	//--

#ifdef USE_MASK
	srcFbo.allocate(1920, 1080, GL_RGBA);
	//srcFbo.allocate(w, h, GL_RGBA);
	srcFbo.begin();
	{
		ofClear(0);
	}
	srcFbo.end();

	maskFbo.allocate(1920, 1080, GL_RGBA);
	//maskFbo.allocate(w, h, GL_RGBA);
	maskFbo.begin();
	{
		ofClear(0);
	}
	maskFbo.end();
#endif

	//--

	//blendMode.setSerializable(false);
	//blendModeName.setSerializable(false);

	params.add(DEMO2_Test);
	params.add(DEMO2_Edit);
	params.add(DEMO2_Scale);
	params.add(DEMO2_Alpha);
	params.add(blendMode);
	params.add(blendModeName);

	ofAddListener(params.parameterChangedE(), this, &DEMO_Svg::Changed_Controls);

	//--

	gui.setup("ofxSCENE-SVG");
	gui.add(params);

	//--

	startup();
}

//--------------------------------------------------------------
void DEMO_Svg::startup() {
	ofLogNotice(__FUNCTION__);

	ofxSurfingHelpers::loadGroup(params, path_AppSettings);
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
	ofLogNotice(__FUNCTION__) << "scrollX: " << scrollX << "  scrollY: " << scrollY;

	if (DEMO2_Edit)
	{
		if (rSvg.inside(glm::vec2(x, y)))//zoom 
			if (scrollY == 1) DEMO2_Scale += 0.025f;
			else if (scrollY == -1) DEMO2_Scale -= 0.025f;
	}
}

//--------------------------------------------------------------
void DEMO_Svg::Changed_Controls(ofAbstractParameter &e)
{
	std::string name = e.getName();

	ofLogNotice(__FUNCTION__) << name << " : " << e;

	//----

	if (false) {}

	//----

	// demo2 svg
	else if (name == DEMO2_Edit.getName())
	{
		setEdit(DEMO2_Edit);
	}
	else if (name == DEMO2_Scale.getName())
	{
		setScale(DEMO2_Scale);
	}
	else if (name == DEMO2_Alpha.getName())
	{
		setAlpha(DEMO2_Alpha);
	}

	// blend
	else if (name == blendMode.getName())
	{
		blendModeName = psBlend.getBlendMode(blendMode);
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

			for (int i = 0; i < maxNumSvgGroupColors; i++)
			{
				paletteSvg[i] = (*palette_TARGET)[i % szp];
			}
		}

		//--

		// assign fill color to svg groups

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

	if (rSvg.isEditing())
	{
		////highlight
		//ofFill();
		//int fr = ofGetFrameNum() % 60;
		//ofSetColor(fr < 30 ? ofColor(255, 16) : (ofColor(0, 16)));
		//ofDrawRectangle(rSvg);

		//-

		w2 = (rSvgBounds.getWidth() * scale);
		h2 = (rSvgBounds.getHeight() * scale);

		x2 = rSvg.getX();
		y2 = rSvg.getY();

		rSvg.setWidth(w2);
		rSvg.setHeight(h2);

		//float _ratio = rSvg.getHeight() / rSvg.getHeight();
		//scale = rSvg.getY() / rSvgBounds.getY();
	}
}

#ifdef USE_MASK
//--------------------------------------------------------------
void DEMO_Svg::update_Mask()
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
		img_Mask.draw(x2, y2, w2, h2);
	}
	maskFbo.end();
}

//--------------------------------------------------------------
void DEMO_Svg::draw_Mask()
{
	// srcFbo maskFbo
	ofSetColor(255, 255);
	alphaMask.begin(maskFbo.getTexture());
	{
		srcFbo.draw(0, 0, w, h);
	}
	alphaMask.end();

	//previews
	//ofPushMatrix();
	//{
	//	ofScale(scale, scale);
	//	srcFbo.draw(0, 0);
	//	maskFbo.draw(w, 0);
	//}
	//ofPopMatrix();
}

#endif

////--------------------------------------------------------------
//void DEMO_Svg::draw(glm::vec2 _pos) //force pos
//{
//	pos = _pos;
//	rSvg.setPosition(pos.x, pos.y);
//	draw();
//}

//--------------------------------------------------------------
void DEMO_Svg::draw_SVG()
{
	psBlend.begin();
	svg.draw();
	psBlend.end();

	//--

	//TODO:
	// nike
	ofClear(255);

	//-

	//blend types
	//string str;
	//str += "Press UP/DOWN key\n";
	//str += "Blend Mode: [" + ofToString(blendMode) + "] " + psBlend.getBlendMode(blendMode);
	//ofDrawBitmapStringHighlight(str, 20, 30);

	ofPushStyle();
	ofPushMatrix();

	ofTranslate(rSvg.getX(), rSvg.getY());

	//ofPushMatrix();
	//ofTranslate(rSvg.getWidth() / 2.f, rSvg.getHeight()/2.0f);
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
	if (DEMO2_Test)
	{
		update();

		//----

#ifndef USE_MASK
		draw_SVG();
#endif

#ifdef USE_MASK
		draw_Mask();
#endif

	}

	//----

	if (ShowGui) gui.draw();

	//ImGui
	//ofxImGui::AddParameter(DEMO2_Svg.DEMO2_Test);
	//if (DEMO2_Svg.DEMO2_Test)
	//{
	//	ofxImGui::AddParameter(DEMO2_Svg.DEMO2_Edit);
	//	//if (ImGui::DragFloat("Scale", &scale, 0.2, 1.0))
	//	if (ofxImGui::AddParameter(DEMO2_Svg.DEMO2_Scale))
	//	{
	//	}
	//	if (ofxImGui::AddParameter(DEMO2_Svg.DEMO2_Alpha))
	//	{
	//	}
	//}
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
	const int key = eventArgs.key;

	// modifiers
	bool mod_COMMAND = eventArgs.hasModifier(OF_KEY_COMMAND);
	bool mod_CONTROL = eventArgs.hasModifier(OF_KEY_CONTROL);
	bool mod_ALT = eventArgs.hasModifier(OF_KEY_ALT);
	bool mod_SHIFT = eventArgs.hasModifier(OF_KEY_SHIFT);

	ofLogNotice(__FUNCTION__) << key;

	if (/*key == OF_KEY_UP ||*/ key == '-')
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

	else if (/*key == OF_KEY_DOWN || key == ' ' ||*/ key == '+')
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
}
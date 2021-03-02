ofxSCENE-SVG
=============================

# Overview
**ofxSCENE-SVG** is an **openFrameworks** addon to load and live-colorize an **SVG** file layered by named groups.  
Also blends the **SVG** with a **JPG** file, like an outline B&W lines image.

## Screenshot
![image](/readme_images/Capture2.PNG?raw=true "image")

## Features
- GUI and store/recall settings.
- Resize and scale using mouse.
- Different blend modes and transparency.

## Usage
Look the example.
On Illustrator: 
Import your image to be vectorized.  
Draw all each color mask/shape by hand.  
Name the groups/layers as: *group1*, *group2*, *group3*... as in the screenshot.  
Save as **SVG Tiny 1.1**.  

## Dependencies
* [ofxSurfingHelpers](https://github.com/moebiussurfing/ofxSurfingHelpers)  
* ofxGui

Already included into *OF_ADDON/libs*. No need to add manually.  
Look into folders to authorship, original forks, or licenses.  
* ofxPSBlend
* ofxScaleDragRect
* ofxSvg
* ofxSvgLoader

## TODO:
* add masked mode.
* size colors is hardcoded now to my two SVG samples.

## Tested systems
- **Windows10** / **VS2017** / **OF ~0.11**

## Author
An addon by **@moebiusSurfing**  
*(ManuMolina). 2020.*

## License
*MIT License.*
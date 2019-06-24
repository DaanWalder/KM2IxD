#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

#define CAM_WIDTH 320
#define CAM_HEIGHT 240
#define HUE_MARGIN 5

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void mousePressed(int x, int y, int button);

	ofVideoGrabber grabber;
	ofxCvHaarFinder haarFinder;
	ofxCvHaarFinder faceFinder;
	ofxCvHaarFinder handFinder;
	ofxCvContourFinder colorFinder;
	ofImage image;

	ofxCvColorImage rgbImage;
	ofxCvColorImage hsvImage;
		ofxCvGrayscaleImage hueImage;
		ofxCvGrayscaleImage satImage;
		ofxCvGrayscaleImage valImage;

		ofxCvGrayscaleImage filtered;
		ofxCvContourFinder contours;
		int selectedHue;
};

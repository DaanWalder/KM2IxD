#pragma once

#include "ofMain.h"

#define CAM_WIDTH 320
#define CAM_HEIGHT 240

class ofApp : public ofBaseApp {

public:
	void setup();

	void update();

	void draw();

	void keyPressed(int key);

private:
	ofVideoGrabber grabber;
	ofImage image;
	ofPixels workspace;

	int randomRMutation = -1;
	int randomGMutation = -1;
	int randomBMutation = -1;
	bool drawGrabbedImage = true;

	void randomizeColors();
};

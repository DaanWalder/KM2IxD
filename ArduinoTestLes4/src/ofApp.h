#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		ofxPanel gui;
		ofParameter<bool> LED;

		ofArduino arduino;
		void setupArduino(const int& version);
};

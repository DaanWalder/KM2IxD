#include "ofApp.h"

void ofApp::setup() {
	// for info:
	grabber.listDevices();

	grabber.setDeviceID(0);
	grabber.initGrabber(CAM_WIDTH, CAM_HEIGHT);
	grabber.setDesiredFrameRate(30);

	// create a scratchpad of the same size as the camera image
	workspace.allocate(CAM_WIDTH, CAM_HEIGHT, OF_IMAGE_COLOR);
}

void ofApp::randomizeColors() {
	// pick random values to mutate the original colour values
	randomRMutation = ofRandom(255);
	randomGMutation = ofRandom(255);
	randomBMutation = ofRandom(255);
}

void ofApp::update() {
	grabber.update();

	if (grabber.isFrameNew()) {
		ofPixels& pixels = grabber.getPixels();
		for (int y = 0; y < pixels.getHeight(); y++) {
			for (int x = 0; x < pixels.getWidth(); x++) {
				ofColor col = pixels.getColor(x, y);

				if (randomRMutation != -1) {
					col.r = randomRMutation - col.r;
					col.g = randomGMutation - col.g;
					col.b = randomBMutation - col.b;
				}

				workspace.setColor(x, y, col);
			}
		}

		// update the image with the modified pixels
		image.setFromPixels(workspace);
	}
}

void ofApp::draw() {
	// draw the grabbed image, scaled up 3 times
	image.draw(0, 0, CAM_WIDTH * 3, CAM_HEIGHT * 3);

	if (drawGrabbedImage) {
		grabber.draw(0, 0);
	}
}

void ofApp::keyPressed(int key) {
	if (key == ' ') {
		randomizeColors();
	}
	else if (key == 'g') {
		drawGrabbedImage = !drawGrabbedImage;
	}
}

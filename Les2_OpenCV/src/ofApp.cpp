#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	//grabber.listDevices();
	grabber.setDeviceID(0);
	grabber.initGrabber(CAM_WIDTH, CAM_HEIGHT);
	grabber.setDesiredFrameRate(30);

	rgbImage.allocate(CAM_WIDTH, CAM_HEIGHT);
	hsvImage.allocate(CAM_WIDTH, CAM_HEIGHT);
	hueImage.allocate(CAM_WIDTH, CAM_HEIGHT);
	satImage.allocate(CAM_WIDTH, CAM_HEIGHT);
	valImage.allocate(CAM_WIDTH, CAM_HEIGHT);
	filtered.allocate(CAM_WIDTH, CAM_HEIGHT);

	haarFinder.setup("haarcascade_eyes.xml");
	faceFinder.setup("haarcascade_frontalface_default.xml");
	handFinder.setup("palm.xml");
	image.load("sunglasses.png");

}

//--------------------------------------------------------------
void ofApp::update() {
	grabber.update();
	
	if (grabber.isFrameNew()) {
		rgbImage.setFromPixels(grabber.getPixels());
		rgbImage.mirror(false, true);

		hsvImage = rgbImage;
		hsvImage.convertRgbToHsv();
		hsvImage.convertToGrayscalePlanarImages(hueImage, satImage, valImage);

		for (int i = 0; i < CAM_HEIGHT*CAM_WIDTH; i++) {
			if (ofInRange(hueImage.getPixels()[i],
				selectedHue-HUE_MARGIN, selectedHue + HUE_MARGIN)) {
				filtered.getPixels()[i] = 255;
			} else {
				filtered.getPixels()[i] = 0;
			}
		}
		filtered.flagImageChanged();
		contours.findContours(filtered, 50, 50, CAM_WIDTH*CAM_HEIGHT / 2, 1, false);
	}

	if (grabber.isFrameNew()) {
		haarFinder.findHaarObjects(grabber.getPixels(), 75,75);
	}
	if (grabber.isFrameNew()) {
		faceFinder.findHaarObjects(grabber.getPixels(), 200, 200);
	}
	if (grabber.isFrameNew()) {
		handFinder.findHaarObjects(grabber.getPixels(), 100, 100);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	rgbImage.draw(0,0, ofGetWidth(), ofGetHeight());
	hsvImage.draw(0, 0);
	//hueImage.draw(0, CAM_HEIGHT);
	//satImage.draw(CAM_WIDTH, CAM_HEIGHT);
	//valImage.draw(CAM_WIDTH * 2, CAM_HEIGHT);
	filtered.draw(0, CAM_HEIGHT);
	contours.draw(0, 0, ofGetWidth(), ofGetHeight());
	ofSetColor(ofColor::blue);
	for (int i = 0; i < contours.blobs.size(); i++) {
		ofDrawCircle(contours.blobs[i].centroid.x * ofGetWidth()/CAM_WIDTH,
			contours.blobs[i].centroid.y *ofGetHeight()/CAM_HEIGHT, 20);
	}
	ofSetColor(ofColor::white);
	/*
	ofNoFill();
	ofSetColor(ofColor::green);
	for (int i = 0; i < faceFinder.blobs.size(); i++) {
		ofRectangle boundingBox = faceFinder.blobs[i].boundingRect;
		ofDrawRectangle(boundingBox);
	}
	ofSetColor(ofColor::blue);
	for (int i = 0; i < haarFinder.blobs.size(); i++) {
		ofRectangle boundingBox = haarFinder.blobs[i].boundingRect;
		image.draw(boundingBox);
	}
	ofSetColor(ofColor::red);
	for (int i = 0; i < handFinder.blobs.size(); i++) {
		ofRectangle boundingBox = handFinder.blobs[i].boundingRect;
		ofDrawRectangle(boundingBox);
	}
	*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

void ofApp::mousePressed(int x, int y, int button) {
	selectedHue = hueImage.getPixels()[y * CAM_WIDTH + CAM_HEIGHT];
	cout << "selected: " << selectedHue << endl;
}
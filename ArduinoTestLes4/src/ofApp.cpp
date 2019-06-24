#include "ofApp.h"

#define PIN_REDLED 12
#define PIN_POT 0
#define PIN_BUTTONRED 6
#define PIN_BUTTONYELLOW 7
//--------------------------------------------------------------
void ofApp::setup(){
	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
	arduino.connect("COM3", 57600);
	arduino.sendFirmwareVersionRequest();

	gui.setup();
	gui.add(LED.set("LED ON/OFF", false));
}

void ofApp::setupArduino(const int& version) {
	ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);
	ofLog() << "Arduino firmware found: " << arduino.getFirmwareName()
		<< " v" << arduino.getMajorFirmwareVersion() << "." << arduino.getMinorFirmwareVersion();

	arduino.sendDigitalPinMode(PIN_BUTTONRED, ARD_OUTPUT);
	arduino.sendDigitalPinMode(7, ARD_INPUT);
	arduino.sendDigitalPinMode(PIN_REDLED, ARD_OUTPUT);
	arduino.sendAnalogPinReporting(0, ARD_ANALOG);
	;

}
//--------------------------------------------------------------
void ofApp::update(){
	arduino.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (LED)
	{
		arduino.sendDigital(PIN_REDLED, ARD_HIGH);
	}
	// Hier zit de foutmelding
	else
	{
		arduino.sendDigital(PIN_REDLED, ARD_LOW);
	}
}


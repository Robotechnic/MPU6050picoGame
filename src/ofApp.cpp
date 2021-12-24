#include "ofApp.h"

void ofApp::updateSerial() {
	auto deviceList = this->serial.getDeviceList();

	this->serialGroup.clear();
	this->serialDevices.clear();

	for (ofSerialDeviceInfo info : deviceList) {
		if (info.getDeviceName()[3] != 'S') { // ignore all devices like ttyS[some number]
			ofxButton *b = new ofxButton();
			ofLog()<<info.getDeviceID()<<" "<<info.getDeviceName()<<" "<<info.getDevicePath();
			this->serialGroup.add(
						b->setup(info.getDeviceName())
						);

			b->addListener(this, &ofApp::connectToSerial);

			this->serialDevices.push_back(*b);
		}
	}

	this->panel.setPosition(
				ofGetWidth() / 2 - this->panel.getWidth() / 2,
				ofGetHeight() / 2 - this->panel.getHeight() / 2
			);
}

void ofApp::connectToSerial(const void *sender) {
	ofParameter<void> * b = (ofParameter<void> *)sender;
	ofLog()<<"Connect to "<<b->getName();
	this->serial.setup(b->getName(), 115200);
}

void ofApp::updatePitchRoll() {
	char ch;
	while (this->serial.available()) {
		ch = this->serial.readByte();
		if (ch != '\n') {
			this->serialData <<	ch;
		} else {
			this->serialData >> this->pitch;
			this->serialData >> this->roll;
		}
	}
}

//--------------------------------------------------------------
void ofApp::setup(){
	this->panel.setup();
	this->panel.setName("Select serial device");
	this->panel.add(this->serialGroup.setup("List of devices :"));
	this->panel.add(this->refresh.setup("Refresh list"));
	this->refresh.addListener(this,&ofApp::updateSerial);
	this->updateSerial();
	this->roll = 0;
	this->pitch = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (this->serial.isInitialized() && this->serial.available()) this->updatePitchRoll();
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (!this->serial.isInitialized())
		this->panel.draw();
	else
		ofDrawEllipse(
					ofMap(-this->roll, -90, 90, 0, ofGetWidth()),
					ofMap(-this->pitch, -90, 90, 0, ofGetHeight()),
					10,
					10
				);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------

ofxButton b;void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
//void ofApp::mouseMoved(int x, int y ){

//}

////--------------------------------------------------------------
//void ofApp::mouseDragged(int x, int y, int button){

//}

////--------------------------------------------------------------
//void ofApp::mousePressed(int x, int y, int button){

//}

////--------------------------------------------------------------
//void ofApp::mouseReleased(int x, int y, int button){

//}

////--------------------------------------------------------------
//void ofApp::mouseEntered(int x, int y){

//}

////--------------------------------------------------------------
//void ofApp::mouseExited(int x, int y){

//}

////--------------------------------------------------------------
//void ofApp::windowResized(int w, int h){

//}

////--------------------------------------------------------------
//void ofApp::gotMessage(ofMessage msg){

//}

////--------------------------------------------------------------
//void ofApp::dragEvent(ofDragInfo dragInfo){

//}

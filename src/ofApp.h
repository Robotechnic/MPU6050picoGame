#pragma once

#include <ofBaseApp.h>
#include <ofGraphics.h>
#include <ofLog.h>
#include <ofxGui.h>
#include <ofxButton.h>
#include <ofxLabel.h>
#include <ofxGuiGroup.h>
#include <ofParameter.h>
#include <ofSerial.h>
#include <vector>
#include <sstream>

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void updateSerial();
	void connectToSerial(const void *sender);

	void keyPressed(int key);
	void keyReleased(int key);
//	void mouseMoved(int x, int y );
//	void mouseDragged(int x, int y, int button);
//	void mousePressed(int x, int y, int button);
//	void mouseReleased(int x, int y, int button);
//	void mouseEntered(int x, int y);
//	void mouseExited(int x, int y);
//	void windowResized(int w, int h);
//	void dragEvent(ofDragInfo dragInfo);
//	void gotMessage(ofMessage msg);

private:
	//serial
	ofSerial serial;
	void updatePitchRoll();
	std::stringstream serialData;
	float pitch, roll;

	// gui
	ofxPanel panel;
	ofxGuiGroup serialGroup;
	std::vector<ofxButton> serialDevices;
	ofxButton refresh;

};

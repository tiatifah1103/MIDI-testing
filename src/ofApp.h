#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

class ofApp : public ofBaseApp, public ofxMidiListener {

	public:
		void setup() override;
//		void update() override;
    void newMidiMessage(ofxMidiMessage& msg);
//		void draw() override;
		void exit() override;

		
		
    ofxMidiIn midiIn;
    ofxMidiMessage midiMessage;
};

#include "ofApp.h"

void ofApp::setup() {
    ofSetLogLevel(OF_LOG_VERBOSE);

    // Open the MIDI port for the Mixtrack Pro
    midiIn.listInPorts(); // Lists available MIDI ports in the console
    midiIn.openPort(0);  // Replace 0 with the Mixtrack Pro's port number
    midiIn.addListener(this);
    midiIn.setVerbose(true); // For debugging
}

void ofApp::newMidiMessage(ofxMidiMessage& msg) {
    midiMessage = msg;

    // Log MIDI input
    ofLog() << "Channel: " << msg.channel
            << " Control: " << msg.control
            << " Value: " << msg.value;
}

void ofApp::exit() {
    midiIn.closePort();
    midiIn.removeListener(this);
}

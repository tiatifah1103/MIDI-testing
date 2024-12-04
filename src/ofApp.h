#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxJSON.h"
#include "maximilian.h"
#include "maxiReverb.h" 

class ofApp : public ofBaseApp, public ofxMidiListener {
public:
    void setup() override;
    void newMidiMessage(ofxMidiMessage& msg);
    void update();
    void exit() override;
    void nextTrack();
    void audioOut(ofSoundBuffer &buffer);
    ofxMidiIn midiIn;
    ofxMidiMessage midiMessage;
    ofSoundPlayer soundPlayer;
    ofSoundPlayer player;
    ofxJSONElement json;

    std::vector<std::string> playlistFiles;
    std::vector<std::string> trackTitles;
    std::vector<std::string> trackArtists;

    int currentTrackIndex = 0;

    // Reverb
    maxiDelayline delay;
    
    ofSoundStream soundStream;

};

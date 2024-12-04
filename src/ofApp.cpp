#include "ofApp.h"

float jogWheelPosition = 0.0; // Store the jog wheel's position as a relative value
float previousJogWheelValue = 0.0; // Store the previous value of the jog wheel
float volume = 1.0; // Default volume value (max)

// Declare the delay-related variables in ofApp.h
float delayAmount = 0.5f;  // Default value for delay amount (range: 0.0 - 1.0)
float delayFeedback = 0.9f;  // Default value for delay feedback (range: 0.0 - 1.0)
float delayTime = 5.0f;  // Default delay time in seconds
float feedback = 0.5f;  // Default feedback value for the reverb effect
float mix = 0.9f;  // The mix amount (dry/wet mix)
float delayBuffer[44100];  // Delay buffer to hold audio samples (1-second buffer at 44.1kHz)
int delayBufferIndex = 0;  // Index to keep track of the buffer position


void ofApp::setup() {
    ofSetLogLevel(OF_LOG_VERBOSE);

    // Opens the MIDI port for the Mixtrack Pro
    midiIn.listInPorts(); // Lists available MIDI ports in the console
    midiIn.openPort(0);
    midiIn.addListener(this);
    midiIn.setVerbose(true); // For debugging
    
//    if (json.open("playlist.json")) {
//        for (auto& track : json) {
//            playlistFiles.push_back(track["file"].asString());
//            trackTitles.push_back(track["title"].asString());
//            trackArtists.push_back(track["artist"].asString());
//        }
//    }
//
//    // Loads the first track
//    if (!playlistFiles.empty()) {
//        player.load(playlistFiles[currentTrackIndex]);
//        player.play();
//        ofLog() << "Now Playing: " << trackTitles[currentTrackIndex];
//    }
//    
//    // Initialize the delay buffer with zeros
//        memset(delayBuffer, 0, sizeof(delayBuffer));
    
    ofSoundStreamSettings settings;
        settings.setOutListener(this);
        settings.sampleRate = 44100;
        settings.numOutputChannels = 2; // Stereo output
        settings.numInputChannels = 0; // No input
        settings.bufferSize = 512;     // Standard buffer size

        soundStream.setup(settings);

        ofLog() << "Audio stream initialized.";
}

void ofApp::update() {
    float time = ofGetElapsedTimef();
    float sine = sin(TWO_PI * 440 * time);
    ofSoundBuffer testBuffer;
    testBuffer.allocate(512, 2);
    for (int i = 0; i < testBuffer.getNumFrames(); i++) {
        testBuffer[i * 2] = sine;     // Left
        testBuffer[i * 2 + 1] = sine; // Right
    }
}

void ofApp::newMidiMessage(ofxMidiMessage& msg) {
//    midiMessage = msg;
//
//    // Log MIDI input to check the message type
//    ofLog() << "Type: " << msg.status
//            << " Control/Pitch: " << (msg.status == MIDI_CONTROL_CHANGE ? msg.control : msg.pitch)
//            << " Value: " << msg.value;
//
//    // Handle Control Change (CC) messages for jog wheel
//    if (msg.status == MIDI_CONTROL_CHANGE) {
//        // Handle jog wheel CC message
//        if (msg.control == 24) {
//            // Calculate the difference in jog wheel movement
//            float jogWheelDelta = (msg.value - previousJogWheelValue) / 127.0; // Normalize the movement to a -1.0 to 1.0 range
//
//            // Update the track's position based on the jog wheel movement
//            jogWheelPosition += jogWheelDelta; // Update position incrementally based on the jog wheel's movement
//            jogWheelPosition = ofClamp(jogWheelPosition, 0.0, 1.0); // Keep position within bounds [0, 1]
//
//            // Update the player position based on jog wheel movement
//            player.setPosition(jogWheelPosition);
//
//            previousJogWheelValue = msg.value; // Store the current value for the next delta calculation
//        }
//
//        // Handle volume control slider (assuming control 23 is mapped to volume)
//        if (msg.control == 23) {
//            volume = ofMap(msg.value, 0, 127, 0.0, 1.0); // Map to range 0-1
//            player.setVolume(volume); // Set the volume
//            ofLog() << "Volume: " << volume;
//        }
//    }
//
//    // Handle Note On/Off messages for play/pause button or other controls
//    if (msg.status == MIDI_NOTE_ON || msg.status == MIDI_NOTE_OFF) {
//        // For play/pause functionality
//        if (msg.pitch == 66) {
//            if (msg.velocity > 0) { // Only toggle on button press (velocity > 0)
//                if (player.isPlaying()) {
//                    player.setPaused(true);  // Pause if currently playing
//                } else {
//                    player.play();  // Play if currently paused
//                }
//            }
//        }
//
//
//        if (msg.pitch == 59) { 
//            nextTrack();
//        }
//    }
//    
//    if (msg.status == MIDI_CONTROL_CHANGE) {
//            // Control for delay amount (knob 1)
//            if (msg.control == 20) {
//                delayAmount = ofMap(msg.value, 0, 127, 0.0, 1.0);  // Map MIDI value to delay range
//                ofLog() << "Delay Amount: " << delayAmount;
//            }
//
//            // Control for delay feedback (knob 2)
//            if (msg.control == 21) {
//                delayFeedback = ofMap(msg.value, 0, 127, 0.0, 1.0);  // Map MIDI value to feedback range
//                ofLog() << "Delay Feedback: " << delayFeedback;
//            }
//        }
}

void ofApp::nextTrack() {
//    currentTrackIndex++;
//    if (currentTrackIndex >= playlistFiles.size()) {
//        currentTrackIndex = 0; // Loop back to the first track
//    }
//    
//    player.stop();  // Stop current track
//    player.load(playlistFiles[currentTrackIndex]);  // Load the next track
//    player.play();  // Play the next track
//    ofLog() << "Now Playing: " << trackTitles[currentTrackIndex];
}

void ofApp::audioOut(ofSoundBuffer &buffer) {
    ofLog() << "audioOut is being called, buffer size: " << buffer.size();

    for (size_t i = 0; i < buffer.getNumFrames(); i++) {
        float sample = sin(TWO_PI * 440 * i / 44100.0);  // 440 Hz test tone
        buffer[i * buffer.getNumChannels()] = sample;    // Left channel
        buffer[i * buffer.getNumChannels() + 1] = sample; // Right channel
    }
}

void ofApp::exit() {
    midiIn.closePort();
    midiIn.removeListener(this);
}

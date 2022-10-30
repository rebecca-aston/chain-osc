#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

// listen on port 12345
#define PORT 9999
#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp {
	public:

		void setup();
		void update();
		void draw();
    
        void setupChain();
    
        void drawMouth(ofEventArgs & args);
        void drawEye(ofEventArgs & args);
        void drawEar(ofEventArgs & args);
        void drawStomach(ofEventArgs & args);

		ofxOscReceiver receiver;
    
        deque<string> messageBuffer;
    
        deque<string> earMessageBuffer;
        deque<string> eyeMessageBuffer;
        deque<string> mouthMessageBuffer;
        deque<string> stomachMessageBuffer;
    
        bool earIsSending;
        bool eyeIsSending;
        bool mouthIsSending;
        bool stomachIsSending;
    
};

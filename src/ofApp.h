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
    
        string wrapString(string text, int width);

		ofxOscReceiver receiver;
    
        deque<string> messageBuffer;
    
        deque<string> earMessageBuffer;
        deque<string> eyeMessageBuffer;
//        deque<float> mouthMessageBuffer;
//        deque<float> stomachMessageBuffer;
        float mouthMessage;
        float stomachMessageX;
        float stomachMessageY;
        float stomachMessageM;
    
        ofColor earColor;
    
        bool earIsSending;
        bool eyeIsSending;
        bool mouthIsSending;
        bool stomachIsSending;
    
        ofTrueTypeFont font;
        float fontSize;
        int sHeight;
};

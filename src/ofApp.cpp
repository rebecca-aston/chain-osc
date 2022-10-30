#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);
    
    ofSetCircleResolution(60);
	ofBackground(30, 30, 130);
    ofSetWindowTitle("CHAIN");
    
    
    earIsSending = false;
    eyeIsSending = false;
    mouthIsSending = false;
    stomachIsSending = false;

}

//--------------------------------------------------------------
void ofApp::update(){

	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);

        if(m.getAddress() == "/gyrosc/gyro") {
            
            earIsSending = true;
            
            // test
            //ear message buffer
            earMessageBuffer.push_front(m.getAddress() + ": " + ofToString(m.getArgAsFloat(0)));
        }else if(m.getAddress() == "/gyrosc/accel") {
                     
            eyeIsSending = true;
            
            // test
            //eye message buffer
            eyeMessageBuffer.push_front(m.getAddress() + ": " + ofToString(m.getArgAsFloat(0)));
            
        }else if(m.getAddress() == "/gyrosc/rrate") {
            
            mouthIsSending = true;
            
            // test
            //mouth message buffer
            mouthMessageBuffer.push_front(m.getAddress() + ": " + ofToString(m.getArgAsFloat(0)));
            
        }else if(m.getAddress() == "/gyrosc/quat") {
            
            stomachIsSending = true;
            
            // test
            //stomach message buffer
            stomachMessageBuffer.push_front(m.getAddress() + ": " + ofToString(m.getArgAsFloat(0)));
            //pop back...
        }
        else {
            // unrecognized message: display on the bottom of the screen
            
            //chain message buffer
            messageBuffer.push_front(m.getAddress() + ": UNRECOGNIZED MESSAGE");
        }
	}
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
	string buf;
	buf = "listening for osc messages on port" + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);

    // read the buffer
	for(int i = 0; i < messageBuffer.size(); i++){
		ofDrawBitmapString(messageBuffer[i], 10, 40 + 15 * i);
	}
    
    
    ofNoFill();
    ofSetLineWidth(2);
    float radius = ofGetWidth()*0.3;
    ofDrawCircle(ofGetWidth()/2,ofGetHeight()/2,radius);
    
    ofFill();
    if(earIsSending){
        ofSetColor(255,0,0);
    }else{
        ofSetColor(255);
    }
    
    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2 - radius, 10);
    
    if(eyeIsSending){
        ofSetColor(255,0,0);
    }else{
        ofSetColor(255);
    }
    
    ofDrawCircle(ofGetWidth()/2 + radius, ofGetHeight()/2 , 10);
    
    if(mouthIsSending){
        ofSetColor(255,0,0);
    }else{
        ofSetColor(255);
    }
    
    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2 + radius, 10);
    
    if(stomachIsSending){
        ofSetColor(255,0,0);
    }else{
        ofSetColor(255);
    }

    ofDrawCircle(ofGetWidth()/2-radius, ofGetHeight()/2, 10);
    
    
    
//    ofSetColor(255);
//    ofDrawBitmapString("Num messages: " + ofToString(messageBuffer.size()), 10, 20);
    //pop back messages once there are more than can be displayed
    float messagePxHeight = messageBuffer.size() * 15;
    if(messagePxHeight > ofGetHeight()){
        messageBuffer.pop_back();
    }
    
    
    //set them to false every frame so we get a flicker effect of data coming in
    
//    if(ofGetFrameNum()%60 == 0){
        earIsSending = false;
        eyeIsSending = false;
        mouthIsSending = false;
        stomachIsSending = false;
//    }

}


void ofApp::setupChain(){
 // setup other screen
}
void ofApp::drawMouth(ofEventArgs & args){
    //draw to other screen
    ofSetWindowTitle("The Mouth");
    ofBackground(255, 0, 0);
    
    ofDrawBitmapString("Num messages: " + ofToString(mouthMessageBuffer.size()), 10, 20);
    
    // read the buffer
    for(int i = 0; i < mouthMessageBuffer.size(); i++){
        ofDrawBitmapString(mouthMessageBuffer[i], 10, 40 + 15 * i);
    }
    
    
    //pop back messages once there are more than can be displayed
    float messagePxHeight = mouthMessageBuffer.size() * 15;
    if(messagePxHeight > ofGetHeight()){
        mouthMessageBuffer.pop_back();
    }
}

void ofApp::drawEye(ofEventArgs & args){
    //setup other screen
    ofSetWindowTitle("The Eye");
    ofBackground(0, 200, 100);
    
    ofDrawBitmapString("Num messages: " + ofToString(eyeMessageBuffer.size()), 10, 20);
    
    // read the buffer
    for(int i = 0; i < eyeMessageBuffer.size(); i++){
        ofDrawBitmapString(eyeMessageBuffer[i], 10, 40 + 15 * i);
    }
    
    //pop back messages once there are more than can be displayed
    float messagePxHeight = eyeMessageBuffer.size() * 15;
    if(messagePxHeight > ofGetHeight()){
        eyeMessageBuffer.pop_back();
    }
}

void ofApp::drawEar(ofEventArgs & args){
    //draw to other screen
    ofSetWindowTitle("The Ear");
    ofBackground(0, 150, 255);
    
    ofDrawBitmapString("Num messages: " + ofToString(earMessageBuffer.size()), 10, 20);
    
    // read the buffer
    for(int i = 0; i < earMessageBuffer.size(); i++){
        ofDrawBitmapString(earMessageBuffer[i], 10, 40 + 15 * i);
    }
    
    //pop back messages once there are more than can be displayed
    float messagePxHeight = earMessageBuffer.size() * 15;
    if(messagePxHeight > ofGetHeight()){
        earMessageBuffer.pop_back();
    }
}

void ofApp::drawStomach(ofEventArgs & args){
    //draw to other screen
    ofSetWindowTitle("The Stomach");
    ofBackground(255, 100, 0);
    
    ofDrawBitmapString("Num messages: " + ofToString(stomachMessageBuffer.size()), 10, 20);
    
    // read the buffer
    for(int i = 0; i < stomachMessageBuffer.size(); i++){
        ofDrawBitmapString(stomachMessageBuffer[i], 10, 40 + 15 * i);
    }
    
    
    //pop back messages once there are more than can be displayed
    float messagePxHeight = stomachMessageBuffer.size() * 15;
    if(messagePxHeight > ofGetHeight()){
        stomachMessageBuffer.pop_back();
    }
}

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);
    
    ofSetCircleResolution(60);
	ofBackground(30, 30, 130);
    ofSetWindowTitle("CHAIN");
    
    fontSize = 16;
    
    font.load("Courier",fontSize);
    
    earIsSending = false;
    eyeIsSending = false;
    mouthIsSending = false;
    stomachIsSending = false;

    stomachMessageX = -20;
    stomachMessageY = -20;
    
    earColor = ofColor(30, 30, 130);
    
} 

//--------------------------------------------------------------
void ofApp::update(){

	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);

        if(m.getAddress().find("ear") != string::npos) {
            
            earIsSending = true;
            
            vector<string> s = ofSplitString(m.getArgAsString(0),",");
            
            ofColor newColor = ofColor(ofToInt(s[0]),ofToInt(s[1]),ofToInt(s[2]));
            
            earColor = earColor.getLerped(newColor,0.9);
            
            // test
            //ear message buffer
//            earMessageBuffer.push_front(m.getAddress() + ": " + ofToString(m.getArgAsFloat(0)));
        }else if(m.getAddress().find("eye") != string::npos) {
                     
            eyeIsSending = true;
            
            // test
            //eye message buffer
            eyeMessageBuffer.push_front( ofToString(m.getArgAsString(0)));
            
        }else if(m.getAddress().find("mouth") != string::npos) {
            
            mouthIsSending = true;
            
            //change this to a vector of floats
            
            // 0 - 1000
            
            cout << m.getAddress() << endl;
            
            // test
            //mouth message buffer
//            mouthMessageBuffer.push_front(m.getArgAsFloat(0));
            mouthMessage = m.getArgAsFloat(0);

            
        }else if(m.getAddress().find("stomach") != string::npos) {
            
            stomachIsSending = true;
            
            if(m.getAddress().find("posX") != string::npos){
                stomachMessageX = m.getArgAsFloat(0);
            }else if(m.getAddress().find("posY") != string::npos){
                stomachMessageY = m.getArgAsFloat(0);
            }else{
                stomachMessageM = m.getArgAsFloat(0);
            }

        }
        else {
            // unrecognized message: display on the bottom of the screen
            
            //chain message buffer
           // messageBuffer.push_front(m.getAddress() + ": UNRECOGNIZED MESSAGE");
        }
	}
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
	string buf;
	buf = "listening for osc messages on port" + ofToString(PORT);
//    font.drawString(buf, 10, 20);

    // read the buffer
	for(int i = 0; i < messageBuffer.size(); i++){
		font.drawString(messageBuffer[i], 10, 20 + (fontSize*1.2) * i);
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
//    font.drawString("Num messages: " + ofToString(messageBuffer.size()), 10, 20);
    //pop back messages once there are more than can be displayed
//    float messagePxHeight = messageBuffer.size() * (fontSize*1.2);
//    if(messagePxHeight > ofGetHeight()){
//        messageBuffer.pop_back();
//    }
    
    
    //set them to false every frame so we get a flicker effect of data coming in
    
    if(ofGetFrameNum()%60 == 0){
        earIsSending = false;
        eyeIsSending = false;
        mouthIsSending = false;
        stomachIsSending = false;
    }

}


void ofApp::setupChain(){
 // setup other screen
}
void ofApp::drawMouth(ofEventArgs & args){
    //draw to other screen
//    ofSetWindowTitle("The Mouth");
    ofBackground(30, 30, 130);
    
    font.drawString("Volume: " + ofToString(mouthMessage), 10, 20);
    
    ofDrawRectangle(0,30,ofGetWidth(),ofGetHeight()*mouthMessage);
    
    // read the buffer
//    for(int i = 0; i < mouthMessageBuffer.size(); i++){
//        font.drawString(ofToString(mouthMessageBuffer[i]), 10, 20 + (fontSize*1.2) * i);
//    }
    
    
    //pop back messages once there are more than can be displayed
//    float messagePxHeight = mouthMessageBuffer.size() * (fontSize*1.2);
//    if(messagePxHeight > ofGetHeight()){
//        mouthMessageBuffer.pop_back();
//    }
}

void ofApp::drawEye(ofEventArgs & args){
    //setup other screen
//    ofSetWindowTitle("The Eye");
    ofBackground(30, 30, 130);
    
//    font.drawString("Num messages: " + ofToString(eyeMessageBuffer.size()), 10, 20);
    
    if(eyeMessageBuffer.size() > 0){
        string s = "";
        
        for(int i = 0; i < eyeMessageBuffer.size(); i++){
     
             s += eyeMessageBuffer[i] + "\n";
      
         }
        
        string wrapped = wrapString(s, ofGetWidth()-200);
        font.drawString(wrapped, 10, fontSize + 8);
        
        
        //pop back messages once there are more than can be displayed
        float messagePxHeight = eyeMessageBuffer.size() * (fontSize*1.2);
        if(eyeMessageBuffer.size() > 7){
            eyeMessageBuffer.pop_back();
        }
    }
  
}

void ofApp::drawEar(ofEventArgs & args){
    //draw to other screen
//    ofSetWindowTitle("The Ear");
    ofBackground(earColor);
    
//    font.drawString("Num messages: " + ofToString(earMessageBuffer.size()), 10, 20);
    
    // read the buffer
//    for(int i = 0; i < earMessageBuffer.size(); i++){
//        font.drawString(earMessageBuffer[i], 10, 20 + (fontSize*1.2) * i);
//    }
//
//    //pop back messages once there are more than can be displayed
//    float messagePxHeight = earMessageBuffer.size() * (fontSize*1.2);
//    if(messagePxHeight > ofGetHeight()){
//        earMessageBuffer.pop_back();
//    }
}

void ofApp::drawStomach(ofEventArgs & args){
    //draw to other screen
//    ofSetWindowTitle("The Stomach");
    ofBackground(30, 30, 130);
    
    font.drawString("Movement: " + ofToString(stomachMessageM), 10, 20);
    
    float x = ofMap(stomachMessageX,0,1920,-10,ofGetWidth());
    float y = ofMap(stomachMessageY,0,1080,-10,ofGetHeight());
    
    ofDrawCircle(x,y,10);
    
    
    // read the buffer
//    for(int i = 0; i < stomachMessageBuffer.size(); i++){
//        font.drawString(ofToString(stomachMessageBuffer[i]), 10, 20 + (fontSize*1.2) * i);
//    }
//
//
//    //pop back messages once there are more than can be displayed
//    float messagePxHeight = stomachMessageBuffer.size() * (fontSize*1.2);
//    if(messagePxHeight > ofGetHeight()){
//        stomachMessageBuffer.pop_back();
//    }
}


string ofApp::wrapString(string text, int width) {
  
    
    string typeWrapped = "";
    string tempString = "";
    vector <string> words = ofSplitString(text, " ");
      
    for(int i=0; i<words.size(); i++) {
  
        string wrd = words[i];
          
        tempString += wrd + " ";
        int stringwidth = font.stringWidth(tempString);
        if(stringwidth >= width) {
            tempString = "";
            typeWrapped += "\n";
        }
          
        typeWrapped += wrd + " ";
    }
      
    return typeWrapped;
      
}

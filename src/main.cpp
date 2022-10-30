#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

//	ofSetupOpenGL(640,480, OF_WINDOW);			// <-------- setup the GL context
//
//	// this kicks off the running of my app
//	// can be OF_WINDOW or OF_FULLSCREEN
//	// pass in width and height too:
//	ofRunApp( new ofApp());
    
    
    ofGLFWWindowSettings settings;
    settings.setSize(600, 600);
    settings.setPosition(ofVec2f(300,0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    //mouth window size / placement
    settings.setSize(300, 300);
    settings.decorated = true;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = false;
    
    settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> mouthWindow = ofCreateWindow(settings);
    mouthWindow->setVerticalSync(false);
    
    //eye window size / placement
    settings.setSize(300, 300);
    settings.decorated = true;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = false;
    
    settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> eyeWindow = ofCreateWindow(settings);
    eyeWindow->setVerticalSync(false);
    
    //ear window size / placement
    settings.setSize(300, 300);
    settings.decorated = true;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = false;
    
    settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> earWindow = ofCreateWindow(settings);
    earWindow->setVerticalSync(false);
    
    //stomach window size / placement
    settings.setSize(300, 300);
    settings.decorated = true;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = false;
    
    settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> stomachWindow = ofCreateWindow(settings);
    stomachWindow->setVerticalSync(false);
    
    shared_ptr<ofApp> mainApp(new ofApp);
    mainApp->setupChain();
    
    ofAddListener(mouthWindow->events().draw,mainApp.get(),&ofApp::drawMouth);
    
    ofAddListener(eyeWindow->events().draw,mainApp.get(),&ofApp::drawEye);
    
    ofAddListener(earWindow->events().draw,mainApp.get(),&ofApp::drawEar);
    
    ofAddListener(stomachWindow->events().draw,mainApp.get(),&ofApp::drawStomach);
    
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
    

}

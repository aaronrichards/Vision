#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    
    ofSetVerticalSync(false);
    ofSetFrameRate(30);
    ofBackground(0, 0, 0);
    
    setupWindows();
    setupCanvas();
    
    mapper.setup(&sourceContentFbo, &outputContentFbo, &canvas);
}

//--------------------------------------------------------------
void ofApp::setupWindows()
{
    
    
    _dm.setup(&outputContentFbo);
    
    //check for second monitor
    if (_dm.totalMonitors() > 1)
    {
        //get size of second monitor
        ofVec2f size = _dm.getMonitorSize(1);
        
        //need to get second monitors position
        ofVec2f pos = _dm.getMonitorPosition(1);
        
        //create window
        _dm.createWindow(pos.x, pos.y, size.x, size.y, true);
        
        //setup fbo to second windows properties
        sourceContentFbo.allocate(size.x, size.y, GL_RGBA);
        outputContentFbo.allocate(size.x, size.y, GL_RGBA);
    }
    else
    {
        //only one monitor. just create a standard window for now
        _dm.createWindow(0, 0, 800, 600);
        sourceContentFbo.allocate(800, 600, GL_RGBA);
        outputContentFbo.allocate(800, 600, GL_RGBA);
    }
    
    scale = 0.5;
    
}

void ofApp::setupCanvas()
{
    
    canvas.setZoom(1.0f);
	canvas.setMinZoom(0.1f);
	canvas.setMaxZoom(5.0f);
    canvas.setCanvasSize(ofVec2f(sourceContentFbo.getWidth(), sourceContentFbo.getHeight()));
	canvas.setScreenSize(ofGetWidth(), ofGetHeight());
	float gap = 50;
//	canvas.setViewportConstrain( ofVec3f(-gap, -gap), ofVec3f(canvas.getCanvasSize().x + gap, canvas.getCanvasSize().y + gap));
	canvas.zoomReset();
	grid.create();

}


void ofApp::exit()
{
    mapper.exit();
}


//--------------------------------------------------------------
void ofApp::update()
{
    canvas.update();
    mapper.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    
    //draw content into source. source content get drawn into the mapper
    sourceContentFbo.begin();
    {
        drawTestPattern();
    }
    sourceContentFbo.end();
    
    //draw the mapper into the canvas
    canvas.begin();
    {
        grid.draw();
        canvas.drawHelpers();
        mapper.draw();
     
    }
	canvas.end();
    
    //sourceContentFbo.draw(0, 0);
    
	canvas.drawDebug();
    mapper.drawDebug();

    
}

void ofApp::drawTestPattern()
{
    
    ofClear(255, 255, 255, 0);
    
    ofPushStyle();
    ofSetColor(200);
    ofRect(0, 0, sourceContentFbo.getWidth(), sourceContentFbo.getHeight());
    ofPopStyle();
    
    ofPushStyle();
    ofSetColor(100);
    ofRect(sourceContentFbo.getWidth() / 2, 0, sourceContentFbo.getWidth() / 2, sourceContentFbo.getHeight() / 2);
    ofPopStyle();
    
    ofPushStyle();
    ofSetColor(150);
    ofRect(0, sourceContentFbo.getHeight() / 2, sourceContentFbo.getWidth() / 2, sourceContentFbo.getHeight() / 2);
    ofPopStyle();
    
    ofPushStyle();
    ofSetColor(180);
    ofRect(sourceContentFbo.getWidth() / 2, sourceContentFbo.getHeight() / 2, sourceContentFbo.getWidth() / 2, sourceContentFbo.getHeight() / 2);
    ofPopStyle();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    
    switch (key)
    {
        case '=':
            canvas.zoomIn();
            break;
            
        case '-':
            canvas.zoomOut();
            break;
            
        case '0':
            canvas.zoomReset();
            break;
        case 'a':
            mapper._quadManager.addQuad();
            break;
            
        case 'd':
            mapper._quadManager.removeQuad();
            break;
            
        case 'm':
            mapper._quadManager.toggleMode();
            break;

    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

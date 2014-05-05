//
//  PanZoom.cpp
//  panzoom
//
//  Created by Aaron Richards on 23/04/2014.
//
//

#include "PanZoom.h"


//--------------------------------------------------------------
// Setup
//--------------------------------------------------------------
PanZoom::PanZoom()
{
    
	smoothFactor = 0.55;
	zoom = 1.0f;
    desiredZoom =  1.0f;
	minZoom = 0.1f;
	maxZoom = 10.0f;

	offset.x = offset.y = desiredOffset.x = desiredOffset.y = 0.0f;
    lastTouch = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
    
}

//--------------------------------------------------------------
void PanZoom::setScreenSize(int x, int y)
{
    
	screenSize.x = x;
	screenSize.y = y;
    
}

//--------------------------------------------------------------
void PanZoom::setCanvasSize(ofVec2f _size)
{
    canvasSize = _size;
}

//--------------------------------------------------------------
ofVec2f PanZoom::getCanvasSize()
{
    return canvasSize;
}

//--------------------------------------------------------------
void PanZoom::setMinZoom(float min)
{
    minZoom = min;
}

//--------------------------------------------------------------
void PanZoom::setMaxZoom(float max)
{
    maxZoom = max;
}

//--------------------------------------------------------------
void PanZoom::setZoom(float z)
{
    zoom = desiredZoom = z;
}

//--------------------------------------------------------------
void PanZoom::setSmoothFactor(float smooth)
{
    smoothFactor = smooth;
}

//--------------------------------------------------------------
float PanZoom::getZoom()
{
    return zoom;
}

//--------------------------------------------------------------
ofVec2f PanZoom::getOffset()
{
    return -offset;
}

//--------------------------------------------------------------
// Controls
//--------------------------------------------------------------
void PanZoom::zoomIn()
{
    desiredZoom = ofClamp( desiredZoom + 0.2, minZoom, maxZoom );
}

//--------------------------------------------------------------
void PanZoom::zoomOut()
{
    desiredZoom = ofClamp( desiredZoom - 0.2, minZoom, maxZoom );
}

//--------------------------------------------------------------
void PanZoom::zoomReset()
{
    
    setZoom(1.0f);
    lookAt(canvasSize/2);
    
}

//--------------------------------------------------------------
void PanZoom::position(ofVec2f pos)
{
    
    ofVec2f p;
    p = lastTouch - pos;
    offset = offset - (p * (1.0f / zoom));
    lastTouch = pos;
    
}

//--------------------------------------------------------------
void PanZoom::lookAt(ofVec2f p)
{
    
	desiredOffset.x = offset.x = -p.x;
	desiredOffset.y = offset.y = -p.y;
    
}

//--------------------------------------------------------------
void PanZoom::begin(int customW, int customH)
{
    
	int ww = customW == 0 ? ofGetWidth() : customW;
	int hh = customH == 0 ? ofGetHeight() : customH;
    
	float w = ww * 0.5f / zoom;
	float h = hh * 0.5f / zoom;
    
	glScalef( zoom, zoom, zoom);
	glTranslatef( offset.x + w, offset.y + h, 0.0f );
    
	//recalc visible box
//	topLeft = screenToWorld( ofVec2f() );
//	bottomRight = screenToWorld( screenSize );
    
}

//--------------------------------------------------------------
void PanZoom::end()
{
	ofSetupScreen();
}





//--------------------------------------------------------------
// Updating
//--------------------------------------------------------------
void PanZoom::update()
{
    
	float time = 1;
    zoom = (time * smoothFactor) * desiredZoom + (1.0f - smoothFactor * time) * zoom;
    offset = (time * smoothFactor) * desiredOffset + (1.0f - smoothFactor * time) * offset;
    
}




//--------------------------------------------------------------
// Drawing
//--------------------------------------------------------------
void PanZoom::drawDebug()
{
    
    char msg[1000];
	sprintf(msg, " zoom: %.1f \n offset: %.1f, %.1f \n lasttouch: %.1f, %.1f \n desiredOffset: %.1f, %.1f \n", zoom, offset.x, offset.y, lastTouch.x, lastTouch.y, desiredOffset.x, desiredOffset.y);
    glColor4f(1, 1, 1, 1);
	ofDrawBitmapString(msg, 3.0f, 25.0f);
    
}

void PanZoom::drawHelpers()
{
    
    //draw space constrains
    glColor4f(1, 1, 1, 0.1);
    ofRect(0, 0, canvasSize.x, canvasSize.y);
    
    glColor4f(1, 0, 0, 1);
    ofNoFill();
    ofSetLineWidth(2);
    ofRect(0, 0, canvasSize.x, canvasSize.y);
    ofFill();
    ofSetLineWidth(1);
    
    //canvas center cross
    glColor4f(1, 1, 1, 1);
    ofPushMatrix();
    ofTranslate(canvasSize.x / 2, canvasSize.y / 2);
    ofLine(0, -60, 0, 60);
    ofLine( -60, 0, 60,0);
    ofPopMatrix();
    
}




//--------------------------------------------------------------
// Mouse events
//--------------------------------------------------------------
void PanZoom::mousePressed(ofVec2f e)
{
    lastTouch = ofVec2f(e.x, e.y);
}

//--------------------------------------------------------------
void PanZoom::mouseDrag(ofVec2f e)
{
    ofVec2f p;
    p = lastTouch - ofVec2f(e.x, e.y);
    desiredOffset = desiredOffset - p * (1.0f / zoom);
    lastTouch = ofVec2f(e.x, e.y);
}

//--------------------------------------------------------------
void PanZoom::mouseReleased(ofVec2f e)
{
    lastTouch = ofVec2f(e.x, e.y);
}




//--------------------------------------------------------------
// Screen
//--------------------------------------------------------------
ofVec2f PanZoom::screenToWorld( const ofVec2f & p )
{
    
	float f = 1.0f / zoom;
	ofVec2f r;
	r.x =  f * p.x - f * ofGetWidth() * 0.5f - offset.x ;
	r.y =  f * p.y - f * ofGetHeight() * 0.5f - offset.y ;
    
	return r;
    
}

//--------------------------------------------------------------
ofVec2f PanZoom::worldToScreen( const ofVec2f & p )
{
    
	float f = 1.0f / zoom;
	ofVec2f r;
	r.x = ( p.x + f * ofGetWidth() * 0.5f + offset.x ) * zoom;
	r.y = ( p.y + f * ofGetHeight() * 0.5f + offset.y ) * zoom;
	return r;
    
}





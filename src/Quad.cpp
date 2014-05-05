//
//  Quad.cpp
//  canvas
//
//  Created by Aaron Richards on 28/04/2014.
//
//

#include "Quad.h"
#include "homography.h"


//--------------------------------------------------------------
// Setup
//--------------------------------------------------------------
void Quad::setup()
{
    
    src[0].x = 0;
    src[0].y = 0;
    src[1].x = 400;
    src[1].y = 0;
    src[2].x = 400;
    src[2].y = 400;
    src[3].x = 0;
    src[3].y = 400;
    
    dst[0].x = 0;
    dst[0].y = 0;
    dst[1].x = 400;
    dst[1].y = 0;
    dst[2].x = 400;
    dst[2].y = 400;
    dst[3].x = 0;
    dst[3].y = 400;
    
    setActive(false);

}


//--------------------------------------------------------------
// Update
//--------------------------------------------------------------
void Quad::update()
{
}



//--------------------------------------------------------------
// Draw
//--------------------------------------------------------------
void Quad::draw()
{
    
    glPushMatrix();
    
    findHomography(src, dst, matrix);
    glMultMatrixf(matrix);
    
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
    {
        
        glTexCoord2f(src[i].x, src[i].y);
        glVertex2f(src[i].x, src[i].y);
        
    }
    glEnd();
    
    glPopMatrix();
    
    
}


//--------------------------------------------------------------
void Quad::drawInputQuad()
{

    //shape
    ofPushStyle();
    ofNoFill();
    ofBeginShape();
    {
        if (activateCenter)
        {
            if (getActive()) ofSetColor(0, 255, 255, 200);
            else ofSetColor(255, 255, 255, 200);
        }
        else
        {
            if (getActive()) ofSetColor(0, 255, 255, 40);
            else ofSetColor(255, 255, 255, 40);
        }
        for (int i=0; i < 4; i++)
        {
            ofVertex(src[i].x, src[i].y);
        }
    }
    ofEndShape(true);
    ofPopStyle();
    
    //corners
    ofPushStyle();
    (getActive()) ? ofFill() : ofNoFill();
    for (int j=0; j < 4; j++)
    {
        if (activateCorner && corner == j)
        {
            if (getActive()) ofSetColor(0, 255, 255, 200);
            else ofSetColor(255, 255, 255, 200);
        }
        else
        {
            if (getActive()) ofSetColor(0, 255, 255, 40);
            else ofSetColor(255, 255, 255, 40);
        }
        ofCircle(src[j].x, src[j].y, 20);
    }
    ofPopStyle();
    
}

//--------------------------------------------------------------
void Quad::drawOutputQuad()
{
    
    //shape
    ofPushStyle();
    ofNoFill();
    ofBeginShape();
    {
        if (activateCenter)
        {
            if (getActive()) ofSetColor(0, 255, 255, 200);
            else ofSetColor(255, 255, 255, 200);
        }
        else
        {
            if (getActive()) ofSetColor(0, 255, 255, 40);
            else ofSetColor(255, 255, 255, 40);
        }
        for (int i=0; i < 4; i++)
        {
            ofVertex(dst[i].x, dst[i].y);
        }
    }
    ofEndShape(true);
    ofPopStyle();
    
    //corners
    ofPushStyle();
    ofNoFill();
    for (int j=0; j < 4; j++)
    {
        if (activateCenter && activateCorner == j)
        {
            
            if (getActive()) ofSetColor(0, 255, 255, 200);
            else ofSetColor(255, 255, 255, 200);
        
        }
        else
        {
            if (getActive()) ofSetColor(0, 255, 255, 40);
            else ofSetColor(255, 255, 255, 40);
        }
        ofCircle(dst[j].x, dst[j].y, 20);
    }
    ofPopStyle();

}


//--------------------------------------------------------------
// Status
//--------------------------------------------------------------
void Quad::setActive(bool _a)
{
    _active = _a;
}

//--------------------------------------------------------------
bool Quad::getActive()
{
    return _active;
}









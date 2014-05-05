//
//  Mapper.cpp
//  Mapper
//
//  Created by Aaron Richards on 24/04/2014.
//
//

#include "Mapper.h"


//--------------------------------------------------------------
// Setup
//--------------------------------------------------------------
void Mapper::setup(ofFbo *source, ofFbo *output, PanZoom* canvas)
{
    
    _canvas = canvas;
    
    _sourceContent = source;
    _outputContent = output;
    
    _quadManager.setup();
    
    ofAddListener(ofEvents().mouseMoved, this, &Mapper::mouseMoved);
    ofAddListener(ofEvents().mouseDragged, this, &Mapper::mouseDragged);
    ofAddListener(ofEvents().mousePressed, this, &Mapper::mousePressed);
    ofAddListener(ofEvents().mouseReleased, this, &Mapper::mouseReleased);
    ofAddListener(ofEvents().keyPressed, this, &Mapper::keyDown);
    ofAddListener(ofEvents().keyReleased, this, &Mapper::keyUp);
    
}

void Mapper::exit()
{
    ofRemoveListener(ofEvents().mouseMoved, this, &Mapper::mouseMoved);
    ofRemoveListener(ofEvents().mouseDragged, this, &Mapper::mouseDragged);
    ofRemoveListener(ofEvents().mousePressed, this, &Mapper::mousePressed);
    ofRemoveListener(ofEvents().mouseReleased, this, &Mapper::mouseReleased);
    ofRemoveListener(ofEvents().keyPressed, this, &Mapper::keyDown);
    ofRemoveListener(ofEvents().keyReleased, this, &Mapper::keyUp);
    
    _quadManager.exit();
}


//--------------------------------------------------------------
// Updating
//--------------------------------------------------------------
void Mapper::update()
{
    _quadManager.update();
};



//--------------------------------------------------------------
// Drawing
//--------------------------------------------------------------
void Mapper::draw()
{
    
    
    if (_quadManager.getMode() == QUAD_MODE_INPUT)
    {
        
        //draws fbo
        renderInput();
        //draws input outlines/quads
        _quadManager.renderInputQuads();
        
    }
    else
    {
        //draws output content
        renderOutput();
        //draws output lines/quads
        _quadManager.renderOutputQuads();
    }
    
    renderOutputDisplay();
    
}

void Mapper::renderOutputDisplay()
{
    //for second display
    _outputContent->begin();
    ofClear(.0f, .0f, .0f, .0f);
    ofClearAlpha();
    renderOutput();
    _outputContent->end();
}

//--------------------------------------------------------------
void Mapper::drawDebug()
{
    
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(ofColor::red);
    ofDrawBitmapString("Total Quads:" + ofToString(_quadManager.totalQuads()), 20, 20);
    ofDrawBitmapString("Active Quad:" + ofToString(_quadManager.activeQuadIndex), 20, 40);
    ofPopStyle();
    ofPopMatrix();
    
}


//--------------------------------------------------------------
// Input (FBO)
//--------------------------------------------------------------
void Mapper::bind()
{
    _sourceContent->begin();
    ofClear(.0f, .0f, .0f, .0f);
    ofClearAlpha();
}

//--------------------------------------------------------------
void Mapper::unbind()
{
    _sourceContent->end();
}

//--------------------------------------------------------------
void Mapper::renderInput()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    _sourceContent->draw(0, 0);
}



//--------------------------------------------------------------
// Output
//--------------------------------------------------------------
void Mapper::renderOutput()
{
    
    _sourceContent->getTextureReference().bind();
    ofSetColor(255, 255, 255, 255);
    _quadManager.draw();
    _sourceContent->getTextureReference().unbind();
    
}







//--------------------------------------------------------------
// Events. Convert the coordinates from the canvas to the quadmapper
//--------------------------------------------------------------
void Mapper::mouseMoved(ofMouseEventArgs &e)
{
    
    if(!modifierDrag)
    {
        ofVec2f point = _canvas->screenToWorld(ofVec2f(e.x, e.y));
        _quadManager.mouseMoved(point.x, point.y);
    }
    
}

//--------------------------------------------------------------
void Mapper::mouseDragged(ofMouseEventArgs &e)
{
    
    if(modifierDrag)
    {
         _canvas->mouseDrag(ofVec2f(e.x, e.y));
    }
    else
    {
        ofVec2f point = _canvas->screenToWorld(ofVec2f(e.x, e.y));
        _quadManager.mouseDragged(point.x, point.y);
    }
    
}

//--------------------------------------------------------------
void Mapper::mouseReleased(ofMouseEventArgs &e)
{
    
    if(modifierDrag)
    {
        _canvas->mouseReleased(ofVec2f(e.x, e.y));
    }
    else
    {
        ofVec2f point = _canvas->screenToWorld(ofVec2f(e.x, e.y));
        _quadManager.mouseReleased(point.x, point.y);
    }
    
}

//--------------------------------------------------------------
void Mapper::mousePressed(ofMouseEventArgs &e)
{
    
    if(modifierDrag)
    {
        _canvas->mousePressed(ofVec2f(e.x, e.y));
    }
    else
    {
        ofVec2f point = _canvas->screenToWorld(ofVec2f(e.x, e.y));
        _quadManager.mousePressed(point.x, point.y);
    }
    
}

//--------------------------------------------------------------
void Mapper::keyDown(ofKeyEventArgs &e)
{
    switch (e.key)
    {
        case ' ':
            modifierDrag = true;
            break;
        case OF_KEY_LEFT:
            _quadManager.activeQuadPrevious();
            break;
        case OF_KEY_RIGHT:
            _quadManager.activeQuadNext();
            break;
        case OF_KEY_UP:
            _quadManager.activeLayerUp();
            break;
        case OF_KEY_DOWN:
            _quadManager.activeLayerDown();
            break;
            
    }
}

//--------------------------------------------------------------
void Mapper::keyUp(ofKeyEventArgs &e)
{
    switch (e.key)
    {
        case ' ':
            modifierDrag = false;
            break;
    }
}







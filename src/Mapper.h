//
//  Mapper.h
//  Mapper
//
//  Created by Aaron Richards on 24/04/2014.
//
//

#ifndef __Vision__Mapper__
#define __Vision__Mapper__

#include "ofMain.h"
#include "QuadManager.h"
#include "PanZoom.h"

class Mapper
{
    
public:
    
    void setup(ofFbo *source, ofFbo *output, PanZoom* canvas);
    void exit();
    void update();

    void draw();
    void drawDebug();
    
    void bind();
    void unbind();
    
    void renderInput();
    void renderOutput();
    
    void renderOutputDisplay();

    ofFbo*          _sourceContent;
    ofFbo*          _outputContent;
    
    QuadManager     _quadManager;
    
    void mouseMoved(ofMouseEventArgs &e);
    void mouseDragged(ofMouseEventArgs &e);
    void mouseReleased(ofMouseEventArgs &e);
    void mousePressed(ofMouseEventArgs &e);
    void keyDown(ofKeyEventArgs &e);
    void keyUp(ofKeyEventArgs &e);
    
    PanZoom*        _canvas;
    
    bool            modifierDrag;
    
};


#endif /* defined(__Mapper__Mapper__) */

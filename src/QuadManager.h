//
//  QuadManager.h
//  canvas
//
//  Created by Aaron Richards on 29/04/2014.
//
//

#ifndef __canvas__QuadManager__
#define __canvas__QuadManager__

#include "ofMain.h"
#include "QuadMode.h"
#include "Quad.h"

class QuadManager
{
    
public:
    
    void setup();
    void exit();
    void update();
    void draw();
    
    
    void toggleMode();
    QuadMode getMode();
    
    void addQuad();
    void removeQuad();
    int  totalQuads();
    bool haveQuads();
    
    void activeQuadNext();
    void activeQuadPrevious();
    
    void activeLayerUp();
    void activeLayerDown();
    
    void renderInputQuads();
    void renderOutputQuads();
    
    
    bool pointCloseToCorner(float _x, float _y, float _smallestDist = 1.0);
    bool pointCloseToCenter(float _x, float _y);
    
    void activateCorner(int _quad);
    void deactivateCorner(int _quad);
    
    void activateCenter(int _quad);
    void deactivateCenter(int _quad);
    
    void moveCornerPosition(float _x, float _y);
    void moveWholeQuad(float _x, float _y);

    void mouseMoved(float _x, float _y);
    void mouseDragged(float _x, float _y);
    void mouseReleased(float _x, float _y);
    void mousePressed(float _x, float _y);
    
    
    QuadMode    _mode;
    vector<Quad> quads;
    
    int activeQuadIndex;
    int corner;
    ofPoint mousePosition;
    
    
};

#endif /* defined(__canvas__QuadManager__) */

//
//  Quad.h
//  canvas
//
//  Created by Aaron Richards on 28/04/2014.
//
//

#ifndef __canvas__Quad__
#define __canvas__Quad__

#include "ofMain.h"

class Quad
{
    
    public:
        
        void setup();
        void update();
    
        void draw();
        void drawInputQuad();
        void drawOutputQuad();
    
    
    void setActive(bool _a);
    bool getActive();


        ofPoint src[4];
        ofPoint dst[4];
        GLfloat matrix[16];
    
        bool activateCorner;
        int corner;
        bool activateCenter;
    
    
    
    //    int quadNumber;
    //    int layer;
    
private:
    bool _active;
    
};

#endif /* defined(__canvas__Quad__) */

//
//  PanZoom.h
//  panzoom
//
//  Created by Aaron Richards on 23/04/2014.
//
//

#ifndef __panzoom__PanZoom__
#define __panzoom__PanZoom__

#include "ofMain.h"

//class testApp;

class PanZoom
{
    
    public:
        
        PanZoom();
        ~PanZoom(){};

        
        void            zoomIn();
        void            zoomOut();
        void            setMinZoom(float min);
        void            setMaxZoom(float max);
        void            setZoom(float z);
        void            zoomReset();
        float           getZoom();
        
        void            setSmoothFactor(float smooth);

        ofVec2f         getOffset();
        
        void            setCanvasSize(ofVec2f _size);
        ofVec2f         getCanvasSize();
        void            setScreenSize(int x, int y);
        
        void            position(ofVec2f pos);
        void            lookAt(ofVec2f p);
        
        void            update();
        
        void            begin(int customW = 0, int customH = 0);
        void            end();
        
        void            drawDebug();
        void            drawHelpers();
        
        ofVec2f         screenToWorld(const ofVec2f & p);
        ofVec2f         worldToScreen(const ofVec2f & p);
        
        void            mousePressed(ofVec2f e);
        void            mouseDrag(ofVec2f e);
        void            mouseReleased(ofVec2f e);
        
    private:
        
        ofVec2f screenSize;
        ofVec2f canvasSize;

        ofVec2f offset;
        ofVec2f desiredOffset;
        
        float zoom;
        float desiredZoom;
        float minZoom;
        float maxZoom;
        
        float smoothFactor;
        
        ofVec2f lastTouch;
    
};

#endif /* defined(__panzoom__PanZoom__) */

#pragma once

#include "ofMain.h"
#include "DisplayManager.h"
#include "PanZoom.h"
#include "Grid.h"
#include "Mapper.h"


class ofApp : public ofBaseApp
{

	public:
    
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    //Displays
    void            setupWindows();
    DisplayManager  _dm;
    
    void            drawTestPattern();
    float           scale;
    
    //Canvas
    void            setupCanvas();
    PanZoom         canvas;
	Grid            grid;
    
    //Mapper
    Mapper mapper;
    
    ofFbo           sourceContentFbo;
    ofFbo           outputContentFbo;
		
};

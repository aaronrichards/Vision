//
//  Grid.h
//  panzoom
//
//  Created by Aaron Richards on 23/04/2014.
//
//

#ifndef __panzoom__Grid__
#define __panzoom__Grid__

#include "ofMain.h"

class Grid {
    
public:
    void create();
    void draw();
    
	float linePointsV[1004];
	float linePointsH[1004];
	GLubyte colors[1004 * 2];
	int	numPoints;
};

#endif /* defined(__panzoom__Grid__) */

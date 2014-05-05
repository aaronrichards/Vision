//
//  QuadManager.cpp
//  canvas
//
//  Created by Aaron Richards on 29/04/2014.
//
//

#include "QuadManager.h"


//--------------------------------------------------------------
// Setup
//--------------------------------------------------------------
void QuadManager::setup()
{
    
    _mode = QUAD_MODE_INPUT;

}

//--------------------------------------------------------------
void QuadManager::exit()
{
}



//--------------------------------------------------------------
// Update
//--------------------------------------------------------------
void QuadManager::update()
{
    
    //update quads
    for (int i = 0; i < totalQuads(); i++)
    {
        quads[i].update();
    }
    
}



//--------------------------------------------------------------
// Drawing
//--------------------------------------------------------------
void QuadManager::draw()
{
    
    for(int j = 0; j < totalQuads(); j++)
    {
        quads[j].draw();
    }
    
}

//--------------------------------------------------------------
void QuadManager::renderInputQuads()
{
    for(int j = 0; j < totalQuads(); j++)
    {
        quads[j].drawInputQuad();
    }
}

//--------------------------------------------------------------
void QuadManager::renderOutputQuads()
{
    for(int j = 0; j < totalQuads(); j++)
    {
        quads[j].drawOutputQuad();
    }
}





//--------------------------------------------------------------
// Mode
//--------------------------------------------------------------
QuadMode QuadManager::getMode()
{
    return _mode;
}

//--------------------------------------------------------------
void QuadManager::toggleMode()
{
    
    _mode = (_mode == QUAD_MODE_INPUT) ? QUAD_MODE_OUTPUT : QUAD_MODE_INPUT;
    ofLogNotice() << "Mode changed to: " << ((_mode == QUAD_MODE_INPUT) ? "input" : "output");
    
}





//--------------------------------------------------------------
// Quads
//--------------------------------------------------------------
void QuadManager::addQuad()
{
    
    Quad q;
    q.setup();
    quads.push_back(q);
    quads[activeQuadIndex].setActive(false);
    activeQuadIndex = totalQuads() - 1;
    quads[activeQuadIndex].setActive(true);
    
}

//--------------------------------------------------------------
void QuadManager::removeQuad()
{
    
    quads.erase(quads.begin() + activeQuadIndex);
    
    //reset active index
    if (activeQuadIndex > 0) activeQuadIndex--;
    else activeQuadIndex = 0; //set to zero incase it was set to -1
    
    //set next quad to active
    quads[activeQuadIndex].setActive(true);
    
}

//--------------------------------------------------------------
int QuadManager::totalQuads()
{
    return quads.size();
}

//--------------------------------------------------------------
bool QuadManager::haveQuads()
{
    return (totalQuads() > 0) ? true : false;
}

//--------------------------------------------------------------
void QuadManager::activeQuadNext()
{
    quads[activeQuadIndex].setActive(false);
    activeQuadIndex++;
    if (activeQuadIndex > totalQuads() -1) activeQuadIndex = 0;
    quads[activeQuadIndex].setActive(true);
}

//--------------------------------------------------------------
void QuadManager::activeQuadPrevious()
{
    quads[activeQuadIndex].setActive(false);
    activeQuadIndex--;
    if (activeQuadIndex < 0) activeQuadIndex = totalQuads() -1;
    quads[activeQuadIndex].setActive(true);
}





//--------------------------------------------------------------
// Events
//--------------------------------------------------------------
void QuadManager::mouseMoved(float _x, float _y)
{

    //check if near corners
    (pointCloseToCorner(_x, _y, 10.0)) ? activateCorner(activeQuadIndex) : deactivateCorner(activeQuadIndex);
    
    //check if near center
    (pointCloseToCenter(_x, _y)) ? activateCenter(activeQuadIndex) : deactivateCenter(activeQuadIndex);
    
}

//--------------------------------------------------------------
void QuadManager::mouseDragged(float _x, float _y)
{
    
    if(corner >= 0)
    {
        //move corne
        moveCornerPosition(_x, _y);
    }
    else
    {
        moveWholeQuad(_x, _y);
    }
    
}

//--------------------------------------------------------------
void QuadManager::mouseReleased(float _x, float _y)
{
    deactivateCorner(activeQuadIndex);
}

//--------------------------------------------------------------
void QuadManager::mousePressed(float _x, float _y)
{
    
    mousePosition.x = _x;
    mousePosition.y = _y;
    pointCloseToCorner(_x, _y, 10.0);
    
}


//--------------------------------------------------------------
// Layers
//--------------------------------------------------------------
void QuadManager::activeLayerUp()
{
    
    if(activeQuadIndex >= totalQuads() - 1)
    {
        ofLogNotice() << "Cannot move up";
        return;
    }
    
    swap(quads[activeQuadIndex], quads[activeQuadIndex+1]);
    
}

void QuadManager::activeLayerDown()
{
    
    if(activeQuadIndex == 0)
    {
        ofLogNotice() << "Cannot move down";
        return;
    }
    
    swap(quads[activeQuadIndex], quads[activeQuadIndex-1]);
    
    activeQuadIndex--;

}




//--------------------------------------------------------------
// Helpers
//--------------------------------------------------------------
bool QuadManager::pointCloseToCorner(float _x, float _y, float _smallestDist)
{
    
    if(haveQuads())
    {
        
        corner = -1;
        float dist;
        
        for(int i = 0; i < 4; i++)
        {
            
            if (_mode == QUAD_MODE_INPUT)
            {
                dist = ofDist(quads[activeQuadIndex].src[i].x, quads[activeQuadIndex].src[i].y, _x, _y);
            }
            else
            {
                dist = ofDist(quads[activeQuadIndex].dst[i].x, quads[activeQuadIndex].dst[i].y, _x, _y);
            }
            
            if(dist < _smallestDist)
            {
                corner = i;
                return true;
            }
            
        }
    
    }
    
    return false;
    
}

//--------------------------------------------------------------
bool QuadManager::pointCloseToCenter(float _x, float _y)
{
    
    if(haveQuads())
    {
        
        ofPolyline p;
        
        for (int i = 0; i < 4; i++)
        {
            
            if (_mode == QUAD_MODE_INPUT)
            {
                p.addVertex(quads[activeQuadIndex].src[i]);
            }
            else
            {
                p.addVertex(quads[activeQuadIndex].dst[i]);
            }
            
        }
        
        if(p.inside(_x, _y))
        {
            return true;
        }
        
    }
    
    return false;
    
}


//--------------------------------------------------------------
void QuadManager::activateCorner(int _quad)
{
    if(haveQuads())
    {
        quads[_quad].activateCorner = true;
        quads[_quad].corner = corner;
    }
}

//--------------------------------------------------------------
void QuadManager::deactivateCorner(int _quad)
{
    if(haveQuads())
    {
        quads[_quad].activateCorner = false;
        quads[_quad].corner = -1;
    }
    
}

//--------------------------------------------------------------
void QuadManager::activateCenter(int _quad)
{
    if(haveQuads())
    {
        quads[_quad].activateCenter = true;
    }
}

//--------------------------------------------------------------
void QuadManager::deactivateCenter(int _quad)
{
    if(haveQuads())
    {
        quads[_quad].activateCenter = false;
    }
}

//--------------------------------------------------------------
void QuadManager::moveCornerPosition(float _x, float _y)
{
    
    if(haveQuads())
    {
        
        if (_mode == QUAD_MODE_INPUT)
        {
            quads[activeQuadIndex].src[corner].x = _x;
            quads[activeQuadIndex].src[corner].y = _y;
        }
        else
        {
            quads[activeQuadIndex].dst[corner].x = _x;
            quads[activeQuadIndex].dst[corner].y = _y;
        }
        
    }
    
}


//--------------------------------------------------------------
void QuadManager::moveWholeQuad(float _x, float _y)
{
    if(haveQuads())
    {
        
        if(quads[activeQuadIndex].activateCenter)
        {
            
            ofPoint mouse;
            ofPoint movement;
            mouse.x = _x;
            mouse.y = _y;
            movement = mouse - mousePosition;
            
            if (_mode == QUAD_MODE_INPUT)
            {
                
                for(int i = 0; i < 4; i++)
                {
                    quads[activeQuadIndex].src[i].x += ((float)movement.x);
                    quads[activeQuadIndex].src[i].y += ((float)movement.y);
                }
                
            }
            else
            {
                
                for(int i = 0; i < 4; i++)
                {
                    quads[activeQuadIndex].dst[i].x += ((float)movement.x);
                    quads[activeQuadIndex].dst[i].y += ((float)movement.y);
                }
                
            }
        
            mousePosition.x = _x;
            mousePosition.y = _y;
            
        }
        
    }
    
}









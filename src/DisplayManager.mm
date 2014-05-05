//
//  DisplayManager.cpp
//  windows
//
//  Created by Aaron Richards on 30/04/2014.
//
//

#include "DisplayManager.h"
#import <Cocoa/Cocoa.h>

//--------------------------------------------------------------
// Setup
//--------------------------------------------------------------
void DisplayManager::setup(ofFbo *content)
{

    _content = content;
    //create first window (main context)
   // GLFWwindow * win = glfwGetCurrentContext();
    DisplayWindow *dw = new DisplayWindow(*glfwGetCurrentContext());
    _windows.push_back(dw);
    refreshMonitorList();
    fullscreen = false;
    
    ofAddListener(ofEvents().draw, this, &DisplayManager::draw);
    
}





//--------------------------------------------------------------
// Monitors
//--------------------------------------------------------------
void DisplayManager::refreshMonitorList()
{
    
    _monitors.clear();
    
    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    
    for (int i = 0; i < count; i++)
    {
        
        GLFWmonitor* newMonitor;
        newMonitor = monitors[i];
        ofLogNotice() << "Found monitor " << i << ": " << glfwGetMonitorName(newMonitor);
        _monitors.push_back(newMonitor);
        
    }
    
}

//--------------------------------------------------------------
GLFWmonitor* DisplayManager::getMonitor(int _id)
{
    
    if (doesMonitorExist(_id))
    {
        return _monitors[_id];
    }
    else
    {
        return NULL;
    }
    
}

//--------------------------------------------------------------
ofVec2f DisplayManager::getMonitorSize(int _id)
{
    
    if (doesMonitorExist(_id))
    {
        GLFWmonitor *monitor = _monitors[_id];
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        return ofVec2f(mode->width, mode->height);
    }
    else
    {
        return ofVec2f(0, 0);
    }
    
}

//--------------------------------------------------------------
ofVec2f DisplayManager::getMonitorPosition(int _id)
{
    
    if (doesMonitorExist(_id))
    {
        GLFWmonitor *monitor = _monitors[_id];
        int x, y;
        glfwGetMonitorPos(monitor, &x, &y);
        return ofVec2f(x, y);
    }
    else
    {
        return ofVec2f(0, 0);
    }
    
}

//--------------------------------------------------------------
bool DisplayManager::doesMonitorExist(int _id)
{
    return (_id < totalMonitors()) ? true : false;
}

//--------------------------------------------------------------
int DisplayManager::totalMonitors()
{
    return _monitors.size();
}










//--------------------------------------------------------------
// Windows
//--------------------------------------------------------------
void DisplayManager::createWindow()
{
    createWindow(100, 100, 400, 400, false, "Window");
}

//--------------------------------------------------------------
void DisplayManager::createWindow(int x, int y)
{
    createWindow(x, y, 400, 400, false, "Window");
}

//--------------------------------------------------------------
void DisplayManager::createWindow(int x, int y, int w, int h, string _windowTitle)
{
    createWindow(x, y, w, h, false, _windowTitle);
}

//--------------------------------------------------------------
void DisplayManager::createWindow(int x, int y, int w, int h, bool _fullscreen, string _windowTitle)
{
	
    DisplayWindow *newWindow = new DisplayWindow(x, y, w, h, _windowTitle);
    newWindow->setId(totalWindows());

    if (_fullscreen)
    {
        newWindow->setHint(GLFW_DECORATED, GL_FALSE);
        newWindow->setHint(GLFW_FOCUSED, GL_FALSE);
    }

    newWindow->create();
    
    _windows.push_back(newWindow);
    
}

int DisplayManager::totalWindows()
{
    return _windows.size();
}

//--------------------------------------------------------------
void DisplayManager::setWindowPosition(int _x, int _y, int _id)
{
    
    if (doesWindowExist(_id))
    {
        _windows[_id]->setPosition(_x, _y);
        ofLogNotice() << "Changed window:" << _id << " position to " << _x << ":" << _y;
    }
    else
    {
        ofLogError() << "Window does not exist. Cannot change window position.";
    }
    
}

//--------------------------------------------------------------
void DisplayManager::setWindowSize(int _w, int _h, int _id)
{
    
    if (doesWindowExist(_id))
    {
        _windows[_id]->setSize(_w, _h);
        ofLogNotice() << "Changed window:" << _id << " size to " << _w << "x" << _h;
    }
    else
    {
        ofLogError() << "Window does not exist. Cannot change window size.";
    }
    
}

//--------------------------------------------------------------
DisplayWindow* DisplayManager::getMainWindow()
{
    return _windows[0];
}

//--------------------------------------------------------------
DisplayWindow* DisplayManager::getWindow(int _window)
{
    if (doesWindowExist(_window))
    {
        return _windows[_window];
    }
    else
    {
        return NULL;
    }
    
}

//--------------------------------------------------------------
bool DisplayManager::doesWindowExist(int _window)
{
    
    if(_window < _windows.size())
    {
        return true;
    }
    else
    {
        return false;
    }
}

//--------------------------------------------------------------
void DisplayManager::toggleFullscreen(int _window)
{
    
    if(doesWindowExist(_window))
    {
        ofLogNotice() << "Toggle not implemented yet.";
    }
    else
    {
        ofLogNotice() << "Cannot toggle fullscreen";
    }
}




//--------------------------------------------------------------
// Updating
//--------------------------------------------------------------
void DisplayManager::update()
{
}




//--------------------------------------------------------------
// Drawing
//--------------------------------------------------------------
void DisplayManager::draw(ofEventArgs &e)
{
    //loop windows and draw them. skip main window
    for (int i = 1; i < _windows.size(); i++)
    {
        
        GLFWwindow *currentWin = _windows[i]->get();
        
        glfwMakeContextCurrent(currentWin);
        int width, height;
        glfwGetFramebufferSize(currentWin, &width, &height);
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0f, width, height, 0.0f, 0.0f, 1.0f);
        //glOrtho(-1,1,1,-1,-1,1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        _content->draw(0, 0);
        //_content->draw(-200, -200);
        glfwSwapBuffers(currentWin);
        glfwPollEvents();
        glfwMakeContextCurrent(getMainWindow()->get());
    }
    
}










//
//  DisplayManager.h
//  windows
//
//  Created by Aaron Richards on 30/04/2014.
//
//

#ifndef __windows__DisplayManager__
#define __windows__DisplayManager__

#include "ofMain.h"
#include <GLFW/glfw3.h>

#include "DisplayWindow.h"


class DisplayManager
{
    
    
public:
    void setup(ofFbo *content);
    void update();
    void draw(ofEventArgs &e);
    
    //window
    void            createWindow();
    void            createWindow(int x, int y);
    void            createWindow(int x, int y, int w, int h, string _windowTitle = "Window");
    void            createWindow(int x, int y, int w, int h, bool _fullscreen, string _windowTitle = "Window");
    
    void            setWindowPosition(int _x, int _y, int _id = 0);
    void            setWindowSize(int _w, int _h, int _id = 0);
    DisplayWindow*  getMainWindow();
    DisplayWindow*  getWindow(int _id);
    bool            doesWindowExist(int _id);
    int             totalWindows();
    void            toggleFullscreen(int _id);
    
    
    //monitors
    void                    refreshMonitorList();
    GLFWmonitor*            getMonitor(int _id);
    ofVec2f                 getMonitorSize(int _id);
    ofVec2f                 getMonitorPosition(int _id);
    bool                    doesMonitorExist(int _id);
    int                     totalMonitors();
    
    
    
    
private:
    
    vector<DisplayWindow*>      _windows;
    vector<GLFWmonitor*>     _monitors;
    
    ofFbo*                      _content;
    bool                        fullscreen;
};

#endif /* defined(__windows__DisplayManager__) */

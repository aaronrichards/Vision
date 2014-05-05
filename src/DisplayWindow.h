//
//  DisplayMonitor.h
//  windows
//
//  Created by Aaron Richards on 1/05/2014.
//
//

#ifndef __windows__DisplayWindow__
#define __windows__DisplayWindow__

#include "ofMain.h"
#include <GLFW/glfw3.h>

class DisplayWindow
{
    
    public:

        DisplayWindow(int x, int y, int w, int h, string _windowTitle);
        DisplayWindow(GLFWwindow &win);
        ~DisplayWindow();
        
        int         getWidth();
        int         getHeight();
        void        setWidth(int _val);
        void        setHeight(int _val);
        
        int         getX();
        int         getY();
        void        setX(int _val); //
        void        setY(int _val); //
        
        int         getId();
        void        setId(int _val);
    
        string      getWindowTitle();
        void        setWindowTitle(string _val);

        GLFWwindow* get();
        void        set(GLFWwindow* _val);
    
    void setHint(int _type, int _val);
    void setPosition(int _x, int _y);
    void setSize(int w, int h);
    void create();
    
    private:

        int         _width;
        int         _height;
        int         _x;
        int         _y;
        int         _id;
        string      _title;
    
        GLFWwindow* _win;
    
};

#endif /* defined(__windows__DisplayMonitor__) */

//
//  DisplayMonitor.cpp
//  windows
//
//  Created by Aaron Richards on 1/05/2014.
//
//

#include "DisplayWindow.h"


DisplayWindow::DisplayWindow(int x, int y, int w, int h, string _windowTitle)
: _x(x)
, _y(y)
, _width(w)
, _height(h)
, _id(-1)
, _title(_windowTitle)
{}

DisplayWindow::DisplayWindow(GLFWwindow &win)
: _x(0)
, _y(0)
, _width(0)
, _height(0)
, _id(-1)
, _title("")
{
    _win = &win;
}

DisplayWindow::~DisplayWindow(){}

void DisplayWindow::create()
{
    _win = glfwCreateWindow(getWidth(), getHeight(), getWindowTitle().c_str(), NULL, glfwGetCurrentContext());
    setPosition(getX(), getY());
}


GLFWwindow* DisplayWindow::get()
{
    return _win;
}

void DisplayWindow::set(GLFWwindow* _val)
{
    _win = _val;
}


void DisplayWindow::setHint(int _type, int _val)
{
    glfwWindowHint(_type, _val);
}

void DisplayWindow::setPosition(int x, int y)
{
    setX(x);
    setY(y);
    glfwSetWindowPos(_win, x, y);
}

void DisplayWindow::setSize(int w, int h)
{
    setWidth(w);
    setHeight(h);
    glfwSetWindowSize(_win, w, h);
}










int DisplayWindow::getWidth()
{
    return _width;
}

int DisplayWindow::getHeight()
{
    return _height;
}

void DisplayWindow::setWidth(int _val)
{
    _width = _val;
}

void DisplayWindow::setHeight(int _val)
{
    _height = _val;
}

int DisplayWindow::getX()
{
    return _x;
}

int DisplayWindow::getY()
{
    return _y;
}

void DisplayWindow::setX(int _val)
{
    _x = _val;
}

void DisplayWindow::setY(int _val)
{
    _y = _val;
}

int DisplayWindow::getId()
{
    return _id;
}

void DisplayWindow::setId(int _val)
{
    _id = _val;
}

string DisplayWindow::getWindowTitle()
{
    return _title;
}

void DisplayWindow::setWindowTitle(string _val)
{
    _title = _val;
}





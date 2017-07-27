#include "window.h"

Window::Window() {

}

Window::~Window() {
	shutdownGL();
}

void Window::initializeGL() {
	initializeOpenGLFunctions();
	printContextInfo();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Window::resizeGL(int width, int height) {

}

void Window::paintGL() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Window::shutdownGL() {

}

void Window::printContextInfo() {

}



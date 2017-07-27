#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_4_Core>

class Window :	public QOpenGLWindow,
				protected QOpenGLFunctions_4_4_Core {
	Q_OBJECT
public:
	Window();
	~Window();

	void initializeGL() override;
	void resizeGL(int width, int height) override;
	void paintGL() override;

	void shutdownGL();

private:
	void printContextInfo();
};

#endif // WINDOW_H

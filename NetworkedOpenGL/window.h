#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class Window :	public QOpenGLWindow,
				protected QOpenGLFunctions_4_5_Core {
	Q_OBJECT
public:
	Window();
	~Window();

	void initializeGL() override;
	void resizeGL(int width, int height) override;
	void paintGL() override;

	void shutdownGL();

protected slots:
	void update();

private:
	QOpenGLBuffer m_VBOplayer1;
	QOpenGLVertexArrayObject m_VAOplayer1;

	QOpenGLShaderProgram m_shaderProgram;

	bool m_hasErrors{false};

	void printContextInfo();
	void checkGLerror(const bool result, const QOpenGLShaderProgram& pgrm);
};

#endif // WINDOW_H

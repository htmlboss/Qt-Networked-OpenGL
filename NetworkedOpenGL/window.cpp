#include "window.h"
#include "vertex.h"

#include <QDebug>

// 2D Triangle
static const Vertex vertices[] {
  Vertex( QVector3D( 0.00f,  0.75f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f) ),
  Vertex( QVector3D( 0.75f, -0.75f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f) ),
  Vertex( QVector3D(-0.75f, -0.75f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f) )
};

/***********************************************************************************/
Window::Window() {
	makeCurrent();
}

/***********************************************************************************/
Window::~Window() {
	makeCurrent();
	shutdownGL();
}

/***********************************************************************************/
void Window::initializeGL() {
	initializeOpenGLFunctions();
	connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
	printContextInfo();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	checkGLerror(m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/basic.vert"), m_shaderProgram);
	checkGLerror(m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/basic.frag"), m_shaderProgram);
	checkGLerror(m_shaderProgram.link(), m_shaderProgram);
	checkGLerror(m_shaderProgram.bind(), m_shaderProgram);

	m_VBOplayer1.create();
	m_VBOplayer1.bind();
	m_VBOplayer1.setUsagePattern(QOpenGLBuffer::StaticDraw);
	m_VBOplayer1.allocate(vertices, sizeof(vertices));

	m_VAOplayer1.create();
	m_VAOplayer1.bind();
	m_shaderProgram.enableAttributeArray(0);
	m_shaderProgram.enableAttributeArray(1);
	m_shaderProgram.setAttributeBuffer(0, GL_FLOAT, Vertex::PositionOffset(), 3, Vertex::Stride());
	m_shaderProgram.setAttributeBuffer(1, GL_FLOAT, Vertex::ColorOffset(), 3, Vertex::Stride());

	if (!m_hasErrors) {
		qDebug() << "OpenGL sucessfully initialized!";
	}
}

/***********************************************************************************/
void Window::resizeGL(int width, int height) {

}

/***********************************************************************************/
void Window::paintGL() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	m_shaderProgram.bind();
	{
		m_VAOplayer1.bind();
		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(vertices[0]));
	}
}

/***********************************************************************************/
void Window::shutdownGL() {
	m_VBOplayer1.destroy();
	m_VAOplayer1.destroy();
}

/***********************************************************************************/
void Window::update() {

}

/***********************************************************************************/
void Window::printContextInfo() {
	QString glType;
	QString glVersion;
	QString glProfile;

	// Get Version Information
	glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
	glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

	// Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
	switch (format().profile()) {
		CASE(NoProfile);
		CASE(CoreProfile);
		CASE(CompatibilityProfile);
	}
#undef CASE

	// qPrintable() will print our QString w/o quotes around it.
	qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}

/***********************************************************************************/
void Window::checkGLerror(const bool result, const QOpenGLShaderProgram& pgrm) {
	if (!result) {
		m_hasErrors = true;
		qDebug() << "Shader error: " << pgrm.log();
	}
}



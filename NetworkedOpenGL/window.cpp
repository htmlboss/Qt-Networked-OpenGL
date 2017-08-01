#include "window.h"
#include "vertex.h"
#include "cube.h"

#include <QDebug>

/***********************************************************************************/
Window::Window() {
	makeCurrent();
	m_transform.translate(0.0f, 0.0f, -5.0f);
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

	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	checkGLerror(m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/basic.vert"), m_shaderProgram);
	checkGLerror(m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/basic.frag"), m_shaderProgram);
	checkGLerror(m_shaderProgram.link(), m_shaderProgram);
	checkGLerror(m_shaderProgram.bind(), m_shaderProgram);

	m_vbo.create();
	m_vbo.bind();
	m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
	m_vbo.allocate(vertices, sizeof(vertices));

	m_uniforms.emplace(std::make_pair<std::string, int>("modelMatrix", m_shaderProgram.uniformLocation("modelMatrix")));
	m_uniforms.emplace(std::make_pair<std::string, int>("projectionMatrix", m_shaderProgram.uniformLocation("projectionMatrix")));

	m_vao.create();
	m_vao.bind();

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
	m_projection.setToIdentity();
	m_projection.perspective(45.0f, width / static_cast<float>(height), 1.0f, 100.0f);
}

/***********************************************************************************/
void Window::paintGL() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	m_shaderProgram.bind();
	m_shaderProgram.setUniformValue(m_uniforms.at("projectionMatrix"), m_projection);
	m_shaderProgram.setUniformValue(m_uniforms.at("modelMatrix"), m_transform.toMatrix());
	m_vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(vertices[0]));
}

/***********************************************************************************/
void Window::shutdownGL() {
}

/***********************************************************************************/
void Window::update() {
	m_transform.rotate(1.0f, QVector3D(0.4f, 0.3f, 0.3f));

	QOpenGLWindow::update();
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



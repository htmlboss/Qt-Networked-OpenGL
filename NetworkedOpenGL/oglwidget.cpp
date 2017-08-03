#include "oglwidget.h"
#include "input.h"
#include "player.h"

#include <QKeyEvent>
#include <QDebug>

/***********************************************************************************/
OGLWidget::OGLWidget(QWidget* parent) : QOpenGLWidget{parent} {
	QSurfaceFormat fmt;
	fmt.setRenderableType(QSurfaceFormat::OpenGL);
	fmt.setProfile(QSurfaceFormat::CoreProfile);
	fmt.setSamples(4);
	fmt.setVersion(4, 5);
	fmt.setSwapInterval(1);

	setFormat(fmt);
}

/***********************************************************************************/
OGLWidget::~OGLWidget() {
	makeCurrent();
	shutdownGL();
}

/***********************************************************************************/
void OGLWidget::initializeGL() {
	if (!initializeOpenGLFunctions()) {
		throw std::runtime_error("Failed to initalise OpenGL functions.");
	}
	connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
	printContextInfo();

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	checkGLerror(m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/basic.vert"), m_shaderProgram);
	checkGLerror(m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/basic.frag"), m_shaderProgram);
	checkGLerror(m_shaderProgram.link(), m_shaderProgram);
	checkGLerror(m_shaderProgram.bind(), m_shaderProgram);

	m_player = std::make_unique<Player>("Player");
	m_player->Translate(QVector3D(0.0f, 0.0f, -4.0f));

	m_uniforms.emplace(std::make_pair<std::string, int>("modelMatrix", m_shaderProgram.uniformLocation("modelMatrix")));
	m_uniforms.emplace(std::make_pair<std::string, int>("projectionMatrix", m_shaderProgram.uniformLocation("projectionMatrix")));
	m_uniforms.emplace(std::make_pair<std::string, int>("viewMatrix", m_shaderProgram.uniformLocation("viewMatrix")));

	if (!m_hasErrors) {
		qDebug() << "OpenGL sucessfully initialized!";
	}
}

/***********************************************************************************/
void OGLWidget::resizeGL(int width, int height) {
	m_projection.setToIdentity();
	m_projection.perspective(45.0f, width / static_cast<float>(height), 1.0f, 100.0f);
}

/***********************************************************************************/
void OGLWidget::paintGL() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	m_shaderProgram.bind();
	m_shaderProgram.setUniformValue(m_uniforms.at("projectionMatrix"), m_projection);
	m_shaderProgram.setUniformValue(m_uniforms.at("viewMatrix"), m_camera.toMatrix());
	m_shaderProgram.setUniformValue(m_uniforms.at("modelMatrix"), m_player->GetPlayerMatrix());

	m_player->Draw();
}

/***********************************************************************************/
void OGLWidget::shutdownGL() {
}

/***********************************************************************************/
void OGLWidget::update() {

	Input::update();

	// Camera Transformation
	if (Input::buttonPressed(Qt::RightButton)) {

		static const auto transSpeed = 0.05f;
		static const auto rotSpeed   = 0.25f;

		// Handle rotations
		m_camera.rotate(-rotSpeed * Input::mouseDelta().x(), m_camera.up());
		m_camera.rotate(-rotSpeed * Input::mouseDelta().y(), m_camera.right());

		// Handle translations
		QVector3D translation;
		if (Input::keyPressed(Qt::Key_W)) {
			translation += m_camera.forward();
		}
		if (Input::keyPressed(Qt::Key_S)) {
			translation -= m_camera.forward();
		}
		if (Input::keyPressed(Qt::Key_A)) {
			translation -= m_camera.right();
		}
		if (Input::keyPressed(Qt::Key_D)) {
			translation += m_camera.right();
		}
		if (Input::keyPressed(Qt::Key_Control)) {
			translation -= m_camera.up();
		}
		if (Input::keyPressed(Qt::Key_Space)) {
			translation += m_camera.up();
		}
		m_camera.translate(transSpeed * translation);
		m_player->Translate(transSpeed * translation);
	}

	// Schedule window update
	QOpenGLWidget::update();
}

/***********************************************************************************/
void OGLWidget::keyPressEvent(QKeyEvent* event) {
	if (event->isAutoRepeat()) {
		event->ignore();
		return;
	}

	Input::registerKeyPress(event->key());
}

/***********************************************************************************/
void OGLWidget::keyReleaseEvent(QKeyEvent* event) {
	if (event->isAutoRepeat()) 	{
		event->ignore();
		return;
	}

	Input::registerKeyRelease(event->key());
}

/***********************************************************************************/
void OGLWidget::mousePressEvent(QMouseEvent* event) {
	Input::registerMousePress(event->button());
}

/***********************************************************************************/
void OGLWidget::mouseReleaseEvent(QMouseEvent* event) {
	Input::registerMouseRelease(event->button());
}

/***********************************************************************************/
void OGLWidget::printContextInfo() {
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
void OGLWidget::checkGLerror(const bool result, const QOpenGLShaderProgram& pgrm) {
	if (!result) {
		m_hasErrors = true;
		qDebug() << "Shader error: " << pgrm.log();
	}
}



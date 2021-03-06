#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

#include <unordered_map>
#include <memory>

#include "serverdialog.h"

#include "transform3d.h"
#include "camera.h"

class Player;

class OGLWidget :	public QOpenGLWidget,
					protected QOpenGLFunctions_4_5_Core {
	Q_OBJECT
public:
	OGLWidget(QWidget* parent = nullptr);
	~OGLWidget();

	void initializeGL() override;
	void resizeGL(int width, int height) override;
	void paintGL() override;

	void shutdownGL();

protected slots:
	void update();

protected:
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

private:
	ServerDialog m_serverDialog;

	std::unique_ptr<Player> m_player;

	QMatrix4x4 m_projection;

	Camera m_camera;
	Transform3D m_transform;

	QOpenGLShaderProgram m_shaderProgram;
	std::unordered_map<std::string, int> m_uniforms;

	bool m_hasErrors{false};

	void printContextInfo();
	void checkGLerror(const bool result, const QOpenGLShaderProgram& pgrm);
};

#endif // WINDOW_H

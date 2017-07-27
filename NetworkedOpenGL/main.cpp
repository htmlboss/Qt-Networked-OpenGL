#include <QGuiApplication>

#include "window.h"

int main(int argc, char* argv[]) {
	QGuiApplication a(argc, argv);

	QSurfaceFormat fmt;
	fmt.setRenderableType(QSurfaceFormat::OpenGL);
	fmt.setProfile(QSurfaceFormat::CoreProfile);
	fmt.setVersion(4, 4);

	Window window;
	window.setFormat(fmt);
	window.resize(1280, 720);
	window.show();

	return a.exec();
}

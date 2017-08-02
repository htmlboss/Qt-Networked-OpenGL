#include <QApplication>

#include "mainwindow.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	MainWindow window;
	window.resize(QSize(1280, 720));
	window.show();

	return a.exec();
}

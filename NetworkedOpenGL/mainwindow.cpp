#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow), m_serverDialog() {
	ui->setupUi(this);

	QFile f(":qdarkstyle/style.qss");
	if (!f.exists()) {
		qDebug() << "Unable to set stylesheet, file not found.";
	}
	else {
		f.open(QFile::ReadOnly | QFile::Text);
		QTextStream ts(&f);
		qApp->setStyleSheet(ts.readAll());
	}
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_actionAbout_Qt_triggered() {
	QApplication::aboutQt();
}

void MainWindow::on_actionStart_server_triggered() {
	m_serverDialog.show();
}

void MainWindow::on_actionConnect_to_server_triggered() {

}

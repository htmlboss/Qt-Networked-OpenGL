#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow), m_serverDialog() {
	ui->setupUi(this);
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

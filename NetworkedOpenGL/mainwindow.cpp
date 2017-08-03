#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "serverdialog.h"
#include "connectdialog.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>

#include <memory>

/***********************************************************************************/
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
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

/***********************************************************************************/
MainWindow::~MainWindow() {
	delete ui;
}

/***********************************************************************************/
void MainWindow::on_actionAbout_Qt_triggered() {
	QApplication::aboutQt();
}

/***********************************************************************************/
void MainWindow::on_actionStart_server_triggered() {
	const auto dialog = std::make_unique<ServerDialog>(this);

	if (dialog->exec()) {
		const auto port = dialog->GetPort();
		qDebug() << port;
		// start udp server
	}
}

/***********************************************************************************/
void MainWindow::on_actionConnect_to_server_triggered() {
	const auto dialog = std::make_unique<ConnectDialog>(this);

	if (dialog->exec()) {
		// connect to another server
	}
}

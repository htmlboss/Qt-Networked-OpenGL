#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "serverdialog.h"
#include "connectdialog.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QNetworkInterface>

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

	// Get local IP Address and display it in status bar and window title.
	QString addr;
	foreach(const QHostAddress& address, QNetworkInterface::allAddresses()) {
		if (address.protocol() == QAbstractSocket::IPv4Protocol &&
			address != QHostAddress(QHostAddress::LocalHost) &&
			address.toString().section(".", -1, -1 ) != "1") {

			addr = address.toString();
		}
	}
	setStatusTip("Local IP Address: " + addr);
	setWindowTitle("Networked OpenGL | " + addr);
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

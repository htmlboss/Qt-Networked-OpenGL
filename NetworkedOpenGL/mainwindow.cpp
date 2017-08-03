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
MainWindow::MainWindow(QWidget* parent) : QMainWindow{parent}, ui{new Ui::MainWindow} {
	ui->setupUi(this);

	// Set dark stylesheet
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
	foreach(const QHostAddress& address, QNetworkInterface::allAddresses()) {
		if (address.protocol() == QAbstractSocket::IPv4Protocol &&
			address != QHostAddress(QHostAddress::LocalHost) &&
			address.toString().section(".", -1, -1 ) != "1") {

			m_ipAddress = address.toString();
		}
	}
	setStatusTip("Local IP Address: " + m_ipAddress);
	setWindowTitle("Networked OpenGL | " + m_ipAddress);
}

/***********************************************************************************/
MainWindow::~MainWindow() {
	delete ui;
}

/***********************************************************************************/
void MainWindow::on_actionAbout_Qt_triggered() {
	// Show pre-made Qt dialog
	QApplication::aboutQt();
}

/***********************************************************************************/
void MainWindow::on_actionStart_server_triggered() {
	const auto dialog = std::make_unique<ServerDialog>(this);

	if (dialog->exec()) {
		const auto port = dialog->GetPort();

		// Instantiate UDPSocket class
		m_udpSocket = std::make_unique<QUdpSocket>(this);
		// Try to open UDP socket
		if (!m_udpSocket->bind(QHostAddress::LocalHost, port)) {
			setStatusTip("Failed to open UDP port. Please try another port number.");
			return;
		}
		connect(m_udpSocket.get(), SIGNAL(readyRead()), this, SLOT(readyRead()));

		setStatusTip("Opened UDP port: " + QString::number(port));
		setWindowTitle("Networked OpenGL | Listening... " + m_ipAddress + ":" + QString::number(port));
#ifdef QT_DEBUG
		qDebug() << "Opened UDP port: " << port << "Listening...";
#endif
	}
}

/***********************************************************************************/
void MainWindow::on_actionConnect_to_server_triggered() {
	const auto dialog = std::make_unique<ConnectDialog>(this);

	if (dialog->exec()) {
		// connect to another server
	}
}

/***********************************************************************************/
void MainWindow::readyRead() {
	// When data is coming in
	QByteArray buffer;
	buffer.resize(m_udpSocket->pendingDatagramSize());

	QHostAddress sender;
	quint16 senderPort;

	// Try to write incoming data to buffer.
	if (m_udpSocket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort) == -1) {
		qDebug() << "Failed to read datagram from host: " << sender << " on port " << senderPort;
	}
}

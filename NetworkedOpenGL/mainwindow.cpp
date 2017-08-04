#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "serverdialog.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QNetworkInterface>

#include <memory>

/***********************************************************************************/
// Helper function to de-serialize a stream into T
template<typename T>
auto get(QDataStream& str) -> T {
	T value;
	str >> value;
	return value;
}

/***********************************************************************************/
// Provide operator<< and operator>> overloads so QVector3D can be serialized into QDataStream
// and vice versa
QDataStream& operator<<(QDataStream& str, const QVector3D& vec) {
	// Send components in reverse order so they get de-serialized in correct order.
	return str << vec.z() << vec.y() << vec.x();
}
QDataStream& operator>>(QDataStream& str, QVector3D& vec) {
	vec = QVector3D(get<float>(str),
					get<float>(str),
					get<float>(str));
	return str;
}

/***********************************************************************************/
MainWindow::MainWindow(QWidget* parent) : QMainWindow{parent}, ui{new Ui::MainWindow} {
	ui->setupUi(this);
	ui->pushButton->setEnabled(false);

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
void MainWindow::readyRead() {

	QHostAddress sender;
	quint16 senderPort;

	QVector3D vec;

	while (m_udpSocket->hasPendingDatagrams()) {
		// When data is coming in
		QByteArray buffer(m_udpSocket->pendingDatagramSize(), Qt::Uninitialized);
		QDataStream str(&buffer, QIODevice::ReadOnly);

		// Try to write incoming data to buffer.
		if (m_udpSocket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort) == -1) {
			qDebug() << "Failed to read datagram from host: " << sender << " on port " << senderPort;
		}

		str >> vec;

		qDebug() << "Data from: " << sender.toString();
		qDebug() << "Remote port: " << senderPort;
		qDebug() << vec.x() << " " << vec.y() << " " << vec.z();
	}
}

/***********************************************************************************/
void MainWindow::on_actionOpen_network_connection_triggered() {
	const auto dialog = std::make_unique<ServerDialog>(this);

	if (dialog->exec()) {
		const auto udpData = dialog->GetNetworkInfo();

		// Instantiate UDPSocket class
		m_udpSocket = std::make_unique<QUdpSocket>(this);
		m_remoteIPaddress = udpData.RemoteIP;
		m_remotePort = udpData.RemotePort;

		// Try to open UDP socket
		if (!m_udpSocket->bind(QHostAddress::LocalHost, udpData.LocalPort)) {
			setStatusTip("Failed to open UDP port. Please try another port number.");
			return;
		}
		connect(m_udpSocket.get(), SIGNAL(readyRead()), this, SLOT(readyRead()));

		setStatusTip("Opened UDP port: " + QString::number(udpData.LocalPort));
		setWindowTitle("Networked OpenGL | Listening... " + m_ipAddress + ":" + QString::number(udpData.LocalPort));
#ifdef QT_DEBUG
		qDebug() << "Opened UDP port: " << udpData.LocalPort << "Listening...";
#endif
		ui->pushButton->setEnabled(true);
	}
}

void MainWindow::on_pushButton_clicked() {
	QByteArray data;
	QDataStream str(&data, QIODevice::WriteOnly);

	str << QVector3D(2, 3, 4);

	m_udpSocket->writeDatagram(data, m_remoteIPaddress, m_remotePort);
}

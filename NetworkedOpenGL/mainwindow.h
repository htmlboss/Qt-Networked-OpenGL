#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>

#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_actionAbout_Qt_triggered();
	void readyRead();

	void on_actionOpen_network_connection_triggered();

	void on_pushButton_clicked();

private:
	Ui::MainWindow* ui;

	// Network stuff
	std::unique_ptr<QUdpSocket> m_udpSocket;
	QString m_ipAddress;
	QHostAddress m_remoteIPaddress;
	std::size_t m_remotePort;
};

#endif // MAINWINDOW_H

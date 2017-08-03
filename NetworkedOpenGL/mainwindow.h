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
	void on_actionStart_server_triggered();
	void on_actionConnect_to_server_triggered();

	void readyRead();

private:
	Ui::MainWindow* ui;

	// Network stuff
	std::unique_ptr<QUdpSocket> m_udpSocket;
	QString m_ipAddress;
};

#endif // MAINWINDOW_H

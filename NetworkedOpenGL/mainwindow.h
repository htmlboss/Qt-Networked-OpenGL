#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "serverdialog.h"

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

private:
	Ui::MainWindow* ui;

	ServerDialog m_serverDialog;

};

#endif // MAINWINDOW_H

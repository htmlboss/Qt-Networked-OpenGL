#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
};

#endif // MAINWINDOW_H

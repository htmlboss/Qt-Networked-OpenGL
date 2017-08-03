#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog {
	Q_OBJECT

public:
	explicit ConnectDialog(QWidget *parent = nullptr);
	~ConnectDialog();

private slots:
	void on_buttonBox_rejected();

	void on_buttonBox_accepted();

private:
	Ui::ConnectDialog* ui;
};

#endif // CONNECTDIALOG_H

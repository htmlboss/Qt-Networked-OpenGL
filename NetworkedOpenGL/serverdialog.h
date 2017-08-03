#ifndef SERVERDIALOG_H
#define SERVERDIALOG_H

#include <QDialog>

namespace Ui {
class ServerDialog;
}

class ServerDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ServerDialog(QWidget *parent = 0);
	~ServerDialog();

private slots:
	void on_buttonBox_rejected();

private:
	Ui::ServerDialog* ui;
};

#endif // SERVERDIALOG_H

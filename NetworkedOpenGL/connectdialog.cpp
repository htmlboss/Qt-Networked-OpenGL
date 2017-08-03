#include "connectdialog.h"
#include "ui_connectdialog.h"

/***********************************************************************************/
ConnectDialog::ConnectDialog(QWidget *parent) : QDialog{parent}, ui{new Ui::ConnectDialog} {
	ui->setupUi(this);
}

/***********************************************************************************/
ConnectDialog::~ConnectDialog() {
	delete ui;
}

/***********************************************************************************/
void ConnectDialog::on_buttonBox_rejected() {
	return;
}

/***********************************************************************************/
void ConnectDialog::on_buttonBox_accepted() {

}

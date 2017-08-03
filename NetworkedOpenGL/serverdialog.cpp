#include "serverdialog.h"
#include "ui_serverdialog.h"

/***********************************************************************************/
ServerDialog::ServerDialog(QWidget *parent) : QDialog{parent}, ui{new Ui::ServerDialog}, m_UDPport{12345} {
	ui->setupUi(this);

	ui->udpLineEdit->setText(QString::number(m_UDPport));
}

/***********************************************************************************/
ServerDialog::~ServerDialog() {
	delete ui;
}

/***********************************************************************************/
void ServerDialog::on_buttonBox_rejected() {
	return;
}

/***********************************************************************************/
void ServerDialog::on_buttonBox_accepted() {
	m_UDPport = ui->udpLineEdit->text().toULongLong();
}

#include "serverdialog.h"
#include "ui_serverdialog.h"

/***********************************************************************************/
ServerDialog::ServerDialog(QWidget *parent) : QDialog{parent}, ui{new Ui::ServerDialog}, m_localUDPport{12345}, m_remoteUDPport{12345} {
	ui->setupUi(this);

	ui->localUdpLineEdit->setText(QString::number(m_localUDPport));
	ui->remoteUdpLineEdit->setText(QString::number(m_remoteUDPport));
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
	// Need to verify entered data.
	m_localUDPport = ui->localUdpLineEdit->text().toULongLong();
	m_remoteUDPport = ui->remoteUdpLineEdit->text().toULongLong();
	// https://stackoverflow.com/questions/2240530/does-qt-provide-a-class-that-represents-an-ip-address?rq=1
	m_remoteIP = QHostAddress(ui->remoteIPlineEdit->text());
}

#ifndef SERVERDIALOG_H
#define SERVERDIALOG_H

#include <QDialog>

namespace Ui {
class ServerDialog;
}

class ServerDialog : public QDialog {
	Q_OBJECT

public:
	explicit ServerDialog(QWidget *parent = nullptr);
	~ServerDialog();

	auto GetPort() const noexcept { return m_UDPport; }

private slots:
	void on_buttonBox_rejected();

	void on_buttonBox_accepted();

private:
	Ui::ServerDialog* ui;

	std::size_t m_UDPport;
};

#endif // SERVERDIALOG_H

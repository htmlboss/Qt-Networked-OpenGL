#ifndef SERVERDIALOG_H
#define SERVERDIALOG_H

#include <QDialog>
#include <QHostAddress>

namespace Ui {
class ServerDialog;
}

/***********************************************************************************/
struct UDPData {
	UDPData(const std::size_t local, const std::size_t remote, const QHostAddress& ip) :	LocalPort{local},
																							RemotePort{remote},
																							RemoteIP{ip} {}

	const std::size_t LocalPort, RemotePort;
	const QHostAddress RemoteIP;
};
Q_DECLARE_TYPEINFO(UDPData, Q_MOVABLE_TYPE);

/***********************************************************************************/
class ServerDialog : public QDialog {
	Q_OBJECT

public:
	explicit ServerDialog(QWidget *parent = nullptr);
	~ServerDialog();

	auto GetNetworkInfo() const { return UDPData(m_localUDPport, m_remoteUDPport, m_remoteIP); }

private slots:
	void on_buttonBox_rejected();

	void on_buttonBox_accepted();

private:
	Ui::ServerDialog* ui;

	std::size_t m_localUDPport, m_remoteUDPport;
	QHostAddress m_remoteIP;
};

#endif // SERVERDIALOG_H

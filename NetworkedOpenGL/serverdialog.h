#ifndef SERVERDIALOG_H
#define SERVERDIALOG_H

#include <QWidget>

class QVBoxLayout;

namespace Ui {
class ServerDialog;
}

class ServerDialog : public QWidget {
	Q_OBJECT

public:
	explicit ServerDialog(QWidget* parent = nullptr);

private:
	QVBoxLayout* m_layout;
};

#endif // SERVERDIALOG_H

#include "serverdialog.h"
#include "ui_serverdialog.h"

#include <QVBoxLayout>

#include <QtWidgets>

ServerDialog::ServerDialog(QWidget* parent) : QWidget(parent), m_layout(new QVBoxLayout) {

	setWindowTitle(tr("Start Server"));
	setLayout(m_layout);
}

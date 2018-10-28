#include "dsettings.h"
#include "ui_dsettings.h"

DSettings::DSettings(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DSettings) {
	ui->setupUi(this);
	this->setModal(true);

	pref = Preferences::getInstance();

	// Load settings
	ui->cb_showThreshold->setChecked(pref->getShowThreshold());
	ui->sb_thresholdValue->setValue(pref->getThresholdValue());
	ui->le_thresholdLabel->setText(pref->getThresholdLabel());
	ui->le_host->setText(pref->getAddress());
	ui->le_port->setText(QString::number(pref->getPort()));
	ui->l_result->setText("");
	ui->sb_timeout_s->setValue(pref->getTimeout());
}

DSettings::~DSettings() {
	delete ui;
}

void DSettings::on_cb_showThreshold_toggled(bool checked) {
	pref->setShowThreshold(checked);
	ui->sb_thresholdValue->setEnabled(checked);
	ui->le_thresholdLabel->setEnabled(checked);
}

void DSettings::on_sb_thresholdValue_editingFinished() {
	pref->setThresholdValue(ui->sb_thresholdValue->value());
}

void DSettings::on_le_thresholdLabel_editingFinished() {
	pref->setThresholdLabel(ui->le_thresholdLabel->text());
}

void DSettings::on_le_host_editingFinished() {
	pref->setAddress(ui->le_host->text());
}

void DSettings::on_le_port_editingFinished() {
	bool convertSuccess = false;
	int port = ui->le_port->text().toInt(&convertSuccess);

	if (convertSuccess)
		pref->setPort(port);
}

void DSettings::on_pb_checkConnection_clicked() {
	Ping p;

	QString address = pref->getAddress();
	int port = pref->getPort();

	if (address.isEmpty() || !NetworkUtility::isAddressValid(address)) {
		ui->l_result->setText(tr("Please enter a valid address."));
		return;
	}

	if (!NetworkUtility::isPortValid(port)) {
		ui->l_result->setText(tr("Please enter a valid port."));
		return;
	}

	int ping_ms = p.measure(address, port);
	if (ping_ms < 0)
		ui->l_result->setText(tr("The host is not reachable."));
	else
		ui->l_result->setText(QString(tr("The host is reachable! And the ping is %1ms")).arg(ping_ms));
}

void DSettings::on_sb_timeout_s_editingFinished() {
	pref->setTimeout(ui->sb_timeout_s->value());
}

void DSettings::on_pb_ok_clicked() {
	this->accept();
}

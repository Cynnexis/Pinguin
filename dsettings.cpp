#include "dsettings.h"
#include "ui_dsettings.h"

DSettings::DSettings(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DSettings) {
	ui->setupUi(this);
	this->setModal(true);

	// Load settings
	if (pref.value("server/address", "").toString().isEmpty())
		pref.setValue("server/address", "www.google.com");

	ui->le_host->setText(pref.value("server/address", "").toString());

	bool convertSuccess = false;
	int port = pref.value("server/port", -1).toInt(&convertSuccess);
	if (!convertSuccess || port <= 0 || port >= 65535) {
		port = 80;
		pref.setValue("server/port", port);
	}
	ui->le_port->setText(QString::number(port));

	ui->l_result->setText("");

	convertSuccess = false;
	int timeout = pref.value("server/timeout", -1).toInt(&convertSuccess);
	if (!convertSuccess || timeout < 0 || timeout > 60) {
		timeout = 30;
		pref.setValue("server/timeout", timeout);
	}
	ui->sb_timeout_s->setValue(timeout);
}

DSettings::~DSettings() {
	delete ui;
}

void DSettings::on_le_host_editingFinished() {
	QString atomicAddress = "";
	QString strAtomicPort = "";
	int atomicPort = -1;

	if (ui->le_host->text().contains(':')) {
		atomicAddress = ui->le_host->text().split(":")[0];
		strAtomicPort = ui->le_host->text().split(":")[1];

		bool convertSuccess = false;
		atomicPort = strAtomicPort.toInt(&convertSuccess);
		if (convertSuccess && 0 < atomicPort && atomicPort <= 65535) {
			ui->le_port->setText(strAtomicPort);
			pref.setValue("server/port", atomicPort);
		}
	}
	else
		atomicAddress = ui->le_host->text();

	pref.setValue("server/address", atomicAddress);
}

void DSettings::on_le_port_editingFinished() {
	bool convertSuccess = false;
	int port = ui->le_port->text().toInt(&convertSuccess);

	if (convertSuccess && 0 < port && port <= 65535)
		pref.setValue("server/port", ui->le_port->text().toInt());
	else {
		ui->le_port->setText("80");
		pref.setValue("server/port", 80);
	}
}

void DSettings::on_pb_checkConnection_clicked() {
	Ping p(this);

	QString address = pref.value("server/address", "").toString();
	bool convertSuccess = false;
	int port = pref.value("server/port", -1).toInt(&convertSuccess);

	if (address.isEmpty()) {
		ui->l_result->setText("Please enter a valid address.");
		return;
	}

	if (!convertSuccess || port <= 0 || port >= 65535) {
		ui->l_result->setText("Please enter a valid port.");
		return;
	}

	int ping_ms = p.measure(address, port);
	if (ping_ms < 0)
		ui->l_result->setText("The host is not reachable.");
	else
		ui->l_result->setText(QString("The host is reachable! And the ping is %1ms").arg(ping_ms));
}

void DSettings::on_sb_timeout_s_editingFinished() {
	pref.setValue("server/timeout", ui->sb_timeout_s->value());
}

void DSettings::on_pb_ok_clicked() {
	this->accept();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);
	this->setWindowTitle(qApp->applicationName());
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_pb_debug_clicked() {
	Ping p;
	int ping_ms = p.measure("www.google.com", 80);
	if (ping_ms > 0) {
		qDebug() << "Connected: ping = " << ping_ms << "ms";
		ui->le_currentPing->setText(QString::number(ping_ms));
	}
	else
		QMessageBox::information(this, "Host not reachable", "The host cannot be reached. Is it in Antartica?");
}

void MainWindow::on_actionSettings_triggered() {
	diagSettings = new DSettings(this);
	diagSettings->exec();
}

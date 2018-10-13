#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);
	this->setWindowTitle(qApp->applicationName());

	pref = Preferences::getInstance(this);

	connect(&loop, SIGNAL(resultAvailable(int)), this, SLOT(onReceivePing(int)));
	loop.start();
}

MainWindow::~MainWindow() {
	delete ui;
	loop.stop();
	loop.wait();
}

void MainWindow::on_pb_debug_clicked() {
	Ping p;
	connect(&p, SIGNAL(measureDone(int)), this, SLOT(onReceivePing(int)));
	p.measure("www.google.com", 80);
}

void MainWindow::onReceivePing(int ping_ms) {
	if (ping_ms > 0) {
		qDebug() << "Connected: ping = " << ping_ms << "ms";
		ui->le_currentPing->setText(QString::number(ping_ms));
	}
	else
		ui->statusBar->showMessage(tr("The host cannot be reached. Is it in Antartica?"), 10000);
}

void MainWindow::on_actionSettings_triggered() {
	diagSettings = new DSettings(this);
	diagSettings->exec();
}

void MainWindow::on_actionExit_triggered() {
	qApp->exit();
}

void MainWindow::on_actionAbout_Pinguin_triggered() {
	QMessageBox::about(this, tr("About %1...", "About [Application Name]...").arg(qApp->applicationName()), "Pinguin is a simple application that plot the ping from your computer to a specific certain as a function of time. It is written in C++ with Qt Framework.");
}

void MainWindow::on_actionAbout_Qt_triggered() {
	QMessageBox::aboutQt(this, tr("About Qt..."));
}

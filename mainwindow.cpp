#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);
	this->setWindowTitle(qApp->applicationName());

	pref = Preferences::getInstance(this);

	connect(pref, SIGNAL(addressChanged(QString)), this, SLOT(onAddressUpdated(QString)));
	connect(pref, SIGNAL(portChanged(int)), this, SLOT(onPortUpdated(int)));
	connect(&loop, SIGNAL(resultAvailable(int)), this, SLOT(onReceivePing(int)));

	updateServer(pref->getAddress(), pref->getPort());

	pc_chart = new PingChart();
	ui->gv_chartPlaceholder->setChart(pc_chart);
	ui->gv_chartPlaceholder->setRenderHint(QPainter::Antialiasing);

#ifdef QT_DEBUG
	qDebug() << tr("It's DEBUG TIME!");
	ui->menuDebug->menuAction()->setVisible(true);
#else
	ui->menuDebug->menuAction()->setVisible(false);
#endif

	loop.start();
}

MainWindow::~MainWindow() {
	delete ui;
	loop.stop();
	loop.wait();
}

void MainWindow::updateServer(QString address, int port) {
	QString server = "[";
	QString actual = ui->l_server_ip->text();

	if (address != "")
		server += address;
	else
		server += actual.replace("[", "").split(":")[0];

	server += ":";

	if (port > 0)
		server += QString::number(port);
	else
		server += actual.replace("]", "").split(":")[1];

	server += "]";
	ui->l_server_ip->setText(server);
}

void MainWindow::onAddressUpdated(QString address) {
	updateServer(address);
}

void MainWindow::onPortUpdated(int port) {
	updateServer("", port);
}

void MainWindow::onReceivePing(int ping_ms) {
	if (ping_ms > 0) {
		ui->le_currentPing->setText(QString::number(ping_ms));
		pc_chart->append(ping_ms);
		pc_chart->update();
		ui->gv_chartPlaceholder->repaint();
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

void MainWindow::on_actionMagic_Debug_triggered() {
	// Add your debugging code here.
}

void MainWindow::on_actionAbout_Pinguin_triggered() {
	QMessageBox::about(this, tr("About %1...", "About [Application Name]...").arg(qApp->applicationName()), "Pinguin is a simple application that plot the ping from your computer to a specific certain as a function of time. It is written in C++ with Qt Framework.");
}

void MainWindow::on_actionAbout_Qt_triggered() {
	QMessageBox::aboutQt(this, tr("About Qt..."));
}

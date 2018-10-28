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
	ui->pb_debug->setVisible(true);
#else
	ui->pb_debug->setVisible(false);
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

void MainWindow::on_pb_debug_clicked() {
	QString content = "";
	for (int i = 0; i < pc_chart->getSeries().points().length(); i++)
		content += "(" + QString::number(pc_chart->getSeries().points()[i].x()) + ", " + QString::number(pc_chart->getSeries().points()[i].y()) + ")\n";

	QMessageBox::information(this, "Debug", content);
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

void MainWindow::on_actionAbout_Pinguin_triggered() {
	QMessageBox::about(this, tr("About %1...", "About [Application Name]...").arg(qApp->applicationName()), "Pinguin is a simple application that plot the ping from your computer to a specific certain as a function of time. It is written in C++ with Qt Framework.");
}

void MainWindow::on_actionAbout_Qt_triggered() {
	QMessageBox::aboutQt(this, tr("About Qt..."));
}

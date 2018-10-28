#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);
	this->setWindowTitle(qApp->applicationName());

	pref = Preferences::getInstance(this);
	style = StyleManager::getInstance(this);
	clipboard = QApplication::clipboard();

	ui->menuFile->setTitle(qApp->applicationName());

	connect(pref, SIGNAL(addressChanged(QString)), this, SLOT(onAddressUpdated(QString)));
	connect(pref, SIGNAL(portChanged(int)), this, SLOT(onPortUpdated(int)));
	connect(pref, SIGNAL(themeChanged(Theme)), this, SLOT(onThemeChanged(Theme)));
	connect(&loop, SIGNAL(resultAvailable(int)), this, SLOT(onReceivePing(int)));

	ui->l_server_ip->setTextFormat(Qt::RichText);
	ui->l_server_ip->setTextInteractionFlags(Qt::TextBrowserInteraction);
	ui->l_server_ip->setOpenExternalLinks(true);

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

	// Load style
	onThemeChanged();

	loop.start();
}

MainWindow::~MainWindow() {
	delete ui;
	loop.stop();
	loop.wait();
}

void MainWindow::updateServer(QString address, int port) {
	QString server = tr("<h1>Server: <a href=\"%1\">%1</a></h1>", "\"%1\" represents the address to the server.");
	ui->l_server_ip->setText(server.arg(address + ":" + QString::number(port)));
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

void MainWindow::onThemeChanged(Theme theme) {
	style->apply(theme);
}

void MainWindow::onThemeChanged() {
	onThemeChanged(pref->getTheme());
}

void MainWindow::on_actionPause_Ping_triggered() {
	if (loop.isPaused()) {
		loop.resume();
		ui->actionPause_Ping->setText(tr("Pause Ping"));
		ui->actionPause_Ping->setIcon(QIcon(":/icons/material-design/res/icons/material-design/ic_pause_48px.svg"));
	}
	else {
		loop.pause();
		ui->actionPause_Ping->setText(tr("Resume Ping"));
		ui->actionPause_Ping->setIcon(QIcon(":/icons/material-design/res/icons/material-design/ic_play_arrow_48px.svg"));
	}
}

void MainWindow::on_actionCopy_current_ping_to_clipboard_triggered() {
	clipboard->setText(ui->le_currentPing->text());
	ui->statusBar->showMessage(tr("Ping value copied to clipboard!", "Status message"), 5000);
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

void MainWindow::on_actionForce_Theme_Update_triggered() {
	onThemeChanged();
}

void MainWindow::on_actionAbout_Pinguin_triggered() {
	QMessageBox::about(this, tr("About %1...", "About [Application Name]...").arg(qApp->applicationName()), "Pinguin is a simple application that plot the ping from your computer to a specific certain as a function of time. It is written in C++ with Qt Framework.");
}

void MainWindow::on_actionAbout_Qt_triggered() {
	QMessageBox::aboutQt(this, tr("About Qt..."));
}

void MainWindow::on_actionSee_Source_Code_triggered() {
	QDesktopServices::openUrl(QUrl("https://github.com/Cynnexis/Pinguin"));
}

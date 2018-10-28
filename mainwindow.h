#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

#include "dsettings.h"
#include "pingchart.h"
#include "pingloop.h"

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QElapsedTimer>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

#include <QDebug>

using namespace std;
QT_CHARTS_USE_NAMESPACE

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void updateServer(QString address = "", int port = -1);

private slots:
	void onAddressUpdated(QString address);
	void onPortUpdated(int port);
	void onReceivePing(int ping_ms);
	void onThemeChanged(Theme theme);
	void onThemeChanged();

	void on_actionPause_Ping_triggered();
	void on_actionCopy_current_ping_to_clipboard_triggered();
	void on_actionSettings_triggered();
	void on_actionExit_triggered();
	void on_actionMagic_Debug_triggered();
	void on_actionAbout_Pinguin_triggered();
	void on_actionAbout_Qt_triggered();
	void on_actionSee_Source_Code_triggered();

private:
	Ui::MainWindow *ui;

	Preferences* pref;
	PingLoop loop;
	DSettings* diagSettings;

	PingChart* pc_chart;

	QClipboard* clipboard;
};

#endif // MAINWINDOW_H

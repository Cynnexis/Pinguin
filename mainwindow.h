#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dsettings.h"

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QElapsedTimer>

#include <QDebug>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_pb_debug_clicked();
	void on_actionSettings_triggered();

	void onReceivePing(int ping_ms);

private:
	Ui::MainWindow *ui;

	DSettings* diagSettings;
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include <iostream>
#include <QApplication>

#include <QDebug>
#include <QFontDatabase>

using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication::setOrganizationName("Aezy");
	QCoreApplication::setApplicationName(qApp->applicationName());
	QApplication a(argc, argv);

	QFontDatabase::addApplicationFont(":/fonts/roboto/res/fonts/Roboto-Regular.ttf");

	MainWindow w;
	w.show();

	return a.exec();
}

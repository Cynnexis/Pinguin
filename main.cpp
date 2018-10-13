#include "mainwindow.h"
#include <iostream>
#include <QApplication>

#include <QDebug>

using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication::setOrganizationName("Aezy");
	QCoreApplication::setApplicationName(qApp->applicationName());
	QApplication a(argc, argv);

	MainWindow w;
	w.show();

	return a.exec();
}

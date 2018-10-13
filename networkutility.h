#ifndef NETWORKUTILITY_H
#define NETWORKUTILITY_H

#include <iostream>

#include <QObject>
#include <QRegularExpression>

#include <QDebug>

using namespace std;

namespace NetworkUtility
{
	bool isAddressValid(QString address, bool acceptHttp = true);
	bool isPortValid(int port);
	QString removeHttp(QString address);
	void splitHostname(QString hostname, QString& address, int& port);
};

#endif // NETWORKUTILITY_H

#ifndef PINGLOOP_H
#define PINGLOOP_H

#include "ping.h"
#include "preferences.h"

#ifdef Q_OS_WIN
//#include <windows.h> // for Sleep
#endif

#include <iostream>
#include <QObject>
#include <QThread>
#include <QDebug>

using namespace std;

class PingLoop : public QThread
{
	Q_OBJECT

public:
	PingLoop(QObject* parent = nullptr);
	void run() override;

public slots:
	void resume();
	void pause();
	void stop();

signals:
	void resultAvailable(int ping_ms);

private:
	Ping ping;
	Preferences* pref;
	bool _pause = false;
	bool _stop = false;

	QString address;
	int port;

private slots:
	void transferResult(int ping_ms = -1);

	void updateAddress(QString newAddress);
	void updatePort(int newPort);
};

#endif // PINGLOOP_H

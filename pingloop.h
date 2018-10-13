#ifndef PINGLOOP_H
#define PINGLOOP_H

#include "ping.h"

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
	QSettings pref;
	bool _pause = false;
	bool _stop = false;

private slots:
	void transferResult(int ping_ms = -1);
};

#endif // PINGLOOP_H

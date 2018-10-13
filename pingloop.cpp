#include "pingloop.h"

PingLoop::PingLoop(QObject* parent) : QThread(parent) {
	pref = Preferences::getInstance();
	connect(&ping, SIGNAL(measureDone(int)), this, SLOT(transferResult(int)));
	connect(&ping, SIGNAL(measureNotReachable()), this, SLOT(transferResult()));
}

void PingLoop::run() {
	while (!_stop) {
		while (_pause);
		int ping_ms = ping.measure(/*pref->getAddress(), pref->getPort()*/"www.google.com", 80);
		qDebug() << QString("[%1:%2] ping = %3ms").arg(/*pref->getAddress(), pref->getPort()*/"google.com", QString::number(80), QString::number(ping_ms));

		int ms = 1000;
#ifdef Q_OS_WIN
		Sleep(uint(ms));
#else
		struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
		nanosleep(&ts, NULL);
#endif
	}
}

void PingLoop::resume() {
	_pause = false;
}

void PingLoop::pause() {
	_pause = true;
}

void PingLoop::stop() {
	_stop = true;
}

void PingLoop::transferResult(int ping_ms) {
	emit resultAvailable(ping_ms);
}

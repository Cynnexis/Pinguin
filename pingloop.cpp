#include "pingloop.h"

PingLoop::PingLoop(QObject* parent) : QThread(parent) {
	pref = Preferences::getInstance();

	connect(&ping, SIGNAL(measureDone(int)), this, SLOT(transferResult(int)));
	connect(&ping, SIGNAL(measureNotReachable()), this, SLOT(transferResult()));

	connect(pref, SIGNAL(addressChanged(QString)), this, SLOT(updateAddress(QString)));
	connect(pref, SIGNAL(portChanged(int)), this, SLOT(updatePort(int)));

	updateAddress(pref->getAddress());
	updatePort(pref->getPort());
}

void PingLoop::run() {
	while (!_stop) {
		while (_pause);
		int ping_ms = ping.measure(address, port);
		qDebug() << QString("[%1:%2] ping = %3ms").arg(address, QString::number(port), QString::number(ping_ms));

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

void PingLoop::updateAddress(QString newAddress) {
	address = newAddress;
}

void PingLoop::updatePort(int newPort) {
	port = newPort;
}

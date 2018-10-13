#include "pingloop.h"

PingLoop::PingLoop(QObject* parent) : QThread(parent) {
	connect(&ping, SIGNAL(measureDone(int)), this, SLOT(transferResult(int)));
	connect(&ping, SIGNAL(measureNotReachable()), this, SLOT(transferResult()));
}

void PingLoop::run() {
	while (!_stop) {
		while (_pause);
		ping.measure(pref.value("server/address").toString(), pref.value("server/port").toInt());
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

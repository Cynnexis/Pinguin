#include "ping.h"

Ping::Ping(QObject *parent) : QObject(parent) {
	//
}

/**
 * @brief Ping::measure
 * Measure the ping between the computer and a server
 * @param address The address of the host. It can contain the port
 * @param port The port. If not defined, try to read it in `address`. If not in address, take port 80.
 * @return Return the time in millisecond, or -1 if the destination could not be reached.
 */
int Ping::measure(QString address, int port) {

	QElapsedTimer stopwatch;
	QTcpSocket* socket = new QTcpSocket(this);

	stopwatch.start();
	socket->connectToHost(address, port);
	//								30s
	if (socket->waitForConnected(30000)) {
		int ping_ms = stopwatch.elapsed();
		measureDone(ping_ms);
		socket->close();
		return ping_ms;
	}
	else
		return -1;
}

void Ping::measureAsync(QString address, int port) {
	QSignalMapper* mapper = new QSignalMapper(this);

	QThread thread;
	moveToThread(&thread);

	connect(&thread, SIGNAL(started()), mapper, SLOT(map()));

	mapper->setMapping(&thread, address + ":" + QString::number(port));

	QString strAddress = address;
	connect(mapper, SIGNAL(mapped(QString)), this, SLOT(measure(QString)));
	thread.start();
}

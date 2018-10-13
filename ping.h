#ifndef PING_H
#define PING_H

#include <iostream>
#include <QObject>
#include <QTcpSocket>
#include <QMessageBox>
#include <QElapsedTimer>
#include <QThread>
#include <QSignalMapper>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

#include <QDebug>

using namespace std;

class Ping : public QObject
{
	Q_OBJECT
public:
	explicit Ping(QObject *parent = nullptr);
	~Ping();

signals:
	void measureDone(int ping_ms);
	void measureNotReachable();

public slots:
	int measure(QString address, int port = 80);
};

#endif // PING_H

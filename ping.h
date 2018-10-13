#ifndef PING_H
#define PING_H

#include <QObject>
#include <QTcpSocket>
#include <QMessageBox>
#include <QElapsedTimer>

#include <QDebug>

class Ping : public QObject
{
	Q_OBJECT
public:
	explicit Ping(QObject *parent = nullptr);

	int measure(QString address, int port = 80);

signals:
	void measureDone(int ping_ms);

public slots:
};

#endif // PING_H

#ifndef PING_H
#define PING_H

#include <QObject>
#include <QTcpSocket>
#include <QMessageBox>
#include <QElapsedTimer>
#include <QThread>
#include <QSignalMapper>

#include <QDebug>

class Ping : public QObject
{
	Q_OBJECT
public:
	explicit Ping(QObject *parent = nullptr);

signals:
	void measureDone(int ping_ms);

public slots:
	int measure(QString address, int port = 80);
	void measureAsync(QString address, int port = 80);
};

#endif // PING_H

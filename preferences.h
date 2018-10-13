#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <iostream>
#include <QObject>
#include <QSettings>
#include <QDebug>

#include "networkutility.h"

using namespace std;

class Preferences : public QObject
{
	Q_OBJECT

public:
	static Preferences* getInstance(QObject* parent = nullptr);

	bool isFirstLaunch();
	void setFirstLaunch(bool firstLaunch);
	void initFirstLaunch();

	QString getAddress();
	void setAddress(QString address);
	void initAddress();

	int getPort();
	void setPort(int port);
	void initPort();

	int getTimeout();
	void setTimeout(int timeout_ms);
	void initTimeout();

private:
	explicit Preferences(QObject* parent = nullptr);

	static Preferences* pref;
	QSettings settings;
};

#endif // PREFERENCES_H

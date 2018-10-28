#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <iostream>
#include <QObject>
#include <QSettings>
#include <QDebug>

#include "networkutility.h"
#include "theme.h"

using namespace std;

class Preferences : public QObject
{
	Q_OBJECT

public:
	static Preferences* getInstance(QObject* parent = nullptr);

	bool isFirstLaunch();
	void setFirstLaunch(bool firstLaunch = true);
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

	bool getShowThreshold();
	void setShowThreshold(bool showThreshold);
	void initShowThreshold();

	int getThresholdValue();
	void setThresholdValue(int thresholdValue);
	void initThresholdValue();

	QString getThresholdLabel();
	void setThresholdLabel(QString thresholdLabel);
	void initThresholdLabel();

	Theme getTheme();
	void setTheme(Theme theme);
	void initTheme();

signals:
	void firstLaunchChanged(bool);
	void addressChanged(QString);
	void portChanged(int);
	void timeoutChanged(int);
	void showThresholdChanged(bool);
	void thresholdValueChanged(int);
	void thresholdLabelChanged(QString);
	void themeChanged(Theme);

private:
	explicit Preferences(QObject* parent = nullptr);

	static Preferences* pref;
	QSettings settings;
};

#endif // PREFERENCES_H

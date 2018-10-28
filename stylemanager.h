#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include <iostream>

#include "preferences.h"

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QApplication>

using namespace std;

class StyleManager : public QObject
{
	Q_OBJECT
public:
	static StyleManager* getInstance(QObject* parent = nullptr);

public slots:
	void apply(Theme theme);
	void refresh();

private:
	explicit StyleManager(QObject *parent = nullptr);
	static StyleManager* style;

	Preferences* pref;

	QString getFileContent(QString filename);
	QHash<QString, QString> getVars(QString varFile);
	QString merge(QString css, QHash<QString, QString> vars);

	QString getAbstractCSS();
	QString getAbstractVAR();
	QString getAbstractStylesheet();
	QString getLightCSS();
	QString getLightVAR();
	QString getLightStylesheet();
	QString getDarkCSS();
	QString getDarkVAR();
	QString getDarkStylesheet();

	QString getResourceDirectoryPath();
};

#endif // STYLEMANAGER_H

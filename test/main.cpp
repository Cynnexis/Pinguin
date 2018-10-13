#include <iostream>
#include <QObject>
#include <QtTest>
#include <QApplication>
#include <QDebug>

#include "networkutilitytestcase.h"

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

	qDebug() << "Starting Test Cases...";

	QList<QObject*> testcases;
	NetworkUtilityTestCase testcase1;
	testcases.append(new NetworkUtilityTestCase());
	//return QTest::qExec(&testcase1, argc, argv);
	bool verify = true;
	for (int i = 0; i < testcases.size(); i++) {
		if (!QTest::qExec(testcases[i], argc, argv))
			verify = false;
	}

	return verify;
}

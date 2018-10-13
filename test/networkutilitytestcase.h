#ifndef NETWORKUTILITYTESTCASE_H
#define NETWORKUTILITYTESTCASE_H

#include <iostream>
#include <QObject>
#include <QtTest>

#include <QDebug>

using namespace std;

class NetworkUtilityTestCase : public QObject
{
	Q_OBJECT

private slots:
	// functions executed by QtTest before and after test suite
	void initTestCase();
	void cleanupTestCase();

	// functions executed by QtTest before and after each test
	void init();
	void cleanup();

	// test functions
	void test_isAddressValid();
};

#endif // NETWORKUTILITYTESTCASE_H

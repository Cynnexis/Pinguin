#include "preferences.h"

Preferences* Preferences::pref;

Preferences::Preferences(QObject* parent) : QObject(parent) {
	if (!isFirstLaunch()) {
		initAddress();
		initPort();
		initTimeout();

		// Last
		initFirstLaunch();
	}
}

Preferences* Preferences::getInstance(QObject* parent) {
	if (Preferences::pref == nullptr)
		Preferences::pref = new Preferences(parent);

	return Preferences::pref;
}

bool Preferences::isFirstLaunch() {
	return settings.value("app/firstLaunch", false).toBool();
}

void Preferences::setFirstLaunch(bool firstLaunch) {
	settings.setValue("app/firstLaunch", firstLaunch);
}

void Preferences::initFirstLaunch() {
	settings.setValue("app/firstLaunch", true);
}

QString Preferences::getAddress() {
	QString address = settings.value("server/address", "").toString();
	if (!address.isEmpty() && NetworkUtility::isAddressValid(address))
		return address;
	else {
		initAddress();
		return getAddress();
	}
}

void Preferences::setAddress(QString address) {
	address = NetworkUtility::removeHttp(address);
	if (NetworkUtility::isAddressValid(address, false)) {
		// Maybe the port is in the address too
		QString atomicAddress = "";
		int atomicPort = -1;
		bool success = NetworkUtility::splitHostname(address, atomicAddress, atomicPort);
		if (success) {
			settings.setValue("server/address", atomicAddress);
			if (atomicPort > 0)
				setPort(atomicPort);
		}
		else
			settings.setValue("server/address", address);
	}
}

void Preferences::initAddress() {
	setAddress("www.google.com");
}

int Preferences::getPort() {
	bool success = false;
	int port = settings.value("server/port", -1).toInt(&success);
	if (success && NetworkUtility::isPortValid(port))
		return port;
	else {
		initPort();
		return getPort();
	}
}

void Preferences::setPort(int port) {
	if (NetworkUtility::isPortValid(port))
		settings.setValue("server/port", port);
}

void Preferences::initPort() {
	setPort(80);
}

int Preferences::getTimeout() {
	bool success = false;
	int timeout_s = settings.value("server/timeout", -1).toInt(&success);
	if (success && 0 <= timeout_s && timeout_s <= 60)
		return timeout_s;
	else {
		initTimeout();
		return getTimeout();
	}
}

void Preferences::setTimeout(int timeout_s) {
	if (0 <= timeout_s && timeout_s <= 60)
		settings.setValue("server/timeout", timeout_s);
}

void Preferences::initTimeout() {
	setTimeout(30);
}

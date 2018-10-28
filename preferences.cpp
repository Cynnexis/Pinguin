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
	emit firstLaunchChanged(firstLaunch);
}

void Preferences::initFirstLaunch() {
	setFirstLaunch(true);
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
			emit addressChanged(atomicAddress);
			if (atomicPort > 0)
				setPort(atomicPort);
		}
		else {
			settings.setValue("server/address", address);
			emit addressChanged(address);
		}
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
	if (NetworkUtility::isPortValid(port)) {
		settings.setValue("server/port", port);
		emit portChanged(port);
	}
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
	if (0 <= timeout_s && timeout_s <= 60) {
		settings.setValue("server/timeout", timeout_s);
		emit timeoutChanged(timeout_s);
	}
}

void Preferences::initTimeout() {
	setTimeout(30);
}

bool Preferences::getShowThreshold() {
	return settings.value("app/showThreshold", true).toBool();
}

void Preferences::setShowThreshold(bool showThreshold) {
	settings.setValue("app/showThreshold", showThreshold);
	emit showThresholdChanged(showThreshold);
}

void Preferences::initShowThreshold() {
	setShowThreshold(true);
}

int Preferences::getThresholdValue() {
	bool success = false;
	int thresholdValue = settings.value("app/thresholdValue", -1).toInt(&success);
	if (success && 0 <= thresholdValue && thresholdValue <= 10000)
		return thresholdValue;
	else {
		initThresholdValue();
		return getThresholdValue();
	}
}

void Preferences::setThresholdValue(int thresholdValue) {
	if (0 <= thresholdValue && thresholdValue <= 10000) {
		settings.setValue("app/thresholdValue", thresholdValue);
		emit thresholdValueChanged(thresholdValue);
	}
}

void Preferences::initThresholdValue() {
	setThresholdValue(100);
}

QString Preferences::getThresholdLabel() {
	QString thresholdLabel = settings.value("app/thresholdLabel", "").toString();
	if (!thresholdLabel.isEmpty())
		return thresholdLabel;
	else {
		initThresholdLabel();
		return getThresholdLabel();
	}
}

void Preferences::setThresholdLabel(QString thresholdLabel) {
	if (!thresholdLabel.isEmpty()) {
		settings.setValue("app/thresholdLabel", thresholdLabel);
		emit thresholdLabelChanged(thresholdLabel);
	}
}

void Preferences::initThresholdLabel() {
	setThresholdLabel("Playable");
}

Theme Preferences::getTheme() {
	bool success = false;
	int i_theme = settings.value("style/theme", "").toInt(&success);

	if (!success) {
		initTheme();
		return getTheme();
	}

	Theme t = static_cast<Theme>(i_theme);

	if (t == Theme::LIGHT || t == Theme::DARK)
		return static_cast<Theme>(i_theme);
	else {
		initTheme();
		return getTheme();
	}
}

void Preferences::setTheme(Theme theme) {
	switch (theme)
	{
		case Theme::LIGHT:
			settings.setValue("style/theme", 0);
			emit themeChanged(theme);
			break;
		case Theme::DARK:
			settings.setValue("style/theme", 1);
			emit themeChanged(theme);
			break;
	}
}

void Preferences::initTheme() {
	setTheme(Theme::LIGHT);
}

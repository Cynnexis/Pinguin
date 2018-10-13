#include "networkutility.h"

bool NetworkUtility::isAddressValid(QString address, bool acceptHttp) {
	QString pattern;
	if (acceptHttp)
		pattern = "^(http:\\/\\/www\\.|https:\\/\\/www\\.|http:\\/\\/|https:\\/\\/)?";
	else
		pattern = "^";

	pattern += "[a-z0-9]+([\\-\\.]{1}[a-z0-9]+)*\\.[a-z]{2,5}(:[0-9]{1,5})?(\\/.*)?$";
	qDebug() << "URL pattern is \"" << pattern << "\"";
	QRegularExpression re(pattern);
	QRegularExpressionMatch match = re.match(address);
	return match.hasMatch();
}

bool NetworkUtility::isPortValid(int port) {
	return 0 < port && port <= 65535;
}

QString NetworkUtility::removeHttp(QString address) {
	/*if (!isAddressValid(address))
		return address;*/

	QRegularExpression re("http[s]:\\/\\/");
	return address.remove(re);
}

void NetworkUtility::splitHostname(QString hostname, QString& address, int& port) {
	//
}



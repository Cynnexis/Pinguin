#include "networkutility.h"

bool NetworkUtility::isAddressValid(QString address, bool acceptHttp) {
	QString pattern;
	if (acceptHttp)
		pattern = "^(http:\\/\\/www\\.|https:\\/\\/www\\.|http:\\/\\/|https:\\/\\/)?";
	else
		pattern = "^";

	pattern += "[a-z0-9]+([\\-\\.]{1}[a-z0-9]+)*\\.[a-z]{2,5}(:[0-9]{1,5})?(\\/.*)?$";
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

/**
 * @brief NetworkUtility::splitHostname Split the address and the port from the hostname
 * @param hostname The URL
 * @param address The reference to the address
 * @param port The reference to the port
 * @return Return the address, and the port if found (if not found, the port is equal to -1). If the conversion is finished, returned `true`, other `false`.
 */
bool NetworkUtility::splitHostname(QString hostname, QString& address, int& port) {
	hostname = removeHttp(hostname);
	if (!isAddressValid(hostname))
		return false;

	if (!hostname.contains(':')) {
		address = hostname;
		port = -1;
		return true;
	}

	address = hostname.split(':')[0];
	QString s_port = hostname.split(':')[1];
	s_port = s_port.split('/')[0];

	bool success = false;
	port = s_port.toInt(&success);

	if (!success) {
		port = -1;
		return false;
	}

	return isAddressValid(address) && isPortValid(port);
}



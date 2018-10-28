#include "stylemanager.h"

StyleManager* StyleManager::style;

StyleManager::StyleManager(QObject *parent) : QObject(parent) {
	pref = Preferences::getInstance();

	connect(pref, SIGNAL(themeChanged(Theme)), this, SLOT(apply(Theme)));
}

StyleManager* StyleManager::getInstance(QObject* parent) {
	if (StyleManager::style == nullptr) {
		// Make sure that Preference is loaded as well
		Preferences::getInstance();

		StyleManager::style = new StyleManager(parent);
	}

	return StyleManager::style;
}

void StyleManager::apply(Theme theme) {
	if (theme == Theme::DEFAULT)
		qApp->setStyleSheet("");
	else {
		QString abstract = getAbstractStylesheet();
		QString themeStylesheet;
		switch (theme)
		{
			case Theme::LIGHT:
				themeStylesheet = getLightStylesheet();
				break;
			default: // DARK
				themeStylesheet = getDarkStylesheet();
				break;
		}
		QString final = abstract + "\n\n" + themeStylesheet;
		qApp->setStyleSheet(final);
	}
}

void StyleManager::refresh() {
	apply(pref->getTheme());
}

QString StyleManager::getFileContent(QString filename) {
	QFile f(getResourceDirectoryPath() + filename);
	f.open(QFile::ReadOnly);
	return f.readAll();
}

QHash<QString, QString> StyleManager::getVars(QString varFile) {
	varFile = varFile.replace("\r\n", "\n");
	varFile = varFile.replace(" = ", "=");
	varFile = varFile.replace(" =", "=");
	varFile = varFile.replace("= ", "=");
	QHash<QString, QString> vars;
	QStringList list = varFile.split("\n");

	for (int i = 0; i < list.length(); i++) {
		QStringList statement = list[i].split("=");
		if (statement.length() == 2)
			vars[statement[0]] = statement[1];
	}

	return vars;
}

QString StyleManager::merge(QString css, QHash<QString, QString> vars) {
	QList<QString> keys = vars.uniqueKeys();

	for (int i = 0; i < keys.length(); i++)
		css = css.replace(keys[i], vars[keys[i]]);

	return css;
}

QString StyleManager::getAbstractCSS() {
	return getFileContent("abstract-style.css");
}

QString StyleManager::getAbstractVAR() {
	return getFileContent("abstract-style.var");
}

QString StyleManager::getAbstractStylesheet() {
	return merge(getAbstractCSS(), getVars(getAbstractVAR()));
}

QString StyleManager::getLightCSS() {
	return getFileContent("light-style.css");
}

QString StyleManager::getLightVAR() {
	return getFileContent("light-style.var");
}

QString StyleManager::getLightStylesheet() {
	return merge(getLightCSS(), getVars(getLightVAR()));
}

QString StyleManager::getDarkCSS() {
	return getFileContent("dark-style.css");
}

QString StyleManager::getDarkVAR() {
	return getFileContent("dark-style.var");
}

QString StyleManager::getDarkStylesheet() {
	return merge(getDarkCSS(), getVars(getDarkVAR()));
}

QString StyleManager::getResourceDirectoryPath() {
#ifdef QT_DEBUG
	return "..\\res\\css\\";
#else
	return ":/css/res/css/";
#endif
}

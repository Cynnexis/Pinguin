#include "pingchart.h"

PingChart::PingChart() : QChart() {
	pref = Preferences::getInstance();

	xi = 0;

	xmin = 0;
	xmax = 10 + xeps;
	ymin = 0;
	ymax = 500 + yeps;

	axisX = new QValueAxis();
	axisY = new QValueAxis();

	axisX->setTickCount(1);
	axisX->setRange(xmin, xmax);
	axisY->setRange(ymin, ymax);
	//axisY->setTickCount(50);

	this->addAxis(axisX, Qt::AlignBottom);

	ls_ping = new QLineSeries(this);
	ls_ping->setName(tr("Ping (ms)", "Series name"));

	this->legend()->show();
	this->addSeries(ls_ping);
	this->setTitle(tr("Ping (ms)", "Chart name"));
	this->addAxis(axisY, Qt::AlignLeft);

	ls_ping->attachAxis(axisX);
	ls_ping->attachAxis(axisY);

	// Load threshold properties
	threshold = pref->getThresholdValue();
	ls_threshold = new QLineSeries(this);
	ls_threshold->setName(pref->getThresholdLabel());
	this->addSeries(ls_threshold);
	ls_threshold->attachAxis(axisX);
	ls_threshold->attachAxis(axisY);

	connect(ls_ping, SIGNAL(pointAdded(int)), this, SLOT(onPointAdded(int)));
	connect(ls_ping, SIGNAL(pointAdded(int)), this, SLOT(addThresholdPoint()));
	connect(pref, SIGNAL(showThresholdChanged(bool)), this, SLOT(onShowThresholdChanged(bool)));
	connect(pref, SIGNAL(thresholdValueChanged(int)), this, SLOT(onThresholdValueChanged(int)));
	connect(pref, SIGNAL(thresholdLabelChanged(QString)), this, SLOT(onThresholdLabelChanged(QString)));

	onShowThresholdChanged(pref->getShowThreshold());
}

QLineSeries& PingChart::getSeries() {
	return *(this->ls_ping);
}

int PingChart::getThreshold() {
	return threshold;
}

void PingChart::setThreshold(int threshold) {
	this->threshold = threshold;
}

void PingChart::append(const QPointF point) {
	*ls_ping << point;
}
void PingChart::append(const qreal x, const qreal y) {
	append(QPointF(x, y));
}
void PingChart::append(const qreal y) {
	append(QPointF(++xi, y));
}

PingChart& PingChart::operator+=(const QPointF point) {
	append(point);
	return *this;
}
PingChart& PingChart::operator+=(const qreal y) {
	append(y);
	return *this;
}

PingChart& PingChart::operator<<(const QPointF point) {
	append(point);
	return *this;
}
PingChart& PingChart::operator<<(const qreal y) {
	append(y);
	return *this;
}

void PingChart::onPointAdded(int index) {
	int x, y;
	x = round(ls_ping->points()[index].x());
	y = round(ls_ping->points()[index].y());

	// Delete the first items if the number of points has reached a threshold
	while (ls_ping->points().length() > 0 && ls_ping->points().length() >= xlimit)
		ls_ping->remove(0);

	if (ls_ping->points().size() == 0)
		return;

	xmin = xmax = x;
	ymax = y;

	// Update the chart area
	for (int i = 0; i < ls_ping->count(); i++) {
		const QPointF& point = ls_ping->at(i);

		if (point.x() > xmax)
			xmax = round(point.x());

		if (point.x() < xmin)
			xmin = round(point.x());

		if (point.y() > ymax)
			ymax = round(point.y());
	}

	xmin = xmin;
	xmax = xmax;
	ymin = 0;
	ymax = ymax + yeps;

	// Update the axis
	axisX->setRange(xmin, xmax);
	axisY->setRange(ymin, ymax);
}

void PingChart::onShowThresholdChanged(bool showThreshold) {
	if (showThreshold)
		ls_threshold->show();
	else
		ls_threshold->hide();
}

void PingChart::onThresholdValueChanged(int thresholdValue) {
	threshold = thresholdValue;
	for (int i = 0; i < ls_threshold->count(); i++)
		ls_threshold->points()[i].setY(threshold);
}

void PingChart::onThresholdLabelChanged(QString thresholdLabel) {
	ls_threshold->setName(thresholdLabel);
}

void PingChart::addThresholdPoint() {
	ls_threshold->append(xi, threshold);
}

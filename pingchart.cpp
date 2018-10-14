#include "pingchart.h"

PingChart::PingChart() : QChart() {
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
	connect(ls_ping, SIGNAL(pointAdded(int)), this, SLOT(onPointAdded(int)));

	this->legend()->hide();
	this->addSeries(ls_ping);
	this->setTitle(tr("Ping (ms)"));

	axisY->setLinePenColor(ls_ping->pen().color());
	this->addAxis(axisY, Qt::AlignLeft);

	ls_ping->attachAxis(axisX);
	ls_ping->attachAxis(axisY);
}

QLineSeries& PingChart::getSeries() {
	return *(this->ls_ping);
}

void PingChart::append(const QPointF point) {
	qDebug() << "PingChart::append(" + QString::number(point.x()) + ", " + QString::number(point.y()) + ")> Point Added";
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

	if (x > xmax - xeps)
		xmax = x + xeps;

	// if it is the first point added or if the graph must be resized...
	else if (ls_ping->points().length() == 1 || y > ymax - yeps)
		ymax = y + yeps;

	axisX->setRange(xmin, xmax);
	axisY->setRange(ymin, ymax);
}

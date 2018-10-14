#include "pingchart.h"

PingChart::PingChart() : QChart() {
	ls_ping = new QLineSeries(this);

	xi = 0;

	this->legend()->show();
	this->addSeries(ls_ping);
	this->createDefaultAxes();
	this->setTitle(tr("Ping (ms)"));
}

QLineSeries& PingChart::getSeries() {
	return *(this->ls_ping);
}

void PingChart::append(const QPointF point) {
	qDebug() << "PingChart::append(" << QString::number(point.x()) << ", " << QString::number(point.y()) << ")> Point Added";
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

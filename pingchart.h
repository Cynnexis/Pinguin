#ifndef PINGCHART_H
#define PINGCHART_H

#include <iostream>
#include <QObject>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QDebug>

QT_CHARTS_USE_NAMESPACE
using namespace std;

class PingChart : public QChart
{
	Q_OBJECT

public:
	PingChart();

	QLineSeries& getSeries();

	void append(const QPointF point);
	void append(const qreal x, const qreal y);
	void append(const qreal y);

	PingChart& operator+=(const QPointF point);
	PingChart& operator+=(const qreal y);
	PingChart& operator<<(const QPointF point);
	PingChart& operator<<(const qreal y);

private:
	int xi;
	QLineSeries* ls_ping;
};

#endif // PINGCHART_H

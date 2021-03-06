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

#include "preferences.h"

QT_CHARTS_USE_NAMESPACE
using namespace std;

class PingChart : public QChart
{
	Q_OBJECT

public:
	PingChart();

	QLineSeries& getSeries();

	int getThreshold();
	void setThreshold(int threshold);

	void append(const QPointF point);
	void append(const qreal x, const qreal y);
	void append(const qreal y);

	PingChart& operator+=(const QPointF point);
	PingChart& operator+=(const qreal y);
	PingChart& operator<<(const QPointF point);
	PingChart& operator<<(const qreal y);

private:
	Preferences* pref;

	int xi;
	const int xeps = 1, yeps = 10;

	int xmin, xmax;
	int ymin, ymax;

	int xlimit = 15;

	int threshold = -1;

	QValueAxis* axisX;
	QValueAxis* axisY;
	QLineSeries* ls_ping;
	QLineSeries* ls_threshold;

private slots:
	void onPointAdded(int index);
	void onShowThresholdChanged(bool showThreshold);
	void onThresholdValueChanged(int thresholdValue);
	void onThresholdLabelChanged(QString thresholdLabel);
	void addThresholdPoint();
};

#endif // PINGCHART_H

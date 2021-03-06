#ifndef DSETTINGS_H
#define DSETTINGS_H

#include <QDialog>
#include <QSettings>

#include "ping.h"
#include "preferences.h"

namespace Ui {
	class DSettings;
}

class DSettings : public QDialog
{
	Q_OBJECT

public:
	explicit DSettings(QWidget *parent = nullptr);
	~DSettings();

private slots:
	void on_cb_showThreshold_toggled(bool checked);
	void on_sb_thresholdValue_editingFinished();
	void on_le_thresholdLabel_editingFinished();
	void on_le_host_editingFinished();
	void on_le_port_editingFinished();
	void on_pb_checkConnection_clicked();
	void on_sb_timeout_s_editingFinished();

	void on_pb_ok_clicked();

private:
	Ui::DSettings *ui;
	Preferences* pref;
};

#endif // DSETTINGS_H

#ifndef FLYSOFTGROUNDSTATION_H
#define FLYSOFTGROUNDSTATION_H

#include <QMainWindow>
#include <QString>
#include <QtCore/QDateTime>
#include <QtMqtt/QMqttClient>
#include <QtWidgets/QMessageBox>
#include "ui_flysoftgroundstation.h"

namespace Ui {
class FlysoftGroundStation;
}

class FlysoftGroundStation : public QMainWindow
{
    Q_OBJECT

public:
    explicit FlysoftGroundStation(QWidget *parent = nullptr);
    ~FlysoftGroundStation();

public slots:
    void setClientPort(int p);

private slots:
    void on_buttonConnect_clicked();
    void on_buttonQuit_clicked();
    void updateLogStateChange();
    void brokerDisconnected();
    void on_buttonPublish_clicked();
    void on_buttonSubscribe_clicked();

private:
    Ui::FlysoftGroundStation *ui;
    QMqttClient *m_client;
};
#endif // FLYSOFTGROUNDSTATION_H

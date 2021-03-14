#ifndef FLYSOFTMQTTADAPTER_H
#define FLYSOFTMQTTADAPTER_H

#include "flysoft_global.h"

class FlysoftMqttAdapter : public QObject{
    Q_OBJECT
public:
    explicit FlysoftMqttAdapter(QObject *parent = nullptr);
    bool setHostname(QString address);
    bool setPort(qint32 port);
private:

    QMqttClient *m_client;
    QString m_sSettingsFile;
    QString mqtt_address;
    quint16 mqtt_port;
    void loadSettings();
    void saveSettings();
    char log_msg[256];
    void topicSubscribe();

    void parseMessage(QString topic, QString message);
private slots:
    void brokerDisconnected();
    void tryMqttConnect();
    void stateChange();
    void tryMqttDisconnect();
    void messageReceived(QString topic, QString message);
    void brokerConnected();

signals:
    void pingResponseReceived(QString content);
    void notifyReceived(QString content);
    void mqttAdapterConnected();
    void mqttAdapterDisconnected();

};

#endif // FLYSOFTMQTTADAPTER_H

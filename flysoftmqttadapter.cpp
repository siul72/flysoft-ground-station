#include "flysoftmqttadapter.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

FlysoftMqttAdapter::FlysoftMqttAdapter(QObject *parent) : QObject(parent){
    m_client = new QMqttClient(this);

    m_sSettingsFile = QApplication::applicationDirPath().left(1) + "./settings.ini";
    loadSettings();
    this->m_client->setHostname(this->mqtt_address);
    this->m_client->setPort(this->mqtt_port);

    connect(m_client, &QMqttClient::stateChanged, this, &FlysoftMqttAdapter::stateChange);
    connect(m_client, &QMqttClient::connected, this, &FlysoftMqttAdapter::brokerConnected);
    connect(m_client, &QMqttClient::disconnected, this, &FlysoftMqttAdapter::brokerDisconnected);

    connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
        const QString my_topic = topic.name();
        const QString my_content = message;
        this->messageReceived(my_topic, my_content);
    });

    connect(m_client, &QMqttClient::pingResponseReceived, this, [this]() {
        const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(" PingResponse")
                    + QLatin1Char('\n');
        this->pingResponseReceived(content);
    });

    //trigger timer to connect
    QTimer::singleShot(10000, this, SLOT(tryMqttConnect()));

}

void FlysoftMqttAdapter::loadSettings() {
    bool ok;
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);
    this->mqtt_address = settings.value("mqtt_address", "127.0.0.1").toString();
    this->mqtt_port = settings.value("mqtt_port", "1883").toInt(&ok);
    if (!ok) {
        qDebug() << "not possible to get value";
    }

}

void FlysoftMqttAdapter::topicSubscribe() {
}

void FlysoftMqttAdapter::saveSettings() {

    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);
    settings.setValue("mqtt_address", this->mqtt_address);
    settings.setValue("mqtt_port", this->mqtt_port);


}

bool FlysoftMqttAdapter::setHostname(QString address){
    m_client->setHostname(address);
    return true;
}

bool FlysoftMqttAdapter::setPort(qint32 port){
    m_client->setPort(port);
    return true;
}

void FlysoftMqttAdapter::brokerConnected(){
    QMqttTopicFilter filter;
    filter.setFilter("#");

    auto subscription = m_client->subscribe(filter);
    if (!subscription) {
        qDebug() << "Could not subscribe. Is there a valid connection?";

    }

}

void FlysoftMqttAdapter::brokerDisconnected(){

}

void FlysoftMqttAdapter::tryMqttConnect(){
    if (m_client->state() == QMqttClient::Disconnected) {
        sprintf(log_msg, "Connecting to mqtt %s:%d",
                this->m_client->hostname().toStdString().c_str(), this->m_client->port());
        qInfo() << log_msg;
        m_client->connectToHost();
        emit mqttAdapterConnected();
    }
}

void FlysoftMqttAdapter::stateChange(){
    const QString content =QString("state change %1").arg(m_client->state());
    qDebug() << content;
}

void FlysoftMqttAdapter::messageReceived(QString topic, QString message){
    QString log_msg = QString("topic=%1 message=%2").arg(topic).arg(message);
    qDebug() << log_msg;

    this->parseMessage(topic, message);
}

void FlysoftMqttAdapter::parseMessage(QString topic , QString message){
    if (strcasecmp("flysoft/telemetry/mavlink", topic.toStdString().c_str()) == 0) {
        //deserialize message
        auto json_doc = QJsonDocument::fromJson(message.toUtf8());
        if (json_doc.isNull()) {
            qDebug() << "Failed to create JSON doc.";
            return;
        }

        if (!json_doc.isObject()) {
            qDebug() << "JSON is not an object."  ;
            return;
        }

        QJsonObject json_obj = json_doc.object();

        if (json_obj.isEmpty()) {
            qDebug() << "JSON object is empty." ;
            return;
        }
        //parse the mavlink message
        bool ok;
        uint32_t message_id = json_obj["msg_id"].toInt(&ok);
        if (!ok) {
            qDebug() << "messageId not int";
            return;

        }
        parseMessageId(message_id, json_obj);
    }
}

void FlysoftMqttAdapter::parseMessageId(uint32_t message_id, QJsonObject json_obj){
    QJsonObject data;
    switch (message_id) {
    case 30:
        qDebug() << "messageId 30:acc data";
        data = json_obj["attitude"];
        //get values and update objects
    break;
    default:
    break;
    }
}


void FlysoftMqttAdapter::tryMqttDisconnect(){
    if (m_client->state() == QMqttClient::Connected) {
           m_client->disconnectFromHost();
           emit mqttAdapterDisconnected();
       }

}

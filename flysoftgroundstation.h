#ifndef FLYSOFTGROUNDSTATION_H
#define FLYSOFTGROUNDSTATION_H
#include "flysoft_global.h"
#include "flysoftmqttadapter.h"
#include "configdialog.h"
#include "debugdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FlysoftGroundStation; }
QT_END_NAMESPACE

class FlysoftGroundStation : public QMainWindow{
    Q_OBJECT

public:
    FlysoftGroundStation(FlysoftMqttAdapter *con, QWidget *parent = nullptr);
    ~FlysoftGroundStation();


private:
    Ui::FlysoftGroundStation *ui;
    FlysoftMqttAdapter *m_mqttClient;
    ConfigDialog *configdialog;
    DebugDialog *debugdialog;

private slots:
    void onMenuActionConfig();
    void onMenuActionDebug();
};
#endif // FLYSOFTGROUNDSTATION_H

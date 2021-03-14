#include "flysoftgroundstation.h"
#include "ui_flysoftgroundstation.h"

FlysoftGroundStation::FlysoftGroundStation(FlysoftMqttAdapter *con, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::FlysoftGroundStation){
    ui->setupUi(this);
    m_mqttClient = con;
    connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(onMenuActionConfig()));
    connect(ui->actionDebug, SIGNAL(triggered()), this, SLOT(onMenuActionDebug()));
}

FlysoftGroundStation::~FlysoftGroundStation(){
    delete ui;
}

void FlysoftGroundStation::onMenuActionConfig(){
    this->configdialog = new ConfigDialog();
    this->configdialog->show();
}

void FlysoftGroundStation::onMenuActionDebug(){
    this->debugdialog = new DebugDialog();
    this->debugdialog->show();
}


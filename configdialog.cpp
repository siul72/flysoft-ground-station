#include "configdialog.h"
#include "ui_config_dialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog){
    ui->setupUi(this);

}

ConfigDialog::~ConfigDialog(){
    delete ui;
}

#include "properties.h"
#include "ui_properties.h"

Properties::Properties(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Properties)
{
    ui->setupUi(this);
}

Properties::~Properties()
{
    delete ui;
}

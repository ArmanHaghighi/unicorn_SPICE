#include "addelementdialog.h"
#include "ui_addelementdialog.h"

AddElementDialog::AddElementDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddElementDialog)
{
    ui->setupUi(this);
}

AddElementDialog::~AddElementDialog()
{
    delete ui;
}

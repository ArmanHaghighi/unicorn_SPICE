#include "phaseDialog.h"

phaseDialog::phaseDialog(QWidget* parent)
    : QDialog(parent),
    ui(new Ui::phaseDialog())
{
    ui->setupUi(this);
    setWindowTitle("Phase Sweep");
    connect(ui->okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

phaseDialog::~phaseDialog()
{
    delete ui;
}

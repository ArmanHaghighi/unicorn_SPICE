#include "TranDialog.h"

TranDialog::TranDialog(QWidget* parent)
    : QDialog(parent),
    ui(new Ui::TranDialog())
{
    ui->setupUi(this);
    setWindowTitle("Transient Analysis");
    connect(ui->okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    // connect(ui->okButton, &QPushButton::clicked, this, &TranDialog::accepted);
    // connect(ui->cancelButton, &QPushButton::clicked, this, &TranDialog::rejected);
}

TranDialog::~TranDialog()
{
    delete ui;
}

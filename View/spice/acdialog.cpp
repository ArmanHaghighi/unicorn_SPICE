#include "ACDialog.h"

ACDialog::ACDialog(QWidget* parent)
    : QDialog(parent),
    ui(new Ui::ACDialog())
{
    ui->setupUi(this);
    setWindowTitle("AC Sweep");
    connect(ui->okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

ACDialog::~ACDialog()
{
    delete ui;
}

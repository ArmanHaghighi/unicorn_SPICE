#include "DCDialog.h"

DCDialog::DCDialog(QWidget* parent)
    : QDialog(parent),
    ui(new Ui::DCDialog())
{
    ui->setupUi(this);
    setWindowTitle("DC Sweep");
    connect(ui->okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

DCDialog::~DCDialog()
{
    delete ui;
}

#pragma once
#include "ui_DCDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DCDialog; };
QT_END_NAMESPACE

class DCDialog : public QDialog
{
    Q_OBJECT
public:
    DCDialog(QWidget* parent = nullptr);
    ~DCDialog();

    Ui::DCDialog* ui;
};

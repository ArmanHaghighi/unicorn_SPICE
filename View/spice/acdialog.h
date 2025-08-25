#pragma once
#include "ui_ACDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ACDialog; };
QT_END_NAMESPACE

class ACDialog : public QDialog
{
    Q_OBJECT
public:
    ACDialog(QWidget* parent = nullptr);
    ~ACDialog();

    Ui::ACDialog* ui;
};

#pragma once
#include "ui_TranDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TranDialog; };
QT_END_NAMESPACE

class TranDialog : public QDialog
{
    Q_OBJECT
public:
    TranDialog(QWidget* parent = nullptr);
    ~TranDialog();

    Ui::TranDialog* ui;
};

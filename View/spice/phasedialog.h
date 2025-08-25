#pragma once
#include "ui_phaseDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class phaseDialog; };
QT_END_NAMESPACE

class phaseDialog : public QDialog
{
    Q_OBJECT
public:
    phaseDialog(QWidget* parent = nullptr);
    ~phaseDialog();

    Ui::phaseDialog* ui;
};

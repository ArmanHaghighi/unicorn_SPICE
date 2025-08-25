/********************************************************************************
** Form generated from reading UI file 'properties.ui'
**
** Created by: Qt User Interface Compiler version 5.15.17
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTIES_H
#define UI_PROPERTIES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_Properties
{
public:
    QGridLayout *gridLayout;
    QLineEdit *NameTxt;
    QLineEdit *ValTxt;
    QLabel *Value;
    QLabel *Name;
    QDialogButtonBox *buttonBox;
    QLabel *label;

    void setupUi(QDialog *Properties)
    {
        if (Properties->objectName().isEmpty())
            Properties->setObjectName(QString::fromUtf8("Properties"));
        Properties->resize(383, 182);
        gridLayout = new QGridLayout(Properties);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        NameTxt = new QLineEdit(Properties);
        NameTxt->setObjectName(QString::fromUtf8("NameTxt"));

        gridLayout->addWidget(NameTxt, 2, 0, 1, 1);

        ValTxt = new QLineEdit(Properties);
        ValTxt->setObjectName(QString::fromUtf8("ValTxt"));

        gridLayout->addWidget(ValTxt, 5, 0, 1, 1);

        Value = new QLabel(Properties);
        Value->setObjectName(QString::fromUtf8("Value"));

        gridLayout->addWidget(Value, 4, 0, 1, 1);

        Name = new QLabel(Properties);
        Name->setObjectName(QString::fromUtf8("Name"));

        gridLayout->addWidget(Name, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Properties);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Orientation::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        gridLayout->addWidget(buttonBox, 0, 1, 2, 1);

        label = new QLabel(Properties);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(Properties);
        QObject::connect(buttonBox, SIGNAL(accepted()), Properties, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Properties, SLOT(reject()));

        QMetaObject::connectSlotsByName(Properties);
    } // setupUi

    void retranslateUi(QDialog *Properties)
    {
        Properties->setWindowTitle(QCoreApplication::translate("Properties", "Dialog", nullptr));
        Value->setText(QCoreApplication::translate("Properties", "Value", nullptr));
        Name->setText(QCoreApplication::translate("Properties", "Name", nullptr));
        label->setText(QCoreApplication::translate("Properties", "Enter values for this element", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Properties: public Ui_Properties {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTIES_H

/********************************************************************************
** Form generated from reading UI file 'trandialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.17
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANDIALOG_H
#define UI_TRANDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TranDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *stopTime;
    QLineEdit *inputStop;
    QVBoxLayout *verticalLayout_2;
    QLabel *startTime;
    QLineEdit *inputStart;
    QVBoxLayout *verticalLayout_3;
    QLabel *maxTime;
    QLineEdit *inputStep;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *TranDialog)
    {
        if (TranDialog->objectName().isEmpty())
            TranDialog->setObjectName(QString::fromUtf8("TranDialog"));
        TranDialog->resize(600, 414);
        gridLayout = new QGridLayout(TranDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stopTime = new QLabel(TranDialog);
        stopTime->setObjectName(QString::fromUtf8("stopTime"));

        verticalLayout->addWidget(stopTime);

        inputStop = new QLineEdit(TranDialog);
        inputStop->setObjectName(QString::fromUtf8("inputStop"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(inputStop->sizePolicy().hasHeightForWidth());
        inputStop->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(inputStop);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        startTime = new QLabel(TranDialog);
        startTime->setObjectName(QString::fromUtf8("startTime"));

        verticalLayout_2->addWidget(startTime);

        inputStart = new QLineEdit(TranDialog);
        inputStart->setObjectName(QString::fromUtf8("inputStart"));
        sizePolicy.setHeightForWidth(inputStart->sizePolicy().hasHeightForWidth());
        inputStart->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(inputStart);


        gridLayout->addLayout(verticalLayout_2, 1, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        maxTime = new QLabel(TranDialog);
        maxTime->setObjectName(QString::fromUtf8("maxTime"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(maxTime->sizePolicy().hasHeightForWidth());
        maxTime->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(maxTime);

        inputStep = new QLineEdit(TranDialog);
        inputStep->setObjectName(QString::fromUtf8("inputStep"));
        sizePolicy.setHeightForWidth(inputStep->sizePolicy().hasHeightForWidth());
        inputStep->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(inputStep);


        gridLayout->addLayout(verticalLayout_3, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(239, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        okButton = new QPushButton(TranDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout_4->addWidget(okButton);

        cancelButton = new QPushButton(TranDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout_4->addWidget(cancelButton);


        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 1);


        retranslateUi(TranDialog);

        QMetaObject::connectSlotsByName(TranDialog);
    } // setupUi

    void retranslateUi(QDialog *TranDialog)
    {
        TranDialog->setWindowTitle(QCoreApplication::translate("TranDialog", "Dialog", nullptr));
        stopTime->setText(QCoreApplication::translate("TranDialog", "Stop Time:", nullptr));
        startTime->setText(QCoreApplication::translate("TranDialog", "Time to start saving data:", nullptr));
        maxTime->setText(QCoreApplication::translate("TranDialog", "Maximum timestep:", nullptr));
        okButton->setText(QCoreApplication::translate("TranDialog", "Ok", nullptr));
        cancelButton->setText(QCoreApplication::translate("TranDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TranDialog: public Ui_TranDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANDIALOG_H

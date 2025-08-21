/********************************************************************************
** Form generated from reading UI file 'phaseDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.17
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PHASEDIALOG_H
#define UI_PHASEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_phaseDialog
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLineEdit *iFreq;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLineEdit *iStartPhase;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_4;
    QLineEdit *iEndPhase;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_5;
    QLineEdit *iNumOfPts;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *phaseDialog)
    {
        if (phaseDialog->objectName().isEmpty())
            phaseDialog->setObjectName(QString::fromUtf8("phaseDialog"));
        phaseDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(phaseDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(phaseDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        iFreq = new QLineEdit(phaseDialog);
        iFreq->setObjectName(QString::fromUtf8("iFreq"));

        verticalLayout_2->addWidget(iFreq);


        verticalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(phaseDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_3->addWidget(label_3);

        iStartPhase = new QLineEdit(phaseDialog);
        iStartPhase->setObjectName(QString::fromUtf8("iStartPhase"));

        verticalLayout_3->addWidget(iStartPhase);


        verticalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_4 = new QLabel(phaseDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_4->addWidget(label_4);

        iEndPhase = new QLineEdit(phaseDialog);
        iEndPhase->setObjectName(QString::fromUtf8("iEndPhase"));

        verticalLayout_4->addWidget(iEndPhase);


        verticalLayout->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_5 = new QLabel(phaseDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_5->addWidget(label_5);

        iNumOfPts = new QLineEdit(phaseDialog);
        iNumOfPts->setObjectName(QString::fromUtf8("iNumOfPts"));

        verticalLayout_5->addWidget(iNumOfPts);


        verticalLayout->addLayout(verticalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(385, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(phaseDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(phaseDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(phaseDialog);

        QMetaObject::connectSlotsByName(phaseDialog);
    } // setupUi

    void retranslateUi(QDialog *phaseDialog)
    {
        phaseDialog->setWindowTitle(QCoreApplication::translate("phaseDialog", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("phaseDialog", "Base frequency:", nullptr));
        label_3->setText(QCoreApplication::translate("phaseDialog", "Start phase:", nullptr));
        label_4->setText(QCoreApplication::translate("phaseDialog", "End phase:", nullptr));
        label_5->setText(QCoreApplication::translate("phaseDialog", "Number of points:", nullptr));
        okButton->setText(QCoreApplication::translate("phaseDialog", "Ok", nullptr));
        cancelButton->setText(QCoreApplication::translate("phaseDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class phaseDialog: public Ui_phaseDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PHASEDIALOG_H

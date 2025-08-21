/********************************************************************************
** Form generated from reading UI file 'DCDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.17
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DCDIALOG_H
#define UI_DCDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DCDialog
{
public:
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QRadioButton *octave;
    QRadioButton *decade;
    QRadioButton *linear;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLineEdit *iStartVal;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLineEdit *iStopVal;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_5;
    QLineEdit *iIncrement;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *DCDialog)
    {
        if (DCDialog->objectName().isEmpty())
            DCDialog->setObjectName(QString::fromUtf8("DCDialog"));
        DCDialog->resize(400, 300);
        verticalLayout_5 = new QVBoxLayout(DCDialog);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_4 = new QLabel(DCDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        octave = new QRadioButton(DCDialog);
        octave->setObjectName(QString::fromUtf8("octave"));

        verticalLayout->addWidget(octave);

        decade = new QRadioButton(DCDialog);
        decade->setObjectName(QString::fromUtf8("decade"));

        verticalLayout->addWidget(decade);

        linear = new QRadioButton(DCDialog);
        linear->setObjectName(QString::fromUtf8("linear"));

        verticalLayout->addWidget(linear);


        verticalLayout_5->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(DCDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        iStartVal = new QLineEdit(DCDialog);
        iStartVal->setObjectName(QString::fromUtf8("iStartVal"));

        verticalLayout_2->addWidget(iStartVal);


        verticalLayout_5->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(DCDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_3->addWidget(label_3);

        iStopVal = new QLineEdit(DCDialog);
        iStopVal->setObjectName(QString::fromUtf8("iStopVal"));

        verticalLayout_3->addWidget(iStopVal);


        verticalLayout_5->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_5 = new QLabel(DCDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_4->addWidget(label_5);

        iIncrement = new QLineEdit(DCDialog);
        iIncrement->setObjectName(QString::fromUtf8("iIncrement"));

        verticalLayout_4->addWidget(iIncrement);


        verticalLayout_5->addLayout(verticalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(385, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(DCDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(DCDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        verticalLayout_5->addLayout(horizontalLayout);


        retranslateUi(DCDialog);

        QMetaObject::connectSlotsByName(DCDialog);
    } // setupUi

    void retranslateUi(QDialog *DCDialog)
    {
        DCDialog->setWindowTitle(QCoreApplication::translate("DCDialog", "Dialog", nullptr));
        label_4->setText(QCoreApplication::translate("DCDialog", "Type of sweep:", nullptr));
        octave->setText(QCoreApplication::translate("DCDialog", "Octave", nullptr));
        decade->setText(QCoreApplication::translate("DCDialog", "Decade", nullptr));
        linear->setText(QCoreApplication::translate("DCDialog", "Linear", nullptr));
        label_2->setText(QCoreApplication::translate("DCDialog", "Start value:", nullptr));
        label_3->setText(QCoreApplication::translate("DCDialog", "Stop value:", nullptr));
        label_5->setText(QCoreApplication::translate("DCDialog", "Increment:", nullptr));
        okButton->setText(QCoreApplication::translate("DCDialog", "Ok", nullptr));
        cancelButton->setText(QCoreApplication::translate("DCDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DCDialog: public Ui_DCDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DCDIALOG_H

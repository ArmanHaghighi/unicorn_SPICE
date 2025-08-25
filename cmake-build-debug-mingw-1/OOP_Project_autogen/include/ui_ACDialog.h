/********************************************************************************
** Form generated from reading UI file 'ACDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.17
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACDIALOG_H
#define UI_ACDIALOG_H

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

class Ui_ACDialog
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
    QLineEdit *istartFreq;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLineEdit *istopFreq;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QLineEdit *inumOfPts;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *ACDialog)
    {
        if (ACDialog->objectName().isEmpty())
            ACDialog->setObjectName(QString::fromUtf8("ACDialog"));
        ACDialog->resize(400, 300);
        verticalLayout_5 = new QVBoxLayout(ACDialog);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_4 = new QLabel(ACDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        octave = new QRadioButton(ACDialog);
        octave->setObjectName(QString::fromUtf8("octave"));

        verticalLayout->addWidget(octave);

        decade = new QRadioButton(ACDialog);
        decade->setObjectName(QString::fromUtf8("decade"));

        verticalLayout->addWidget(decade);

        linear = new QRadioButton(ACDialog);
        linear->setObjectName(QString::fromUtf8("linear"));

        verticalLayout->addWidget(linear);


        verticalLayout_5->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(ACDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        istartFreq = new QLineEdit(ACDialog);
        istartFreq->setObjectName(QString::fromUtf8("istartFreq"));

        verticalLayout_2->addWidget(istartFreq);


        verticalLayout_5->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(ACDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_3->addWidget(label_3);

        istopFreq = new QLineEdit(ACDialog);
        istopFreq->setObjectName(QString::fromUtf8("istopFreq"));

        verticalLayout_3->addWidget(istopFreq);


        verticalLayout_5->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label = new QLabel(ACDialog);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_4->addWidget(label);

        inumOfPts = new QLineEdit(ACDialog);
        inumOfPts->setObjectName(QString::fromUtf8("inumOfPts"));

        verticalLayout_4->addWidget(inumOfPts);


        verticalLayout_5->addLayout(verticalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(385, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(ACDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(ACDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        verticalLayout_5->addLayout(horizontalLayout);


        retranslateUi(ACDialog);

        QMetaObject::connectSlotsByName(ACDialog);
    } // setupUi

    void retranslateUi(QDialog *ACDialog)
    {
        ACDialog->setWindowTitle(QCoreApplication::translate("ACDialog", "Dialog", nullptr));
        label_4->setText(QCoreApplication::translate("ACDialog", "Type of sweep:", nullptr));
        octave->setText(QCoreApplication::translate("ACDialog", "Octave", nullptr));
        decade->setText(QCoreApplication::translate("ACDialog", "Decade", nullptr));
        linear->setText(QCoreApplication::translate("ACDialog", "Linear", nullptr));
        label_2->setText(QCoreApplication::translate("ACDialog", "Start frquency:", nullptr));
        label_3->setText(QCoreApplication::translate("ACDialog", "Stop frquency:", nullptr));
        label->setText(QCoreApplication::translate("ACDialog", "Number of points:", nullptr));
        okButton->setText(QCoreApplication::translate("ACDialog", "Ok", nullptr));
        cancelButton->setText(QCoreApplication::translate("ACDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ACDialog: public Ui_ACDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACDIALOG_H

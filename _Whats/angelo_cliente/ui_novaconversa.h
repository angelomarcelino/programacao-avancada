/********************************************************************************
** Form generated from reading UI file 'novaconversa.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOVACONVERSA_H
#define UI_NOVACONVERSA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_novaconversa
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *labelNovaconv;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *labelConv;
    QLineEdit *CorrespEdit;

    void setupUi(QDialog *novaconversa)
    {
        if (novaconversa->objectName().isEmpty())
            novaconversa->setObjectName(QStringLiteral("novaconversa"));
        novaconversa->resize(280, 180);
        buttonBox = new QDialogButtonBox(novaconversa);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(0, 120, 221, 41));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        labelNovaconv = new QLabel(novaconversa);
        labelNovaconv->setObjectName(QStringLiteral("labelNovaconv"));
        labelNovaconv->setGeometry(QRect(100, 30, 101, 16));
        widget = new QWidget(novaconversa);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 70, 261, 22));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        labelConv = new QLabel(widget);
        labelConv->setObjectName(QStringLiteral("labelConv"));

        horizontalLayout->addWidget(labelConv);

        CorrespEdit = new QLineEdit(widget);
        CorrespEdit->setObjectName(QStringLiteral("CorrespEdit"));

        horizontalLayout->addWidget(CorrespEdit);


        retranslateUi(novaconversa);
        QObject::connect(buttonBox, SIGNAL(accepted()), novaconversa, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), novaconversa, SLOT(reject()));

        QMetaObject::connectSlotsByName(novaconversa);
    } // setupUi

    void retranslateUi(QDialog *novaconversa)
    {
        novaconversa->setWindowTitle(QApplication::translate("novaconversa", "Nova Conversa", 0));
        labelNovaconv->setText(QApplication::translate("novaconversa", "NOVA CONVERSA", 0));
        labelConv->setText(QApplication::translate("novaconversa", "Correspondente:", 0));
    } // retranslateUi

};

namespace Ui {
    class novaconversa: public Ui_novaconversa {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOVACONVERSA_H

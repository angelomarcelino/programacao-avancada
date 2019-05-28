/********************************************************************************
** Form generated from reading UI file 'novocircuito.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOVOCIRCUITO_H
#define UI_NOVOCIRCUITO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_novoCircuito
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *in_label;
    QSpinBox *in_spinBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *out_label;
    QSpinBox *out_spinBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *portas_label;
    QSpinBox *portas_spinBox;

    void setupUi(QDialog *novoCircuito)
    {
        if (novoCircuito->objectName().isEmpty())
            novoCircuito->setObjectName(QStringLiteral("novoCircuito"));
        novoCircuito->resize(230, 200);
        buttonBox = new QDialogButtonBox(novoCircuito);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(40, 160, 156, 23));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        widget = new QWidget(novoCircuito);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 10, 191, 131));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        in_label = new QLabel(widget);
        in_label->setObjectName(QStringLiteral("in_label"));

        horizontalLayout->addWidget(in_label);

        in_spinBox = new QSpinBox(widget);
        in_spinBox->setObjectName(QStringLiteral("in_spinBox"));
        in_spinBox->setWrapping(true);

        horizontalLayout->addWidget(in_spinBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        out_label = new QLabel(widget);
        out_label->setObjectName(QStringLiteral("out_label"));

        horizontalLayout_4->addWidget(out_label);

        out_spinBox = new QSpinBox(widget);
        out_spinBox->setObjectName(QStringLiteral("out_spinBox"));
        out_spinBox->setWrapping(true);

        horizontalLayout_4->addWidget(out_spinBox);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        portas_label = new QLabel(widget);
        portas_label->setObjectName(QStringLiteral("portas_label"));

        horizontalLayout_5->addWidget(portas_label);

        portas_spinBox = new QSpinBox(widget);
        portas_spinBox->setObjectName(QStringLiteral("portas_spinBox"));
        portas_spinBox->setWrapping(true);

        horizontalLayout_5->addWidget(portas_spinBox);


        verticalLayout->addLayout(horizontalLayout_5);


        retranslateUi(novoCircuito);
        QObject::connect(buttonBox, SIGNAL(rejected()), novoCircuito, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), novoCircuito, SLOT(accept()));

        QMetaObject::connectSlotsByName(novoCircuito);
    } // setupUi

    void retranslateUi(QDialog *novoCircuito)
    {
        novoCircuito->setWindowTitle(QApplication::translate("novoCircuito", "Novo Circuito", 0));
        in_label->setText(QApplication::translate("novoCircuito", "N\303\272mero de Entradas:", 0));
        out_label->setText(QApplication::translate("novoCircuito", "N\303\272mero de Sa\303\255das:", 0));
        portas_label->setText(QApplication::translate("novoCircuito", "N\303\272mero de Portas:", 0));
    } // retranslateUi

};

namespace Ui {
    class novoCircuito: public Ui_novoCircuito {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOVOCIRCUITO_H

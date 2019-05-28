/********************************************************************************
** Form generated from reading UI file 'modificarsaida.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFICARSAIDA_H
#define UI_MODIFICARSAIDA_H

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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModificarSaida
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_SAIDA;
    QLabel *label_saidaN;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_id;
    QSpinBox *id_spinBox;

    void setupUi(QDialog *ModificarSaida)
    {
        if (ModificarSaida->objectName().isEmpty())
            ModificarSaida->setObjectName(QStringLiteral("ModificarSaida"));
        ModificarSaida->resize(232, 197);
        buttonBox = new QDialogButtonBox(ModificarSaida);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 150, 161, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(ModificarSaida);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 30, 171, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_SAIDA = new QLabel(layoutWidget);
        label_SAIDA->setObjectName(QStringLiteral("label_SAIDA"));

        horizontalLayout->addWidget(label_SAIDA);

        label_saidaN = new QLabel(layoutWidget);
        label_saidaN->setObjectName(QStringLiteral("label_saidaN"));

        horizontalLayout->addWidget(label_saidaN);

        layoutWidget1 = new QWidget(ModificarSaida);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(30, 80, 171, 51));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_id = new QLabel(layoutWidget1);
        label_id->setObjectName(QStringLiteral("label_id"));

        horizontalLayout_2->addWidget(label_id);

        id_spinBox = new QSpinBox(layoutWidget1);
        id_spinBox->setObjectName(QStringLiteral("id_spinBox"));
        id_spinBox->setWrapping(true);

        horizontalLayout_2->addWidget(id_spinBox);


        retranslateUi(ModificarSaida);
        QObject::connect(buttonBox, SIGNAL(accepted()), ModificarSaida, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ModificarSaida, SLOT(reject()));

        QMetaObject::connectSlotsByName(ModificarSaida);
    } // setupUi

    void retranslateUi(QDialog *ModificarSaida)
    {
        ModificarSaida->setWindowTitle(QApplication::translate("ModificarSaida", "Modificar Sa\303\255da", 0));
        label_SAIDA->setText(QApplication::translate("ModificarSaida", "SA\303\215DA:", 0));
        label_saidaN->setText(QApplication::translate("ModificarSaida", "TextLabel", 0));
        label_id->setText(QApplication::translate("ModificarSaida", "Id de origem:", 0));
    } // retranslateUi

};

namespace Ui {
    class ModificarSaida: public Ui_ModificarSaida {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFICARSAIDA_H

/********************************************************************************
** Form generated from reading UI file 'modificarporta.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFICARPORTA_H
#define UI_MODIFICARPORTA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModificarPorta
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label_portaN;
    QLabel *label_PORTA;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_tipo;
    QComboBox *tipo_comboBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_entr;
    QSpinBox *entrd_spinBox;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_id1;
    QSpinBox *id1_spinBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_id2;
    QSpinBox *id2_spinBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_id3;
    QSpinBox *id3_spinBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_id4;
    QSpinBox *id4_spinBox;

    void setupUi(QDialog *ModificarPorta)
    {
        if (ModificarPorta->objectName().isEmpty())
            ModificarPorta->setObjectName(QStringLiteral("ModificarPorta"));
        ModificarPorta->resize(280, 360);
        buttonBox = new QDialogButtonBox(ModificarPorta);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(-120, 320, 341, 31));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label_portaN = new QLabel(ModificarPorta);
        label_portaN->setObjectName(QStringLiteral("label_portaN"));
        label_portaN->setGeometry(QRect(157, 20, 120, 33));
        label_PORTA = new QLabel(ModificarPorta);
        label_PORTA->setObjectName(QStringLiteral("label_PORTA"));
        label_PORTA->setGeometry(QRect(30, 20, 121, 33));
        widget = new QWidget(ModificarPorta);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 60, 231, 261));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_tipo = new QLabel(widget);
        label_tipo->setObjectName(QStringLiteral("label_tipo"));

        horizontalLayout_2->addWidget(label_tipo);

        tipo_comboBox = new QComboBox(widget);
        tipo_comboBox->setObjectName(QStringLiteral("tipo_comboBox"));
        tipo_comboBox->setEditable(false);

        horizontalLayout_2->addWidget(tipo_comboBox);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_entr = new QLabel(widget);
        label_entr->setObjectName(QStringLiteral("label_entr"));

        horizontalLayout_3->addWidget(label_entr);

        entrd_spinBox = new QSpinBox(widget);
        entrd_spinBox->setObjectName(QStringLiteral("entrd_spinBox"));
        entrd_spinBox->setWrapping(true);
        entrd_spinBox->setMinimum(1);
        entrd_spinBox->setMaximum(4);
        entrd_spinBox->setValue(1);

        horizontalLayout_3->addWidget(entrd_spinBox);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_id1 = new QLabel(widget);
        label_id1->setObjectName(QStringLiteral("label_id1"));

        horizontalLayout_7->addWidget(label_id1);

        id1_spinBox = new QSpinBox(widget);
        id1_spinBox->setObjectName(QStringLiteral("id1_spinBox"));
        id1_spinBox->setWrapping(true);

        horizontalLayout_7->addWidget(id1_spinBox);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_id2 = new QLabel(widget);
        label_id2->setObjectName(QStringLiteral("label_id2"));

        horizontalLayout_4->addWidget(label_id2);

        id2_spinBox = new QSpinBox(widget);
        id2_spinBox->setObjectName(QStringLiteral("id2_spinBox"));
        id2_spinBox->setWrapping(true);

        horizontalLayout_4->addWidget(id2_spinBox);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_id3 = new QLabel(widget);
        label_id3->setObjectName(QStringLiteral("label_id3"));

        horizontalLayout_6->addWidget(label_id3);

        id3_spinBox = new QSpinBox(widget);
        id3_spinBox->setObjectName(QStringLiteral("id3_spinBox"));
        id3_spinBox->setWrapping(true);

        horizontalLayout_6->addWidget(id3_spinBox);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_id4 = new QLabel(widget);
        label_id4->setObjectName(QStringLiteral("label_id4"));

        horizontalLayout_5->addWidget(label_id4);

        id4_spinBox = new QSpinBox(widget);
        id4_spinBox->setObjectName(QStringLiteral("id4_spinBox"));
        id4_spinBox->setWrapping(true);

        horizontalLayout_5->addWidget(id4_spinBox);


        verticalLayout->addLayout(horizontalLayout_5);


        retranslateUi(ModificarPorta);
        QObject::connect(buttonBox, SIGNAL(accepted()), ModificarPorta, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ModificarPorta, SLOT(reject()));

        QMetaObject::connectSlotsByName(ModificarPorta);
    } // setupUi

    void retranslateUi(QDialog *ModificarPorta)
    {
        ModificarPorta->setWindowTitle(QApplication::translate("ModificarPorta", "Modificar Porta", 0));
        label_portaN->setText(QApplication::translate("ModificarPorta", "text", 0));
        label_PORTA->setText(QApplication::translate("ModificarPorta", "PORTA:", 0));
        label_tipo->setText(QApplication::translate("ModificarPorta", "Tipo da porta:", 0));
        tipo_comboBox->setCurrentText(QString());
        label_entr->setText(QApplication::translate("ModificarPorta", "N\302\272 de entradas:", 0));
        label_id1->setText(QApplication::translate("ModificarPorta", "Id da entrada 1:", 0));
        label_id2->setText(QApplication::translate("ModificarPorta", "Id da entrada 2:", 0));
        label_id3->setText(QApplication::translate("ModificarPorta", "Id da entrada 3:", 0));
        label_id4->setText(QApplication::translate("ModificarPorta", "Id da entrada 4:", 0));
    } // retranslateUi

};

namespace Ui {
    class ModificarPorta: public Ui_ModificarPorta {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFICARPORTA_H

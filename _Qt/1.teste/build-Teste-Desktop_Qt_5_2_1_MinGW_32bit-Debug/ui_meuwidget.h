/********************************************************************************
** Form generated from reading UI file 'meuwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEUWIDGET_H
#define UI_MEUWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MeuWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *labelLinha;
    QLineEdit *lineEdit;

    void setupUi(QWidget *MeuWidget)
    {
        if (MeuWidget->objectName().isEmpty())
            MeuWidget->setObjectName(QStringLiteral("MeuWidget"));
        MeuWidget->resize(480, 360);
        horizontalLayout = new QHBoxLayout(MeuWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelLinha = new QLabel(MeuWidget);
        labelLinha->setObjectName(QStringLiteral("labelLinha"));

        horizontalLayout->addWidget(labelLinha);

        lineEdit = new QLineEdit(MeuWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        retranslateUi(MeuWidget);

        QMetaObject::connectSlotsByName(MeuWidget);
    } // setupUi

    void retranslateUi(QWidget *MeuWidget)
    {
        MeuWidget->setWindowTitle(QApplication::translate("MeuWidget", "MeuWidget", 0));
        labelLinha->setText(QApplication::translate("MeuWidget", "Meu Nome: ", 0));
    } // retranslateUi

};

namespace Ui {
    class MeuWidget: public Ui_MeuWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEUWIDGET_H

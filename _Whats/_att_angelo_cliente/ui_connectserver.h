/********************************************************************************
** Form generated from reading UI file 'connectserver.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTSERVER_H
#define UI_CONNECTSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_connectServer
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *servLabel;
    QLineEdit *servEdit;
    QLabel *logLabel;
    QLineEdit *logEdit;
    QLabel *passLabel;
    QLineEdit *passEdit;
    QPushButton *cadastrarButton;

    void setupUi(QDialog *connectServer)
    {
        if (connectServer->objectName().isEmpty())
            connectServer->setObjectName(QStringLiteral("connectServer"));
        connectServer->resize(300, 220);
        buttonBox = new QDialogButtonBox(connectServer);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(110, 180, 160, 30));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        servLabel = new QLabel(connectServer);
        servLabel->setObjectName(QStringLiteral("servLabel"));
        servLabel->setGeometry(QRect(30, 40, 61, 21));
        servEdit = new QLineEdit(connectServer);
        servEdit->setObjectName(QStringLiteral("servEdit"));
        servEdit->setGeometry(QRect(100, 40, 170, 20));
        logLabel = new QLabel(connectServer);
        logLabel->setObjectName(QStringLiteral("logLabel"));
        logLabel->setGeometry(QRect(30, 90, 61, 21));
        logEdit = new QLineEdit(connectServer);
        logEdit->setObjectName(QStringLiteral("logEdit"));
        logEdit->setGeometry(QRect(100, 90, 170, 20));
        passLabel = new QLabel(connectServer);
        passLabel->setObjectName(QStringLiteral("passLabel"));
        passLabel->setGeometry(QRect(30, 120, 61, 21));
        passEdit = new QLineEdit(connectServer);
        passEdit->setObjectName(QStringLiteral("passEdit"));
        passEdit->setGeometry(QRect(100, 120, 170, 20));
        cadastrarButton = new QPushButton(connectServer);
        cadastrarButton->setObjectName(QStringLiteral("cadastrarButton"));
        cadastrarButton->setGeometry(QRect(30, 183, 75, 23));

        retranslateUi(connectServer);
        QObject::connect(buttonBox, SIGNAL(accepted()), connectServer, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), connectServer, SLOT(reject()));

        QMetaObject::connectSlotsByName(connectServer);
    } // setupUi

    void retranslateUi(QDialog *connectServer)
    {
        connectServer->setWindowTitle(QApplication::translate("connectServer", "Conectar \303\240 um servidor", 0));
#ifndef QT_NO_TOOLTIP
        connectServer->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        connectServer->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_ACCESSIBILITY
        connectServer->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
        servLabel->setText(QApplication::translate("connectServer", "SERVIDOR:", 0));
        logLabel->setText(QApplication::translate("connectServer", "LOGIN:", 0));
        passLabel->setText(QApplication::translate("connectServer", "SENHA:", 0));
        cadastrarButton->setText(QApplication::translate("connectServer", "Cadastrar", 0));
    } // retranslateUi

};

namespace Ui {
    class connectServer: public Ui_connectServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTSERVER_H

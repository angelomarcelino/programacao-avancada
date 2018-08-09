/********************************************************************************
** Form generated from reading UI file 'whatsclient.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WHATSCLIENT_H
#define UI_WHATSCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WhatsClient
{
public:
    QAction *actionConectar;
    QAction *actionDesconectar;
    QAction *actionSair;
    QAction *actionNovaConv;
    QAction *actionApagar;
    QWidget *centralWidget;
    QLabel *msgLabel;
    QLineEdit *msgEdit;
    QPushButton *enviarButton;
    QTableWidget *conversasTable;
    QTableWidget *msgsTable;
    QMenuBar *menuBar;
    QMenu *menuConex_o;
    QMenu *menuConversas;
    QMenu *menuMensagens;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WhatsClient)
    {
        if (WhatsClient->objectName().isEmpty())
            WhatsClient->setObjectName(QStringLiteral("WhatsClient"));
        WhatsClient->resize(800, 600);
        actionConectar = new QAction(WhatsClient);
        actionConectar->setObjectName(QStringLiteral("actionConectar"));
        actionDesconectar = new QAction(WhatsClient);
        actionDesconectar->setObjectName(QStringLiteral("actionDesconectar"));
        actionSair = new QAction(WhatsClient);
        actionSair->setObjectName(QStringLiteral("actionSair"));
        actionNovaConv = new QAction(WhatsClient);
        actionNovaConv->setObjectName(QStringLiteral("actionNovaConv"));
        actionApagar = new QAction(WhatsClient);
        actionApagar->setObjectName(QStringLiteral("actionApagar"));
        centralWidget = new QWidget(WhatsClient);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        msgLabel = new QLabel(centralWidget);
        msgLabel->setObjectName(QStringLiteral("msgLabel"));
        msgLabel->setGeometry(QRect(10, 530, 59, 16));
        msgEdit = new QLineEdit(centralWidget);
        msgEdit->setObjectName(QStringLiteral("msgEdit"));
        msgEdit->setGeometry(QRect(70, 530, 640, 20));
        enviarButton = new QPushButton(centralWidget);
        enviarButton->setObjectName(QStringLiteral("enviarButton"));
        enviarButton->setGeometry(QRect(720, 527, 70, 25));
        conversasTable = new QTableWidget(centralWidget);
        if (conversasTable->columnCount() < 2)
            conversasTable->setColumnCount(2);
        conversasTable->setObjectName(QStringLiteral("conversasTable"));
        conversasTable->setGeometry(QRect(10, 10, 240, 510));
        conversasTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        conversasTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        conversasTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        conversasTable->setTabKeyNavigation(false);
        conversasTable->setAlternatingRowColors(true);
        conversasTable->setSelectionMode(QAbstractItemView::NoSelection);
        conversasTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        conversasTable->setColumnCount(2);
        conversasTable->horizontalHeader()->setDefaultSectionSize(50);
        conversasTable->horizontalHeader()->setMinimumSectionSize(50);
        conversasTable->horizontalHeader()->setStretchLastSection(true);
        conversasTable->verticalHeader()->setVisible(false);
        msgsTable = new QTableWidget(centralWidget);
        if (msgsTable->columnCount() < 2)
            msgsTable->setColumnCount(2);
        msgsTable->setObjectName(QStringLiteral("msgsTable"));
        msgsTable->setGeometry(QRect(260, 10, 530, 510));
        msgsTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        msgsTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        msgsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        msgsTable->setTabKeyNavigation(false);
        msgsTable->setSelectionMode(QAbstractItemView::NoSelection);
        msgsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        msgsTable->setColumnCount(2);
        msgsTable->horizontalHeader()->setCascadingSectionResizes(false);
        msgsTable->horizontalHeader()->setMinimumSectionSize(50);
        msgsTable->horizontalHeader()->setStretchLastSection(true);
        msgsTable->verticalHeader()->setVisible(false);
        WhatsClient->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WhatsClient);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuConex_o = new QMenu(menuBar);
        menuConex_o->setObjectName(QStringLiteral("menuConex_o"));
        menuConversas = new QMenu(menuBar);
        menuConversas->setObjectName(QStringLiteral("menuConversas"));
        menuMensagens = new QMenu(menuBar);
        menuMensagens->setObjectName(QStringLiteral("menuMensagens"));
        WhatsClient->setMenuBar(menuBar);
        statusBar = new QStatusBar(WhatsClient);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        WhatsClient->setStatusBar(statusBar);

        menuBar->addAction(menuConex_o->menuAction());
        menuBar->addAction(menuConversas->menuAction());
        menuBar->addAction(menuMensagens->menuAction());
        menuConex_o->addAction(actionConectar);
        menuConex_o->addAction(actionDesconectar);
        menuConex_o->addSeparator();
        menuConex_o->addAction(actionSair);
        menuConversas->addAction(actionNovaConv);
        menuMensagens->addAction(actionApagar);

        retranslateUi(WhatsClient);

        QMetaObject::connectSlotsByName(WhatsClient);
    } // setupUi

    void retranslateUi(QMainWindow *WhatsClient)
    {
        WhatsClient->setWindowTitle(QApplication::translate("WhatsClient", "Cliente WhatsProg", 0));
        actionConectar->setText(QApplication::translate("WhatsClient", "Conectar...", 0));
        actionDesconectar->setText(QApplication::translate("WhatsClient", "Desconectar", 0));
        actionSair->setText(QApplication::translate("WhatsClient", "Sair", 0));
        actionNovaConv->setText(QApplication::translate("WhatsClient", "Nova Conversa...", 0));
        actionApagar->setText(QApplication::translate("WhatsClient", "Apagar", 0));
        msgLabel->setText(QApplication::translate("WhatsClient", "MENSAGEM:", 0));
        enviarButton->setText(QApplication::translate("WhatsClient", "ENVIAR", 0));
        menuConex_o->setTitle(QApplication::translate("WhatsClient", "Conex\303\243o", 0));
        menuConversas->setTitle(QApplication::translate("WhatsClient", "Conversas", 0));
        menuMensagens->setTitle(QApplication::translate("WhatsClient", "Mensagens", 0));
    } // retranslateUi

};

namespace Ui {
    class WhatsClient: public Ui_WhatsClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WHATSCLIENT_H

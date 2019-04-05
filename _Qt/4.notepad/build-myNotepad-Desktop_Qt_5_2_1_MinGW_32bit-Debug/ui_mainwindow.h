/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSalvar;
    QAction *actionSair;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *editor;
    QPushButton *SairButton;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuArquivo;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        actionSalvar = new QAction(MainWindow);
        actionSalvar->setObjectName(QStringLiteral("actionSalvar"));
        actionSair = new QAction(MainWindow);
        actionSair->setObjectName(QStringLiteral("actionSair"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        editor = new QTextEdit(centralWidget);
        editor->setObjectName(QStringLiteral("editor"));

        verticalLayout->addWidget(editor);

        SairButton = new QPushButton(centralWidget);
        SairButton->setObjectName(QStringLiteral("SairButton"));

        verticalLayout->addWidget(SairButton);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        menuArquivo = new QMenu(menuBar);
        menuArquivo->setObjectName(QStringLiteral("menuArquivo"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuArquivo->menuAction());
        menuArquivo->addAction(actionSalvar);
        menuArquivo->addSeparator();
        menuArquivo->addAction(actionSair);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionSalvar->setText(QApplication::translate("MainWindow", "Salvar", 0));
        actionSair->setText(QApplication::translate("MainWindow", "Sair", 0));
        SairButton->setText(QApplication::translate("MainWindow", "Sair", 0));
        menuArquivo->setTitle(QApplication::translate("MainWindow", "Arquivo", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

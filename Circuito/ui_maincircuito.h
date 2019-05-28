/********************************************************************************
** Form generated from reading UI file 'maincircuito.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINCIRCUITO_H
#define UI_MAINCIRCUITO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainCircuito
{
public:
    QAction *actionNovo;
    QAction *actionLer;
    QAction *actionSalvar;
    QAction *actionSair;
    QAction *actionGerar_Tabela;
    QWidget *centralWidget;
    QLabel *label_cir;
    QLabel *label_tv;
    QLabel *label_port;
    QLabel *label_saidas;
    QTableWidget *tab_port;
    QTableWidget *tab_saidas;
    QTableWidget *tab_tv;
    QMenuBar *menuBar;
    QMenu *menuCircuito;
    QMenu *menuSimular;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainCircuito)
    {
        if (MainCircuito->objectName().isEmpty())
            MainCircuito->setObjectName(QStringLiteral("MainCircuito"));
        MainCircuito->resize(780, 630);
        actionNovo = new QAction(MainCircuito);
        actionNovo->setObjectName(QStringLiteral("actionNovo"));
        actionLer = new QAction(MainCircuito);
        actionLer->setObjectName(QStringLiteral("actionLer"));
        actionSalvar = new QAction(MainCircuito);
        actionSalvar->setObjectName(QStringLiteral("actionSalvar"));
        actionSair = new QAction(MainCircuito);
        actionSair->setObjectName(QStringLiteral("actionSair"));
        actionGerar_Tabela = new QAction(MainCircuito);
        actionGerar_Tabela->setObjectName(QStringLiteral("actionGerar_Tabela"));
        centralWidget = new QWidget(MainCircuito);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_cir = new QLabel(centralWidget);
        label_cir->setObjectName(QStringLiteral("label_cir"));
        label_cir->setGeometry(QRect(0, 0, 385, 30));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_cir->setFont(font);
        label_cir->setFrameShape(QFrame::Box);
        label_cir->setAlignment(Qt::AlignCenter);
        label_tv = new QLabel(centralWidget);
        label_tv->setObjectName(QStringLiteral("label_tv"));
        label_tv->setGeometry(QRect(395, 0, 385, 30));
        label_tv->setFont(font);
        label_tv->setFrameShape(QFrame::Box);
        label_tv->setTextFormat(Qt::RichText);
        label_tv->setScaledContents(true);
        label_tv->setAlignment(Qt::AlignCenter);
        label_port = new QLabel(centralWidget);
        label_port->setObjectName(QStringLiteral("label_port"));
        label_port->setGeometry(QRect(0, 30, 291, 30));
        label_port->setFont(font);
        label_port->setFrameShape(QFrame::Box);
        label_port->setAlignment(Qt::AlignCenter);
        label_saidas = new QLabel(centralWidget);
        label_saidas->setObjectName(QStringLiteral("label_saidas"));
        label_saidas->setGeometry(QRect(290, 30, 95, 30));
        label_saidas->setFont(font);
        label_saidas->setFrameShape(QFrame::Box);
        label_saidas->setAlignment(Qt::AlignCenter);
        tab_port = new QTableWidget(centralWidget);
        if (tab_port->columnCount() < 6)
            tab_port->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tab_port->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tab_port->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tab_port->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tab_port->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tab_port->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tab_port->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tab_port->setObjectName(QStringLiteral("tab_port"));
        tab_port->setGeometry(QRect(0, 60, 291, 525));
        tab_port->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tab_port->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tab_port->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tab_port->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tab_port->setTabKeyNavigation(false);
        tab_port->setAlternatingRowColors(true);
        tab_port->setSelectionMode(QAbstractItemView::SingleSelection);
        tab_port->setSelectionBehavior(QAbstractItemView::SelectRows);
        tab_port->setRowCount(0);
        tab_port->horizontalHeader()->setCascadingSectionResizes(false);
        tab_port->horizontalHeader()->setDefaultSectionSize(42);
        tab_port->horizontalHeader()->setHighlightSections(false);
        tab_port->horizontalHeader()->setMinimumSectionSize(42);
        tab_port->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tab_port->horizontalHeader()->setStretchLastSection(true);
        tab_port->verticalHeader()->setVisible(false);
        tab_port->verticalHeader()->setMinimumSectionSize(30);
        tab_saidas = new QTableWidget(centralWidget);
        if (tab_saidas->columnCount() < 1)
            tab_saidas->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tab_saidas->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        tab_saidas->setObjectName(QStringLiteral("tab_saidas"));
        tab_saidas->setGeometry(QRect(290, 60, 95, 525));
        tab_saidas->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tab_saidas->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tab_saidas->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tab_saidas->setTabKeyNavigation(false);
        tab_saidas->setAlternatingRowColors(true);
        tab_saidas->setSelectionMode(QAbstractItemView::SingleSelection);
        tab_saidas->setSelectionBehavior(QAbstractItemView::SelectRows);
        tab_saidas->horizontalHeader()->setDefaultSectionSize(48);
        tab_saidas->horizontalHeader()->setHighlightSections(false);
        tab_saidas->horizontalHeader()->setStretchLastSection(true);
        tab_tv = new QTableWidget(centralWidget);
        tab_tv->setObjectName(QStringLiteral("tab_tv"));
        tab_tv->setGeometry(QRect(395, 30, 385, 555));
        tab_tv->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tab_tv->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tab_tv->setTabKeyNavigation(false);
        tab_tv->setAlternatingRowColors(true);
        tab_tv->setSelectionMode(QAbstractItemView::NoSelection);
        tab_tv->setSelectionBehavior(QAbstractItemView::SelectItems);
        tab_tv->horizontalHeader()->setVisible(false);
        tab_tv->horizontalHeader()->setDefaultSectionSize(40);
        tab_tv->horizontalHeader()->setHighlightSections(false);
        tab_tv->horizontalHeader()->setMinimumSectionSize(40);
        tab_tv->verticalHeader()->setVisible(false);
        tab_tv->verticalHeader()->setHighlightSections(false);
        MainCircuito->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainCircuito);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 780, 21));
        menuCircuito = new QMenu(menuBar);
        menuCircuito->setObjectName(QStringLiteral("menuCircuito"));
        menuSimular = new QMenu(menuBar);
        menuSimular->setObjectName(QStringLiteral("menuSimular"));
        MainCircuito->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainCircuito);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainCircuito->setStatusBar(statusBar);

        menuBar->addAction(menuCircuito->menuAction());
        menuBar->addAction(menuSimular->menuAction());
        menuCircuito->addAction(actionNovo);
        menuCircuito->addAction(actionLer);
        menuCircuito->addAction(actionSalvar);
        menuCircuito->addSeparator();
        menuCircuito->addAction(actionSair);
        menuSimular->addAction(actionGerar_Tabela);

        retranslateUi(MainCircuito);

        QMetaObject::connectSlotsByName(MainCircuito);
    } // setupUi

    void retranslateUi(QMainWindow *MainCircuito)
    {
        MainCircuito->setWindowTitle(QApplication::translate("MainCircuito", "Simulador de Circuitos Digitais", 0));
        actionNovo->setText(QApplication::translate("MainCircuito", "Novo...", 0));
        actionLer->setText(QApplication::translate("MainCircuito", "Ler...", 0));
        actionSalvar->setText(QApplication::translate("MainCircuito", "Salvar...", 0));
        actionSair->setText(QApplication::translate("MainCircuito", "Sair", 0));
        actionGerar_Tabela->setText(QApplication::translate("MainCircuito", "Gerar Tabela", 0));
        label_cir->setText(QApplication::translate("MainCircuito", "CIRCUITOS", 0));
        label_tv->setText(QApplication::translate("MainCircuito", "TABELA VERDADE", 0));
        label_port->setText(QApplication::translate("MainCircuito", "PORTAS E CONEX\303\225ES", 0));
        label_saidas->setText(QApplication::translate("MainCircuito", "SAIDAS", 0));
        QTableWidgetItem *___qtablewidgetitem = tab_port->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainCircuito", "TIPO", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tab_port->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainCircuito", " #\n"
"INPUT", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tab_port->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainCircuito", " IN\n"
" #1", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tab_port->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainCircuito", " IN\n"
" #2", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tab_port->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainCircuito", " IN\n"
" #3", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tab_port->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainCircuito", " IN\n"
" #4", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tab_saidas->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("MainCircuito", "OUT\n"
"FROM", 0));
        menuCircuito->setTitle(QApplication::translate("MainCircuito", "Circuito", 0));
        menuSimular->setTitle(QApplication::translate("MainCircuito", "Simular", 0));
    } // retranslateUi

};

namespace Ui {
    class MainCircuito: public Ui_MainCircuito {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINCIRCUITO_H

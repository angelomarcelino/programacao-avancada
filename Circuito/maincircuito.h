#ifndef MAINCIRCUITO_H
#define MAINCIRCUITO_H

#include <QMainWindow>
#include "circuito.h"
#include "novocircuito.h"
#include "modificarporta.h"
#include "modificarsaida.h"

namespace Ui {
class MainCircuito;
}

class MainCircuito : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainCircuito(QWidget *parent = 0);
    ~MainCircuito();

    void redimensionar_tabelas();
    void exibir_porta(unsigned i);
    void exibir_saida(unsigned i);
    void exibir_tv();

    void exibir_erro(QString mensagem);

    void imprimirEntradas(int i);
    void imprimirSaidas(int i);

private slots:
    void on_actionLer_triggered();

    void on_actionGerar_Tabela_triggered();

    void on_actionSalvar_triggered();

    void on_actionSair_triggered();

    void on_actionNovo_triggered();

    void on_tab_port_cellDoubleClicked(int row, int column);

    void on_tab_saidas_cellDoubleClicked(int row, int column);

private:
    Ui::MainCircuito *ui;
    novoCircuito NovoCircuito;
    ModificarPorta ModPorta;
    ModificarSaida ModSaida;

};

#endif // MAINCIRCUITO_H

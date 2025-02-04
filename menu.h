#ifndef MENU_H
#define MENU_H
//#include <string.h>
// #include <iostream>

class Menu
{

private:

    void novoJogo();
    void continuarJogo();
    void estatisticas();
    void top10();
    int escolhaSair;

public:
    Menu();
    void imprimirMenu();
    int modo();
    int dificuldade();
    int dificuldade2();
    void sairMenu();

    int escolha;
    int opcaoMenu;
    bool continuarSalvo;
    int escolhaModo;
    int escolhaJogo;
    int escolhaJogo2;
};
#endif // MENU_H

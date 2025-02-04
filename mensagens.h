#ifndef MENSAGENS_H
#define MENSAGENS_H

class mensagens {
public:
    mensagens();

    void opcaoInvalida();
    void entradaInvalida();

    void venceu();
    void empatou();
    void perdeu();

    void Fim();

    void Menu();
    void Modo();
    void Dificuldade();

    void temCerteza();
    void getEscolha();

    // linhas
    void LinhaS(); // Small
    void LinhaM(); // Medium
    void LinhaL(); // Large

    void inicio();

    int escolha;
private:

};

#endif // MENSAGENS_H

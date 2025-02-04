#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>

class Jogo
{
private:
    int posicao;
    char casas[10];
    void desenharTabuleiro(int i);
    void numTabuleiro(int i);
    void turnos(int &jogaprimeiro);
    int espacosEmFalta(int &espacos);
    bool verificarVitoria();
    bool verificarEmpate();
    void jogadaHumano(bool play2);
    void jogadaBotLevel1(bool bot2);
    void jogadaBotLevel2(bool bot2);
    void jogadaBotLevel3(bool bot2);
    void jogadaBotLevel4(bool bot2);
    int minimax(char move[10], int profundidade, bool maxplayer, bool bot2);
    bool fimdejogo();
    char vervencedorMinimax(char espaco[]);
    void imprimirTabuleiros();
    void imprimirlado();

    void computadorVsComputador();
    void pcJoga();
    void pcDefende();
    void humanoJoga();
    void pcAtaca();
    std::vector<std::string> separarlinhas(const std::string& str);

    struct Jogadores{
        char humano;
        char bot;
        char bot2;
        char vazio='-';
    };
    Jogadores jogadores;

public:

    Jogo();
    void funcionamentoJogo(std::string name);
    bool sair();
    void limpar();
    void comecarNovamente(int &jogaprimeiro);



    std::string NAME;
    std::string texto;
    std::string tabtex[10];
    std::size_t tamtabtex;
    int val;
    int movimento;
    int jogaPrimeiro;
};

#endif // GAME_H

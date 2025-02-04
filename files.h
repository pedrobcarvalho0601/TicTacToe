#ifndef FILES_H
#define FILES_H
#include <string>




class CNoLista{
public:

    std::string dados;
    int pontuacao;

    CNoLista *proximo;
}; // fim de class CNoLista


class CListaInteiros{
    int opcao;
    CNoLista *cabeca;

public:

    struct Dados{
        int vitorias=0;
        int empates=0;
        int derrotas=0;
    };
    Dados Dados;

    int scoreExistente;
    std::string nome;

    CListaInteiros(void);
    ~CListaInteiros(void);

    CListaInteiros(char *str);

    std::string ultimoValor();
    int maioresQue(std::string);
    void insereItem(std::string, int score);
    void ordenaTop();
    void apagaItem(std::string);
    bool procuraItem(std::string) const;
    void escreveLista(void) const;
    void escreveLista10(void) const;
    void carregarEstatisticas();
    void imprimirEstatisticas();
    void carregaDados(const char*);
    void limparEstatisticas();
    std::string solicitarUsername();
    void bemVindo();
    int obterScore(std::string item) const;
    void atualizarPontuacao(std::string item, int novaPontuacao);
    void salvarJogo(char tabuleiro[9]);
    void carregarJogo(char tabuleiro[9]);
    void contadorResultados(/*int vitorias, int derrotas, int empates,*/ int pontos, std::string item);
    void imprimirResultados();

}; // fim de class CListaInteiros


#endif // FILES_H

#include "files.h"
#include "mensagens.h"
#include "menu.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h> // Para _getch() -> Caracteres invisiveis
#include <utilapiset.h>
#include <Windows.h>
#include <mmsystem.h>

using namespace std;

CListaInteiros::CListaInteiros(){ // Construtor por omissao
    cabeca = nullptr;
}

CListaInteiros::~CListaInteiros(){
    CNoLista *atual, *proximo;

    atual=cabeca;
    while (atual != nullptr){
        proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
}

void CListaInteiros::insereItem(string item, int score){
    CNoLista *atual = cabeca;

    while (atual != nullptr) {
        if (atual->dados == item) {
            // Se o nome já existe, atualiza a pontuação
            atual->pontuacao = score;
            return; // Sai da função após atualizar a pontuação
        }
        atual = atual->proximo;
    }

    CNoLista *novo = new CNoLista;

    novo->dados = item;
    novo->pontuacao = score;
    novo->proximo = nullptr;

    if(cabeca == nullptr){
        cabeca=novo;
    }else{
        atual = cabeca;
        while (atual->proximo != nullptr)
            atual = atual->proximo;
        atual->proximo = novo;
    }
}

void CListaInteiros::ordenaTop(){
    CNoLista *atual;
    CNoLista *proximo;
    string tempNome;
    int tempPontuacao;

    if (cabeca == nullptr)
        return;

    for (atual = cabeca; atual->proximo != nullptr; atual = atual->proximo) {
        for (proximo = atual->proximo; proximo != nullptr; proximo = proximo->proximo) {
            if (atual->pontuacao < proximo->pontuacao) {
                // Troca os dados dos nós
                tempNome = atual->dados;
                tempPontuacao = atual->pontuacao;
                atual->dados = proximo->dados;
                atual->pontuacao = proximo->pontuacao;
                proximo->dados = tempNome;
                proximo->pontuacao = tempPontuacao;
            }
        }
    }
}

void CListaInteiros::escreveLista(void) const{
    CNoLista *atual = cabeca;
    mensagens mensagem;

    int totalJogadores = 0;
    int totalPontos = 0;

    cout << "--------------- ESTATISTICAS ---------------" << endl;

    if(cabeca == nullptr) {
        cout << "Lista Vazia..." << endl;
        mensagem.LinhaM();
    }
    else{
        while (atual != nullptr){
            cout << atual->dados << " - " << atual->pontuacao << " pontos" << endl;
            totalJogadores++; // Incrementa o total de jogadores
            totalPontos += atual->pontuacao; // Adiciona os pontos do jogador ao total
            atual = atual->proximo;
        }
        cout << "-------------------- FIM -------------------" << endl;
        cout << "Total de Jogadores: " << totalJogadores << "\tTotal de Pontos: " << totalPontos << endl;
    }
}

void CListaInteiros::escreveLista10(void) const{
    CNoLista *atual = cabeca;
    mensagens mensagem;

    cout << "------------- TOP10 -------------" << endl;

    if(cabeca == nullptr) {
        cout << "Lista Vazia..." << endl;
        mensagem.LinhaM();
    }
    else{
        int contador = 0; // Contador para controlar os elementos exibidos
        while (atual != nullptr && contador < 11){
            cout << contador << ". " << atual->dados << " - " << atual->pontuacao << " pontos" << endl;
            atual = atual->proximo;
            contador++; // Aumenta o contador a cada elemento para definir o limite
        }
        cout << "-------------- FIM --------------" << endl;
    }
}

bool CListaInteiros::procuraItem(string item) const{
    CNoLista *atual = cabeca;

    if(cabeca == nullptr)
        return false;
    else{
        while (atual != nullptr){
            if (atual->dados == item)
                return true;
            atual = atual->proximo;
        }
        return false;
    }
}

void CListaInteiros::apagaItem(string item){

    CNoLista *atual = cabeca;
    CNoLista *anterior;

    if(cabeca == nullptr) return;
    else{
        anterior = nullptr;
        while (atual != nullptr){
            if (atual->dados == item){
                if (anterior == nullptr)
                    cabeca = atual->proximo;
                else
                    anterior->proximo = atual->proximo;
                delete atual;
                return;
            }
            anterior = atual;
            atual = atual->proximo;
        }
    }
}

void CListaInteiros::carregarEstatisticas(){

    ofstream arquivo("exemplo.txt", std::ios::out| std::ofstream::trunc);

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo.is_open()) {

        CNoLista *atual = cabeca;

        if(cabeca == nullptr)
            arquivo << "Lista Vazia..." << endl;
        else{
            while (atual != nullptr){
                arquivo << atual->dados << " " << atual->pontuacao << " pontos" << endl;
                atual = atual->proximo;
            }
        }

        // Fecha o arquivo
        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo.\n";
    }
}

void CListaInteiros::imprimirEstatisticas(){

    ifstream estats("exemplo.txt");
    if (estats.is_open()) {
        string linha;
        while (getline(estats, linha)) {
            cout << linha << endl; // Imprime cada linha do arquivo
        }
        estats.close();
    } else {
        cerr << "Erro ao abrir o arquivo de estatisticas." << endl;
    }
}

void CListaInteiros::carregaDados(const char* nomeArquivo) {
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        cerr << "- Erro ao abrir o arquivo -" << endl;
        return;
    }

    string item;
    while (getline(arquivo, item)) {

        stringstream ss(item);
        string nome;
        int score;
        ss >> nome >> score;
        insereItem(nome, score);

    }

    arquivo.close();
}

void CListaInteiros::limparEstatisticas() {
    ofstream estats("exemplo.txt");
    if (estats.is_open()) {
        estats.close();
    } else {
        cerr << "Erro ao abrir o arquivo de estatisticas." << endl;
    }
}

int CListaInteiros::obterScore(string item) const {
    CNoLista *atual = cabeca;

    while (atual != nullptr) {
        if (atual->dados == item) {
            return atual->pontuacao;
        }
        atual = atual->proximo;
    }

    // Se o nome não for encontrado, retorne um valor indicativo, como -1
    return -1;
}

// Pedido do Nome de Utilizador - Username
string CListaInteiros::solicitarUsername() {
    carregaDados("exemplo.txt");
    Menu menu;
    mensagens mensagem;
    string item;

    system("cls");
    cout << "Digite o seu nome de utilizador: ";
    cin >> item;
    nome = item;

    while (nome.size() < 3) {
        system("cls");

        cout << "--------- Minimo de 3 caracteres! --------" << endl << "Por favor, insira outro nome de utilizador: " << endl;
        cin >> item;
        nome = item;
        system("cls");
    }

    while (nome.size() > 20) {
        system("cls");

        cout << "-------- Maximo de 20 caracteres! --------" << endl << "Por favor, insira outro nome de utilizador: " << endl;
        cin >> item;
        nome = item;
        system("cls");
    }

    cout << "--------------------------------------------------------------------" << string(item.size(), '-') << endl;
    cout << "O utilizador " << item << " ja existe. Deseja continuar (1) ou trocar (2) de nome?" << endl;
    cout << "--------------------------------------------------------------------" << string(item.size(), '-') << endl;

    if (procuraItem(item)) {
        while (true) {

            mensagem.getEscolha();

            if (mensagem.escolha == 1) {
                scoreExistente = obterScore(item);
                apagaItem(item);
                insereItem(item, scoreExistente);
                carregarEstatisticas();
                break; // Para sair do loop
            } else if (mensagem.escolha == 2) {
                system("cls");
                return solicitarUsername();
            } else {
                mensagem.opcaoInvalida();
            }
        }
    } else {
        int score = 0;
        insereItem(item, score);
        carregarEstatisticas();
    }
    bemVindo();

    nome = item;

    return item;
}

void CListaInteiros::bemVindo() {
    system("cls");
    cout << "------------------------------------------------" << string(nome.size(), '-') << endl;
    cout << "Bem-vindo " << nome << ", prima qualquer tecla para continuar!" << endl;
    cout << "------------------------------------------------" << string(nome.size(), '-') << endl;
    _getch(); // Recebe o char mas não o mostra
    while (_kbhit()) // Flush noutros caracteres no buffer
        _getch();
    Beep(320,200);
}
//----------------------------------------resultados------------------------------------------------//

void CListaInteiros::contadorResultados(/*int vitorias, int derrotas, int empates*/int pontos, string item){
    /*
    Dados.vitorias = vitorias;
    Dados.derrotas = derrotas;
    Dados.empates = empates;
*/
    // Carrega a pontuação atual do jogador
    carregaDados("exemplo.txt");

    scoreExistente=obterScore(item);
    // Calcula a nova pontuação do jogador considerando as vitórias e derrotas
    int novaPontuacao = scoreExistente + pontos; // vitorias - derrotas;

    // Atualiza a pontuação do jogador
    atualizarPontuacao(item, novaPontuacao);

    // Atualiza as estatísticas no arquivo
    carregarEstatisticas();
}

void CListaInteiros::atualizarPontuacao(string item,  int novaPontuacao) {

    CNoLista *atual=cabeca;

    while (atual != nullptr){
        if (atual->dados == item){
            atual->pontuacao = novaPontuacao;
        }
        atual = atual->proximo;
    }
}

//------------------------------------salvamento continuar jogo-------------------------------------------//

void CListaInteiros::salvarJogo(char tabuleiro[9]) {
    ofstream jogosalvo("jogo.txt");
    if (jogosalvo.is_open()) {
        for (int i = 0; i < 9; ++i) {
            jogosalvo << tabuleiro[i] << " ";
        }
        jogosalvo << endl;

        jogosalvo.close();
    }else {
        cout << "Erro ao salvar o jogo." << endl;
    }
}

// Carregar o jogo salvo
void CListaInteiros::carregarJogo( char tabuleiro[9]){

    ifstream jogosalvo("jogo.txt");

    if (jogosalvo.is_open()) {
        for (int i = 0; i < 9; ++i) {
            if (!(jogosalvo >> tabuleiro[i])) {
                cout << "Erro ao ler o elemento " << i << " do arquivo." << endl;
                break;
            }
        }jogosalvo.close();
    } else {
        cout << "Erro ao abrir o arquivo." << endl;
    }
}

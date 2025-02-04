#include "game.h"
#include "mensagens.h"
#include "menu.h"
#include "files.h"
#include <iomanip>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

Jogo::Jogo(){
    for(int i = 0; i < 9; i++){
        casas[i] = jogadores.vazio;
    }
}

//-----------------------------------------dados do jogo------------------------------------------------//


// Função para dividir uma string em várias linhas com base no caractere de quebra de linha
vector<string> Jogo::separarlinhas(const string& str) {
    vector<string> linhas;
    stringstream ss(str);
    string linha;
    while (getline(ss, linha, '\n')) {
        linhas.push_back(linha);
    }
    return linhas;
}

void Jogo::imprimirlado() {
    system("cls");
    mensagens mensagem;
    Menu menu;
    // Verificar se há tabuleiros para imprimir
    if (tamtabtex == 0) {
        cout << "Nenhum tabuleiro disponivel." << endl;
        return;
    }

    // Calcular o número máximo de linhas e o comprimento máximo de cada linha
    size_t maxlinha = 0;
    size_t maxlargura = 0;

    // Mostrar até quatro tabuleiros por linha
    size_t inicio = max((int)tamtabtex - 4, 0);
    size_t final = tamtabtex;

    mensagem.LinhaL();
    // Imprimir o número do turno atual
    cout << "                     Turno " << tamtabtex << endl << endl;
    mensagem.LinhaL();
    cout << endl;

    for (size_t j = inicio; j < final; ++j) {
        // Verificar se o tabuleiro j existe
        if (j < tamtabtex) {
            const auto& text = tabtex[j];
            vector<string> lines = separarlinhas(text);
            maxlinha = max(maxlinha, lines.size());
            for (const auto& line : lines) {
                maxlargura = max(maxlargura, line.size());
            }
        }
    }

    // Loop para imprimir cada linha de cada tabuleiro
    for (size_t i = 0; i < maxlinha; ++i) {
        for (size_t j = inicio; j < final; ++j) {
            // Verificar se o tabuleiro j existe
            if (j < tamtabtex) {
                const auto& text = tabtex[j];
                vector<string> linhas = separarlinhas(text);
                if (!linhas.empty() && i < linhas.size()) {
                    // Preencher a linha atual com espaços em branco se necessário
                    cout << setw(maxlargura) << left << linhas[i];
                } else {
                    // Se a linha não existir, imprimir espaços em branco
                    cout << string(linhas.empty() ? 0 : linhas[0].size(), ' ');
                }
            }
            if (j != inicio - 1) {
                cout << "    ";
            }
        }
        cout << endl;
    }
}

void Jogo::imprimirTabuleiros() {
    imprimirlado();
}

void Jogo::desenharTabuleiro(int i) {
    stringstream ss;
    ss << "       |       |       \n"
       << "    " << casas[0] << "  |    " << casas[1] << "  |    " << casas[2] << "   \n"
       << "       |       |       \n"
       << "-------|-------|-------\n"
       << "       |       |       \n"
       << "    " << casas[3] << "  |    " << casas[4] << "  |    " << casas[5] << "   \n"
       << "       |       |       \n"
       << "-------|-------|-------\n"
       << "       |       |       \n"
       << "    " << casas[6] << "  |    " << casas[7] << "  |    " << casas[8] << "   \n"
       << "       |       |       \n ";

    /*    Alternativa com numeros
         ss <<  "       |       |       \n"
           " 1  " << casas[0] << "  | 2  " << casas[1] << "  | 3  " << casas[2] << "   \n"
           "       |       |       \n"
           "-------|-------|-------\n"
           "       |       |       \n"
           " 4  " << casas[3] << "  | 5  " << casas[4] << "  | 6  " << casas[5] << "   \n"
           "       |       |       \n"
           "-------|-------|-------\n"
           "       |       |       \n"
           " 7  " << casas[6] << "  | 8  " << casas[7] << "  | 9  " << casas[8] << "   \n"
           "       |       |       \n";
*/
    // Atualiza o tabuleiro atual na posição i
    tabtex[i] = ss.str();
    // Atualiza o tamanho do vetor de tabuleiros
    tamtabtex = i + 1;
}


//-----------------------------------------dados do jogo------------------------------------------------//

int Jogo::espacosEmFalta(int &espacos){
    espacos = 0;

    for(int i = 0; i < 9; i++ ){
        if(casas[i] == jogadores.vazio){
            espacos = espacos + 1;
        }
    }

    return espacos;
}

void Jogo::limpar(){
    for(int i = 0; i < 10; i++){
        casas[i] = jogadores.vazio;
    }
    for (size_t i = 0; i < tamtabtex; i++) {
        tabtex[i] = "";
    }
    tamtabtex = 0;

}

bool Jogo::sair(){
    if(posicao == 0){
        return true;
    }
    else return false;
}

//-----------------------------------------fins de jogo-------------------------------------------------//

bool Jogo::verificarVitoria(){
    for(int i = 0; i < 3; ++i) {
        if (casas[i] != '-' && casas[i] == casas[i+3] && casas[i] == casas[i+6]) {
            return true;
        } //verificar linhas
    }
    for(int i=0; i<9; i+=3) {
        if (casas[i] != '-' && casas[i] == casas[i+1] && casas[i]== casas[i+2]) {
            return true;
        }//verificar colunas
    }
    if (casas[0] != '-' && casas[0] == casas[4] && casas[0] == casas[8]) {
        return true;
    }
    if (casas[2] != '-' && casas[2] == casas[4] && casas[2] == casas[6]) {
        return true;
    }//verificar diagonais
    return false;
}

bool Jogo::verificarEmpate(){
    for(int i = 0; i < 9; i++){
        if(casas[i] == jogadores.vazio){ //ha espaco vazio logo não pode existir empate
            return false;
        }
    }
    return true;
}

bool Jogo::fimdejogo(){
    mensagens mensagem;

    //funçao que retorna se o jogo acabou
    if(verificarVitoria() == true){
        return true;
    }else if(verificarVitoria() == false){
        if(verificarEmpate() == true){
            return true;
        }
    }
    return false;
}

void Jogo::comecarNovamente(int &jogaprimeiro) {
    mensagens mensagem;
    Menu menu;

    mensagem.LinhaL();
    mensagem.Fim();
    cout << endl << "[1]             Comecar Novamente" << endl << "[2]              Voltar ao Menu" << endl << "[3]               Sair do Jogo" << endl;
    mensagem.LinhaL();

    mensagem.getEscolha();
    if (mensagem.escolha == 1) {
        turnos(jogaprimeiro);
    } else if (mensagem.escolha == 2) {
        system("cls");

        limpar();
        menu.escolhaModo=0;
        funcionamentoJogo(NAME);
    } else if (mensagem.escolha == 3) {
        menu.sairMenu();
    }
}

//---------------------------------------------------------------------------------------------//
//---------------------------------turnos e jogadas------------------------------------------//

void Jogo::turnos(int &jogaprimeiro){

    if(jogaprimeiro==1){
        jogadores.humano='X';               //Humano joga primeiro se "jogaprimeiro==1"
        jogadores.bot='O';
    }else if(jogaprimeiro==2){
        jogadores.humano='O';               //computador joga primeiro se "jogaprimeiro==2"
        jogadores.bot='X';

    }
}

void Jogo::jogadaHumano(bool play2){
    mensagens mensagem;
    CListaInteiros jogosalvo;
    Menu menu;

    mensagem.LinhaL();
    cout << "     [1-9] Jogar | [0] Menu | [-1] Suspender" << endl;
    mensagem.LinhaL();
    cin >> posicao;


    while (posicao < -1 || posicao > 9) {
        cout << "Posicao invalida, tente novamente." << endl;
        cin >> posicao;
    }
    if(posicao == -1){
        system("cls");
        cout<<"Deseja mesmo sair do jogo?" << endl << "[1] Sim" << endl << "[0] Nao" << endl;
        cin >> posicao;
        if(posicao == 1){
            cout << "Fim do jogo." << endl;
            system("pause");

            jogosalvo.salvarJogo(casas);
            exit(0);

        }if(posicao == 0){
            system("cls");
            desenharTabuleiro(val);
            imprimirTabuleiros();
            jogadaHumano(play2);
        }
    }

    if(posicao == 0){
        system("cls");

        limpar();
        menu.escolhaModo=0;
        funcionamentoJogo(NAME);
    }
    if(casas[posicao-1] != jogadores.vazio){
        mensagem.LinhaL();
        cout << "         Posicao ocupada, tente novamente!" << endl;
        jogadaHumano(play2);
    }

    if(play2 == false){
        casas[posicao-1] = jogadores.humano;
        desenharTabuleiro(val = val + 1);
        imprimirTabuleiros();
    }
    else if(play2 == true){
        casas[posicao - 1] = jogadores.bot;
        desenharTabuleiro(val = val + 1);
        imprimirTabuleiros();
    }
}

//--------------------------------BOTS------------------------------------------//

void Jogo::jogadaBotLevel1(bool bot2){    //level 1, computador joga numa casa aleatóriamente

    static bool srandCalled = false;
    if (!srandCalled) {
        srand(time(NULL));
        srandCalled = true;
    }

    int posicao;
    do {
        posicao = rand() % 9;
    } while (casas[posicao] != jogadores.vazio);
    if(bot2==false){
        casas[posicao] = jogadores.bot;
        desenharTabuleiro(val=val+1);
        imprimirTabuleiros();
        pcJoga();
        cout << posicao+1 << endl;
    }
    if(bot2==true){
        casas[posicao] = jogadores.humano;
        desenharTabuleiro(val=val+1);
        imprimirTabuleiros();
        pcJoga();
        cout << posicao+1 << endl;
    }
}

/********************************************************************************/

void Jogo::jogadaBotLevel2(bool bot2){

    // Verificar se há uma jogada vencedora ou defensiva
    for(int i = 0; i < 9; i++){
        if(casas[i] == jogadores.vazio){
            // Simula uma jogada do bot
            // Verifica se o bot ganha com essa jogada
            if(bot2==false) casas[i] = jogadores.bot;
            if(bot2==true) casas[i] = jogadores.humano;
            if(verificarVitoria()){
                desenharTabuleiro(val=val+1);
                imprimirTabuleiros();
                pcAtaca();
                cout << posicao+1 << endl;
                return; // Retorna imediatamente após fazer uma jogada vencedora
            }

            // Verifica se o humano ganharia com a próxima jogada
            if(bot2==false) casas[i] = jogadores.humano;
            if(bot2==true) casas[i] = jogadores.bot;
            if(verificarVitoria()){
                if(bot2==false) casas[i] = jogadores.bot;
                if(bot2==true) casas[i] = jogadores.humano;
                desenharTabuleiro(val = val + 1);
                imprimirTabuleiros();
                pcDefende();
                cout << posicao+1 << endl;
                return; // Retorna imediatamente após fazer uma jogada defensiva
            }
            // Desfaz a jogada simulada
            casas[i] = jogadores.vazio;
        }
    }

    // Se não houver jogada vencedora ou defensiva, joga aleatoriamente
    int posicao;
    do {
        posicao = rand() % 9;
    } while (casas[posicao] != jogadores.vazio);
    if(bot2==false){
        casas[posicao] = jogadores.bot;
        desenharTabuleiro(val=val+1);
        imprimirTabuleiros();
        pcJoga();
        cout << posicao+1 << endl;
    }
    if(bot2==true){
        casas[posicao] = jogadores.humano;
        desenharTabuleiro(val=val+1);
        imprimirTabuleiros();
        pcJoga();
        cout << posicao+1 << endl;
    }
}

/***************************************************************************************/

void Jogo::jogadaBotLevel3(bool bot2){
    bool jogadaFeita = false;
    int jogadorAtual = bot2 ? jogadores.humano : jogadores.bot;
    int oponente = bot2 ? jogadores.bot : jogadores.humano;

    for (int i = 0; i < 9; i++) {
        if (casas[i] == jogadores.vazio) {
            // Tenta ganhar ou bloquear o oponente
            casas[i] = jogadorAtual;  // Assume a jogada
            if (verificarVitoria()) {
                desenharTabuleiro(val += 1);
                imprimirTabuleiros();
                cout << i + 1 << endl;
                jogadaFeita = true;
                break;
            }
            casas[i] = oponente; // Testa jogada do oponente
            if (verificarVitoria()) {
                casas[i] = jogadorAtual; // Bloqueia jogada do oponente
                desenharTabuleiro(val += 1);
                imprimirTabuleiros();
                cout << i + 1 << endl;
                jogadaFeita = true;
                break;
            }
            casas[i] = jogadores.vazio; // Restaura a casa
        }
    }

    // Se nenhuma jogada efetiva foi feita, faz uma jogada aleatória
    if (!jogadaFeita) {
        int posicao;
        srand(time(NULL));  // Inicializa o gerador de números aleatórios uma vez
        do {
            posicao = rand() % 9;
        } while (casas[posicao] != jogadores.vazio);

        casas[posicao] = jogadorAtual;
        desenharTabuleiro(val += 1);
        imprimirTabuleiros();
        cout << posicao + 1 << endl;
    }
}

/********************************************************************************/

void Jogo::jogadaBotLevel4(bool bot2) {
    int melhorval = INT_MIN;
    int melhorposicao = -1;

    for (int i = 0; i < 9; i++) {
        if (casas[i] == jogadores.vazio) {
            if(bot2==false) casas[i] = jogadores.bot;
            if(bot2==true) casas[i] = jogadores.humano;
            int moveval = minimax(casas, 0, false, bot2); // Simula o movimento do jogador humano
            casas[i] = jogadores.vazio;

            if (moveval > melhorval) {
                melhorval = moveval;
                melhorposicao = i;
            }
        }
    }

    cout << "O melhorval tem um valor de : " << melhorval << "\n" << endl;

    if (melhorposicao != -1) {
        if(bot2==false) casas[melhorposicao] = jogadores.bot;
        if(bot2==true) casas[melhorposicao] = jogadores.humano;
        desenharTabuleiro(val=val+1);
        imprimirTabuleiros();
        pcJoga();
        cout << melhorposicao + 1 << endl;
    } else {
        cout << "Nenhuma jogada disponível." << endl;
    }
}

int Jogo::minimax(char move[10], int profundidade, bool maxplayer, bool bot2) {

    if(bot2==false){
        char vencedor = vervencedorMinimax(casas);
        if (vencedor == jogadores.bot) return 10-profundidade;
        else if (vencedor == jogadores.humano) return -10+profundidade;
        else if (vencedor == 'e') return 0;
    }
    else if(bot2==true){
        char vencedor = vervencedorMinimax(casas);
        if (vencedor == jogadores.humano) return 10-profundidade;
        else if (vencedor == jogadores.bot) return -10+profundidade;
        else if (vencedor == 'e') return 0;
    }

    int valormax;
    if (maxplayer) {
        valormax = INT_MIN;
        for (int i = 0; i < 9; i++) {
            if (move[i] == jogadores.vazio) {
                if(bot2==false) move[i] = jogadores.bot;
                if(bot2==true) move[i] = jogadores.humano;
                int valor = minimax(move, profundidade + 1, false, bot2);
                move[i] = jogadores.vazio;
                if (valor > valormax) {
                    valormax = valor;
                }
            }
        }
    } else {
        valormax = INT_MAX;
        for (int i = 0; i < 9; i++) {
            if (move[i] == jogadores.vazio) {
                if(bot2==false) move[i] = jogadores.humano;
                if(bot2==true) move[i] = jogadores.bot;
                int valor = minimax(move, profundidade + 1, true, bot2);
                move[i] = jogadores.vazio;
                if (valor < valormax) {
                    valormax = valor;
                }
            }
        }

    }
    return valormax;
}

//---------------------------FUNCAO VER VENCEDOR MINIMAX---------------------------

char Jogo::vervencedorMinimax(char espaco[]) {
    for (int i = 0; i < 3; ++i) {
        if (espaco[i * 3] == espaco[i * 3 + 1] && espaco[i * 3 + 1] == espaco[i * 3 + 2] && espaco[i * 3] != jogadores.vazio) {
            return espaco[i * 3];
        }
    }
    for (int i = 0; i < 3; ++i) {
        if (espaco[i] == espaco[i + 3] && espaco[i + 3] == espaco[i + 6] && espaco[i] !=jogadores.vazio) {
            return espaco[i];
        }
    }
    if ((espaco[0] == espaco[4] && espaco[4] == espaco[8] && espaco[0] != jogadores.vazio) ||
        (espaco[2] == espaco[4] && espaco[4] == espaco[6] && espaco[2] != jogadores.vazio)) {
        return espaco[4];
    }
    for (int i = 0; i < 9; ++i) {
        if (espaco[i] == jogadores.vazio) {
            return jogadores.vazio;
        }
    }
    return 'e';
}

/***********************************************************************************************************/


//-------------------------------------------------------------------------------------------//
//---------------------------------------pré jogo--------------------------------------------//



void Jogo::funcionamentoJogo(string name){
    Menu menu;
    mensagens mensagem;
    CListaInteiros estatisticas;
    NAME=name;
    menu.imprimirMenu();

    int vitorias=0, derrotas=0, empates=0;
    int pontos=0;

    if(menu.continuarSalvo==true){
        estatisticas.carregarJogo(casas);

        for (int i = 0; i < 9; ++i) {
            cout << casas[i];
        }cout << endl;
    } else {
        limpar();
    }

    if (menu.escolhaModo == 1) {
        mensagem.LinhaL();
        cout << "Quem vai jogar primeiro?" << endl << "[1] Jogador" << endl << "[2] Computador" << endl;
        mensagem.LinhaL();
        mensagem.getEscolha();
        jogaPrimeiro = mensagem.escolha;
    } else if (menu.escolhaModo == 2) {
        mensagem.LinhaL();
        cout << "Quem vai jogar primeiro?" << endl << "[1] Jogador" << endl << "[2] Convidado" << endl;
        mensagem.LinhaL();
        mensagem.getEscolha();
        jogaPrimeiro = mensagem.escolha;
    } else if (menu.escolhaModo == 3) {
        srand(time(0));
        jogaPrimeiro = (rand() %2) + 1; // Para gerar 1 ou 2 aleatoriamente
    }

    int espacos=0;
    estatisticas.carregaDados("exemplo.txt");
    //------------------------------------jogo--------------------------------//

    do{
        turnos(jogaPrimeiro);
        espacos=0;
        val=0;
        desenharTabuleiro(val);
        imprimirTabuleiros();

        if(jogaPrimeiro==1){
            do{
                pontos=0;
                estatisticas.contadorResultados(/*vitorias, derrotas, empates*/  pontos, name);
                if(menu.escolhaModo == 1||menu.escolhaModo == 2){
                    jogadaHumano(false);                        //vez do humano
                }else if(menu.escolhaModo == 3){
                    if(menu.escolhaJogo == 1) jogadaBotLevel1(true);
                    if(menu.escolhaJogo == 2) jogadaBotLevel2(true);  //vez do bot2
                    if(menu.escolhaJogo == 3)  jogadaBotLevel3(true);
                    if(menu.escolhaJogo == 4) jogadaBotLevel4(true);
                }
                estatisticas.salvarJogo(casas);
                espacosEmFalta(espacos);
                if (verificarVitoria()==true){
                    limpar();
                    jogaPrimeiro=2;
                    if(menu.escolhaModo == 1||menu.escolhaModo == 2){
                        vitorias++;
                        pontos++;
                        estatisticas.contadorResultados(/*vitorias, derrotas, empates*/  pontos, name);
                        mensagem.LinhaL();
                        cout << "      Vitorias: " << vitorias << " | Derrotas:" << derrotas << " | Empates: " << empates << endl;
                    }
                    if(menu.escolhaModo == 1 || menu.escolhaModo == 2) {
                        mensagem.venceu();
                    } else if (menu.escolhaModo == 3) {
                        cout << "Dificuldades:" << "      Bot 1 -> " << menu.escolhaJogo << "     Bot 2 -> " << menu.escolhaJogo2 << endl;
                        mensagem.LinhaL();
                        cout << "                   Bot 1 ganhou!" << endl;
                    }
                    comecarNovamente(jogaPrimeiro);
                    break;
                }
                if (verificarVitoria()==false){
                    if (verificarEmpate()==true){
                        limpar();
                        jogaPrimeiro=2;
                        if(menu.escolhaModo == 1||menu.escolhaModo == 2){
                            empates++;
                            estatisticas.contadorResultados(/*vitorias, derrotas, empates*/  pontos, name);
                            mensagem.LinhaL();
                            cout << "      Vitorias: " << vitorias << " | Derrotas:" << derrotas << " | Empates: " << empates << endl;
                        }
                        if (menu.escolhaModo == 3) {
                            cout << "Dificuldades:" << "      Bot 1 -> " << menu.escolhaJogo << "     Bot 2 -> " << menu.escolhaJogo2 << endl;
                            mensagem.LinhaL();
                        }
                        mensagem.empatou();
                        comecarNovamente(jogaPrimeiro);
                        break;
                    }
                }
                if(menu.escolhaModo == 1){
                    if(menu.escolhaJogo == 1) jogadaBotLevel1(false);
                    if(menu.escolhaJogo == 2) jogadaBotLevel2(false);  //vez do bot
                    if(menu.escolhaJogo == 3) jogadaBotLevel3(false);
                    if(menu.escolhaJogo == 4) jogadaBotLevel4(false);
                }
                if(menu.escolhaModo == 2) jogadaHumano(true);

                if(menu.escolhaModo == 3){
                    if(menu.escolhaJogo2 == 1) jogadaBotLevel1(false);
                    if(menu.escolhaJogo2 == 2) jogadaBotLevel2(false);  //vez do bot2
                    if(menu.escolhaJogo2 == 3)  jogadaBotLevel3(false);
                    if(menu.escolhaJogo2 == 4) jogadaBotLevel4(false);
                }

                estatisticas.salvarJogo(casas);
                espacosEmFalta(espacos);
                if (verificarVitoria()==true){
                    limpar();
                    jogaPrimeiro=2;
                    if(menu.escolhaModo == 1||menu.escolhaModo == 2){
                        pontos--;
                        derrotas++;
                        estatisticas.contadorResultados(/*vitorias, derrotas, empates*/  pontos, name);
                        mensagem.LinhaL();
                        cout << "      Vitorias: " << vitorias << " | Derrotas:" << derrotas << " | Empates: " << empates << endl;
                    }
                    if(menu.escolhaModo == 1 || menu.escolhaModo == 2) {
                        mensagem.perdeu();
                    } else if (menu.escolhaModo == 3) {
                        cout << "Dificuldades:" << "      Bot 1 -> " << menu.escolhaJogo << "     Bot 2 -> " << menu.escolhaJogo2 << endl;
                        mensagem.LinhaL();
                        cout << "                   Bot 2 ganhou!" << endl;
                    }
                    comecarNovamente(jogaPrimeiro);
                    break;
                }
                if (verificarVitoria()==false){
                    if (verificarEmpate()==true){
                        limpar();
                        jogaPrimeiro=2;
                        if(menu.escolhaModo == 1||menu.escolhaModo == 2){
                            empates++;
                            estatisticas.contadorResultados(/*vitorias, derrotas, empates*/  pontos, name);
                            mensagem.LinhaL();
                            cout << "      Vitorias: " << vitorias << " | Derrotas:" << derrotas << " | Empates: " << empates << endl;
                        }
                        if (menu.escolhaModo == 3) {
                            cout << "Dificuldades:" << "      Bot 1 -> " << menu.escolhaJogo << "     Bot 2 -> " << menu.escolhaJogo2 << endl;
                            mensagem.LinhaL();
                        }
                        mensagem.empatou();
                        comecarNovamente(jogaPrimeiro);
                        break;
                    }
                }
            }while(fimdejogo()==false);


        }else if(jogaPrimeiro == 2){
            do{
                pontos=0;
                estatisticas.contadorResultados(/*vitorias, derrotas, empates*/  pontos, name);

                if(menu.escolhaModo == 1){
                    if(menu.escolhaJogo == 1) jogadaBotLevel1(false);
                    if(menu.escolhaJogo == 2) jogadaBotLevel2(false);  //vez do bot
                    if(menu.escolhaJogo == 3) jogadaBotLevel3(false);
                    if(menu.escolhaJogo == 4) jogadaBotLevel4(false);
                }
                if(menu.escolhaModo == 2) jogadaHumano(true);

                if(menu.escolhaModo == 3){
                    if(menu.escolhaJogo2 == 1) jogadaBotLevel1(false);
                    if(menu.escolhaJogo2 == 2) jogadaBotLevel2(false);  //vez do bot2
                    if(menu.escolhaJogo2 == 3)  jogadaBotLevel3(false);
                    if(menu.escolhaJogo2 == 4) jogadaBotLevel4(false);
                }
                estatisticas.salvarJogo(casas);
                mensagem.LinhaL();
                espacosEmFalta(espacos);

                if (verificarVitoria()==true){
                    limpar();
                    jogaPrimeiro=1;
                    if(menu.escolhaModo == 1||menu.escolhaModo == 2){
                        pontos--;
                        derrotas++;
                        estatisticas.contadorResultados(/*vitorias, derrotas, empates*/  pontos, name);
                        mensagem.LinhaL();
                        cout << "      Vitorias: " << vitorias << " | Derrotas:" << derrotas << " | Empates: " << empates << endl;
                    }
                    if(menu.escolhaModo == 1 || menu.escolhaModo == 2) {
                        mensagem.perdeu();
                    } else if (menu.escolhaModo == 3) {
                        cout << "Dificuldades:" << "      Bot 1 -> " << menu.escolhaJogo << "     Bot 2 -> " << menu.escolhaJogo2 << endl;
                        mensagem.LinhaL();
                        cout << "                   Bot 2 ganhou!" << endl;
                    }

                    comecarNovamente(jogaPrimeiro);
                    break;
                }
                if (verificarVitoria()==false){
                    if (verificarEmpate()==true){
                        limpar();
                        jogaPrimeiro=1;
                        if(menu.escolhaModo == 1||menu.escolhaModo == 2){
                            empates++;
                            estatisticas.contadorResultados(/*vitorias, derrotas, empates*/  pontos, name);
                            mensagem.LinhaL();
                            cout << "      Vitorias: " << vitorias << " | Derrotas:" << derrotas << " | Empates: " << empates << endl;
                        }
                        if (menu.escolhaModo == 3) {
                            cout << "Dificuldades:" << "      Bot 1 -> " << menu.escolhaJogo << "     Bot 2 -> " << menu.escolhaJogo2 << endl;
                            mensagem.LinhaL();
                        }
                        mensagem.empatou();

                        comecarNovamente(jogaPrimeiro);
                        break;
                    }
                }
                if(menu.escolhaModo == 1||menu.escolhaModo == 2){
                    jogadaHumano(false);                        //vez do humano
                }else if(menu.escolhaModo == 3){
                    if(menu.escolhaJogo == 1) jogadaBotLevel1(true);
                    if(menu.escolhaJogo == 2) jogadaBotLevel2(true);  //vez do bot2
                    if(menu.escolhaJogo == 3)  jogadaBotLevel3(true);
                    if(menu.escolhaJogo == 4) jogadaBotLevel4(true);
                }
                estatisticas.salvarJogo(casas);
                espacosEmFalta(espacos);
                if (verificarVitoria()==true){
                    limpar();
                    jogaPrimeiro=1;
                    if(menu.escolhaModo == 1||menu.escolhaModo == 2){
                        pontos++;
                        vitorias++;
                        estatisticas.contadorResultados(/*vitorias, derrotas, empates*/  pontos, name);
                        mensagem.LinhaL();
                        cout << "      Vitorias: " << vitorias << " | Derrotas:" << derrotas << " | Empates: " << empates << endl;
                    }
                    if(menu.escolhaModo == 1 || menu.escolhaModo == 2) {
                        mensagem.venceu();
                    } else if (menu.escolhaModo == 3){
                        cout << "Dificuldades:" << "      Bot 1 -> " << menu.escolhaJogo << "     Bot 2 -> " << menu.escolhaJogo2 << endl;
                        mensagem.LinhaL();
                        cout << "                   Bot 1 ganhou!" << endl;
                    }
                    comecarNovamente(jogaPrimeiro);
                    break;
                }
                if (verificarVitoria()==false){
                    if (verificarEmpate()==true){
                        limpar();
                        jogaPrimeiro=1;
                        if(menu.escolhaModo == 1||menu.escolhaModo == 2){
                            empates++;
                            estatisticas.contadorResultados(/*vitorias, derrotas, empates*/  pontos, name);
                            mensagem.LinhaL();
                            cout << "      Vitorias: " << vitorias << " | Derrotas:" << derrotas << " | Empates: " << empates << endl;
                        }
                        if (menu.escolhaModo == 3) {
                            cout << "Dificuldades:" << "      Bot 1 -> " << menu.escolhaJogo << "     Bot 2 -> " << menu.escolhaJogo2 << endl;
                            mensagem.LinhaL();
                        }
                        mensagem.empatou();
                        comecarNovamente(jogaPrimeiro);
                        break;
                    }
                }
            }while(fimdejogo() == false);
        }
    }while(sair()==false);
}


// Mensagem para quando o computador faz uma jogada
void Jogo::pcJoga() {
    mensagens mensagem;

    mensagem.LinhaL();
    cout << "         O computador jogou na posicao: ";
}

// Mensagem para quando o computador ataca propositadamente
void Jogo::pcDefende() {
    mensagens mensagem;

    mensagem.LinhaL();
    cout << "         O computador atacou na posicao: ";
}

// Mensagem para quando o computador defende propositadamente
void Jogo::pcAtaca() {
    mensagens mensagem;

    mensagem.LinhaL();
    cout << "        O computador defendeu na posicao: ";
}

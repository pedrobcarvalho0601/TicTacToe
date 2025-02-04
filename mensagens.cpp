#include "mensagens.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <conio.h>
#include <utilapiset.h>
#include <Windows.h>
#include <mmsystem.h>

//#include <cctype>

using namespace std;

mensagens::mensagens() {}

// Opcao invalida para numeros
void mensagens::opcaoInvalida() {
    cout << "Opcao invalida! Por favor, escolha uma das opcoes." << endl;
    cin.clear(); // Limpa o buffer de entrada
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora o restante da linha inválida
}

// Entrada invalida para caracteres
void mensagens::entradaInvalida() {
    cout << "Indisponivel! Por favor, insira uma das opcoes." << endl;
    cin.clear(); // Limpa o buffer de entrada
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora o restante da linha inválida
}

// Venceu
void mensagens::venceu() {
    cout << "                   Venceu! :)" << endl;
}

// Empatou
void mensagens::empatou() {
    cout << "                  O Jogo Empatou!" << endl;

}

// Perdeu
void mensagens::perdeu() {
    cout << "                   Perdeu :(" << endl;
}

// Fim
void mensagens::Fim() {
    cout << "                _____ _           " << endl;
    cout << "               |  ___(_)_ __ ___  " << endl;
    cout << "               | |_  | | '_ ` _ \\ " << endl;
    cout << "               |  _| | | | | | | |" << endl;
    cout << "               |_|   |_|_| |_| |_|" << endl;
}

// Menu
void mensagens::Menu() {
    system("cls");
    LinhaS();
    cout << "    __  __                   " << endl;
    cout << "   |  \\/  | ___ _ __  _   _   " << endl;
    cout << "   | |\\/| |/ _ \\ '_ \\| | | |  " << endl;
    cout << "   | |  | |  __/ | | | |_| |  " << endl;
    cout << "   |_|  |_|\\___|_| |_|\\__,_|  " << endl;
    cout << "" << endl;
    LinhaS();
    cout << "[1]         Novo jogo" << endl;
    cout << "[2]         Continuar" << endl;
    cout << "[3]       Estastisticas" << endl;
    cout << "[4]           Top10" << endl;
    cout << "[5]        Sair do Jogo" << endl;
    LinhaS();
}

// Modo
void mensagens::Modo() {
    system("cls");
    LinhaM();
    cout << "        __  __           _       " << endl;
    cout << "       |  \\/  | ___   __| | ___ " << endl;
    cout << "       | |\\/| |/ _ \\ / _` |/ _ \\" << endl;
    cout << "       | |  | | (_) | (_| | (_) |" << endl;
    cout << "       |_|  |_|\\___/ \\__,_|\\___/ " << endl;
    LinhaM();
    cout << "[1] Player vs Bot" << endl; // Jogador vs Computador
    cout << "[2] Player vs Player " << endl; // 2 Jogadores
    cout << "[3] Bot vs Bot " << endl; // 2 Computadores
    cout << "[4] Voltar" << endl; // Ao menu
    LinhaM();
}

// Dificuldade
void mensagens::Dificuldade(){
    system("cls");
    LinhaL();
    cout << " ____  _  __ _            _     _           _      " << endl;
    cout << "|  _ \\(_)/ _(_) ___ _   _| | __| | __ _  __| | ___ " << endl;
    cout << "| | | | | |_| |/ __| | | | |/ _` |/ _` |/ _` |/ _ \\" << endl;
    cout << "| |_| | |  _| | (__| |_| | | (_| | (_| | (_| |  __/" << endl;
    cout << "|____/|_|_| |_|\\___|\\__,_|_|\\__,_|\\__,_|\\__,_|\\___|" << endl << endl;
    LinhaL();
    cout << "[1] Elementar" << endl;
    cout << "[2] Basico" << endl;
    cout << "[3] Medio " << endl;
    cout << "[4] Impossivel " << endl;
    cout << "[5] Aleatorio" << endl;
    cout << "[6] Voltar" << endl; // ao menu do Modo de Jogo
    LinhaL();
}

// Tem a certeza?
void mensagens::temCerteza() {
    cout << "Quer mesmo continuar?" << endl;
    cout << "[1] Sim" << endl;
    cout << "[2] Nao" << endl;
    LinhaS();
}

// Linha pequena
void mensagens::LinhaS() {
    cout << "--------------------------------" << endl;
}

void mensagens::LinhaM() {
    cout << "----------------------------------------" << endl;
}

void mensagens::LinhaL() {
    cout << "---------------------------------------------------" << endl;
}

// Para aceitar apenas numeros nas escolhas
bool isNumber(const std::string &s) {
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

void mensagens::getEscolha() {
    mensagens mensagem;
    std::string input; // Variável temporária para armazenar o input do usuário

    while (true) {
        std::cin >> input;
        //  cout<<'\a';
        Beep(320,200);
        if (!isNumber(input)) { // Verifica se o input é um número
            mensagem.entradaInvalida();
        } else {
            escolha = stoi(input);
            break; // Sai se o input for um número
        }

    }
}

void mensagens::inicio() {
    cout << "--------------------------------------------------------------" << endl;
    cout << "       ___  ________  ________  ________                    " << endl;
    cout << "      |\\  \\|\\   __  \\|\\   ____\\|\\   __  \\                   " << endl;
    cout << "      \\ \\  \\ \\  \\|\\  \\ \\  \\___|\\ \\  \\|\\  \\                  " << endl;
    cout << "    __ \\ \\  \\ \\  \\\\\\  \\ \\  \\  __\\ \\  \\\\\\  \\                 " << endl;
    cout << "   |\\  \\\\_\\  \\ \\  \\\\\\  \\ \\  \\|\\  \\ \\  \\\\\\  \\                " << endl;
    cout << "   \\ \\________\\ \\_______\\ \\_______\\ \\_______\\               " << endl;
    cout << "    \\|________|\\|_______|\\|_______|\\|_______|                          " << endl;
    cout << "                                                            " << endl;
    cout << "              ________  ________                              " << endl;
    cout << "             |\\   ___ \\|\\   __  \\                             " << endl;
    cout << "             \\ \\  \\_|\\ \\ \\  \\|\\  \\                            " << endl;
    cout << "              \\ \\  \\ \\\\ \\ \\   __  \\                           " << endl;
    cout << "               \\ \\  \\_\\\\ \\ \\  \\ \\  \\                          " << endl;
    cout << "                \\ \\_______\\ \\__\\ \\__\\                         " << endl;
    cout << "                 \\|_______|\\|__|\\|__|                         " << endl;
    cout << "                                                             " << endl;
    cout << "   ___      ___ _______   ___       ___  ___  ________       " << endl;
    cout << "  |\\  \\    /  /|\\  ___ \\ |\\  \\     |\\  \\|\\  \\|\\   __  \\      " << endl;
    cout << "  \\ \\  \\  /  / | \\   __/|\\ \\  \\    \\ \\  \\\\\\  \\ \\  \\|\\  \\     " << endl;
    cout << "   \\ \\  \\/  / / \\ \\  \\_|/_\\ \\  \\    \\ \\   __  \\ \\   __  \\    " << endl;
    cout << "    \\ \\    / /   \\ \\  \\_|\\ \\ \\  \\____\\ \\  \\ \\  \\ \\  \\ \\  \\   " << endl;
    cout << "     \\ \\__/ /     \\ \\_______\\ \\_______\\ \\__\\ \\__\\ \\__\\ \\__\\  " << endl;
    cout << "      \\|__|/       \\|_______|\\|_______|\\|__|\\|__|\\|__|\\|__|  " << endl;
    cout << endl <<"--------------------------------------------------------------" << endl << endl;
    cout << "            Prima qualquer tecla para continuar!" <<endl;
    cout << endl <<"--------------------------------------------------------------" << endl;
    _getch(); // Recebe o char mas não o mostra
    while (_kbhit()) // Flush noutros caracteres no buffer
        _getch();
    Beep(320,200);
}

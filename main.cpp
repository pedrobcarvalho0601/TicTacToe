#include "files.h"
#include "game.h"
#include "mensagens.h"
#include <string>

using namespace std;

int main()
{

    CListaInteiros lista;
    Jogo player;
    mensagens mensagem;

    mensagem.inicio();

    string name = lista.solicitarUsername();

    player.funcionamentoJogo(name);


    return 0;
}

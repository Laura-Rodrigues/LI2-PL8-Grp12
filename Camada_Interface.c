//
// Created by laura on 12/03/20.
//

#include <stdio.h>
#include <string.h>
#include "Logica_Programa.h"
#include "Camada_dados.h"

#define BUF_SIZE 1024

// Função que permite mostrar o tabuleiro;
void mostrar_tabuleiro(ESTADO *estado){
    for (int i = 0; i < 8; i++) {
        printf("%c ", '8' - i );
        for (int j = 0; j < 8; j++) {
            COORDENADA c = {i,j};
            if (obter_estado_casa(estado ,c) == DOIS) printf("2 ");
            else if (obter_estado_casa(estado ,c) == UM) printf("1 ");
            else if (obter_estado_casa(estado ,c) == VAZIO) printf(". ");
            else if (obter_estado_casa(estado ,c) == PRETA) printf("# ");
            else if (obter_estado_casa(estado ,c) == BRANCA) printf("* ");
        }
        printf("\n");
    }
    printf("  ");
    for(int i = 0; i < 8; i++) {
        printf("%c ", 'a' + i);
    };
    printf("\n");

}

void prompt (ESTADO*e){
    int numerojogadas = obter_numero_de_jogadas (e) +1;
    int njogador = obter_jogador_atual (e);
    int njogadoratual;
    if (njogador == 1) njogadoratual = 2;
    else njogadoratual = 1;
    if (numerojogadas -1 == 0) {
        printf( "#0 PL1 -> e5 \n");
        printf ("#%d PL%d -> ", numerojogadas, njogadoratual);
    }
    else printf ("#%d PL%d -> ", numerojogadas, njogadoratual);
}


// Interpretador
int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char col[2], lin[2];
    prompt(e);
    if (strcmp (linha, "Q\n") == 0) return 0;
    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;
    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
        COORDENADA coord = {*col -'a', *lin -'1'};
        jogar(e, coord);
        mostrar_tabuleiro(e);
    }
    return 1;
}

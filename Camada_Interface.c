//
// Created by laura on 12/03/20.
//

#include <stdio.h>
#include <string.h>
#include "Logica_Programa.h"
#include "Camada_Interface.h"
#include "Camada_dados.h"

#define BUF_SIZE 1024

// Função que permite mostrar o tabuleiro;
void mostrar_tabuleiro(ESTADO *estado){
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            COORDENADA c = {i,j};
            if (i == 0 && j == 7) printf("2 ");
            else if (i == 7 && j == 0) printf("1 ");
            else if (obter_estado_casa(estado ,c) == VAZIO) printf(". ");
            else if (obter_estado_casa(estado ,c) == PRETA) printf("# ");
            else if (obter_estado_casa(estado ,c) == BRANCA) printf("* ");
        }
        printf("\n");
    }
}

// Interpretador
int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char col[2], lin[2];
    int numerojogadas = obter_numero_de_jogadas (e);
    int njogador = obter_jogador_atual (e);
    if (numerojogadas == 0) {
        printf( "#0 PL1 -> e5 \n");
        printf ("#%d PL%d -> ", numerojogadas+1, njogador );
    }
    else  printf ("#%d PL%d ->", numerojogadas, njogador );
    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;

    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
        COORDENADA coord = {*col -'a', *lin -'1'};
        jogar(e, coord);
        mostrar_tabuleiro(e);
    }
    return 1;
}

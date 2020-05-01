//
// Created by laura on 01/05/20.
//

#include "Funcoes_Ficheiro.h"
#include "Camada_Interface.h"
#include "Camada_dados.h"
#include "Logica_Programa.h"
#include "listas.h"
#include <stdio.h>
#include <stdlib.h>

void fptabuleiro(FILE *Projeto_Rastros, ESTADO *e){
    for (int i = 0; i < 8; i++) {
        //fprintf(Projeto_Rastros, "%c ", '8' - i );
        for (int j = 0; j < 8; j++) {
            COORDENADA c = {i,j};
            if (obter_estado_casa(e,c) == DOIS) fprintf(Projeto_Rastros, "2 ");
            else if (obter_estado_casa(e ,c) == UM) fprintf(Projeto_Rastros, "1 ");
            else if (obter_estado_casa(e ,c) == VAZIO) fprintf(Projeto_Rastros, ". ");
            else if (obter_estado_casa(e ,c) == PRETA) fprintf(Projeto_Rastros, "# ");
            else if (obter_estado_casa(e ,c) == BRANCA) fprintf(Projeto_Rastros, "* ");
        }
        fprintf(Projeto_Rastros, "\n");
    }
    fprintf(Projeto_Rastros, "  ");
    //for(int i = 0; i < 8; i++) {
    //    fprintf(Projeto_Rastros, "%c ", 'a' + i);
    //}
    fprintf(Projeto_Rastros, "\n");
}

int movsficheiro (ESTADO *estado, FILE *nome_fich) {
    char col1, col2;
    int ind, lin1, lin2, jogada = obter_numero_de_jogadas( estado ), jogador = obter_jogador_atual( estado );
    COORDENADA jog1, jog2;
    if ( jogador == 1 ) jogada--;
    for ( ind = 1; ind <= jogada ; ind++ ) {
        jog1 = obter_jogada( estado, ind, 1 );
        jog2 = obter_jogada( estado, ind, 2 );
        col1 = jog1.coluna + 'a';
        lin1 = jog1.linha + 1;
        col2 = jog2.coluna + 'a';
        lin2 = jog2.linha + 1;
        if ( ind < jogada )
            fprintf( nome_fich, "%02d: %c%d %c%d \n", ind, col1, lin1, col2, lin2 );
        else {
            if ( jogador == 2)
                fprintf(nome_fich, "%02d: %c%d \n", ind , col1, lin1 );
            else
                fprintf( nome_fich,"%02d: %c%d %c%d \n", ind, col1, lin1, col2, lin2 );
        }
    }
    return 0;
}

int gr ( char nomeficheiro[], ESTADO *estado ){
    FILE *fp = fopen( nomeficheiro, "w" );
    if( fp == NULL ){
        fclose( fp );
        return 0;
    } else {
        fptabuleiro( fp, estado );
        movsficheiro ( estado, fp );
        fclose(fp);
    }
    return 1;
}

ESTADO *ler ( char nomeficheiro[], ESTADO *estado ){
    FILE *fp = fopen( nomeficheiro, "r+" );
    if ( fp == NULL )
        printf("Nome inválido. \n");
    else{
        char str[BUF_SIZE];
        int jog, lin1 ,lin2;
        char col1, col2;
        estado = inicializar_estado();
        faz_primeira_jogada( estado );
        while ( ( fgets( str, BUF_SIZE, fp ) ) != NULL ){
            if ( sscanf( str, "0%d: %c%d %c%d", &jog, &col1, &lin1, &col2, &lin2 ) ){
                COORDENADA c0 = {col1 - 'a', lin1 - 1 };
                COORDENADA c1 = {col2 -'a' , lin2 - 1 };
                if ( jog != 0 && jogada_valida( estado, c0 ) )
                    altera_estado(estado, c0);
                if ( jog != 0 && jogada_valida( estado, c1 ) )
                    altera_estado( estado, c1 );
            }
        }
        fclose ( fp );
    }
    return estado;
}

int det_dist(COORDENADA c, int nj){
    int cc = c.coluna, cl = c.linha, total;
    if( nj == 1){
        total = cc+cl;
    } else {
        total = abs(cc-7) + abs(cl-7);
    }
    return total;
}

COORDENADA dist_euclidiana ( ESTADO *e, LISTA L){
    COORDENADA melhor, c;
    int menor = 32, dist, jogador = obter_jogador_atual(e);
    LISTA Temp;
    for ( Temp = L; !lista_esta_vazia(proximo(Temp)); Temp = remove_cabeca(Temp)){
        c = *(COORDENADA *) devolve_cabeca(Temp);
        dist = det_dist(c, jogador);
        if ( dist < menor ){
            menor = dist;
            melhor = c;
        }
    }
    return melhor;
}

int vitoria (ESTADO *e, COORDENADA C){
    int r = 0, j = obter_jogador_atual(e);
    if (j == 1 && C.coluna == 0 && C.linha == 0) r = 1;
    else if ( j == 2 && C.coluna == 7 && C.linha == 7) r = 1;
    else if ( vizivalide(e, C) >= 7){
        r = 1;
    }
    return r;
}

int derrota (ESTADO *e, COORDENADA c){
    int r = 0, j = obter_jogador_atual(e);
    if (j == 2 && c.coluna == 0 && c.linha == 0) r = 1;
    else if ( j == 1 && c.coluna == 7 && c.linha == 7) r = 1;
    return r;
}


LISTA remove_opcoes (ESTADO *e, LISTA l){
    LISTA T  = l, FINAL = criar_lista();
    int i, falha = 0;
    COORDENADA *c, f, ls[8] ;
    while (!lista_esta_vazia(proximo(T))){
        c = (COORDENADA *) devolve_cabeca(T);
        f = *c;
        coordvizinho(ls, f);
        for ( i = 0; i < 8; i++) {
            if (possivel(e, ls[i]) && !(cond_canto(ls[i]))) {
                if (vitoria ( e, ls[i]))
                    falha = 1;
            }
        }
        if ( falha == 1){
            printf("Removendo: %c%d \n", (c->coluna)+'a', c->linha+1);
            falha = 0;
        }
        else{
            FINAL = insere_cabeca(FINAL, c);
        }
        T = remove_cabeca(T);
    }
    return FINAL;
}


COORDENADA heuristica (ESTADO *e) {
    int i;
    COORDENADA c, ls[8], coord = obter_ultima_jogada(e);
    coordvizinho(ls, coord);
    LISTA L = criar_lista();
    for ( i = 0; i < 8; i++){
        if (possivel(e, ls[i]) && !(cond_canto(ls[i])) ) {
            if ( vitoria ( e, ls[i] ))
                return ls[i];
            if ( !(derrota (e , ls[i])) ){
                L = insere_cabeca(L, ls+i);
            }
        }
    }
    if ( len_Lista(L) == 1 ) c = *(COORDENADA *)devolve_cabeca(L);
    else {
        L = remove_opcoes(e,L);
        if ( len_Lista(L) > 1 ) c = dist_euclidiana ( e, L );
        else  c = * (COORDENADA *)devolve_cabeca(L);
    }
    return c;
}

COORDENADA jog2 ( ESTADO *e ) {
    COORDENADA c = heuristica(e);
    printf("A jogada recomendada é: %c%d. \n", c.coluna + 'a', c.linha + 1);
    return c;
}

COORDENADA jog ( ESTADO *e ){
    COORDENADA ls[8], atual = obter_ultima_jogada(e), final;
    int i;
    coordvizinho(ls, atual);
    LISTA L = criar_lista();
    for ( i = 0; i < 8; i++){
        if ( possivel (e, ls[i]) && !(cond_canto(ls[i])) ){
            L = insere_cabeca(L, ls+i);
        }
    }
    final = dist_euclidiana( e, L);
    printf("A jogada recomendada é: %c%d. \n", final.coluna+'a', final.linha+1);
    return final;
}
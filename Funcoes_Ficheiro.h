//
// Created by laura on 26/03/20.
//

#ifndef PROJETORASTROS_FUNCOES_FICHEIRO_H
#define PROJETORASTROS_FUNCOES_FICHEIRO_H

#include <stdio.h>
#include "Camada_dados.h"
#include "Listas/listas.h"

/**
\brief Permite imprimir o tabuleiro no ficheiro
@param Projeto_Rastros Apontador para o ficheiro
@param e Apontador para o estado
*/
void fptabuleiro(FILE *Projeto_Rastros, ESTADO *e);

/**
\brief Mostra a lista de movimentos no ficheiro
@param e Apontador para o estado
@param nome Apontador para o ficheiro
@returns 0
*/
int movsficheiro (ESTADO *e, FILE *nome);

/**
\brief Grava o tabuleiro
@param e Apontador para o estado
@param nomeficheiro Apontador para o ficheiro
@returns 1
*/
int gr(char nomeficheiro[], ESTADO *e);

/**
\brief Lê o tabuleiro e atualiza o estado
@param e Apontador para o estado
@param nomeficheiro Apontador para o ficheiro
@returns o estado alterado
*/
ESTADO *ler(char nomeficheiro[], ESTADO *e);

/**
\brief Mostra a lista de movimentos
@param e Apontador para o estado
@returns 0
*/
int movs ( ESTADO *e);

/**
\brief Permitir ao utilizador aceder a uma jogada anterior
@param e Apontador para o estado
@param dado Apontador para a jogada pretendida
@returns estado
*/
ESTADO* pos (ESTADO *e, int dado);

COORDENADA coordvizinho(ESTADO *e, int i);

int det_dist(COORDENADA c, int nj);

COORDENADA jog ( ESTADO *e);

//vizinhas livres numa lista
LISTA listvizinho(ESTADO *e, COORDENADA c);

//distancia as casas objetico
int *distcasa(int nj, COORDENADA c);

//Vê qual e a vizinha com mais casa pretas em volta;
int max(int *l);

//Escolhe a casa para mover
COORDENADA len_Viz(COORDENADA c, ESTADO *e);

//novaheuristica
ESTADO floodfill (ESTADO *e, LISTA li);

ESTADO jog2 (ESTADO *e);

#endif //PROJETORASTROS_FUNCOES_FICHEIRO_H

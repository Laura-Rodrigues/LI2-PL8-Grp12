//
// Created by laura on 12/03/20.
//

/**
@file Logica_Programa.h
Definição da função jogar e funções associadas a essa
*/

#ifndef PROJETORASTROS_LOGICA_PROGRAMA_H
#define PROJETORASTROS_LOGICA_PROGRAMA_H

#include "Camada_dados.h"

/**
\brief Testa se a Coordenada é vizinha da Coordenada anterior e se se encontra dentro do tabuleiro
@param e Apontador para o estado
@param c A coordenada
@returns 0 ou 1 para verdadeiro ou falso
*/
int vizinha(ESTADO *e, COORDENADA c);

/**
\brief Testa se a Jogada é válida
@param estado Apontador para o estado
@param c A coordenada
@returns 0 ou 1 para verdadeiro ou falso
*/
int jogada_valida (ESTADO *estado, COORDENADA c);

int vizivalide(ESTADO *e);

/**
\brief Testa se a Coordenada é igual à final
@param c A coordenada
@returns 0 ou 1 para verdadeiro ou falso
*/
int fim(COORDENADA c);

/**
\brief Modifica o estado ao jogar na casa correta se a jogada for válida
@param estado Apontador para o estado
@param c A coordenada
@returns 0 ou 1 para verdadeiro ou falso
*/
int jogar(ESTADO *estado, COORDENADA c);

#endif //PROJETORASTROS_LOGICA_PROGRAMA_H

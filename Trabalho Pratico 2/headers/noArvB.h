#ifndef __NO_ARV_B__
#define __NO_ARV_B__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesFornecidas.h"

typedef struct
{
    int chave;
    int rrnDados;
} Chave;

typedef struct
{
    char *folha;
    int *nroChavesNo;
    int *alturaNo;
    int *RRNdoNo;
    Chave *chaves;
    int *descendentes;
} noArvB;

/**
 * Aloca memoria para todos os ponteiros do RegistroDados.
 *
 * @param registros vetor de RegistroDados.
 * @param numReg quantidade de itens do vetor de RegistroDados
 */
void alocaNoArvB(noArvB **registros, int numReg);

/**
 * Desaloca memoria de todos os ponteiros do RegistroDados.
 *
 * @param registros vetor de RegistroDados.
 * @param numReg quantidade de itens do vetor de RegistroDados.
 */
void desalocaNoArvB(noArvB **registros, int numReg);

/**
 * Insere uma chave de forma ordenada em um no da arvore-B.
 *
 * @param  no No onde sera inserido a chave de forma ordenada.
 * @param Cn Chave a ser inserida.
 * @param PRn RRN da chave (Cn) no arquivo de dados.
 */
void insereChaveOrdenadaNoArvB(noArvB *no, Chave Cn, int filho);

/**
 * Imprime no da arvore B na tela
 */
void imprimeNoTela(noArvB *no);

/**
 * Preenche os valores padrao de um no da arvore B
 */
void inicializaNoArvB(noArvB *no);

int buscaChaveNo(noArvB *no, int chave, int* rrnBusca);
#endif
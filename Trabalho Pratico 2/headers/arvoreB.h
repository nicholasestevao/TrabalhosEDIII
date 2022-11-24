#ifndef __ARVORE_B_C__
#define __ARVORE_B_C__

#include <stdlib.h>
#include "arquivoBin.h"
#include "arquivoCsv.h"
#include "mensagens.h"
#include "cabecalhoArvB.h"
#include "noArvB.h"

/**
 * Tamanho da pagina de disco do arquivo da arvore-B.
 */
#define TAM_PAGINA_DISCO_ARV_B 65

//=====================================================================

/**
 * Grava registro de cabecalho no arquivo da arvore-B.
 * 
 * @param arquivoArvB Ponteiro para arquivo da arcore-B.
 * @param cabecalho Ponteiro para cabecalho a ser 
 * escrito no aquivo da arvore-B.  
 */
void escreverCabecalhoArquivoAvrB(FILE* arquivoArvB, cabecalhoArvB* cabecalho); 

/**
 * Escreve noh no arquivo da arvore-B.
 * 
 * @param arquivoArvB Ponteiro para arquivo da arcore-B.
 * @param cabecalho Ponteiro para cabecalho a ser 
 * escrito no aquivo da arvore-B. 
 * @param no Ponteiro para no a ser 
 * escrito no arquivo da arvore-B.
 */
void escreveNoArvB(FILE* arquivoArvB,  cabecalhoArvB* cabecalho, noArvB* no);

/**
 * Le registro de cabecalho do arquivo da arvore-B.
 * 
 * @param arquivoArvB Nome do arquivo.
 */
cabecalhoArvB* lecabecalhoArvB(FILE* arquivoArvB);

/**
 * Le registro de dados do arquivo da arvore-B por RRN
 * 
 * @param arquivoArvB Nome do arquivo.
 * @param RRN Numero Relativo do Registro.
 * 
 * @return Retorna um ponteiro para o dado do RRN.
 */ 
noArvB* leNoArvB_RRN(FILE* arquivoArvB, int RRN);


/**
 * Busca uma chave na arvore B
*/
int buscaChaveArvoreB(FILE* arquivoArvB, noArvB *raiz, int chave, int *RRN_resultado);

/**
 * Escreve um no da arvore B no arquivo de indice binario
*/
void escreveNoArqIndice(FILE* arqIndice,cabecalhoArvB* cabecalho ,noArvB* no, int rrn);

/**
 * Escreve o cabecalho da arvore B no arquivo de indice binario
*/
void escreveCabecalhoArqIndice(FILE* arqIndice,cabecalhoArvB* cabecalho);

/**
 * Insere um no na arvore B
*/
int insercaoArvoreB(FILE* arqIndice, int Cn, int PRn, noArvB* raiz, cabecalhoArvB* cabecalho);

/**
 * Imprime a arvore ordenada (para debug)
*/
void imprimeOrdenado(FILE * arq_indice, int rrn);

#endif
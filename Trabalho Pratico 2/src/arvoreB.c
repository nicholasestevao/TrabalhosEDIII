#define PROMOCAO 0
#define SEM_PROMOCAO 1
#define ERRO 2

#include "../headers/arvoreB.h"

CabecalhoArvB *lecabecalhoArvB(FILE *arquivoArvB)
{
    CabecalhoArvB *cabecalho;
    alocaCabecalhoArvB(&cabecalho);
    fseek(arquivoArvB, 0, SEEK_SET);

    fread(cabecalho->status, sizeof(char), 1, arquivoArvB);
    fread(cabecalho->noRaiz, sizeof(int), 1, arquivoArvB);
    fread(cabecalho->nroChavesTotal, sizeof(int), 1, arquivoArvB);
    fread(cabecalho->alturaArvore, sizeof(int), 1, arquivoArvB);
    fread(cabecalho->RRNproxNo, sizeof(int), 1, arquivoArvB);

    return cabecalho;
}

NoArvB *leNoArvB_RRN(FILE *arquivoArvB, int RRN)
{
    NoArvB *no;
    alocaNoArvB(&no, 1);

    long byteofset = (RRN * TAM_PAGINA_DISCO_ARV_B) + TAM_PAGINA_DISCO_ARV_B;

    fseek(arquivoArvB, byteofset, SEEK_SET);

    fread(no->folha, sizeof(char), 1, arquivoArvB);
    fread(no->nroChavesNo, sizeof(int), 1, arquivoArvB);
    fread(no->alturaNo, sizeof(int), 1, arquivoArvB);
    fread(no->RRNdoNo, sizeof(int), 1, arquivoArvB);
    fread(&(no->descendentes[0]), sizeof(int), 1, arquivoArvB);
    fread(&(no->chaves[0].chave), sizeof(int), 1, arquivoArvB);
    fread(&(no->chaves[0].rrnDados), sizeof(int), 1, arquivoArvB);
    fread(&(no->descendentes[1]), sizeof(int), 1, arquivoArvB);
    fread(&(no->chaves[1].chave), sizeof(int), 1, arquivoArvB);
    fread(&(no->chaves[1].rrnDados), sizeof(int), 1, arquivoArvB);
    fread(&(no->descendentes[2]), sizeof(int), 1, arquivoArvB);
    fread(&(no->chaves[2].chave), sizeof(int), 1, arquivoArvB);
    fread(&(no->chaves[2].rrnDados), sizeof(int), 1, arquivoArvB);
    fread(&(no->descendentes[3]), sizeof(int), 1, arquivoArvB);
    fread(&(no->chaves[3].chave), sizeof(int), 1, arquivoArvB);
    fread(&(no->chaves[3].rrnDados), sizeof(int), 1, arquivoArvB);
    fread(&(no->descendentes[4]), sizeof(int), 1, arquivoArvB);

    return no;
}

int buscaChaveArvoreB(FILE* arquivoArvB, NoArvB *raiz, int chave, int *RRN_resultado) {
    long nroPagDiscoAcessadas = 1;
    if(raiz == NULL) {
        return -1;
    }
    int RRN_busca = -1;

    *RRN_resultado = buscaChaveNo(raiz, chave, &RRN_busca);
    while(RRN_busca != -1) {
        NoArvB *no = leNoArvB_RRN(arquivoArvB, RRN_busca);
        *RRN_resultado = buscaChaveNo(no, chave, &RRN_busca);
        if(*(no->alturaNo) == 1 && *RRN_resultado == -1) {
            desalocaNoArvB(&no, 1);
            break;
        }
        desalocaNoArvB(&no, 1);
        nroPagDiscoAcessadas++;
    }
    return nroPagDiscoAcessadas;
}

void escreveNoArqIndice(FILE *arqIndice, CabecalhoArvB *cabecalho, NoArvB *no, int rrn)
{
    int byteoffset = TAM_PAGINA_DISCO_ARV_B * (rrn + 1);
    fseek(arqIndice, byteoffset, SEEK_SET);

    fwrite(no->folha, sizeof(char), 1, arqIndice);
    fwrite(no->nroChavesNo, sizeof(int), 1, arqIndice);
    fwrite(no->alturaNo, sizeof(int), 1, arqIndice);
    fwrite(no->RRNdoNo, sizeof(int), 1, arqIndice);
    fwrite(&(no->descendentes[0]), sizeof(int), 1, arqIndice);
    fwrite(&(no->chaves[0].chave), sizeof(int), 1, arqIndice);
    fwrite(&(no->chaves[0].rrnDados), sizeof(int), 1, arqIndice);
    fwrite(&(no->descendentes[1]), sizeof(int), 1, arqIndice);
    fwrite(&(no->chaves[1].chave), sizeof(int), 1, arqIndice);
    fwrite(&(no->chaves[1].rrnDados), sizeof(int), 1, arqIndice);
    fwrite(&(no->descendentes[2]), sizeof(int), 1, arqIndice);
    fwrite(&(no->chaves[2].chave), sizeof(int), 1, arqIndice);
    fwrite(&(no->chaves[2].rrnDados), sizeof(int), 1, arqIndice);
    fwrite(&(no->descendentes[3]), sizeof(int), 1, arqIndice);
    fwrite(&(no->chaves[3].chave), sizeof(int), 1, arqIndice);
    fwrite(&(no->chaves[3].rrnDados), sizeof(int), 1, arqIndice);
    fwrite(&(no->descendentes[4]), sizeof(int), 1, arqIndice);
}

void escreveCabecalhoArqIndice(FILE *arqIndice, CabecalhoArvB *cabecalho)
{
    fseek(arqIndice, 0, SEEK_SET);

    fwrite(cabecalho->status, sizeof(char), 1, arqIndice);
    fwrite(cabecalho->noRaiz, sizeof(int), 1, arqIndice);
    fwrite(cabecalho->nroChavesTotal, sizeof(int), 1, arqIndice);
    fwrite(cabecalho->alturaArvore, sizeof(int), 1, arqIndice);
    fwrite(cabecalho->RRNproxNo, sizeof(int), 1, arqIndice);

    char *lixo = malloc(sizeof(char) * TAM_PAGINA_DISCO_ARV_B);
    for (int i = 0; i < TAM_PAGINA_DISCO_ARV_B; i++)
    {
        lixo[i] = '$';
    }
    fwrite(lixo, sizeof(char), TAM_PAGINA_DISCO_ARV_B - 17, arqIndice);
    free(lixo);
}

/**
 * Realiza a rotina de split em um no da arvoreB.
 * Para isso recebe um nó cheio, uma chave para inserir (e seu filho a dreita se possuir) e um nó vazio.
 * Além disso retorna por paramentro a chave promovida e o seu filho a direita.
 * 
 * @param arq_indice Arquivo de indice (Arvore B) .bin.
 * @param chave Chave a ser inserida.
 * @param filho_chave No filho da chave a ser inserida.
 * @param pagina No cheio que ira sofrer split.
 * @param chave_promocao Chave que foi promovida retornada por parametro.
 * @param filho_chave_promocao Filho a direita da chave que sera promovida.
 * @param novaPagina No vazio para realizar o split (novo no criado).
 * @param rrnNovaPagina RRN desse novo no.
 */
void splitNosArvB(FILE *arq_indice, Chave chave, int filho_chave, NoArvB *pagina, Chave *chave_promocao, int *filho_chave_promocao, NoArvB *novaPagina, int rrnNovaPagina)
{
    // Recebe um nó cheio, uma chave para inserir e um nó vazio
    // Retorna a chave que foi promovida

    int no[16]; // vetor auxiliar que funciona como um no que cabe 5 chaves (armezana todos os ponteiros, chaves e RRNs)
    // Preenche vetor no com os dados do nó atual (cheio)
    for (int i = 0; i < 4; i++)
    {
        no[i * 3] = pagina->descendentes[i];
        no[i * 3 + 1] = (pagina->chaves[i].chave);
        no[i * 3 + 2] = (pagina->chaves[i].rrnDados);
    }
    no[12] = pagina->descendentes[4];
    // Preenche final do vetor (dados da quinta chave) no com -1
    for (int i = 13; i < 16; i++)
    {
        no[i] = -1;
    }

    // Encontra posicao onde a chave deve ser inserida
    int i = 0;
    while (i < 4 && no[i * 3 + 1] < (chave.chave))
    {
        i++;
    }

    // Desloca dados das chaves maiores do que a que será inserida para a direita (abre espaço para inserir a chave no "meio")
    no[15] = no[12]; // descendente[4]
    for (int j = 3; j >= i; j--)
    {
        no[j * 3 + 3] = no[j * 3];
        no[j * 3 + 4] = no[j * 3 + 1];
        no[j * 3 + 5] = no[j * 3 + 2];
    }
    // Insere dados da quinta chave no "meio"
    no[3 * i + 1] = (chave.chave);
    no[3 * i + 2] = (chave.rrnDados);
    no[3 * i + 3] = filho_chave;

    // Passa os dados do vetor no para a pagina original
    pagina->descendentes[0] = no[0];
    (pagina->chaves[0].chave) = no[1];
    (pagina->chaves[0].rrnDados) = no[2];
    pagina->descendentes[1] = no[3];
    (pagina->chaves[1].chave) = no[4];
    (pagina->chaves[1].rrnDados) = no[5];
    pagina->descendentes[2] = no[6];
    // Reseta as duas ultima das chaves do no que estava cheio
    (pagina->chaves[2].chave) = -1;
    (pagina->chaves[2].rrnDados) = -1;
    pagina->descendentes[3] = -1;
    (pagina->chaves[3].chave) = -1;
    (pagina->chaves[3].rrnDados) = -1;
    pagina->descendentes[4] = -1;

    // Preenche dados da chave a ser promovida (a que esta no meio do vetor no)
    (chave_promocao->chave) = no[7];
    (chave_promocao->rrnDados) = no[8];
    *filho_chave_promocao = rrnNovaPagina;

    // Passa os dados do vetor no para a nova pagina
    novaPagina->descendentes[0] = no[9];
    (novaPagina->chaves[0].chave) = no[10];
    (novaPagina->chaves[0].rrnDados) = no[11];
    novaPagina->descendentes[1] = no[12];
    (novaPagina->chaves[1].chave) = no[13];
    (novaPagina->chaves[1].rrnDados) = no[14];
    novaPagina->descendentes[2] = no[15];

    *(pagina->nroChavesNo) = 2;
    *(novaPagina->nroChavesNo) = 2;

    *(novaPagina->RRNdoNo) = rrnNovaPagina;

    // Novo nó criado no mesmo nivel
    *(novaPagina->alturaNo) = *(pagina->alturaNo);

    // Como estao no mesmo nivel, configuracao de folha permanece a mesma
    if (*(pagina->alturaNo) != 1)
    {
        *(pagina->folha) = '0';
        *(novaPagina->folha) = '0';
    }
    else
    {
        *(pagina->folha) = '1';
        *(novaPagina->folha) = '1';
    }
}

/**
 * Insere um no na arvore B de forma recursiva, descendo na arvore B
 * ate achar um no folha onde a chave deve ser inserida. Caso nao haja espaco
 * realiza a subrotina de split.
 * 
 * @param arq_indice Arquivo de indice (Arvore B) .bin.
 * @param Cn Chave (par chave e RRN do dado) a ser insereida.
 * @param raiz Noh raiz da Arvore B.
 * @param cabecalho Cabecalho do arquivo de indice.
 * @param RRN_atual RRN do noh atual em que a recursao estah.
 * @param chave_promocao Chave (par chave e RRN do dado) que serah promovida.
 * @param filho_chave_promocao Filho a direita da chave que sera promovida.
 */
int insercaoRecursiva(FILE *arqIndice, Chave Cn, NoArvB *raiz, CabecalhoArvB *cabecalho, int RRN_atual, Chave *chave_promocao, int *filho_chave_promocao)
{

    NoArvB *pagina;
    int resBusca = -1;
    int rrnBusca = -1; // rrn de onde a chave buscada deveria estar

    // Desce na arvore ate encontrar o no onde a chave deve ser inserida
    if (RRN_atual == -1)
    {
        *chave_promocao = Cn;
        *filho_chave_promocao = -1;
        return PROMOCAO;
    }
    else
    {
        if (RRN_atual == *(cabecalho->noRaiz))
        {
            pagina = raiz;
        }
        else
        {
            pagina = leNoArvB_RRN(arqIndice, RRN_atual);
        }
        resBusca = buscaChaveNo(pagina, (Cn.chave), &rrnBusca);
    }

    if(resBusca != -1){
        //Chave duplicada
        if (RRN_atual != *(cabecalho->noRaiz))
        {
            desalocaNoArvB(&pagina, 1);
        }
        return ERRO;
    }

    Chave chave_promocao_below;
    (chave_promocao_below.chave) = -1;
    (chave_promocao_below.rrnDados) = -1;
    int filho_chave_promocao_below = -1;

    // Tenta inserir na posicao (descendente) onde a chave deveria estar
    int retorno = insercaoRecursiva(arqIndice, Cn, raiz, cabecalho, rrnBusca, &chave_promocao_below, &filho_chave_promocao_below);

    if (retorno == SEM_PROMOCAO || retorno == ERRO)
    {
        if (RRN_atual != *(cabecalho->noRaiz))
        {
            desalocaNoArvB(&pagina, 1);
        }
        return retorno;
    }
    else if (*(pagina->nroChavesNo) < 4)
    { // se tem espaço no nó
        insereChaveOrdenadaNoArvB(pagina, chave_promocao_below, filho_chave_promocao_below);
        escreveNoArqIndice(arqIndice, cabecalho, pagina, *(pagina->RRNdoNo));
        if (RRN_atual != *(cabecalho->noRaiz))
        {
            desalocaNoArvB(&pagina, 1);
        }
        return SEM_PROMOCAO;
    }
    else
    { // se nao tem espaco no nó -> ocorre split
        // Cria novo no
        NoArvB *nova_pagina;
        alocaNoArvB(&nova_pagina, 1);
        // Divide as chaves entre os nós e decide qual vai ser promovida
        splitNosArvB(arqIndice, chave_promocao_below, filho_chave_promocao_below, pagina, chave_promocao, filho_chave_promocao, nova_pagina, *(cabecalho->RRNproxNo));

        *(cabecalho->RRNproxNo) = *(cabecalho->RRNproxNo) + 1; // incrementa proxRRN

        // Grava nos atualizados no arquivo de indice
        escreveNoArqIndice(arqIndice, cabecalho, pagina, *(pagina->RRNdoNo));

        escreveNoArqIndice(arqIndice, cabecalho, nova_pagina, *(nova_pagina->RRNdoNo));
        if (RRN_atual != *(cabecalho->noRaiz))
        {
            desalocaNoArvB(&pagina, 1);
        }
        desalocaNoArvB(&nova_pagina, 1);

        return PROMOCAO;
    }
    return ERRO;
}

int insercaoArvoreB(FILE *arqIndice, int Cn, int PRn, NoArvB *raiz, CabecalhoArvB *cabecalho)
{
    // Cria nova chave
    Chave chave;
    (chave.chave) = Cn;
    (chave.rrnDados) = PRn;

    if (*(cabecalho->noRaiz) == -1)
    {
        // Situacao inicial (nenhum nó nem registro)
        insereChaveOrdenadaNoArvB(raiz, chave, -1);
        *(raiz->folha) = '1';
        *(raiz->alturaNo) = 1;
        *(raiz->nroChavesNo) = 1;
        *(raiz->RRNdoNo) = 0;
        escreveNoArqIndice(arqIndice, cabecalho, raiz, 0);
        *(cabecalho->noRaiz) = 0;
        *(cabecalho->alturaArvore) = 1;
        *(cabecalho->nroChavesTotal) = 1;
        *(cabecalho->RRNproxNo) = 1;
        return SEM_PROMOCAO;
    }
    else
    {
        // Inicializa variaveis da chave promovida
        Chave chave_promo;
        (chave_promo.chave) = -1;
        (chave_promo.rrnDados) = -1;
        int filho_chave_promo = -1;

        if (insercaoRecursiva(arqIndice, chave, raiz, cabecalho, *(cabecalho->noRaiz), &chave_promo, &filho_chave_promo) == PROMOCAO)
        {
            // Ocorreu split na raiz (necessario criar nova raiz)
            inicializaNoArvB(raiz);
            *(raiz->RRNdoNo) = *(cabecalho->RRNproxNo);    // nova raiz armazenada em um novo no
            raiz->descendentes[0] = *(cabecalho->noRaiz);  // descendente esquerdo é a raiz antiga
            raiz->descendentes[1] = filho_chave_promo;     // descendente direito é o filho da chave que foi promovida (a nova raiz)
            (raiz->chaves[0].chave) = (chave_promo.chave); // nova raiz é a chave que foi promovida
            (raiz->chaves[0].rrnDados) = (chave_promo.rrnDados);
            *(raiz->nroChavesNo) = 1;
            *(cabecalho->RRNproxNo) = *(cabecalho->RRNproxNo) + 1;       // incrementa o proxRRN pois foi inserido um novo no
            *(cabecalho->noRaiz) = *(raiz->RRNdoNo);                     // armazena RRN da nova raiz
            *(raiz->alturaNo) = *(cabecalho->alturaArvore) + 1;          // Altura da raiz um nivel acima (arvore aumentou um nivel)
            *(cabecalho->alturaArvore) = *(cabecalho->alturaArvore) + 1; // Aumenta a altura da arvore
            *(raiz->folha) = '0';                                        // raiz nao é folha pois tem filhos

            escreveCabecalhoArqIndice(arqIndice, cabecalho);
            escreveNoArqIndice(arqIndice, cabecalho, raiz, *(raiz->RRNdoNo));
        }
        *(cabecalho->nroChavesTotal) = *(cabecalho->nroChavesTotal) + 1;
        return SEM_PROMOCAO;
    }
    return ERRO;
}

void imprimeOrdenado(FILE *arq_indice, int rrn)
{
    NoArvB *no_atual = leNoArvB_RRN(arq_indice, rrn);
    for (int i = 0; i < 4; i++)
    {
        if (no_atual->descendentes[i] != -1)
        {
            imprimeOrdenado(arq_indice, no_atual->descendentes[i]);
            printf("%d ", (no_atual->chaves[i].chave));
        }
        else if ((no_atual->chaves[i].chave) != -1)
        {
            printf("%d ", (no_atual->chaves[i].chave));
        }
        else
        {
            break;
        }
    }
}
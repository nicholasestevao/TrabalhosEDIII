#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/funcoesFornecidas.h"
#include "../headers/arquivoBin.h"
#include "../headers/funcionalidades.h"


int main(int argC, char *argV[]){

    int opcao;
    char * nome_arquivo = malloc(sizeof(char)*20);
    
    scanf("%d %s", &opcao, nome_arquivo);
    
    //Create table (1) - Isaac e Nicholas
    //le do csv
    
    //Select (2) - Nicholas
    // mostra tudo (so le do binario)
    if(opcao == 2){
        funcionalidade2Select(nome_arquivo);
    }    

    //Select where (3) - Isaac
    //le comando da tela
    if(opcao == 3){
            //numeros de buscas a serem realizadas
            int numBuscas;
            scanf("%d", &numBuscas);
            printf("%d--%s--%d--", opcao, nome_arquivo,numBuscas);
            char * nome_campo = malloc(sizeof(char)*20);
            char * valor_campo = malloc(sizeof(char)*800);
             
            for(int i=0; i<numBuscas; i++){
                scanf("%s", nome_campo);
                fgetc(stdin);
                fgets(valor_campo, 799, stdin);
                valor_campo[strlen(valor_campo)-1] = '\0';
                


            }
    }


    //Remocao logica (4) - Isaac
    //le comando da tela

    //Insercao (5) - Nicholas
    //insere no binario
    //le da tela

    //Compactacao (6) - Isaac
    //cria outro binario
    
    return 0;
}   


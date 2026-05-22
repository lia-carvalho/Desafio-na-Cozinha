#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 97

int calcularHash(char *chave){
    int hash = 0; 

    while(*chave){
        hash = (hash * 31 + *chave) % TAMANHO_HASH;
        chave++;
    }

        return hash;
}

void inicializarTabela(HashNode *tabela[]){
    for (int i=0; i< TAMANHO_HASH ; i++){
        tabela[i]= NULL;
    }
}
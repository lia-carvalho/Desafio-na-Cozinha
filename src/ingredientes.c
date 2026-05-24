#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ingredientes.h"

static TrieIngrediente* criarNoIngrediente(){
    TrieIngrediente* no = (TrieIngrediente*)malloc(sizeof(TrieIngrediente));

    if(no == NULL){
        printf("erro ao criar no ingrediente\n");
        exit(1);
    }

    no->fim = false;

    no->receitasComIngrediente = (ListaReceitas*)malloc(sizeof(ListaReceitas));
    if(no->receitasComIngrediente != NULL){
        no->receitasComIngrediente->inicio = NULL;
        no->receitasComIngrediente->tamanho = 0;
    }
    for(int i= 0; i <256; i++){
        no->filhos[i] = NULL;
    }
    return no;
}

ArvoreIngredientes* criarTrieIngredientes() {
    ArvoreIngredientes* trie = (ArvoreIngredientes*)malloc(sizeof(ArvoreIngredientes));
    if(trie== NULL){
        printf("falha ao alocar a arvore de ingredientes\n");
        exit(1);
    }
    trie->raiz = criarNoIngrediente();
    return trie;
}

void vincularIngrediente(ArvoreIngredientes* trie, const char* ingrediente, Receita* receita){
    if(trie == NULL || ingrediente == NULL || strlen(ingrediente) == 0 || receita == NULL ){
        return;
    }

    TrieIngrediente* atual = trie->raiz;

    for(int i = 0; ingrediente[i] != '\0'; i++){
        unsigned char c = tolower((unsigned char) ingrediente[i]);

        if(atual->filhos[c] == NULL){
            atual->filhos[c] = criarNoIngrediente();
        }
        atual = atual->filhos[c];
    }
    atual->fim = true;

    adicionarNaLista(atual->receitasComIngrediente, receita);
}

static void AcharReceitas(TrieIngrediente* no, ListaReceitas* resultados){
    if(no == NULL) return;

    if(no->fim && no->receitasComIngrediente != NULL){
        NoLista* atual = no->receitasComIngrediente->inicio;
        while(atual != NULL){
            adicionarNaLista(resultados, atual->receita);
            atual = atual->prox;
        }
    }

    for(int i = 0; i< 256; i++){
        if(no->filhos[i] != NULL){
            acharReceitas(no->filhos[i], resultados);
        }
    }
}

ListaReceitas* buscarIngredientePorPrefixo(ArvoreIngredientes* trie, const char* prefixo){
    ListaReceitas* resultados = (ListaReceitas*)malloc(sizeof(ListaReceitas));
    resultados->inicio = NULL;
    resultados->tamanho = 0;
    
    if(trie == NULL || prefixo == NULL || strlen(prefixo) == 0){
        return resultados;
    }
    TrieIngrediente* atual = trie->raiz;

    for(int i = 0; prefixo[i] != '\0'; i++){
        unsigned char c = tolower((unsigned char)prefixo[i]);

        if(atual->filhos[c] == NULL){
            return resultados;
        }
        atual = atual->filhos[c];
    }
   buscarReceitas(atual, resultados);
    return resultados;
}

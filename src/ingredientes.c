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
    if(trie == NULL || ingrediente == NULL | strlen(ingrediente) == 0 || receita == NULL ){
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

ListaReceitas* buscarIngrediente(ArvoreIngredientes* trie, const char* ingrediente){
    if(trie == NULL || ingrediente == NULL || strlen(ingrediente) == 0){
        return NULL;
    }
    TrieIngrediente* atual = trie->raiz;

    for(int i = 0; ingrediente[i] != '\0'; i++){
        unsigned char c = tolower((unsigned char)ingrediente[i]);

        if(atual->filhos[c] == NULL){
            return NULL;
        }
        atual = atual->filhos[c];
    }
    if(atual->fim){
        return atual->receitasComIngrediente;
    }
    return NULL;
}
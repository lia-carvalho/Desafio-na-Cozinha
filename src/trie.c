#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

TrieNode* criarNo() {
    TrieNode* novoNo = (TrieNode*)malloc(sizeof(TrieNode));
    novoNo->fim = false;
    novoNo->receita = NULL;
    for (int i = 0; i < 256; i++) {
        novoNo->filhos[i] = NULL;
    }
    return novoNo;
}

void adicionarNaLista(ListaReceitas* lista, Receita* receita) {
    NoLista* novoNo = (NoLista*)malloc(sizeof(NoLista));
    novoNo->receita = receita;
    novoNo->prox = lista->inicio;
    lista->inicio = novoNo;
    lista->tamanho++;
}

void coletarSubarvores(TrieNode* no, ListaReceitas* resultados) {
    if (no == NULL) return;
    if (no->fim && no->receita != NULL) {
        adicionarNaLista(resultados, no->receita);
    }
    
    for (int i = 0; i < 256; i++) {
        if (no->filhos[i] != NULL) {
            coletarSubarvores(no->filhos[i], resultados);
        }
    }
}

ArvoreTrie* criarTrie() {
    ArvoreTrie* trie = (ArvoreTrie*)malloc(sizeof(ArvoreTrie));
    trie->raiz = criarNo();
    return trie;
}

void inserirTrie(ArvoreTrie* trie, const char* nome, Receita* receita) {
    if(nome == NULL || strlen(nome) == 0) return;

    TrieNode* atual = trie->raiz;

    for (int i = 0; nome[i] != '\0'; i++) {
        unsigned char c = tolower((unsigned char)nome[i]);
        
        if (atual->filhos[c] == NULL) {
            atual->filhos[c] = criarNo();
        }
        atual = atual->filhos[c];
    }
    atual->fim = true;
    atual->receita = receita;
}

ListaReceitas* buscarPrefixo(ArvoreTrie* trie, const char* prefixo) {
    ListaReceitas* resultados = (ListaReceitas*)malloc(sizeof(ListaReceitas));
    resultados->inicio = NULL;
    resultados->tamanho = 0;

    if(prefixo == NULL || strlen(prefixo) == 0) {
        return resultados; 
    }
    
    TrieNode* atual = trie->raiz;

    for (int i = 0; prefixo[i] != '\0'; i++) {
        unsigned char c = tolower((unsigned char)prefixo[i]);
        
        if (atual->filhos[c] == NULL) {
            return resultados; 
        }
        atual = atual->filhos[c];
    }

    
    coletarSubarvores(atual, resultados);
    return resultados;
}
#ifndef trie_h
#define trie_h

#include "receitas.h"
#include <stdbool.h>

typedef struct TrieNode {
    struct TrieNode* filhos[256];
    bool fim;
    Receita* receita;
} TrieNode;

typedef struct {
    TrieNode* raiz;
} ArvoreTrie;

ArvoreTrie* criarTrieNode();

void inserirTrie(ArvoreTrie* trie, const char* nome, Receita* receita);  

ListaReceitas* buscarPrefixo(ArvoreTrie* trie, const char* prefixo);

void liberarTrie(TrieNode* no);


#endif 

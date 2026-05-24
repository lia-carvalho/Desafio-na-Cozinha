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

ArvoreTrie* criarTrie();

void inserirTrie(ArvoreTrie* trie, const char* nome, Receita* receita);  

ListaReceitas* buscarPrefixo(ArvoreTrie* trie, const char* prefixo);

#endif 

#ifndef ingredientes_h
#define ingredientes_h
#include <stdbool.h>
#include "trie.h"

typedef struct TrieIngrediente{
    struct TrieIngrediente* filhos[256];
    bool fim;
    ListaReceitas* receitasComIngrediente;
} TrieIngrediente;

typedef struct{
    TrieIngrediente* raiz;
} ArvoreIngredientes;

ArvoreIngredientes* criarTrieIngredientes();
void vincularIngrediente(ArvoreIngredientes* trie, const char* ingrediente, Receita* receita);
ListaReceitas* buscarIngrediente(ArvoreIngredientes* trie, const char* ingrediente);

#endif
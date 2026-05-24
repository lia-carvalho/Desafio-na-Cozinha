#ifndef HASH_H
#define HASH_H

#include "receitas.h"


typedef struct HashNode{
    Receita *receita;
    struct HashNode *prox;
} HashNode;

int calcularHash(char *chave);
void inicializarTabela(HashNode *tabela[]);
void inserirReceita(HashNode *tabela[], Receita *novaReceita);

Receita* buscarReceita(HashNode *tabela[], char *nomeBuscado); 

unsigned int calcularChecksum(Receita *r);
void executarModoInvestigacao(HashNode *tabela[]);
void buscarPorCategoria(HashNode *tabela[], char *categoriaBuscada);

#endif


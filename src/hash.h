#ifndef HASH_H
#define HASH_H


typedef struct{
    char id[30];
    char nome[150];
    char categoria[60];
    char pais[50];
    char ingredientes[600];
    float preco;
    int tempoPreparo;
}Receita;

typedef struct HashNode{
    Receita *receita;
    struct HashNode *prox;
} HashNode;

int calcularHash(char *chave);
void inicializarTabela(HashNode *tabela[]);
#endif


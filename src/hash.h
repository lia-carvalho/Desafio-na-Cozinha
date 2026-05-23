#ifndef HASH_H
#define HASH_H


typedef struct{
    char id[30];
    char nome[150];
    char categoria[60];
    char pais[50];
    char ingredientes[600];
    int tempoPreparo;
    float preco;
    float avaliacao;
    unsigned int checksum;  //para o modo investigação
}Receita;

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

#endif


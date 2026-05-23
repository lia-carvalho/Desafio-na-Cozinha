#ifndef receitas_h
#define receitas_h

typedef struct {
    int id;
    char nome[150];
    char categoria[60];
    char pais[50];
    char ingredientes[600];
    int tempoPreparo; 
    double preco;
    double avaliacao;
    unsigned int checksum;
} Receita;

typedef struct NoLista {
    Receita* receita;
    struct NoLista* prox;
} NoLista;

typedef struct {
    NoLista* inicio;
    int tamanho;
} ListaReceitas;

#endif

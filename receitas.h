#ifndef receitas_h
#define receitas_h

typedef struct {
    int id;
    char nome[100];
    char categoria[50];
    int tempoPreparo; 
    double custo;
    double avaliacao;
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

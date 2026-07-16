#ifndef receitas_h
#define receitas_h

#define MAX_DEPENDENCIAS 10

typedef struct {
    char id[30];
    char nome[150];
    char categoria[60];
    char pais[50];
    char ingredientes[600];
    int tempoPreparo; 
    double preco;
    double avaliacao;
    unsigned int checksum;      //para o modo investigação
    
    char ids_dependencias[MAX_DEPENDENCIAS][30];
    int numero_dependencias;   //contador de dependencias de cada receita
} Receita;

typedef struct NoLista {
    Receita* receita;
    struct NoLista* prox;
} NoLista;

typedef struct {
    NoLista* inicio;
    int tamanho;
} ListaReceitas;

void adicionarNaLista(ListaReceitas* lista, Receita* receita);
#endif

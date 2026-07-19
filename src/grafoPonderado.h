#ifndef GRAFOPONDERADO_H
#define GRAFOPONDERADO_H

typedef struct ArestaLogistica{
    int indiceDestino;
    int peso;
    struct ArestaLogistica* proximo;
} ArestaLogistica;

typedef struct VerticeLogistico{
    char nomeRegiao[100];
    ArestaLogistica* arestas;
} VerticeLogistico;

typedef struct GrafoLogistico{
    VerticeLogistico* listaAdjacencia;
    int totalVertices;
} GrafoLogistico;

GrafoLogistico* criarGrafoLogistico(int totalVertices);
void adicionarArestaLogistica(GrafoLogistico* grafo, int origem, int destino, int peso);
void liberarGrafoLogistico(GrafoLogistico* grafo);
void imprimirGrafoLogistico(GrafoLogistico* grafo);
void definirNomeRegiao(GrafoLogistico* grafo, int indice, const char* nome);
#endif

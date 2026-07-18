#ifndef GRAFOS_H
#define GRAFOS_H

#include "receitas.h"

typedef struct Aresta{
    int indice_destino;
    struct Aresta* proximo;
}Aresta;

typedef struct Vertice{
    Receita* receita;
    Aresta* arestas;   //arestas que saem do vértice
    int cor;
}Vertice;

typedef struct Grafo{
    int total_vertices;
    Vertice* lista_adjacencia;
}Grafo;

Grafo* criarGrafo(int total_vertices);
void conectarDependencias(Grafo* grafo, Receita* catalogo[], int total_vertices);
void verificarErrosDependencia(Grafo* grafo, Receita* catalogo[], int total_vertices);
void ordemProducao(Grafo* grafo, Receita* catalogo[], int total_vertices, int indiceAlvo);
void liberarGrafo(Grafo* grafo, int total_vertices);
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

Grafo* criarGrafo(int total_vertices){
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->total_vertices = total_vertices;

    grafo->lista_adjacencia = (Vertice*) malloc (total_vertices * (Vertice));

    for (int i=0; i< total_vertices; i++){
        grafo->lista_adjacencia[i].receita = NULL;
        grafo->lista_adjacencia[i].arestas = NULL;
        grafo->lista_adjacencia[i].cor = 0;  //Branco(não visitado)
    }

    return grafo;
}

void adicionarAresta(Grafo* grafo, int origem, int destino){
    Aresta* novaAresta = (Aresta*) malloc(sizeof(Aresta));
    novaAresta->indice_destino = destino;

    novaAresta->proximo = grafo->lista_adjacencia[origem].arestas;
    grafo->lista_adjacencia[origem].arestas = novaAresta;
}
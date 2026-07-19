#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafoPonderado.h"

GrafoLogistico* criarGrafoLogistico(int totalVertices) {
    GrafoLogistico* grafo = (GrafoLogistico*)malloc(sizeof(GrafoLogistico));
    grafo->totalVertices = totalVertices;
    grafo->listaAdjacencia = (VerticeLogistico*)malloc(totalVertices * sizeof(VerticeLogistico));

    for (int i = 0; i < totalVertices; i++) {
        strcpy(grafo->listaAdjacencia[i].nomeRegiao, "Regiao nao definida");
        grafo->listaAdjacencia[i].arestas = NULL;
    }

    return grafo;

}

void definirNomeRegiao(GrafoLogistico* grafo, int indice, const char* nome) {
    if (indice >= 0 && indice < grafo->totalVertices) {
        strcpy(grafo->listaAdjacencia[indice].nomeRegiao, nome);
    }
}

void adicionarArestaLogistica(GrafoLogistico* grafo, int origem, int destino, int peso) {
    ArestaLogistica* novaAresta = (ArestaLogistica*)malloc(sizeof(ArestaLogistica));
    novaAresta->indiceDestino = destino;
    novaAresta->peso = peso;
    novaAresta->proximo = grafo->listaAdjacencia[origem].arestas;
    grafo->listaAdjacencia[origem].arestas = novaAresta;

    ArestaLogistica* arestaInversa = (ArestaLogistica*)malloc(sizeof(ArestaLogistica));
    arestaInversa->indiceDestino = origem;
    arestaInversa->peso = peso;
    arestaInversa->proximo = grafo->listaAdjacencia[destino].arestas;
    grafo->listaAdjacencia[destino].arestas = arestaInversa;
}

void imprimirGrafoLogistico(GrafoLogistico* grafo) {
    for (int i = 0; i < grafo->totalVertices; i++) {
        printf("%d- %s tem rotas para: ", i,  grafo->listaAdjacencia[i].nomeRegiao);

        ArestaLogistica* arestaAtual = grafo->listaAdjacencia[i].arestas;
        while (arestaAtual != NULL) {
            printf( "%d- %s Tempo estimado: %d minutos; ", arestaAtual->indiceDestino, grafo->listaAdjacencia[arestaAtual->indiceDestino].nomeRegiao, arestaAtual->peso);
            arestaAtual = arestaAtual->proximo;
        }
        printf("\n");
    }
}

void liberarGrafoLogistico(GrafoLogistico* grafo) {
    for (int i = 0; i < grafo->totalVertices; i++) {
        ArestaLogistica* arestaAtual = grafo->listaAdjacencia[i].arestas;
        while (arestaAtual != NULL) {
            ArestaLogistica* temp = arestaAtual;
            arestaAtual = arestaAtual->proximo;
            free(temp);
        }
    }
    free(grafo->listaAdjacencia);
    free(grafo);
}

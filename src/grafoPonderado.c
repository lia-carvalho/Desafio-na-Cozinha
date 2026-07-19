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

void calcularRotaEntrega(GrafoLogistico* grafo, int origem, int destino) {
    
    int* distancias = (int*)malloc(grafo->totalVertices * sizeof(int));
    int* anteriores = (int*)malloc(grafo->totalVertices * sizeof(int));
    bool* visitados = (bool*)malloc(grafo->totalVertices * sizeof(bool));

    for (int i = 0; i < grafo->totalVertices; i++) {
        distancias[i] = infinito;
        anteriores[i] = -1;
        visitados[i] = false;
    }

    distancias[origem] = 0;

    for (int count = 0; count < grafo->totalVertices - 1; count++) {
        int u = -1;
        int min = infinito;
        for (int v = 0; v < grafo->totalVertices; v++) {
            if (!visitados[v] && distancias[v] < min) {
                min = distancias[v];
                u = v;
            }
        }
        if(u == -1) {
            break;
        }
        visitados[u] = true;

        ArestaLogistica* arestaAtual = grafo->listaAdjacencia[u].arestas;
        while (arestaAtual != NULL) {
            int v = arestaAtual->indiceDestino;
            int pesoAresta = arestaAtual->peso;

            if (!visitados[v] && distancias[u] != infinito && distancias[u] + pesoAresta < distancias[v]) {
                distancias[v] = distancias[u] + pesoAresta;
                anteriores[v] = u;
            }
            arestaAtual = arestaAtual->proximo;
        }
    }

    if (distancias[destino] == infinito) {
        printf("Nao existe rota de entrega de %s para %s.\n", grafo->listaAdjacencia[origem].nomeRegiao, grafo->listaAdjacencia[destino].nomeRegiao);
    } else {
        printf("Rota de entrega de %s para %s:\n", grafo->listaAdjacencia[origem].nomeRegiao, grafo->listaAdjacencia[destino].nomeRegiao);
        printf("Tempo estimado: %d minutos\n", distancias[destino]);
        printf("Caminho: ");

        int* caminho = (int*)malloc(grafo->totalVertices * sizeof(int));
        int passadas = 0;
        int atual = destino;

        while (atual != -1) {
            caminho[passadas++] = atual;
            atual = anteriores[atual];
        }

        for (int i = passadas - 1; i >= 0; i--) {
            printf("%s", grafo->listaAdjacencia[caminho[i]].nomeRegiao);
            if (i > 0) {
                printf(" -> ");
            } 
        } 
            printf("\n");
             free(caminho);
        }
    free(distancias);
    free(anteriores);
    free(visitados);
    }

void calcularDistribuicao(GrafoLogistico* grafo) {
        int* chaves = (int*)malloc(grafo->totalVertices * sizeof(int));
        int* pai = (int*)malloc(grafo->totalVertices * sizeof(int));
        bool* naArvore = (bool*)malloc(grafo->totalVertices * sizeof(bool));

        for(int i = 0; i < grafo->totalVertices; i++) {
            chaves[i] = infinito;
            pai[i] = -1;
            naArvore[i] = false;
        }

        chaves[0] = 0;

        for(int count = 0; count < grafo->totalVertices - 1; count++) {
            int u = -1;
            int min = infinito;

            for(int v = 0; v < grafo->totalVertices; v++) {
                if(!naArvore[v] && chaves[v] < min) {
                    min = chaves[v];
                    u = v;
                }
            }

            if(u == -1) {
                break;
            }   

            naArvore[u] = true;

            ArestaLogistica* arestaAtual = grafo->listaAdjacencia[u].arestas;
            while(arestaAtual != NULL) {
                int v = arestaAtual->indiceDestino;
                int pesoAresta = arestaAtual->peso;

                if(!naArvore[v] && pesoAresta < chaves[v]) {
                    chaves[v] = pesoAresta;
                    pai[v] = u;
                }
                arestaAtual = arestaAtual->proximo;
            }
        }

        printf("Menor caminho para distribuicao de produtos:\n");
        int custoTotal = 0;

        for(int i = 1; i < grafo->totalVertices; i++) {
            if(pai[i] != -1) {
                printf("Conectar %s a %s: Custo = %d\n", grafo->listaAdjacencia[pai[i]].nomeRegiao, grafo->listaAdjacencia[i].nomeRegiao, chaves[i]);
                custoTotal += chaves[i];
            }
        }

        printf("Custo total da distribuicao: %d\n", custoTotal);

        free(chaves);
        free(pai);
        free(naArvore);
    }

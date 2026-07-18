#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

Grafo* criarGrafo(int total_vertices){
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->total_vertices = total_vertices;

    grafo->lista_adjacencia = (Vertice*) malloc (total_vertices * sizeof(Vertice));

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

void conectarDependencias(Grafo* grafo, Receita* catalogo[], int total_vertices){
 for(int i=0; i < total_vertices; i++){
        int num_dependencias = catalogo[i]->numero_dependencias;

        for(int j=0; j< num_dependencias;j++){
            char* id_procurado = catalogo[i]->ids_dependencias[j];

            int indice_origem = -1;
            for(int k= 0; k < total_vertices; k++){
                if( strcmp(catalogo[k]->id, id_procurado) == 0){
                    indice_origem = k;
                    break;
                }
            }
            if(indice_origem != -1){
                adicionarAresta(grafo, indice_origem, i); //i = receita atual que depende de k
            }
        }
    }
}
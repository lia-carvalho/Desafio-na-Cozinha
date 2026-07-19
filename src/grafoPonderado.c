#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
void calcularRotaEmergenciaBFS(GrafoLogistico* grafo, int origem, int destino) {
    int n = grafo->totalVertices;
    
    int* fila = (int*)malloc(n * sizeof(int));
    int* anteriores = (int*)malloc(n * sizeof(int));
    bool* visitados = (bool*)malloc(n * sizeof(bool));
    
    int inicioFila = 0, fimFila = 0;

    for (int i = 0; i < n; i++) {
        visitados[i] = false;
        anteriores[i] = -1;
    }

    visitados[origem] = true;
    fila[fimFila++] = origem;

    bool encontrou = false;

    while (inicioFila < fimFila) {
        int u = fila[inicioFila++]; 

        if (u == destino) {
            encontrou = true;
            break;
        }

        ArestaLogistica* arestaAtual = grafo->listaAdjacencia[u].arestas;
        while (arestaAtual != NULL) {
            int v = arestaAtual->indiceDestino;
            
            if (!visitados[v]) {
                visitados[v] = true;
                anteriores[v] = u;
                fila[fimFila++] = v; 
            }
            arestaAtual = arestaAtual->proximo;
        }
    }

    
    printf("\n=== Modulo 8: Navegacao de Emergencia (Tempestade) ===\n");
    if (!encontrou) {
        printf("Rota bloqueada ou inacessivel!\n");
    } else {
       
        printf("Caminho mais seguro: ");

        int* caminho = (int*)malloc(n * sizeof(int));
        int passadas = 0;
        int atual = destino;

        while (atual != -1) {
            caminho[passadas++] = atual;
            atual = anteriores[atual];
        }

        
        for (int i = passadas - 1; i >= 0; i--) {
            printf("[%s]", grafo->listaAdjacencia[caminho[i]].nomeRegiao);
            if (i > 0) printf(" -> ");
        }
        
        
        printf("\nTotal de bairros cruzados: %d\n", passadas - 1);
        free(caminho);
    }
    printf("======================================================\n\n");

    free(fila);
    free(anteriores);
    free(visitados);
}


void carregarMapaPelotas(GrafoLogistico* mapa) {
    
    const char* bairros[30] = {
        "Cozinha Central (Centro)", "Fragata", "Tres Vendas", "Areal", "Laranjal",
        "Porto", "Balsa", "Simoes Lopes", "Guabiroba", "Gotuzzo",
        "Bom Jesus", "UFPel Anglo", "UFPel Cotada", "IFSul", "Praca Cel. Pedro Osorio",
        "Mercado Publico", "Shopping Pelotas", "Parque Una", "Recanto de Portugal", "Las Acacias",
        "Sitio Floresta", "Lindoia", "Pestano", "Getulio Vargas", "Fatima",
        "Navegantes", "Rodoviaria", "Aeroporto", "Hospital Chico Paulista", "UFPel Capao do Leao"
    };

    for (int i = 0; i < 30; i++) {
        definirNomeRegiao(mapa, i, bairros[i]);
    }


    adicionarArestaLogistica(mapa, 0, 1, 15);  // Centro -> Fragata
    adicionarArestaLogistica(mapa, 0, 2, 12);  // Centro -> Tres Vendas
    adicionarArestaLogistica(mapa, 0, 3, 10);  // Centro -> Areal
    adicionarArestaLogistica(mapa, 0, 5, 8);   // Centro -> Porto
    adicionarArestaLogistica(mapa, 0, 14, 2);  // Centro -> Praca Cel Pedro Osorio
    adicionarArestaLogistica(mapa, 0, 15, 3);  // Centro -> Mercado Publico
    adicionarArestaLogistica(mapa, 0, 26, 10); // Centro -> Rodoviaria

    
    adicionarArestaLogistica(mapa, 1, 8, 7);   // Fragata -> Guabiroba
    adicionarArestaLogistica(mapa, 1, 9, 6);   // Fragata -> Gotuzzo
    adicionarArestaLogistica(mapa, 1, 13, 5);  // Fragata -> IFSul
    adicionarArestaLogistica(mapa, 1, 7, 8);   // Fragata -> Simoes Lopes
    adicionarArestaLogistica(mapa, 1, 28, 5);  // Fragata -> Hospital Chico Paulista
    adicionarArestaLogistica(mapa, 1, 29, 25); // Fragata -> UFPel Capao do Leao
    adicionarArestaLogistica(mapa, 8, 9, 4);   // Guabiroba -> Gotuzzo
    adicionarArestaLogistica(mapa, 7, 26, 6);  // Simoes Lopes -> Rodoviaria
    adicionarArestaLogistica(mapa, 8, 28, 3);  // Guabiroba -> Hospital Chico Paulista
    adicionarArestaLogistica(mapa, 9, 28, 4);  // Gotuzzo -> Hospital Chico Paulista

    
    adicionarArestaLogistica(mapa, 2, 20, 10); // Tres Vendas -> Sitio Floresta
    adicionarArestaLogistica(mapa, 2, 21, 8);  // Tres Vendas -> Lindoia
    adicionarArestaLogistica(mapa, 2, 22, 12); // Tres Vendas -> Pestano
    adicionarArestaLogistica(mapa, 2, 23, 15); // Tres Vendas -> Getulio Vargas
    adicionarArestaLogistica(mapa, 2, 26, 8);  // Tres Vendas -> Rodoviaria
    adicionarArestaLogistica(mapa, 20, 21, 5); // Sitio Floresta -> Lindoia
    adicionarArestaLogistica(mapa, 21, 22, 6); // Lindoia -> Pestano
    adicionarArestaLogistica(mapa, 22, 23, 7); // Pestano -> Getulio Vargas

    
    adicionarArestaLogistica(mapa, 3, 4, 15);  // Areal -> Laranjal
    adicionarArestaLogistica(mapa, 3, 10, 6);  // Areal -> Bom Jesus
    adicionarArestaLogistica(mapa, 3, 16, 5);  // Areal -> Shopping Pelotas
    adicionarArestaLogistica(mapa, 3, 17, 7);  // Areal -> Parque Una
    adicionarArestaLogistica(mapa, 16, 17, 3); // Shopping -> Parque Una
    adicionarArestaLogistica(mapa, 4, 18, 8);  // Laranjal -> Recanto de Portugal
    adicionarArestaLogistica(mapa, 4, 19, 10); // Laranjal -> Las Acacias
    adicionarArestaLogistica(mapa, 18, 19, 4); // Recanto de Portugal -> Las Acacias

    
    adicionarArestaLogistica(mapa, 5, 6, 5);   // Porto -> Balsa
    adicionarArestaLogistica(mapa, 5, 11, 4);  // Porto -> UFPel Anglo
    adicionarArestaLogistica(mapa, 5, 25, 6);  // Porto -> Navegantes
    adicionarArestaLogistica(mapa, 6, 25, 4);  // Balsa -> Navegantes
    adicionarArestaLogistica(mapa, 11, 12, 5); // UFPel Anglo -> UFPel Cotada
    adicionarArestaLogistica(mapa, 11, 14, 6); // UFPel Anglo -> Praca Cel Pedro Osorio
    

    adicionarArestaLogistica(mapa, 14, 15, 2); // Praca -> Mercado Publico
    adicionarArestaLogistica(mapa, 14, 13, 5); // Praca -> IFSul
    adicionarArestaLogistica(mapa, 15, 5, 4);  // Mercado Publico -> Porto

    
    adicionarArestaLogistica(mapa, 13, 26, 7); // IFSul -> Rodoviaria
    adicionarArestaLogistica(mapa, 16, 2, 15); // Shopping -> Tres Vendas
    adicionarArestaLogistica(mapa, 17, 2, 14); // Parque Una -> Tres Vendas
    adicionarArestaLogistica(mapa, 10, 24, 5); // Bom Jesus -> Fatima
    adicionarArestaLogistica(mapa, 24, 5, 8);  // Fatima -> Porto
    adicionarArestaLogistica(mapa, 26, 27, 12);// Rodoviaria -> Aeroporto
    adicionarArestaLogistica(mapa, 2, 27, 10); // Tres Vendas -> Aeroporto
    adicionarArestaLogistica(mapa, 1, 27, 15); // Fragata -> Aeroporto
    adicionarArestaLogistica(mapa, 3, 2, 10);  // Areal -> Tres Vendas
    adicionarArestaLogistica(mapa, 23, 27, 18);// Getulio Vargas -> Aeroporto
}

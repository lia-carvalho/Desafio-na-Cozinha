#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
bool detectarCiclo_DFS(Grafo* grafo, int indice_atual){
    grafo->lista_adjacencia[indice_atual].cor = 1;  //Receita atual fica cinza(em processamento)

    Aresta* atual = grafo->lista_adjacencia[indice_atual].arestas;

    while(atual != NULL){
        int vizinho = atual->indice_destino;
       
        if(grafo->lista_adjacencia[vizinho].cor == 1){
            return true;
        }else if(grafo->lista_adjacencia[vizinho].cor == 0){
            if(detectarCiclo_DFS(grafo,vizinho) == true){
                return true;
            }
        }
        atual= atual->proximo;
    }
    grafo->lista_adjacencia[indice_atual].cor = 2; //Preto (já processada)
    return false;
}

void verificarErrosDependencia(Grafo* grafo, Receita* catalogo[], int total_vertices){
    bool achou_erro = false;

    for(int i=0; i < total_vertices; i++){
        if (grafo->lista_adjacencia[i].cor == 0){

            if(detectarCiclo_DFS(grafo,i) == true){
                printf("[ALERTA] Erro de dependencia detectado no cardapio!\n");
                printf("A receita %s (ID: %s) esta em um ciclo.\n", catalogo[i]->nome, catalogo[i]->id);
                achou_erro = true;
                break;
            }
        }
    }
    if (!achou_erro){
        printf("Nenhum erro de dependencia encontrado!\n");
    }
}

void ordemProducao(Grafo* grafo, Receita* catalogo[], int total_vertices, int indiceAlvo){
    printf("\n ---PREPAROS NECESSARIOS PARA: %s---\n",catalogo[indiceAlvo]->nome);
    bool tem_dependencia = false;

    for(int i=0; i<total_vertices;i++){

        Aresta*atual = grafo->lista_adjacencia[i].arestas;
        while(atual != NULL){
            if(atual->indice_destino == indiceAlvo){
                printf(" -> %s\n", catalogo[i]->nome);
                tem_dependencia= true;
                break;
            }
            atual = atual->proximo;
        }
    }
    if(!tem_dependencia){
        printf("Esta receita nao depende de nenhuma outra.\n");
    }
}

void liberarGrafo(Grafo* grafo, int total_vertices){
    for (int i= 0; i< total_vertices; i++){
        Aresta* atual = grafo->lista_adjacencia[i].arestas;
        while(atual != NULL){
            Aresta* temporaria = atual;
            atual= atual->proximo;
            free(temporaria);
        }
    }
    free(grafo->lista_adjacencia);
    free(grafo);
}

//Módulo 8 - Comunidades Gastronômicas
int representanteConjunto[100];

int encontrarRaiz(int i){
    if(representanteConjunto[i] == i){
        return i;
    }
    representanteConjunto[i] = encontrarRaiz(representanteConjunto[i]);
    return representanteConjunto[i];
}

void unirConjuntos(int i,int j){
    int raiz_i = encontrarRaiz(i);
    int raiz_j = encontrarRaiz(j);
    if(raiz_i != raiz_j){
        representanteConjunto[raiz_i]=raiz_j;
    }
}

void identificarComunidades(Receita* catalogo[], int totalReceitas){
    for (int i=0; i< totalReceitas; i++){
        representanteConjunto[i]=i;
    }
    for(int i = 0; i < totalReceitas ; i++){
        for(int j = i + 1; j < totalReceitas ; j++){
            //Regra de similaridade: mesma CATEGORIA e mesmo PAÍS
        if(strcmp(catalogo[i]->categoria, catalogo[j]->categoria) == 0 && 
            strcmp(catalogo[i]->pais, catalogo[j]->pais)== 0){
                unirConjuntos(i,j);
            }
        }
    }
    printf("\n ==== FAMILIAS CULINARIAS ENCONTRADAS ====\n");
    int ja_impresso[100] = {0};
    int numComunidade= 1;
    for (int i=0;i<totalReceitas;i++){
        int raiz =encontrarRaiz(i);

        if(ja_impresso[raiz]==0){
            printf(" Familia Culinaria %d (Origem: %s / %s)\n",numComunidade++,catalogo[i]->pais,catalogo[i]->categoria);

            for(int j=0; j<totalReceitas;j++){
                if(encontrarRaiz(j) == raiz){
                    printf("- [%s] %s\n",catalogo[j]->id, catalogo[j]->nome);
                }
            }
            ja_impresso[raiz]= 1;
        }
    }

}
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 97

    int calcularHash(char *chave){
        int hash = 0; 

        while(*chave){
            hash = (hash * 31 + *chave) % TAMANHO_HASH;
            chave++;
        }

        return hash;
    }

    void inicializarTabela(HashNode *tabela[]){
        for (int i=0; i< TAMANHO_HASH ; i++){
         tabela[i]= NULL;
        }
    }

//Tratamento de colisões:
    void inserirReceita(HashNode *head[], Receita *novaReceita){
        int indice = calcularHash(novaReceita ->nome);

        HashNode *novoNo = (HashNode*) malloc (sizeof(HashNode));
            if(novoNo ==NULL){
            printf("Erro ao alocar espaço");
            return;
        }

        novoNo->receita = novaReceita;

        novoNo->prox = head[indice];

        head[indice] = novoNo;
    }

    Receita* buscarReceita(HashNode *tabela[], char *nomeBuscado){
        int indice = calcularHash(nomeBuscado);

        HashNode *atual = tabela[indice];
        while (atual != NULL){
        if(strcmp(atual->receita->nome, nomeBuscado) == 0){
            return atual->receita;
        }
    
        atual = atual->prox;
        }
        return NULL;
    }

    unsigned int calcularChecksum(Receita *r){
        unsigned int hash = 0;
        for(int i = 0; r->id[i] != '\0'; i++){
            hash = hash * 31 + r->id[i];
        }
        for(int i = 0; r->nome[i] != '\0'; i++){
            hash = hash * 31 + r->nome[i];
        }
        for(int i = 0; r->categoria[i] != '\0'; i++){
            hash = hash * 31 + r->categoria[i];
        }
        for(int i = 0; r->pais[i] != '\0'; i++){
            hash = hash * 31 + r->pais[i];
        }
        for(int i = 0; r->ingredientes[i] != '\0'; i++){
            hash = hash * 31 + r->ingredientes[i];
        }
            hash = hash * 31 + r->tempoPreparo;
            hash = hash * 31 + (int)(r->preco * 100);
            hash = hash * 31 + (int)(r->avaliacao * 10);
        return hash;
    }

    void executarModoInvestigacao(HashNode *tabela[]){
        int receitasVerificadas = 0;
        int receitasCorrompidas = 0;
        int receitasDuplicadas = 0;
        int receitasInconsistentes = 0;

        for (int i = 0; i < TAMANHO_HASH ; i++){
            HashNode *atual = tabela[i];

            while(atual != NULL){     //percorre a lista encadeada 
                receitasVerificadas++;
                
                //Testa receitas alteradas
                unsigned int checksumAtual = calcularChecksum(atual->receita);
                if(checksumAtual != atual->receita->checksum){
                    printf("\nRECEITA ADULTERADA!!!\n");
                    printf("   ID: %s | Nome: %s\n", atual->receita->id, atual->receita->nome);
                    receitasCorrompidas++;
                }
                //Testa inconsistências na receita (valores que não fazem sentido)
                if(atual->receita->tempoPreparo < 0 ||
                    atual->receita->preco < 0.0 ||
                    atual->receita->avaliacao < 0.0 ||
                    atual ->receita->avaliacao > 5.0){
                        printf(" \nRECEITA COM DADOS INCONSISTENTES!\n ID %s | Nome: %s\n", atual->receita->id, atual->receita->nome);
                        printf ("Checar Preco, Tempo de Preparo ou Avaliacao.\n");
                        receitasInconsistentes++;
                    }

                //Testa receitas duplicadas
                HashNode *buscador = atual->prox;
                while(buscador != NULL){                  //procura na lista encadeada
                    if(strcmp(atual->receita->id, buscador->receita->id) == 0){
                        printf("\nRECEITA DUPLICADA!\n ID %s aparece mais de uma vez ('%s' e '%s').\n",atual->receita->id,atual->receita->nome,buscador->receita->nome);
                        receitasDuplicadas++;
                    }
                    buscador = buscador->prox;
                }
                for(int j = i+1; j<TAMANHO_HASH;j++){     //procura nas outras posições do vetor menu
                    HashNode *buscaMenu = tabela[j];
                    while (buscaMenu != NULL){
                       if(strcmp(atual->receita->id,buscaMenu->receita->id)== 0){
                        printf("\nRECEITA DUPLICADA!\n ID %s aparece mais de uma vez ('%s' e '%s')\n",atual->receita->id,atual->receita->nome,buscaMenu->receita->nome);
                        receitasDuplicadas++;
                       }
                       buscaMenu= buscaMenu->prox;
                    }
                    
                }
                atual = atual-> prox;
            }
        }
        printf("\nTotal de receitas verificadas: %d\n", receitasVerificadas);
        printf("\nTotal de receitas corrompidas:%d\n",receitasCorrompidas);
        printf("\nTotal receitas inconsistentes: %d\n", receitasInconsistentes);
        printf("\nTotal receitas duplicadas: %d\n", receitasDuplicadas);
    
    
    }

void buscarPorCategoria(HashNode *tabela[], char *categoriaBuscada) {
    printf("\n--- Resultados para a Categoria: %s ---\n", categoriaBuscada);
    int encontrou = 0;

    int tamanhoBusca = strlen(categoriaBuscada);

    for (int i = 0; i < TAMANHO_HASH; i++) {
        HashNode *atual = tabela[i];
        while (atual != NULL) {
            if (strncasecmp(atual->receita->categoria, categoriaBuscada,tamanhoBusca) == 0) {
                printf(" [%s] %s\n", atual->receita->id, atual->receita->nome);
                encontrou++;
            }
            atual = atual->prox;
        }
    }
    
    if (encontrou == 0) {
        printf("Nenhuma receita encontrada nessa categoria.\n");
    }
}


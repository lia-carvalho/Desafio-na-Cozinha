#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define TAMANHO_HASH 97

int main () {
    FILE *arquivo = fopen("../data/receitas.csv", "r");

    if (arquivo == NULL){
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    Receita menu[70];
    HashNode *tabela[TAMANHO_HASH];
    inicializarTabela(tabela);

    int totalReceitas = 0;
    char linha[500];    //string temporária

        fgets(linha, sizeof(linha), arquivo);
        while (fgets(linha, sizeof(linha),arquivo) != NULL){
            
            char *separador = strtok (linha, ",");   //separa as linhas do arquivo quando acha vírgula
            if (separador != NULL){
                strcpy(menu[totalReceitas].id,separador);
            }
            separador = strtok(NULL , ",");
            if (separador != NULL){
                strcpy(menu[totalReceitas].nome, separador);
            }
            separador = strtok(NULL, ",");
            if (separador != NULL){
                strcpy(menu[totalReceitas].categoria, separador);
            }
            separador = strtok(NULL, ",");
            if (separador != NULL){
                strcpy(menu[totalReceitas].pais, separador);
            }
            separador = strtok(NULL, ",");
            if (separador != NULL){
                strcpy(menu[totalReceitas].ingredientes, separador);
            }
            separador = strtok(NULL, ",");
            if (separador != NULL){
                 menu[totalReceitas].tempoPreparo= atoi(separador);
            }
            separador = strtok(NULL, ",");
            if (separador != NULL){
                menu[totalReceitas].preco = atof(separador);
            }
            separador = strtok(NULL, "\n");
            if (separador != NULL){
                menu[totalReceitas].avaliacao = atof(separador);
            }
           
           
            inserirReceita(tabela,&menu[totalReceitas]);
           
            totalReceitas++;
        }
        fclose(arquivo);

        
        printf( " %d receitas foram carregadas.\n", totalReceitas);
       
    return 0;
}
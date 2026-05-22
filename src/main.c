#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

int main () {
    FILE *arquivo = fopen("../data/receitas.csv", "r");

    if (arquivo == NULL){
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    Receita menu[70];
    int totalReceitas = 0;
    char linha[500];    //string temporária

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
            
            separador = strtok(NULL, "\n");
            if (separador != NULL){
                strcpy(menu[totalReceitas].ingredientes, separador);
            }
            menu[totalReceitas].tempoPreparo = 15 + (totalReceitas % 45);  //tempo varia entre 15 e 59 minutos
            menu[totalReceitas].preco = 25.0 + (totalReceitas % 60);       //preço varia entre 25,00 e 84,00
            totalReceitas++;
        }
        fclose(arquivo);

        
        printf( " %d receitas foram carregadas.\n", totalReceitas);
        printf("Primeira Receita: %s | ID: %s | Categoria: %s | Pais:%s | Ingredientes: %s | Tempo de Preparo: %d minutos | Preco:R$%.2f\n", menu[0].nome,menu[0].id,menu[0].categoria,menu[0].pais, menu[0].ingredientes,menu[0].tempoPreparo, menu[0].preco);



    return 0;
}
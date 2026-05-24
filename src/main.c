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
           
           menu[totalReceitas].checksum = calcularChecksum(&menu[totalReceitas]);

            inserirReceita(tabela,&menu[totalReceitas]);   //insere receita na tabela hash
           
            totalReceitas++;
        }
        fclose(arquivo);
        
        executarModoInvestigacao(tabela);

    return 0;
}

void modoBusca(ArvoreTrie* trieNomes, ArvoreIngredientes* trieIngredientes){
    int opcao = -1;
    char busca[100];

    while(opcao != 0){
        printf("MODO DE BUSCA\n");
        printf("Escolha uma opção:\n");
        printf("1- Buscar por ingrediente\n");
        printf("2-Buscar Receitas pelo nome\n");
        printf("0- Voltar ao menu principal\n");
        scanf("%d", &opcao);

    getchar();

    if(opcao == 1){
        printf("Digite o ingrediente ou o prefixo:\n");
        fgets(busca, sizeof(busca), stdin);
        busca[strcspn(busca, "\n")] = 0;
        
        ListaReceitas* resultados = buscarPrefixo(trieIngredientes, busca);
        imprimirResultados(resultados);
    }
    else if(opcao == 2){
        printf("Digite o nome ou prefixo da receita: \n");
        fgets(busca, sizeof(busca), stdin);
        busca[strcspn(busca, "\n")] == 0;

        ListaReceitas* resultados = buscarPrefixo(trieNomes, busca);
        imprimirResultados(resultados);
    }
    else if(opcao != 0){
        printf("opção invalida\n");
        }
    }
}

void modoChef(Receita** catalogo, int totalReceitas){
    int opcao = -1;

    while(opcao != 0){
        printf("MODO CHEF\n");
        printf("Escolha uma opção:\n");
        printf("1- Menu Econõmico\n");
        printf("2-Menu Rápido\n");
        printf("0- Voltar ao menu principal\n");
        scanf("%d", &opcao);

        if(opcao == 1){
            double orcamento;
            printf("Qual o orçamento máximo?\n");
            scanf("%lf", &orcamento);

            ListaReceitas* sugestoes = gerarEconomico(catalogo, totalReceitas, orcamento);
            imprimirResultados(sugestoes);
        } 
        else if( opcao == 2){
            int tempo;
            printf("Qual o tempo máximo disponível?(minutos)\n");
            scanf("%d", &tempo);

            ListaReceitas* sugestoes = gerarRapido(catalogo, totalReceitas, tempo);
            imprimirResultados(sugestoes);
        }
        else if(opcao != 0){
            printf("Opção inválida\n");
        }

    }
}

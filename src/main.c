#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "receitas.h"
#include "hash.h"
#include "trie.h"
#include "ingredientes.h"
#include "chef.h"

#define TAMANHO_HASH 97

void imprimirResultados(ListaReceitas* lista){
    if (lista == NULL || lista->tamanho == 0) {
        printf("Nenhum prato encontrado com esses criterios.\n");
        return;
    }
    NoLista* atual = lista->inicio;
    printf(" %d opcao(oes) encontrada(s):\n", lista->tamanho);
    while (atual != NULL) {
        Receita* r = atual->receita;
        printf("\n [%s] %s | Categoria: %s | Pais:%s | Tempo: %d min | Preco: R$%.2f | Avaliacao: %.1f | Ingredientes: %s\n", 
               r->id, r->nome, r->categoria,r-> pais, r->tempoPreparo, r->preco, r->avaliacao, r->ingredientes);
        atual = atual->prox;
    }
}

int main () {
    FILE *arquivo = fopen("../data/receitas.csv", "r");

    if (arquivo == NULL){
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    Receita menu[70];
    Receita *catalogo[70];      //cópia do vetor menu para o modo chef
    HashNode *tabela[TAMANHO_HASH];
    ArvoreTrie *trieNomes = NULL;
    ArvoreIngredientes *trieIngredientes = NULL;
    
    inicializarTabela(tabela);
    trieNomes = criarTrie(); 
    trieIngredientes = criarTrieIngredientes();

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
           inserirTrie(trieNomes,menu[totalReceitas].nome, &menu[totalReceitas]);    //insere na trie nomes
            
           char copiaIngredientes[500];
           strcpy(copiaIngredientes, menu[totalReceitas].ingredientes);
           char *divide = strtok(copiaIngredientes, "-");
           while (divide!= NULL){
            vincularIngrediente(trieIngredientes, divide, &menu[totalReceitas]);
            divide= strtok(NULL, "-");
           }
           
           totalReceitas++;
        }
        fclose(arquivo);

        for(int i=0; i<totalReceitas;i++){
            catalogo[i]=&menu[i];
        }

//Interface:
int opcaoInicial, opcaoSecundaria;
char textoBuscado[100];
ListaReceitas* resultadosBusca = NULL;

//Testa modo investigação
/*menu[0].preco= -1.99;
strcpy(menu[0].id, menu[3].id); */

do {
        printf("\n");
        printf("====================================================\n");
        printf("                DESAFIO NA COZINHA          \n");
        printf("====================================================\n");
        printf("1. Modulo 1 - Livro de Receitas (Listar tudo)\n");
        printf("2. Modulo 2 - Busca Rapida no Cardapio\n");
        printf("3. Modulo 3 - Consulta por Ingrediente\n");
        printf("4. Modulo 4 - Recomendacao do Chef (Modo Chef)\n");
        printf("5. Modo Investigacao\n");
        printf("0. Sair do Sistema\n");
        printf("====================================================\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcaoInicial);
        
        int c;
        while((c = getchar())!= '\n' && c != EOF);

        switch (opcaoInicial){
        case 1:
            printf("\n--- LIVRO DE RECEITAS ---\n");
                for (int i = 0; i < totalReceitas; i++) {
                    printf("\n[%s] %s | Categoria: %s  |Pais: %s | Tempo de Preparo: %d min | Preco: R$%.2f | Avaliacao: %.1f | Ingredientes: %s\n", 
                           menu[i].id, menu[i].nome, menu[i].categoria,menu[i].pais, menu[i].tempoPreparo, menu[i].preco,menu[i].avaliacao,menu[i].ingredientes);
                }
            break;

        case 2:
            printf("\n--- BUSCA RAPIDA NO CARDAPIO ---\n");
            printf("1. Buscar por Nome\n");
            printf("2. Buscar por ID\n");
            printf("3. Buscar por Categoria\n");
            printf("4. Buscar por Prefixo\n");
            printf("Escolha o filtro: ");
            scanf("%d", &opcaoSecundaria);
                while ((c = getchar()) != '\n' && c != EOF);

                switch (opcaoSecundaria){
                case 1:
                    printf("\nDigite o nome da receita: ");
                        fgets(textoBuscado, sizeof(textoBuscado), stdin);
                        textoBuscado[strcspn(textoBuscado, "\n")] = 0;

                        printf("\n---RESULTADO DA BUSCA POR NOME---\n");
                        Receita *receitaEncontrada = buscarReceita(tabela,textoBuscado);
                        if(receitaEncontrada != NULL){
                            printf("  [%s] %s | Categoria: %s | Pais: %s |Tempo: %d min | Preco: R$%.2f | Avaliacao: %.1f | Ingredientes: %s\n", 
                                   receitaEncontrada->id, receitaEncontrada->nome, receitaEncontrada->categoria, 
                                   receitaEncontrada->pais, receitaEncontrada->tempoPreparo,receitaEncontrada->preco,
                                   receitaEncontrada->avaliacao, receitaEncontrada->ingredientes);
                        } else{
                            printf("Receita nao encontrada.\n");
                        }
                    break;
                
                case 2:
                    printf("\nDigite o ID da receita:\n");
                    fgets(textoBuscado,sizeof(textoBuscado),stdin);
                    textoBuscado[strcspn(textoBuscado,"\n")] = 0;

                    printf("\n---RESULTADO DA BUSCA POR ID---\n");
                    int achouId=0;
                    for(int i=0; i<totalReceitas;i++){
                        if(strcmp(menu[i].id,textoBuscado) == 0){
                            printf(" [%s] %s | Categoria: %s | Pais: %s | Tempo: %d min | Preco: R$%.2f| Avaliacao:%.1f | Ingredientes: %s\n", 
                                       menu[i].id, menu[i].nome, menu[i].categoria,menu[i].pais, menu[i].tempoPreparo, menu[i].preco, 
                                       menu[i].avaliacao,menu[i].ingredientes);
                        achouId =1;
                        break;          
                        }
                    }
                    if(achouId == 0){
                        printf("Nao ha receitas com este ID no sistema.\n");
                    }
                    break;
                case 3:
                    printf("\nDigite a categoria:\n");
                    fgets(textoBuscado, sizeof(textoBuscado), stdin);
                    textoBuscado[strcspn(textoBuscado, "\n")] = 0;
                    buscarPorCategoria(tabela,textoBuscado);
                    break;
                case 4:
                    printf("\nDigite o prefixo da receita:\n");
                    fgets(textoBuscado, sizeof(textoBuscado), stdin);
                    textoBuscado[strcspn(textoBuscado, "\n")] = 0;

                    resultadosBusca = buscarPrefixo(trieNomes, textoBuscado);
                    imprimirResultados(resultadosBusca);
                    break;
                default:
                    printf("Digite uma opcao valida!\n");
                }
                break;
        case 3: 
            printf("\n--- CONSULTA POR INGREDIENTE ---\n");
            printf("Digite o Ingrediente:\n");
            fgets(textoBuscado, sizeof(textoBuscado), stdin);
            textoBuscado[strcspn(textoBuscado, "\n")] = 0;

            resultadosBusca = buscarIngredientePorPrefixo(trieIngredientes, textoBuscado);
            imprimirResultados(resultadosBusca);
            break;

        case 4: 
            printf("\n--- RECOMENDACAO DO CHEF ---\n");
            printf("1. Recomendacao por Tempo (Menu Rapido)\n");
            printf("2. Recomendacao por Custo ( Menu Economico)\n");
            printf("Qual o criterio de recomendacao? ");
            scanf("%d", &opcaoSecundaria);
            while ((c = getchar()) != '\n' && c != EOF);

            switch (opcaoSecundaria){
            case 1:
                {int tempo;
                printf("Qual o tempo maximo disponivel? (minutos)\n");
                scanf("%d", &tempo);
                while ((c = getchar()) != '\n' && c != EOF);
                    
                resultadosBusca = gerarRapido(catalogo, totalReceitas, tempo);
                imprimirResultados(resultadosBusca);}
                break;

            case 2:
               { double orcamento;
                printf("Qual o orcamento maximo?\n");
                scanf("%lf", &orcamento);
                resultadosBusca = gerarEconomico(catalogo, totalReceitas, orcamento);
                imprimirResultados(resultadosBusca);}
                break;
            default:
            printf("Digite opcao válida.\n");
            }
            break;
        case 5:
            printf("\n--- MODO INVESTIGACAO ---\n");
                executarModoInvestigacao(tabela);
            break;
        case 0:
            printf("\nSaindo do Sistema...\n");
            break;
        
        default:
            printf("\nOpcao invalida. Digite novamente.\n");

        }
    } while (opcaoInicial != 0);

    return 0;
}
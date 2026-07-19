#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "receitas.h"
#include "hash.h"
#include "trie.h"
#include "ingredientes.h"
#include "chef.h"
#include "grafo.h"

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
            separador = strtok(NULL, ",");
            if (separador != NULL){
                menu[totalReceitas].avaliacao = atof(separador);
            }
            separador = strtok(NULL, "\n");
            menu[totalReceitas].numero_dependencias=0;
            if (separador != NULL && strcmp(separador, "0") != 0){
                char copiaDependencias[100];
                strcpy(copiaDependencias, separador);

                char *divideDep = strtok(copiaDependencias, "-");
                while(divideDep != NULL && menu[totalReceitas].numero_dependencias < MAX_DEPENDENCIAS){
                    strcpy(menu[totalReceitas].ids_dependencias[menu[totalReceitas].numero_dependencias], divideDep);
                    menu[totalReceitas].numero_dependencias++;
                    divideDep= strtok(NULL, "-");
                }
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
           
           catalogo[totalReceitas]=&menu[totalReceitas];

           totalReceitas++;
        }
        fclose(arquivo);


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
        printf("5. Modulo 5 - Oficina de Producao\n");
        printf("6. Modo Investigacao\n");
        printf("7. Modo Logistica\n");
        printf("8. Laboratorio de Inovacao do Chef\n");
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
        case 5:{
            Grafo* grafo = criarGrafo(totalReceitas);
            conectarDependencias(grafo,catalogo,totalReceitas);
            printf("\n--- OFICINA DE PRODUCAO ---\n");
            printf("1.Verificar se existe erro de dependencia (Ciclos)\n");
            printf("2.Ver preparos anteriores de uma receita especifica\n");
            printf("Digite opcao:\n");
            scanf("%d",&opcaoSecundaria);
            while ((c = getchar()) != '\n' && c != EOF);

            switch(opcaoSecundaria){
                case 1:{
                    verificarErrosDependencia(grafo,catalogo,totalReceitas);
                    break;
                }
                case 2: {
                    char nomeBusca[100];
                    printf("Digite o nome da receita a ser investigada: ");
                    fgets(nomeBusca,sizeof(nomeBusca),stdin);
                    nomeBusca[strcspn(nomeBusca,"\n")] = '\0';

                    int indice = -1;
                    for(int i=0; i<totalReceitas;i++){
                        if(strcmp(catalogo[i]->nome,nomeBusca) == 0){
                            indice =i;
                            break;
                        }
                    }
                    if(indice!= -1){
                        ordemProducao(grafo,catalogo,totalReceitas,indice);
                    } else{
                        printf("[ERRO] Receita nao encontrada \n");
                    }
                    break;
                }
                default:
                printf("Opcao invalida!\n");
            }
            liberarGrafo(grafo,totalReceitas);
            break;
        }
        case 6:
            printf("\n--- MODO INVESTIGACAO ---\n");
            printf("1. Investigar Integridade dos Dados (Hash)\n");
            printf("2. Investigar Inconsistencias Operacionais (Grafos)\n");
            printf("Digite opcao\n");
            scanf("%d", &opcaoSecundaria);
            while ((c = getchar()) != '\n' && c != EOF);

            switch(opcaoSecundaria){
                case 1:{
                    printf("\nIniciando varredura na base de dados\n");
                    executarModoInvestigacao(tabela);
                    break;
                }
                case 2:{
                printf("\nIniciando verificacao de Ciclos\n");

                Grafo* grafo= criarGrafo(totalReceitas);
                conectarDependencias(grafo,catalogo,totalReceitas);
                verificarErrosDependencia(grafo, catalogo, totalReceitas);
                liberarGrafo(grafo,totalReceitas);

                break;
                }
                default:
                printf("Opcao Invalida\n");
            }
            break;
        case 7:
            printf("\n--- MODO LOGISTICA ---\n");
            printf("1. Consultar melhor rota para entregas\n");
            printf("2. Planejar caminho de distribuição de ingredientes\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcaoSecundaria);
            while ((c = getchar()) != '\n' && c != EOF);

            switch (opcaoSecundaria) {
                case 1: {
                    int origem, destino;
                    printf("\n--- REGIOES DISPONIVEIS PARA ENTREGA ---\n");
                    for (int i = 0; i < mapaLogistico->totalVertices; i++) {
                        
                        printf("[%02d] %-25s", i, mapaLogistico->listaAdjacencia[i].nomeRegiao);
                        if ((i + 1) % 2 == 0) {
                            printf("\n"); 
                        }
                    }
                    if (mapaLogistico->totalVertices % 2 != 0) {
                        printf("\n"); 
                    }
                    printf("----------------------------------------\n");
                    printf("Digite o ID da regiao de ORIGEM: ");
                    scanf("%d", &origem);
                    printf("Digite o ID da regiao de DESTINO: ");
                    scanf("%d", &destino);
                    while ((c = getchar()) != '\n' && c != EOF);
                    
                    if (origem >= 0 && origem < mapaLogistico->totalVertices && 
                        destino >= 0 && destino < mapaLogistico->totalVertices) {
                        calcularRotaEntrega(mapaLogistico, origem, destino);
                    } else {
                        printf("\n[ERRO] Regiao invalida! Digite IDs entre 0 e 29.\n");
                    }
                    break;
                }
                case 2:
                    printf("\nAnalisando o melhor caminho para a rede de distribuição...\n");
                    calcularDistribuicao(mapaLogistico);
                    break;
                default:
                    printf("Opcao invalida!\n");
            }

            break;
        case 8:
             printf("\n--- MENU DEGUSTACAO VIP ---\n");
            printf("Escolha a restricao para a otimizacao do cardapio:\n");
            printf("1. Maximar Avaliacao com limite de TEMPO\n");
            printf("2. Maximar Avaliacao com limite de ORÇAMENTO\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcaoSecundaria);
            while ((c = getchar()) != '\n' && c != EOF);

            switch (opcaoSecundaria) {
                case 1: {
                    int tempoMaximo;
                    printf("Digite o tempo maximo de preparo (em minutos): ");
                    scanf("%d", &tempoMaximo);
                    while ((c = getchar()) != '\n' && c != EOF);
                    
                    sugerirMenuVipTempo(catalogo, totalReceitas, tempoMaximo);
                    break;
                }
                case 2: {
                    int orcamentoMaximo; 
                    printf("Digite o orcamento maximo da cozinha (em Reais): R$ ");
                    scanf("%d", &orcamentoMaximo);
                    while ((c = getchar()) != '\n' && c != EOF);
                    
                    sugerirMenuVipPreco(catalogo, totalReceitas, orcamentoMaximo);
                    break;
                }
                default:
                    printf("\n[ERRO] Opcao invalida!\n");
            }
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

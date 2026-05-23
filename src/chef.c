#include <stdio.h>
#include <stdlib.h>
#include "chef.h"
#include "trie.h"

static int compararEconomia(const void* um, const void* dois){
    Receita* r1 = *(Receita**)um;
    Receita* r2 = *(Receita**)dois;

    double razao1 = r1->avaliacao / r1->preco;
    double razao2 = r2->avaliacao / r2->preco;

    if(razao1 < razao2) return 1;
    if(razao1 > razao2) return -1;
    return 0;
}

static int compararTempo(const void* um, const void* dois){
    Receita* r1 = *(Receita**)um;
    Receita* r2 = *(Receita**)dois;

    if (r1->tempoPreparo > r2->tempoPreparo) return 1;
    if(r1->tempoPreparo < r2->tempoPreparo) return -1;
    return 0;
}

ListaReceitas* gerarEconomico(Receita** todasReceitas, int totalReceitas, double orcamento){
   ListaReceitas* menuSugerido = (ListaReceitas*)malloc(sizeof(ListaReceitas));
   menuSugerido->inicio = NULL;
   menuSugerido->tamanho = 0;

   if(todasReceitas == NULL || totalReceitas == 0 | orcamento<= 0){
    return menuSugerido;

   }

   qsort(todasReceitas, totalReceitas, sizeof(Receita*), compararEconomia);

   for(int i= 0; i < totalReceitas; i++){
    Receita* atual = todasReceitas[i];

    if(atual->preco <= orcamento ){
        adicionarNaLista(menuSugerido, atual);
    }
   }

   return menuSugerido;
}

ListaReceitas* gerarRapido(Receita** todasReceitas, int totalReceitas, int tempo){
    ListaReceitas* menuSugerido = (ListaReceitas*)malloc(sizeof(ListaReceitas));
    menuSugerido->inicio = NULL;
    menuSugerido->tamanho = 0;

    if(todasReceitas == NULL || totalReceitas == 0 || tempo <=0){
        return menuSugerido;
    }

    qsort(todasReceitas, totalReceitas, sizeof(Receita*), compararTempo);

    for(int i = 0; i < totalReceitas; i++){
        Receita* atual = todasReceitas[i];

        if(atual->tempoPreparo <= tempo){
            adicionarNaLista(menuSugerido, atual);
        }
    }
    return menuSugerido;
}
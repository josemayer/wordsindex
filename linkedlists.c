#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "linkedlists.h"

/* Funções ok para par_info abaixo disso */

celula * insereNoFimParInfos (celula * inicio, item x) {
  if (inicio == NULL) {
    inicio = malloc (sizeof(celula));
    inicio->info.linha = x.linha;
    inicio->info.ocorr = x.ocorr;
    inicio->prox = NULL;
  } 
  else inicio->prox = insereNoFimParInfos (inicio->prox, x);
  
  return inicio;
} 

celula * buscaLinhaParInfos(celula * inicio, int x) {
  if (inicio == NULL || inicio->info.linha == x)
    return inicio;
  return (buscaLinhaParInfos(inicio->prox, x));
}

void destroiListaInfos(celula * inicio){
  celula * aux;
  while(inicio != NULL){
    aux = inicio;
    inicio = inicio->prox;
    free(aux);
  }
}

/* Tudo ok abaixo disso */

celula2 * insereNoFimPalavras (celula2 * inicio, char * x_palavra) {
  if (inicio == NULL) {
    /* aloca o espaço da célula */
    inicio = malloc(sizeof(celula2));
    /* aloca o espaço da palavra, com tamanho máximo MAX_TAM_PALAVRA */
    inicio->info.palavra = malloc(MAX_TAM_PALAVRA * sizeof(char));
    /* copia x_palavra para a parte da célula que guarda a palavra */
    strcpy(inicio->info.palavra, x_palavra);
    /* inicializa a lista ligada, que possui as ocorrências e linhas da palavra, vazia */
    inicio->info.lista_infos = NULL;

    inicio->prox = NULL;
  } 
  else inicio->prox = insereNoFimPalavras (inicio->prox, x_palavra);
  
  return inicio;
}

celula2 * buscaPalavras (celula2 * inicio, char * x_palavra) {
  if (inicio == NULL || strcmp(inicio->info.palavra, x_palavra) == 0)
    return inicio;
  return (buscaPalavras(inicio->prox, x_palavra));
}

void destroiListaPalavras(celula2 * inicio){
  celula2 * aux;
  while(inicio != NULL){
    aux = inicio;
    inicio = inicio->prox;
    free(aux->info.palavra);
    destroiListaInfos(aux->info.lista_infos);
    free(aux);
  }
}
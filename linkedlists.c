#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "linkedlists.h"

/* Funções ok para par_info abaixo disso */

void imprimeListaParInfos (celula * inicio) {
  if (inicio != NULL) {
    printf ("%d(%d) ", inicio->info.linha, inicio->info.ocorr);
    imprimeListaParInfos (inicio->prox);
  }
  else printf("\n"); 
}

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

/* Criar uma função para destruir lista de par de informações e chamá-la ao destruir as palavras, p valgrind nao tiltar */

/* Tudo ok abaixo disso */

void imprimeListaPalavras (celula2 * inicio) {
  if (inicio != NULL) {
    printf ("%s ", inicio->info.palavra);
    imprimeListaPalavras(inicio->prox);
  }
  else printf("\n"); 
}

celula2 * buscaPalavras (celula2 * inicio, char * x_palavra) {
  if (inicio == NULL || strcmp(inicio->info.palavra, x_palavra) == 0)
    return inicio;
  return (buscaPalavras(inicio->prox, x_palavra));
}

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
  
/* Criar uma função para destruir a lista ligada de PALAVRAS p valgrind nao tiltar */
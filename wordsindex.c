/* O que o programa faz até agora:
 * Recebe um arquivo texto e, dele, separa as palavras
 * O que falta:
 * Manipular a estrutura das listas ligadas para armazenar essas palavras em seus devidos lugares, assim como implementar a tabela de hash.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlists.h"

int main(int argc, char * argv[]){
    if(argc != 2){
        printf("Uso: %s <nome do arquivo>\n", argv[0]);
        return 0;
    }

    char * palavra_lida = malloc(MAX_TAM_PALAVRA * sizeof(char));
    char caractere;
    int posicao_caractere = 0;
    int armazenou_palavra = 0; /* 'Booleano' que indica se a palavra já foi ou não armazenada */
    int linha = 1;

    FILE * arq;
    arq = fopen(argv[1], "r");

    while((caractere = fgetc(arq)) != EOF){

        if(caractere == ' ' || caractere == '.' || caractere == ',' || caractere == ';' || caractere == '!' || caractere == '?' || caractere == '\n'){
            if(!armazenou_palavra){
                printf("Palavra: %s (%d)\n", palavra_lida, linha);
                
                posicao_caractere = 0;
                armazenou_palavra = 1;
            }
        } else {
            palavra_lida[posicao_caractere] = caractere;
            palavra_lida[posicao_caractere + 1] = '\0';
            posicao_caractere++;
            armazenou_palavra = 0;
        }

        if(caractere == '\n'){
            linha++;
        }
    }

    /* Executa o 'armazenamento' da última palavra, se ela nao foi armazenada ainda */
    if(!armazenou_palavra){
        printf("Palavra: %s (%d)\n", palavra_lida, linha);
    }
    
    free(palavra_lida);
    fclose(arq);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlists.h"

/* A função de hashing calcula a posição de uma palavra na tabela, com base na codificação da palavra na tabela
 * ASCII. Ela soma o valor correspondente a todos os caracteres da palavra, aplicando pesos de 1 ao tamanho da
 * palavra a cada soma feita, para evitar colisões de palavras que possuem a mesma permutação. Ao fim, ela calcula
 * o resto da divisão pelo tamanho da tabela, indicando a posição adequada.
 */
int funcao_de_hashing(char * palavra){
    int i;
    int posicao = 0;
    int numb_char;
    for(i = 0; i < strlen(palavra); i++){
        numb_char = palavra[i];
        posicao += (numb_char * (i + 1));
    }
    posicao = posicao % MAX_TAM_TABELA;
    return posicao;
}

/* Função que converte todas as letras de uma palavra para minúsculas */
void normaliza_palavra(char * palavra){
    int i;
    int cod_char;
    char letra_minuscula;
    int tam = strlen(palavra);
    for(i = 0; i < tam; i++){
        cod_char = palavra[i];
        if(cod_char >= 65 && cod_char <= 90){
            cod_char = cod_char + 32;
            letra_minuscula = cod_char;
            palavra[i] = letra_minuscula;
        }
    }
}

/* Função utilizada no algoritmo de ordenação quickSort */
int separa(celula2 ** lista, int inicio, int fim){
    int i;
    celula2 * pivo = lista[fim];
    celula2 * aux;
    int sep = inicio - 1;

    /* Para comparar apenas em ordem alfabética, normaliza uma cópia da palavra e do pivô em letras minúsculas */
    char * copia_minuscula_palavra = malloc(MAX_TAM_PALAVRA * sizeof(char));
    char * copia_minuscula_pivo = malloc(MAX_TAM_PALAVRA * sizeof(char));
    strcpy(copia_minuscula_pivo, pivo->info.palavra);
    normaliza_palavra(copia_minuscula_pivo);

    for(i = inicio; i < fim; i++){
        strcpy(copia_minuscula_palavra, lista[i]->info.palavra);
        normaliza_palavra(copia_minuscula_palavra);

        if(strcmp(copia_minuscula_palavra, copia_minuscula_pivo) < 0){
            sep++;
            aux = lista[sep];
            lista[sep] = lista[i];
            lista[i] = aux;
        }
    }
    aux = lista[sep + 1];
    lista[sep + 1] = lista[fim];
    lista[fim] = aux;

    free(copia_minuscula_palavra);
    free(copia_minuscula_pivo);

    return sep + 1;
}

/* Algoritmo de ordenação quickSort, que ordena os ponteiros de célula com base na palavra */
void quickSort(celula2 ** lista, int inicio, int fim){
    int pivo;
    if(inicio < fim){
        pivo = separa(lista, inicio, fim);
        quickSort(lista, inicio, pivo - 1);
        quickSort(lista, pivo + 1, fim);
    }
}

int main(int argc, char * argv[]){
    int i;
    char * palavra_lida;
    char caractere;
    int posicao_caractere = 0;
    int armazenou_palavra = 0; /* 'Booleano' que indica se a palavra já foi ou não armazenada */
    int linha_do_arquivo = 1;
    int palavras_adicionadas = 0;
    int indice_vetor = 0;
    int posicao_na_tabela;
    par_info informacao;
    celula * celula_da_info;
    celula * lista_de_informacoes;
    celula2 ** tabela_de_hash;
    celula2 ** v_celulas;
    celula2 * celula_da_palavra;
    celula2 * inicio_da_lista;
    FILE * arq;

    if(argc != 2){
        printf("Uso: %s <nome do arquivo>\n", argv[0]);
        return 0;
    }

    arq = fopen(argv[1], "r");

    if(!arq) {
        printf("O arquivo não existe ou seu nome foi digitado incorretamente.\n");
        return 0;
    }

    palavra_lida = malloc(MAX_TAM_PALAVRA * sizeof(char));
    tabela_de_hash = malloc(MAX_TAM_TABELA * sizeof(celula *));

    /* Inicializa todas as posições da tabela de hash com as listas vazias */
    for(i = 0; i < MAX_TAM_TABELA; i++){
        tabela_de_hash[i] = NULL;
    }

    /* Lê caractere por caractere até o fim do arquivo */
    while((caractere = fgetc(arq)) != EOF){
        /* Verifica se o caractere lido é um separador */
        if(caractere == ' ' || caractere == '.' || caractere == ',' || caractere == ';' || caractere == '!' ||
           caractere == '?' || caractere == ':' || caractere == '"' || caractere == '(' || caractere == ')' || 
           caractere == '[' || caractere == ']' || caractere == '{' || caractere == '}' || caractere == '/' ||
           caractere == '=' || caractere == '+' || caractere == '_' || caractere == '*' || caractere == '\n'){
            /* Verifica se a palavra lida não é um hífen único ou uma aspa única */
            if(strcmp(palavra_lida, "-") != 0 && strcmp(palavra_lida, "'") != 0){
                /* Verifica se a palavra lida já foi armazenada */
                if(!armazenou_palavra){
                    posicao_na_tabela = funcao_de_hashing(palavra_lida);
                    celula_da_palavra = buscaPalavras(tabela_de_hash[posicao_na_tabela], palavra_lida);
                    if(celula_da_palavra == NULL){
                        /* Insere na tabela, caso não exista */
                        tabela_de_hash[posicao_na_tabela] = insereNoFimPalavras(tabela_de_hash[posicao_na_tabela], palavra_lida);
                        /* Incrementa o número de palavras adicionadas */
                        palavras_adicionadas++;
                        /* Faz celula_da_palavra apontar para a posição inserida */
                        celula_da_palavra = buscaPalavras(tabela_de_hash[posicao_na_tabela], palavra_lida);
                        informacao.linha = linha_do_arquivo;
                        informacao.ocorr = 1;
                        /* Insere a informação primária da palavra, ou seja, a linha e 1 ocorrência */
                        celula_da_palavra->info.lista_infos = insereNoFimParInfos(celula_da_palavra->info.lista_infos, informacao);
                    } else {
                        /* Altera ou insere informações, caso já exista uma célula daquela palavra */
                        celula_da_info = buscaLinhaParInfos(celula_da_palavra->info.lista_infos, linha_do_arquivo);
                        if(celula_da_info == NULL){
                            /* Se não tem uma célula que já possui o número daquela linha, insere uma nova célula de informação */
                            informacao.linha = linha_do_arquivo;
                            informacao.ocorr = 1;
                            celula_da_palavra->info.lista_infos = insereNoFimParInfos(celula_da_palavra->info.lista_infos, informacao);
                        } else {
                            /* Caso já exista a célula da linha, incrementa a ocorrência naquela linha */
                            celula_da_info->info.ocorr += 1;
                        }
                    }
                    /* Zera o índice de posicao_caractere, para que uma nova palavra possa ser escrita a partir do começo, na string palavra_lida */
                    posicao_caractere = 0;
                    /* Marca que, nessa iteração, uma palavra foi armazenada, para evitar repetições em caso de múltiplos separadores*/
                    armazenou_palavra = 1;
                }
            }
        } else {
            /* Lê caractere por caractere, formando a palavra em palavra_lida */
            palavra_lida[posicao_caractere] = caractere;
            palavra_lida[posicao_caractere + 1] = '\0';
            posicao_caractere++;
            armazenou_palavra = 0;
        }
        
        /* Incrementa a linha do arquivo que está sendo lida, condicionada a partir do caractere de nova linha */
        if(caractere == '\n'){
            linha_do_arquivo++;
        }
    }

    /* Executa a mesma rotina de armazenamento para a última palavra, se ela não foi armazenada ainda */
    if(!armazenou_palavra){
        posicao_na_tabela = funcao_de_hashing(palavra_lida);
        celula_da_palavra = buscaPalavras(tabela_de_hash[posicao_na_tabela], palavra_lida);
        if(celula_da_palavra == NULL){
            tabela_de_hash[posicao_na_tabela] = insereNoFimPalavras(tabela_de_hash[posicao_na_tabela], palavra_lida);
            celula_da_palavra = buscaPalavras(tabela_de_hash[posicao_na_tabela], palavra_lida);
            informacao.linha = linha_do_arquivo;
            informacao.ocorr = 1;
            celula_da_palavra->info.lista_infos = insereNoFimParInfos(celula_da_palavra->info.lista_infos, informacao);
        } else {
            celula_da_info = buscaLinhaParInfos(celula_da_palavra->info.lista_infos, linha_do_arquivo);
            if(celula_da_info == NULL){
                informacao.linha = linha_do_arquivo;
                informacao.ocorr = 1;
                celula_da_palavra->info.lista_infos = insereNoFimParInfos(celula_da_palavra->info.lista_infos, informacao);
            } else {
                celula_da_info->info.ocorr += 1;
            }
        }
    }

    /* Cria um vetor de ponteiros de células com todas as palavras, que será ordenado de modo alfabético */
    v_celulas = malloc(palavras_adicionadas * sizeof(celula2 *));
    for(i = 0; i < MAX_TAM_TABELA; i++){
        inicio_da_lista = tabela_de_hash[i];
        while(inicio_da_lista != NULL){
            v_celulas[indice_vetor] = inicio_da_lista;
            indice_vetor++;
            inicio_da_lista = inicio_da_lista->prox;
        }
    }

    /* Ordena o vetor com os ponteiros */
    quickSort(v_celulas, 0, palavras_adicionadas - 1);

    /* Imprime as palavras do vetor de ponteiros, com as respectivas informações */
    for(i = 0; i < palavras_adicionadas; i++){
        printf("%s: ", v_celulas[i]->info.palavra);
        /* Para cada palavra, imprime as linhas em que ocorre e as suas ocorrências, ao modelo do enunciado */
        lista_de_informacoes = v_celulas[i]->info.lista_infos;
        while(lista_de_informacoes != NULL){
            if(lista_de_informacoes->info.ocorr == 1){
                printf("%d ", lista_de_informacoes->info.linha);
            } else {
                printf("%d(%d) ", lista_de_informacoes->info.linha, lista_de_informacoes->info.ocorr);
            }
            lista_de_informacoes = lista_de_informacoes->prox;
        }
        printf("\n");
    }

    /* Libera todas as células alocadas, pela tabela */
    for(i = 0; i < MAX_TAM_TABELA; i++){
        if(tabela_de_hash[i] != NULL){
            destroiListaPalavras(tabela_de_hash[i]);
        }
    }
    /* Libera o vetor de ponteiros para as células */
    free(v_celulas);
    /* Libera a tabela de hash */
    free(tabela_de_hash);
    /* Libera a string da palavra lida */
    free(palavra_lida);
    /* Fecha o arquivo */
    fclose(arq);

    return 0;
}
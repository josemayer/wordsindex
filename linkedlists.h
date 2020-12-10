#define MAX_TAM_PALAVRA 50
#define MAX_TAM_TABELA 350

typedef struct {
    int linha;
    int ocorr;
} par_info;

typedef par_info item;

typedef struct cel {
  item info;
  struct cel * prox;
} celula; 

void imprimeListaParInfos (celula * inicio);
celula * insereNoFimParInfos (celula * inicio, item x);

typedef struct {
    char * palavra;
    celula * lista_infos;
} par_palavra;

typedef par_palavra item2;

typedef struct cel2 {
  item2 info;
  struct cel2 * prox;
} celula2; 

void imprimeListaPalavras (celula2 * inicio);
celula2 * buscaPalavras (celula2 * inicio, char * x_palavra);
celula2 * insereNoFimPalavras (celula2 * inicio, char * x_palavra);
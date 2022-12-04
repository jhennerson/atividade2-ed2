#include "arvoreAVL.h"
#include "arvoreRubroNegra.h"

int leDadosAVL(char arq[], Pessoa *p, arvAVL *raiz);
int leDadosLLRB(char arq[], Pessoa *p, arvLLRB *raiz);
criaArquivoOrdenado(char arqD[], char arqO[]);
int comparador(const void *x, const void *y);

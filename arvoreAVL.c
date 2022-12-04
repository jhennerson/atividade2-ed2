#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"
#include "arquivo.h"

struct NoAVL {
    Pessoa p;
    int alt;
    struct NoAVL *esq;
    struct NoAVL *dir;
};

arvAVL *cria_arvAVL() {
    arvAVL *raiz = (arvAVL*) malloc(sizeof(arvAVL));
    if(raiz != NULL) {
        *raiz = NULL;
    }
    return raiz;
}

void libera_arvAVL(arvAVL *raiz) {
    if(raiz == NULL) {
        return;
    }
    libera_NoAVL(*raiz);
    free(raiz);
}

void libera_NoAVL(struct NoAVL *no) {
    if(no == NULL) {
        return;
    }
    libera_NoAVL(no->esq);
    libera_NoAVL(no->dir);
}

int vazia_arvAVL(arvAVL *raiz) {
    if(raiz == NULL) {
       return 1;
    }
    if(*raiz == NULL) {
        return 1;
    }
    return 0;
}

int altura_arvAVL(arvAVL *raiz) {
    if(raiz == NULL) {
        return 0;
    }
    if(*raiz == NULL) {
        return 0;
    }
    int alt_esq = altura_arvAVL(&((*raiz)->esq));
    int alt_dir = altura_arvAVL(&((*raiz)->dir));
    if(alt_esq > alt_dir) {
        return(alt_esq + 1);
    } else {
        return(alt_dir + 1);
    }
}

int totalNoAVL_arvAVL(arvAVL *raiz) {
    if(raiz == NULL) {
        return 0;
    }
    if(*raiz == NULL) {
        return 0;
    }
    int alt_esq = totalNoAVL_arvAVL(&((*raiz)->esq));
    int alt_dir = totalNoAVL_arvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

void preOrdem_arvAVL(arvAVL *raiz) {
    if(raiz == NULL) {
        return;
    }
    if(*raiz != NULL) {
//      printf("%d\n", (*raiz)->p.codigo);
        preOrdem_arvAVL(&((*raiz)->esq));
        preOrdem_arvAVL(&((*raiz)->dir));
    }
}

void emOrdem_arvAVL(arvAVL *raiz) {
    if(raiz == NULL) {
        return;
    }
    if(*raiz != NULL) {
        emOrdem_arvAVL(&((*raiz)->esq));
//      printf("%d\n", (*raiz)->p.codigo);
        emOrdem_arvAVL(&((*raiz)->dir));
    }
}

void posOrdem_arvAVL(arvAVL *raiz) {
    if(raiz == NULL) {
        return;
    }
    if(*raiz != NULL) {
        posOrdem_arvAVL(&((*raiz)->esq));
        posOrdem_arvAVL(&((*raiz)->dir));
//      printf("%d\n", (*raiz)->p.codigo);
    }
}

int consulta_arvAVL(arvAVL *raiz, int cod) {
    if(raiz == NULL) {
        return 0;
    }
    struct NoAVL *atual = *raiz;
    while(atual != NULL) {
        if(cod == atual->p.codigo) {
            return 1;
        }
        if(cod > atual->p.codigo) {
            atual = atual->dir;
        } else {
            atual = atual->esq;
        }
    }
    return 0;
}

int alt_no(struct NoAVL *no) {
    if(no == NULL) {
        return -1;
    }else{
        return no->alt;
    }
}

int fatorBalanceamento_NoAVL(struct NoAVL *no) {
    return labs(alt_no(no->esq) - alt_no(no->dir));
}

int maior(int x, int y) {
    if(x > y) {
        return (x);
    } else {
        return (y);
    }
}

void rotacaoLL(arvAVL *raiz) {
    struct NoAVL *no;
    no = (*raiz)->esq;
    (*raiz)->esq = no->dir;
    no->dir = *raiz;
    (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
    no->alt = maior(alt_no(no->esq), (*raiz)->alt + 1);
    *raiz = no;
}

void rotacaoRR(arvAVL *raiz) {
    struct NoAVL *no;
    no = (*raiz)->dir;
    (*raiz)->dir = no->esq;
    no->esq = (*raiz);
    (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
    no->alt = maior(alt_no(no->dir), (*raiz)->alt) + 1;
    (*raiz) = no;
}

void rotacaoLR(arvAVL *raiz) {
    rotacaoRR(&(*raiz)->esq);
    rotacaoLL(raiz);
}

void rotacaoRL(arvAVL *raiz) {
    rotacaoLL(&(*raiz)->dir);
    rotacaoRR(raiz);
}

int insere_arvAVL(arvAVL *raiz, Pessoa p) {
    int res;
    if(*raiz == NULL) {
        struct NoAVL *novo;
        novo = (struct NoAVL*) malloc(sizeof(struct NoAVL));
        if(novo == NULL) {
            return 0;
        }
        novo->p = p;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }
    struct NoAVL *atual = *raiz;
    if(p.codigo < atual->p.codigo) {
        if((res = insere_arvAVL(&(atual->esq), p)) == 1) {
            if(fatorBalanceamento_NoAVL(atual) >= 2) {
                if(p.codigo < (*raiz)->esq->p.codigo) {
                    rotacaoLL(raiz);
                } else {
                    rotacaoLR(raiz);
                }
            }
        }
    } else {
        if(p.codigo > atual->p.codigo) {
            if((res = insere_arvAVL(&(atual->dir), p)) == 1) {
                if(fatorBalanceamento_NoAVL(atual) >= 2) {
                    if((*raiz)->dir->p.codigo < p.codigo) {
                        rotacaoRR(raiz);
                    } else {
                        rotacaoRL(raiz);
                    }
                }
            }
        } else {
            printf("p.codigo duplicado!\n");
            return 0;
        }
    }
    atual->alt = maior(alt_no(atual->esq), alt_no(atual->dir)) + 1;
    return res;
}

int remove_arvAVL(arvAVL *raiz, int cod) {
    if(*raiz == NULL) {
        return 0;
    }
    int res;
    if(cod < (*raiz)->p.codigo) {
        if((res = remove_arvAVL(&(*raiz)->esq, cod)) == 1) {
            if(fatorBalanceamento_NoAVL(*raiz) >= 2) {
                if(alt_no((*raiz)->dir->esq) <= alt_no((*raiz)->dir->dir)) {
                    rotacaoRR(raiz);
                } else {
                    rotacaoLL(raiz);
                }
            }
        }
    }
    if((*raiz)->p.codigo < cod) {
        if((res = remove_arvAVL(&(*raiz)->dir, cod)) == 1) {
            if(fatorBalanceamento_NoAVL(*raiz) >= 2) {
                if(alt_no((*raiz)->esq->dir) <= alt_no((*raiz)->esq->esq)) {
                    rotacaoLL(raiz);
                } else {
                    rotacaoRR(raiz);
                }
            }
        }
    }
    if((*raiz)->p.codigo == cod) {
        if(((*raiz)->esq == NULL) || (*raiz)->dir == NULL) {
            struct NoAVL *no_velho = (*raiz);
            if((*raiz)->esq != NULL) {
                *raiz = (*raiz)->esq;
            } else {
                *raiz = (*raiz)->dir;
            }
            free(no_velho);
        } else {
            struct NoAVL *temp = procuramenor((*raiz)->dir);
            (*raiz)->p = temp->p;
            remove_arvAVL((*raiz)->dir, (*raiz)->p.codigo);
            if(fatorBalanceamento_NoAVL(*raiz) >= 2) {
                if(alt_no((*raiz)->esq->dir) <= alt_no((*raiz)->esq->esq)) {
                    rotacaoLL(raiz);
                } else {
                    rotacaoRR(raiz);
                }
            }
        }
        if(*raiz != NULL) {
            (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
        }
        return 1;
    }
    if(*raiz != NULL) {
        (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
    }
    return res;
}

struct NoAVL *procuramenor(struct NoAVL *atual) {
    struct NoAVL *no1 = atual;
    struct NoAVL *no2 = atual->esq;
    while(no2 != NULL) {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

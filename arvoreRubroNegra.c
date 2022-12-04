#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"
#include "arquivo.h"

#define RED 1
#define BLACK 0

struct NoLLRB {
    Pessoa p;
    struct NoLLRB *esq;
    struct NoLLRB *dir;
    int cor;
};

arvLLRB *cria_arvLLRB() {
    arvLLRB *raiz = (arvLLRB*) malloc(sizeof(arvLLRB));
    if(raiz != NULL) {
        *raiz = NULL;
    }
    return raiz;
}

void libera_arvLLRB(arvLLRB *raiz) {
    if(raiz == NULL) {
        return;
    }
    libera_NoLLRB(*raiz);
    free(raiz);
}

void libera_NoLLRB(struct NoLLRB *no) {
    if(no == NULL) {
        return;
    }
    libera_NoLLRB(no->esq);
    libera_NoLLRB(no->dir);
}

int vazia_arvLLRB(arvLLRB *raiz) {
    if(raiz == NULL) {
       return 1;
    }
    if(*raiz == NULL) {
        return 1;
    }
    return 0;
}

int altura_arvLLRB(arvLLRB *raiz) {
    if(raiz == NULL) {
        return 0;
    }
    if(*raiz == NULL) {
        return 0;
    }
    int alt_esq = altura_arvLLRB(&((*raiz)->esq));
    int alt_dir = altura_arvLLRB(&((*raiz)->dir));
    if(alt_esq > alt_dir) {
        return(alt_esq + 1);
    } else {
        return(alt_dir + 1);
    }
}

int totalNoLLRB_arvLLRB(arvLLRB *raiz) {
    if(raiz == NULL) {
        return 0;
    }
    if(*raiz == NULL) {
        return 0;
    }
    int alt_esq = totalNoLLRB_arvLLRB(&((*raiz)->esq));
    int alt_dir = totalNoLLRB_arvLLRB(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

void preOrdem_arvLLRB(arvLLRB *raiz) {
    if(raiz == NULL) {
        return;
    }
    if(*raiz != NULL) {
//        printf("%d\n", (*raiz)->p.codigo);
        preOrdem_arvLLRB(&((*raiz)->esq));
        preOrdem_arvLLRB(&((*raiz)->dir));
    }
}

void emOrdem_arvLLRB(arvLLRB *raiz) {
    if(raiz == NULL) {
        return;
    }
    if(*raiz != NULL) {
        emOrdem_arvLLRB(&((*raiz)->esq));
//        printf("%d\n", (*raiz)->p.codigo);
        emOrdem_arvLLRB(&((*raiz)->dir));
    }
}

void posOrdem_arvLLRB(arvLLRB *raiz) {
    if(raiz == NULL) {
        return;
    }
    if(*raiz != NULL) {
        posOrdem_arvLLRB(&((*raiz)->esq));
        posOrdem_arvLLRB(&((*raiz)->dir));
//        printf("%d\n", (*raiz)->p.codigo);
    }
}

int insere_arvLLRB(arvLLRB *raiz, Pessoa p) {
    int resp;
    *raiz = insereNoLLRB(*raiz, p, &resp);
    if((*raiz) != NULL) {
        (*raiz)->cor = BLACK;
    }
    return resp;
}

int remove_arvLLRB(arvLLRB *raiz, int cod) {
    if(consulta_arvLLRB(raiz, cod)) {
        struct NoLLRB *H = *raiz;

        *raiz = removeNoLLRB(H, cod);
        if(*raiz != NULL) {
            (*raiz)->cor = BLACK;
        }
        return 1;
    } else {
        return 0;
    }
}

struct NoLLRB *remove_atual(struct NoLLRB *atual) {
    struct NoLLRB *no1, *no2;
    if(atual->esq == NULL) {
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL) {
        no1 = no2;
        no2 = no2->dir;
    }
    if(no1 != atual) {
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

int consulta_arvLLRB(arvLLRB *raiz, int cod) {
    if(raiz == NULL) {
        return 0;
    }
    struct NoLLRB *atual = *raiz;
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

int cor(struct NoLLRB *H) {
    if(H == NULL){
        return BLACK;
    } else {
        return H->cor;
    }
}

void trocaCor(struct NoLLRB *H) {
    H->cor = !H->cor;
    if(H->esq != NULL) {
        H->esq->cor = !H->esq->cor;
    }
    if(H->dir != NULL) {
        H->dir->cor = !H->dir->cor;
    }
}

struct NoLLRB *rotacionaEsquerda(struct NoLLRB *A) {
    struct NoLLRB *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

struct NoLLRB *rotacionaDireita(struct NoLLRB *A) {
    struct NoLLRB *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

struct NoLLRB *move2EsqRED(struct NoLLRB *H) {
    trocaCor(H);
    if(cor(H->dir->esq) == RED) {
        H->dir = rotacionaDireita(H->dir);
        H = rotacionaEsquerda(H);
        trocaCor(H);
    }
    return H;
}

struct NoLLRB *move2DirRED(struct NoLLRB *H) {
    trocaCor(H);
    if(cor(H->esq->esq) == RED) {
        H = rotacionaDireita(H);
        trocaCor(H);
    }
    return H;
}

struct NoLLRB *balancear(struct NoLLRB *H) {
    if(cor(H->dir) == RED) {
        H = rotacionaEsquerda(H);
    }
    if(H->esq != NULL && cor(H->dir) == RED && cor(H->esq->esq) == RED) {
        H = rotacionaDireita(H);
    }
    if(cor(H->esq) == RED && cor(H->dir) == RED) {
        trocaCor(H);
    }
    return H;
}

struct NoLLRB *insereNoLLRB(struct NoLLRB *H, Pessoa p, int *resp) {
    if(H == NULL) {
        struct NoLLRB *novo;
        novo = (struct NoLLRB*) malloc(sizeof(struct NoLLRB));
        if(novo == NULL) {
            *resp = 0;
            return NULL;
        }
        novo->p = p;
        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        *resp = 1;
        return novo;
    }
    if(p.codigo == H->p.codigo) {
        *resp = 0;
    } else {
        if(p.codigo < H->p.codigo) {
            H->esq = insereNoLLRB(H->esq, p, resp);
        } else {
            H->dir = insereNoLLRB(H->dir, p, resp);
        }
    }
    if(cor(H->dir) == RED && cor(H->esq) == BLACK) {
        H = rotacionaEsquerda(H);
    }
    if(cor(H->dir) == RED && cor(H->esq->esq) == RED) {
        H = rotacionaDireita(H);
    }
    if(cor(H->esq) == RED && cor(H->dir) == RED) {
        trocaCor(H);
    }
    return H;
}

struct NoLLRB *removeMenor(struct NoLLRB *H) {
    if(H->esq == NULL) {
        free(H);
        return NULL;
    }
    if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK) {
        H = move2EsqRED(H);
    }
    H->esq = removeMenor(H->esq);
    return balancear(H);
}

struct NoLLRB *procuraMenor(struct NoLLRB *atual) {
    struct NoLLRB *no1 = atual;
    struct NoLLRB *no2 = atual->esq;
    while(no2 != NULL) {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

struct NoLLRB *removeNoLLRB(struct NoLLRB *H, int cod) {
    if(cod < H->p.codigo) {
        if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK) {
            H = move2EsqRED(H);
        }
        H->esq = removeNoLLRB(H->esq, cod);
    } else {
        if(cor(H->esq) == RED) {
            H = rotacionaDireita(H);
        }
        if(cod == H->p.codigo && (H->dir == NULL)) {
            free(H);
            return NULL;
        }
        if(cor(H->dir) == BLACK && cor(H->dir->esq) == BLACK) {
            H = move2DirRED(H);
        }
        if(cod == H->p.codigo) {
            struct NoLLRB *x = procuraMenor(H->dir);
            H->p.codigo = x->p.codigo;
            H->dir = removeMenor(H->dir);
        } else {
            H->dir = removeNoLLRB(H->dir, cod);
        }
    }
    return balancear(H);
}

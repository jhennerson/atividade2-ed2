#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "pessoa.h"
#include "arvoreAVL.h"
#include "arvoreRubroNegra.h"
#include "arquivo.h"
#include "calculaMedia.h"
#include "printFuctions.h"

#define CAP 15000

double countInsercao_AVL(char arq[]);
double countInsercao_LLRB(char arq[]);

int main() {
    char arqO[] = "massaDados.csv";
    char arqD[] = "dadosOrdenados.csv";

    printf("Carregando dados..");
    criaArquivoOrdenado(arqD, arqO);

    double tempo = 0;
    int opcao;
    int sub;

    do {
        printMainMenu();
        scanf("%d", &opcao);

        switch(opcao) {
        case 1:
            do {
                printSubMenu("Arvore AVL");
                scanf("%d", &sub);
                switch(sub) {
                case 1:
                    system("cls");
                    printf("Insercao na Arvore AVL com dados desordenados:\n");
                    tempo = countInsercao_AVL(arqO);
                    printf("\nTempo de operacao: %lf segundos\n\n", tempo);
                    system("pause");
                    fflush(stdin);
                    break;
                case 2:
                    system("cls");
                    printf("Insercao na Arvore AVL com dados ordenados:\n");
                    tempo = countInsercao_AVL(arqD);
                    printf("\nTempo de operacao: %lf segundos\n\n", tempo);
                    system("pause");
                    fflush(stdin);
                    break;
                case 0:
                    system("cls");
                    break;
                default:
                    printf("Opcao invalida\n");
                    fflush(stdin);
                    system("pause");
                    system("cls");
                    break;
                }
                printf("Pressione qualquer tecla para continuar..\n");
            } while(sub != 0);
            break;
        case 2:
            do {
                printSubMenu("Arvore Rubro Negra");
                scanf("%d", &sub);
                switch(sub) {
                case 1:
                    system("cls");
                    printf("Insercao na Arvore Rubro Negra com dados desordenados:\n");
                    tempo = countInsercao_LLRB(arqO);
                    printf("\nTempo de operacao: %lf segundos\n\n", tempo);
                    system("pause");
                    fflush(stdin);
                    break;
                case 2:
                    system("cls");
                    printf("Insercao na Arvore Rubro Negra com dados ordenados:\n");
                    tempo = countInsercao_LLRB(arqD);
                    printf("\nTempo de operacao: %lf segundos\n\n", tempo);
                    system("pause");
                    fflush(stdin);
                    break;
                case 0:
                    system("cls");
                    break;
                default:
                    printf("Opcao invalida\n");
                    fflush(stdin);
                    system("pause");
                    system("cls");
                    break;
                }
            } while(sub != 0);
            break;
        case 0:
            system("cls");
            printf("Saindo...\n\n");
            break;
        default:
            printf("Opcao invalida\n");
            fflush(stdin);
            system("pause");
            system("cls");
            break;
        }
    } while(opcao != 0);

}

double countInsercao_AVL(char arq[]) {
    arvAVL *raiz = cria_arvAVL();
    Pessoa *p = (Pessoa*) malloc(CAP * sizeof(Pessoa));

    struct timeval start, end;
    double t;
    int registros;

    gettimeofday(&start, NULL);
    registros = leDadosAVL(arq, p, raiz);
    for(int i = 1; i < registros; i++) {
        insere_arvAVL(raiz, p[i]);
    }
    gettimeofday(&end, NULL);

    t = (end.tv_sec + end.tv_usec/1000000.0) - (start.tv_sec + start.tv_usec/1000000.0);

    free(p);
    libera_arvAVL(raiz);

    return t;
}

double countInsercao_LLRB(char arq[]) {
    arvLLRB *raiz = cria_arvLLRB();
    Pessoa *p = (Pessoa*) malloc(CAP * sizeof(Pessoa));

    struct timeval start, end;
    double t;
    int registros;

    gettimeofday(&start, NULL);
    registros = leDadosLLRB(arq, p, raiz);
    for(int i = 1; i < registros; i++) {
        insere_arvLLRB(raiz, p[i]);
    }
    gettimeofday(&end, NULL);

    t = (end.tv_sec + end.tv_usec/1000000.0) - (start.tv_sec + start.tv_usec/1000000.0);

    free(p);
    libera_arvLLRB(raiz);

    return t;
}

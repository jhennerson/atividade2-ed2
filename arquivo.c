#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"
#include "arvoreAVL.h"
#include "arvoreRubroNegra.h"

#define CAP 15000

int comparador(const void *x, const void *y) {
    int primeiro = ((Pessoa *)x)->codigo;
    int segundo = ((Pessoa *)y)->codigo;
    return (primeiro - segundo);
}

int leDadosAVL(char arq[], Pessoa *p, arvAVL *raiz) {
    FILE *f = fopen(arq, "r");
    int registros = 0;
    int linha[256];
    char *campo = NULL;

    while(fgets(linha, 255, f) != NULL) {

        if((strlen(linha) > 0) && (linha[strlen(linha) - 1]) == '\n') {
            linha[strlen(linha) - 1] = '\0';
        }

        if(ferror(f)) {
            printf("\nErro na leitura do arquivo!\n");
            system("pause");
            exit(1);
        }

        campo = strtok(linha, ";");
        p[registros].codigo = atoi(campo);

        campo = strtok(NULL, ";");
        strcpy(p[registros].nome, campo);

        campo = strtok(NULL, ";");
        p[registros].idade = atoi(campo);

        campo = strtok(NULL, ";");
        strcpy(p[registros].empresa, campo);

        campo = strtok(NULL, ";");
        strcpy(p[registros].departamento, campo);

        campo = strtok(NULL, "\n");
        p[registros].salario = atof(campo);

        registros++;
    }

    fclose(f);
    return registros;
}

int leDadosLLRB(char arq[], Pessoa *p, arvLLRB *raiz) {
    FILE *f = fopen(arq, "r");
    int registros = 0;
    int linha[256];
    char *campo = NULL;

    while(fgets(linha, 255, f) != NULL) {

        if((strlen(linha) > 0) && (linha[strlen(linha) - 1]) == '\n') {
            linha[strlen(linha) - 1] = '\0';
        }

        if(ferror(f)) {
            printf("\nErro na leitura do arquivo!\n");
            system("pause");
            exit(1);
        }

        campo = strtok(linha, ";");
        p[registros].codigo = atoi(campo);

        campo = strtok(NULL, ";");
        strcpy(p[registros].nome, campo);

        campo = strtok(NULL, ";");
        p[registros].idade = atoi(campo);

        campo = strtok(NULL, ";");
        strcpy(p[registros].empresa, campo);

        campo = strtok(NULL, ";");
        strcpy(p[registros].departamento, campo);

        campo = strtok(NULL, "\n");
        p[registros].salario = atof(campo);

        registros++;
    }

    fclose(f);
    return registros;
}

void criaArquivoOrdenado(char arqD[], char arqO[]) {
    FILE *fOrig = fopen(arqO, "r");

    if(fOrig == NULL) {
        printf("\n\nErro na abertura do arquivo de origem!!!\n\n");
        system("pause");
        exit(1);
    }

    int registros = 0;

    Pessoa *p = (Pessoa*) malloc(CAP * sizeof(Pessoa));

    while(!feof(fOrig)) {
        int linha[256];
        char *campo = NULL;

        fgets(linha, 255, fOrig);

        linha[strlen(linha) - 1] = '\0';

        if(strlen(linha) < 6) {
            printf("Arquivo formatado incorretamente");
            system("pause");
            exit(1);
        }

        if(ferror(fOrig)) {
            printf("Erro na leitura do arquivo!\n");
            system("pause");
            exit(1);
        }

        campo = strtok(linha, ";");
        p[registros].codigo = atoi(campo);

        campo = strtok(NULL, ";");
        strcpy(p[registros].nome, campo);

        campo = strtok(NULL, ";");
        p[registros].idade = atoi(campo);

        campo = strtok(NULL, ";");
        strcpy(p[registros].empresa, campo);

        campo = strtok(NULL, ";");
        strcpy(p[registros].departamento, campo);

        campo = strtok(NULL, ";");
        p[registros].salario = atof(campo);

        registros++;
    }

    fclose(fOrig);

    FILE *fDest = fopen(arqD, "w");

    if(fDest == NULL) {
        printf("\n\nErro na abertura do arquivo destino!!!\n\n");
        system("pause");
        exit(1);
    }

    fprintf(fDest,"Codigo;Nome;Idade;Empresa;Departamento;Salario\n");

    qsort(p, registros, sizeof(Pessoa), comparador);

    for(int i = 1; i < registros; i++) {
        fprintf(fDest,"%d;%s;%d;%s;%s;%.2lf\n", p[i].codigo,
                                                p[i].nome,
                                                p[i].idade,
                                                p[i].empresa,
                                                p[i].departamento,
                                                p[i].salario);
    }

    fclose(fDest);
}

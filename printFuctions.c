void printMainMenu() {
    system("cls");
    printf("\tBem vindo ao teste de Arvores Binarias de Busca\n");
    printf("\nEscolha uma opcao: \n");
    printLS(1);
    printf("1 - Arvore AVL");
    printLS(1);
    printf("2 - Arvore Rubro Negra");
    printLS(1);
    printf("0 - Sair");
    printLS(1);
}

void printSubMenu(char title[]) {
    system("cls");
    printf("\t%s\n", title);
    printf("\nEscolha a condicao dos dados: \n");
    printLS(1);
    printf("1 - Dados desordenados");
    printLS(1);
    printf("2 - Dados ordenados");
    printLS(1);
    printf("0 - Voltar");
    printLS(1);
}

//LS = LineSkip
void printLS(int n) {
    for(int i = 0; i < n; i++){
        printf("\n");
    }
}

void printRelatorio(double media, double tempoOrdenado, double tempoDesordenado) {
    printf("\nMedia: %f\n", media);
    printf("\nTempo para os arquivos ordenados: %f\n", tempoOrdenado);
    printf("\nTempo para os arquivos desordenados: %f\n\n\n", tempoDesordenado);
}

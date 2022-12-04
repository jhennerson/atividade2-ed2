typedef struct pessoa {
    int codigo;
    char nome[32];
    int idade;
    char empresa[32];
    char departamento[32];
    double salario;
} Pessoa;

void printPessoa(Pessoa p);

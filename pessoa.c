#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"

void printPessoa(Pessoa p) {
    printf("\n%d, %s, %d, %s, %s, %lf", p.codigo,
                                        p.nome,
                                        p.idade,
                                        p.empresa,
                                        p.departamento,
                                        p.salario);
}

#include <stdio.h>
#include <stdlib.h>
#define TEM_CONFLITO(matriz, t1, t2) (matriz[(t1)-1][(t2)-1] == 1)

typedef struct {
    int num;
    int grau;
    int horario;
}Turma;

int** alocarMatrizTurmas(int turmas) {
    int **matriz;
    matriz = (int**)malloc(turmas * sizeof(int*));
    if (matriz == NULL) {
        perror("Erro ao alocar matriz turmas\n");
        return NULL;
    }
    for (int i = 0; i < turmas; i++) {
        matriz[i] = (int*)calloc(turmas, sizeof(int));
        if (matriz[i] == NULL) {
            printf("Erro ao alocar linha %d\n", i);
            for (int j = 0; j < i; j++) {
                free(matriz[j]);
            }
            free(matriz);
            return NULL;
        }
    }

    return matriz;
}


// void mostrarMatriz(int** matriz, int turmas) {
//     printf("\nMatriz de Conflitos:\n");
//
//     // Imprime cabeçalho horizontal (números das turmas)
//     printf("     ");
//     for (int j = 0; j < turmas; j++) {
//         printf("%2d ", j + 1); // Mostra colunas de 1 a N
//     }
//     printf("\n");
//
//     // Imprime cada linha da matriz com índice correspondente
//     for (int i = 0; i < turmas; i++) {
//         printf("%2d: ", i + 1);
//         for (int j = 0; j < turmas; j++) {
//             printf("%2d ", matriz[i][j]); // Mostra 0 ou 1 (conflito)
//         }
//         printf("\n");
//     }
// }

void mostrarGrausRecursivo(Turma* turmas, int indice, int total) {
    if (indice >= total) return;

    printf("Turma %d: grau = %d\n", turmas[indice].num, turmas[indice].grau);
    mostrarGrausRecursivo(turmas, indice + 1, total);
}

void liberarMatrizTurmas(int** matriz, int turmas) {
    if (matriz == NULL) return;
    for (int i = 0; i < turmas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int lerConflitos(FILE *arq, int **matrizTurmas, int totalConflitos) {
    int t1, t2;
    for (int i = 0; i < totalConflitos; i++) {
        if (fscanf(arq, " e %d %d", &t1, &t2) != 2) { //
            printf("Erro na linha do conflito %d\n", i + 1);
            return -1;
        }
        matrizTurmas[t1 - 1][t2 - 1] = 1;
        matrizTurmas[t2 - 1][t1 - 1] = 1;
    }
    return 0;
}

Turma* preencheInfo(int** matrizTurmas, int turmas) {
    Turma* turmasInfo = malloc(turmas * sizeof(Turma));
    if (turmasInfo == NULL) {
        perror("Erro ao alocar vetor de graus");
        return NULL;
    }
    for (int i = 0; i < turmas; i++) {
        turmasInfo[i].num = i+1;
        turmasInfo[i].grau = 0;
        turmasInfo[i].horario = 0;

        for (int j = 0; j < turmas; j++) {
            turmasInfo[i].grau += matrizTurmas[i][j];
            }
        }
    return turmasInfo;
}

void ordenarTurmas(Turma* turmas, int qtd_turmas) {
    for (int i = 0; i < qtd_turmas-1; i++) {
        for (int j = 0; j < qtd_turmas-i-1; j++) {
            if (turmas[j].grau < turmas[j+1].grau) {
                Turma temp = turmas[j];
                turmas[j] = turmas[j+1];
                turmas[j+1] = temp;
            }
        }
    }
}


int alocarHorarios(int** matriz, Turma* turmas, int turmas_count) {
    int *horarios = (int*)calloc(turmas_count, sizeof(int));
    int max_horario = 1;

    turmas[0].horario = 1;

    for (int i = 1; i < turmas_count; i++) {
        int horarioDisponivel = 1;

        for (int j = 0; j < i; j++) {
            if (TEM_CONFLITO(matriz, turmas[i].num, turmas[j].num) &&
                turmas[j].horario == horarioDisponivel) {
                horarioDisponivel++;
                }
        }
        turmas[i].horario = horarioDisponivel;

        if (horarioDisponivel > max_horario) {
            max_horario = horarioDisponivel;
        }
    }

    free(horarios);
    return max_horario;
}


void mostrarHorarios(Turma* turmas, int turmas_count, int total_horarios) {
    printf("\n=== RESULTADO DA ALOCACAO DE HORARIOS ===\n");
    printf("Total de horarios necessarios: %d\n\n", total_horarios);
    printf("\nAgrupamento por horario:\n");
    for (int h = 1; h <= total_horarios; h++) {
        printf("Horario %d: ", h);
        for (int i = 0; i < turmas_count; i++) {
            if (turmas[i].horario == h) {
                printf("%d ", turmas[i].num);
            }
        }
        printf("\n");
    }
}

int main(){
    FILE *arq = fopen("Cenarios/entrada.txt", "r");
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    int turmas, conflitos;
    if (fscanf(arq, "p edge %d %d", &turmas, &conflitos) != 2) {
        printf("Formato de arquivo inválido\n");
        fclose(arq);
        return -1;
    }


    int **matrizTurmas = alocarMatrizTurmas(turmas);
    if (matrizTurmas == NULL) {
        fclose(arq);
        return -1;
    }
    printf("Matriz alocada com sucesso para %d turmas!\n", turmas);

    if (lerConflitos(arq, matrizTurmas, conflitos) != 0) {
        liberarMatrizTurmas(matrizTurmas, turmas);
        fclose(arq);
        return -1;
    }
    fclose(arq);

    Turma* turmasInfo = preencheInfo(matrizTurmas, turmas);
    if (turmasInfo == NULL) {
        liberarMatrizTurmas(matrizTurmas, turmas);
        return -1;
    }

    ordenarTurmas(turmasInfo, turmas);

    printf("\nGrau de cada turma:\n");
    mostrarGrausRecursivo(turmasInfo, 0, turmas);

    int total_horarios = alocarHorarios(matrizTurmas, turmasInfo, turmas);
    mostrarHorarios(turmasInfo, turmas, total_horarios);

    free(turmasInfo);
    liberarMatrizTurmas(matrizTurmas, turmas);

    return 0; 
}
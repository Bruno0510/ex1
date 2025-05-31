#include <stdio.h>
#include <string.h>

#define NUM_ESTADOS 26

typedef struct {
    char nome[50];
    int veiculos;
    int acidentes;
} Estado;

void coletarDados(Estado estados[]) {
    char *nomes[NUM_ESTADOS] = {
        "Acre", "Alagoas", "Amapa", "Amazonas", "Bahia", "Ceara", "Distrito Federal",
        "Espirito Santo", "Goias", "Maranhao", "Mato Grosso", "Mato Grosso do Sul",
        "Minas Gerais", "Para", "Paraiba", "Parana", "Pernambuco", "Piaui", 
        "Rio de Janeiro", "Rio Grande do Norte", "Rio Grande do Sul", "Rondonia", 
        "Roraima", "Santa Catarina", "Sao Paulo", "Sergipe"
    };

    int veiculos[NUM_ESTADOS] = {
        120000, 150000, 80000, 130000, 400000, 300000, 500000,
        200000, 250000, 100000, 110000, 115000,
        600000, 220000, 140000, 350000, 330000, 95000,
        700000, 180000, 360000, 90000, 60000, 270000, 1000000, 85000
    };

    int acidentes[NUM_ESTADOS] = {
        500, 700, 300, 600, 2000, 1200, 1500,
        800, 900, 450, 500, 510,
        2300, 1100, 600, 1300, 1600, 400,
        2700, 650, 1450, 390, 200, 1250, 4500, 380
    };

    for (int i = 0; i < NUM_ESTADOS; i++) {
        strcpy(estados[i].nome, nomes[i]);
        estados[i].veiculos = veiculos[i];
        estados[i].acidentes = acidentes[i];
    }
}


void maiorMenorAcidentes(Estado estados[], int *indiceMaior, int *indiceMenor) {
    *indiceMaior = 0;
    *indiceMenor = 0;
    for (int i = 1; i < NUM_ESTADOS; i++) {
        if (estados[i].acidentes > estados[*indiceMaior].acidentes)
            *indiceMaior = i;
        if (estados[i].acidentes < estados[*indiceMenor].acidentes)
            *indiceMenor = i;
    }
}

float percentualAcidentes(Estado estado) {
    if (estado.veiculos == 0) return 0.0;
    return (float)estado.acidentes / estado.veiculos * 100;
}

float mediaAcidentes(Estado estados[]) {
    int soma = 0;
    for (int i = 0; i < NUM_ESTADOS; i++) {
        soma += estados[i].acidentes;
    }
    return (float)soma / NUM_ESTADOS;
}

void estadosAcimaDaMedia(Estado estados[], float media) {
    printf("\nEstados com acidentes acima da media nacional:\n");
    for (int i = 0; i < NUM_ESTADOS; i++) {
        if (estados[i].acidentes > media) {
            printf("%s - Acidentes: %d\n", estados[i].nome, estados[i].acidentes);
        }
    }
}

int main() {
    Estado estados[NUM_ESTADOS];
    int indMaior, indMenor;
    float media;

    coletarDados(estados);
    
    maiorMenorAcidentes(estados, &indMaior, &indMenor);
    
    printf("\nEstado com MAIOR numero de acidentes: %s (%d acidentes)\n", 
        estados[indMaior].nome, estados[indMaior].acidentes);
    printf("Estado com MENOR numero de acidentes: %s (%d acidentes)\n", 
        estados[indMenor].nome, estados[indMenor].acidentes);

    printf("\nPercentual de veiculos envolvidos em acidentes por estado:\n");
    for (int i = 0; i < NUM_ESTADOS; i++) {
        float perc = percentualAcidentes(estados[i]);
        printf("%s: %.2f%%\n", estados[i].nome, perc);
    }

    media = mediaAcidentes(estados);
    printf("\nMedia de acidentes no pais: %.2f\n", media);

    estadosAcimaDaMedia(estados, media);

    return 0;
}
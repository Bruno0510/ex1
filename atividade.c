#include <stdio.h>
#include <ctype.h>

int contar_vogais(char texto[]) {
    int indice = 0, qtd_vogais = 0;
    char caractere;

    while (texto[indice] != '\0') {
        caractere = texto[indice];
        if (caractere == 'a' || caractere == 'e' || caractere == 'i' || caractere == 'o' || caractere == 'u' ||
            caractere == 'A' || caractere == 'E' || caractere == 'I' || caractere == 'O' || caractere == 'U') {
            qtd_vogais++;
        }
        indice++;
    }

    return qtd_vogais;
}

void inicial_maiucula(char texto[]) {
    int posicao = 0;
    int inicio_palavra = 1;

    while (texto[posicao] != '\0') {
        if (texto[posicao] == ' ') {
            inicio_palavra = 1;
        } else if (inicio_palavra && texto[posicao] >= 'a' && texto[posicao] <= 'z') {
            texto[posicao] = texto[posicao] - 32;
            inicio_palavra = 0;
        } else {
            inicio_palavra = 0;
        }
        posicao++;
    }
}

int main() {
    char entrada[1000];

    printf("Digite uma frase: ");
    fgets(entrada, sizeof(entrada), stdin);

    printf("Frase digitada: %s", entrada);

    int total = contar_vogais(entrada);
    printf("Número de vogais: %d\n", total);

    inicial_maiucula(entrada);
    printf("Frase com iniciais maiúsculas: %s", entrada);

    return 0;
}
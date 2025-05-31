
#include <stdio.h>
#include <ctype.h>

int contar_vogais(char frase[]) {
    int i = 0, contador = 0;
    char c;

    while (frase[i] != '\0') {
        c = frase[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            contador++;
        }
        i++;
    }

    return contador;
}

void letra_upper(char frase[]) {
    int i = 0;
    int nova_palavra = 1;

    while (frase[i] != '\0') {
        if (frase[i] == ' ') {
            nova_palavra = 1;
        } else if (nova_palavra && frase[i] >= 'a' && frase[i] <= 'z') {
            frase[i] = frase[i] - 32;
            nova_palavra = 0;
        } else {
            nova_palavra = 0;
        }
        i++;
    }
}

int main() {
    char frase[1000];

    printf("Digite uma frase: ");
    fgets(frase, sizeof(frase), stdin);

    printf("Frase digitada: %s", frase);

    int total_vogais = contar_vogais(frase);
    printf("numero de vogais: %d\n", total_vogais);

    letra_upper(frase);
    printf("Frases começando com letras maiúsculas: %s", frase);

    return 0;
}
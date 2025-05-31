#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITULO 100
#define MAX_NOME 100
#define MAX_FAVORITOS 10

// Estruturas
typedef struct {
    int id;
    char titulo[MAX_TITULO];
    int duracao;
} Video;

typedef struct {
    int id;
    char nome[MAX_NOME];
    int favoritos[MAX_FAVORITOS];
    int qtd_favoritos;
} Usuario;

// Funções
void cadastrar_video() {
    FILE *arq = fopen("videos.dat", "ab");
    Video v;

    printf("ID do vídeo: ");
    scanf("%d", &v.id);
    getchar();

    printf("Título: ");
    fgets(v.titulo, MAX_TITULO, stdin);
    strtok(v.titulo, "\n");

    printf("Duração (min): ");
    scanf("%d", &v.duracao);

    fwrite(&v, sizeof(Video), 1, arq);
    fclose(arq);
    printf("Vídeo cadastrado com sucesso!\n");
}

void listar_videos() {
    FILE *arq = fopen("videos.dat", "rb");
    Video v;

    printf("\n--- Lista de Vídeos ---\n");
    while (fread(&v, sizeof(Video), 1, arq)) {
        printf("ID: %d | Título: %s | Duração: %d min\n", v.id, v.titulo, v.duracao);
    }

    fclose(arq);
}

void cadastrar_usuario() {
    FILE *arq = fopen("usuarios.dat", "ab");
    Usuario u;

    printf("ID do usuário: ");
    scanf("%d", &u.id);
    getchar();

    printf("Nome: ");
    fgets(u.nome, MAX_NOME, stdin);
    strtok(u.nome, "\n");

    printf("Quantos vídeos favoritados (máx %d)? ", MAX_FAVORITOS);
    scanf("%d", &u.qtd_favoritos);
    if (u.qtd_favoritos > MAX_FAVORITOS) u.qtd_favoritos = MAX_FAVORITOS;

    for (int i = 0; i < u.qtd_favoritos; i++) {
        printf("ID do vídeo favorito %d: ", i + 1);
        scanf("%d", &u.favoritos[i]);
    }

    fwrite(&u, sizeof(Usuario), 1, arq);
    fclose(arq);
    printf("Usuário cadastrado com sucesso!\n");
}

void relatorio_usuarios() {
    FILE *fU = fopen("usuarios.dat", "rb");
    FILE *fV = fopen("videos.dat", "rb");
    Usuario u;
    Video v;

    printf("\n--- Relatório de Usuários ---\n");

    while (fread(&u, sizeof(Usuario), 1, fU)) {
        printf("Usuário: %s (ID %d)\nFavoritos:\n", u.nome, u.id);
        for (int i = 0; i < u.qtd_favoritos; i++) {
            rewind(fV); // volta ao início do arquivo de vídeos
            while (fread(&v, sizeof(Video), 1, fV)) {
                if (v.id == u.favoritos[i]) {
                    printf(" - %s (ID %d)\n", v.titulo, v.id);
                    break;
                }
            }
        }
        printf("\n");
    }

    fclose(fU);
    fclose(fV);
}

void atualizar_video() {
    FILE *arq = fopen("videos.dat", "rb+");
    int id;
    Video v;

    printf("ID do vídeo a atualizar: ");
    scanf("%d", &id);
    getchar();

    while (fread(&v, sizeof(Video), 1, arq)) {
        if (v.id == id) {
            printf("Novo título: ");
            fgets(v.titulo, MAX_TITULO, stdin);
            strtok(v.titulo, "\n");

            printf("Nova duração: ");
            scanf("%d", &v.duracao);

            fseek(arq, -sizeof(Video), SEEK_CUR);
            fwrite(&v, sizeof(Video), 1, arq);
            printf("Vídeo atualizado com sucesso!\n");
            fclose(arq);
            return;
        }
    }

    printf("Vídeo com ID %d não encontrado.\n", id);
    fclose(arq);
}

void remover_video() {
    FILE *orig = fopen("videos.dat", "rb");
    FILE *novo = fopen("videos_temp.dat", "wb");
    int id;
    Video v;
    int encontrado = 0;

    printf("ID do vídeo para remover: ");
    scanf("%d", &id);

    while (fread(&v, sizeof(Video), 1, orig)) {
        if (v.id != id) {
            fwrite(&v, sizeof(Video), 1, novo);
        } else {
            encontrado = 1;
        }
    }

    fclose(orig);
    fclose(novo);

    if (encontrado) {
        remove("videos.dat");
        rename("videos_temp.dat", "videos.dat");
        printf("Vídeo removido com sucesso.\n");
    } else {
        remove("videos_temp.dat");
        printf("Vídeo com ID %d não encontrado.\n", id);
    }
}

void menu() {
    int opcao;
    do {
        printf("\n=== MENU ===\n");
        printf("1. Cadastrar vídeo\n");
        printf("2. Cadastrar usuário\n");
        printf("3. Listar vídeos\n");
        printf("4. Relatório de usuários\n");
        printf("5. Atualizar vídeo\n");
        printf("6. Remover vídeo\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrar_video(); break;
            case 2: cadastrar_usuario(); break;
            case 3: listar_videos(); break;
            case 4: relatorio_usuarios(); break;
            case 5: atualizar_video(); break;
            case 6: remover_video(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

int main() {
    menu();
    return 0;
}
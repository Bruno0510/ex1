#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITULO 100
#define MAX_NOME 100
#define MAX_FAVORITOS 10

typedef struct {
    int id;
    char titulo[MAX_TITULO];
    int duracao; // duração em minutos
} VideoInfo;

typedef struct {
    int id;
    char nome[MAX_NOME];
    int favoritos[MAX_FAVORITOS]; // IDs dos vídeos
    int qtd_favoritos;
} UsuarioInfo;

// Funções auxiliares
void cadastrar_video() {
    FILE *arquivoVideo = fopen("videos.dat", "ab");
    VideoInfo video;

    printf("ID do vídeo: ");
    scanf("%d", &video.id);
    getchar();

    printf("Título: ");
    fgets(video.titulo, MAX_TITULO, stdin);
    strtok(video.titulo, "\n");

    printf("Duração (min): ");
    scanf("%d", &video.duracao);

    fwrite(&video, sizeof(VideoInfo), 1, arquivoVideo);
    fclose(arquivoVideo);
}

void listar_videos() {
    FILE *arquivoVideo = fopen("videos.dat", "rb");
    VideoInfo video;

    printf("\n--- Lista de Vídeos ---\n");
    while (fread(&video, sizeof(VideoInfo), 1, arquivoVideo)) {
        printf("ID: %d | Título: %s | Duração: %d min\n", video.id, video.titulo, video.duracao);
    }
    fclose(arquivoVideo);
}

void cadastrar_usuario() {
    FILE *arquivoUsuario = fopen("usuarios.dat", "ab");
    UsuarioInfo usuario;

    printf("ID do usuário: ");
    scanf("%d", &usuario.id);
    getchar();

    printf("Nome: ");
    fgets(usuario.nome, MAX_NOME, stdin);
    strtok(usuario.nome, "\n");

    printf("Quantos vídeos favoritados (máx %d)? ", MAX_FAVORITOS);
    scanf("%d", &usuario.qtd_favoritos);
    if (usuario.qtd_favoritos > MAX_FAVORITOS) usuario.qtd_favoritos = MAX_FAVORITOS;

    for (int i = 0; i < usuario.qtd_favoritos; i++) {
        printf("ID do vídeo favorito %d: ", i + 1);
        scanf("%d", &usuario.favoritos[i]);
    }

    fwrite(&usuario, sizeof(UsuarioInfo), 1, arquivoUsuario);
    fclose(arquivoUsuario);
}

void listar_usuarios_com_videos() {
    FILE *arquivoUsuario = fopen("usuarios.dat", "rb");
    FILE *arquivoVideo = fopen("videos.dat", "rb");
    UsuarioInfo usuario;
    VideoInfo video;

    printf("\n--- Relatório de Usuários com Vídeos Favoritos ---\n");
    while (fread(&usuario, sizeof(UsuarioInfo), 1, arquivoUsuario)) {
        printf("Usuário: %s (ID %d)\nFavoritos:\n", usuario.nome, usuario.id);
        for (int i = 0; i < usuario.qtd_favoritos; i++) {
            rewind(arquivoVideo);
            while (fread(&video, sizeof(VideoInfo), 1, arquivoVideo)) {
                if (video.id == usuario.favoritos[i]) {
                    printf(" - %s (ID %d)\n", video.titulo, video.id);
                    break;
                }
            }
        }
        printf("\n");
    }

    fclose(arquivoUsuario);
    fclose(arquivoVideo);
}

void atualizar_video() {
    FILE *arquivoVideo = fopen("videos.dat", "rb+");
    int id;
    printf("ID do vídeo para atualizar: ");
    scanf("%d", &id);

    VideoInfo video;

    while (fread(&video, sizeof(VideoInfo), 1, arquivoVideo)) {
        if (video.id == id) {
            printf("Novo título: ");
            getchar();
            fgets(video.titulo, MAX_TITULO, stdin);
            strtok(video.titulo, "\n");

            printf("Nova duração: ");
            scanf("%d", &video.duracao);

            fseek(arquivoVideo, -sizeof(VideoInfo), SEEK_CUR);
            fwrite(&video, sizeof(VideoInfo), 1, arquivoVideo);
            break;
        }
    }
    fclose(arquivoVideo);
}

void remover_video() {
    FILE *arquivoVideo = fopen("videos.dat", "rb");
    FILE *arquivoTemporario = fopen("videos_tmp.dat", "wb");

    int id;
    printf("ID do vídeo para remover: ");
    scanf("%d", &id);

    VideoInfo video;
    while (fread(&video, sizeof(VideoInfo), 1, arquivoVideo)) {
        if (video.id != id) {
            fwrite(&video, sizeof(VideoInfo), 1, arquivoTemporario);
        }
    }

    fclose(arquivoVideo);
    fclose(arquivoTemporario);

    remove("videos.dat");
    rename("videos_tmp.dat", "videos.dat");
}

void menu() {
    int opcao;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Cadastrar vídeo\n");
        printf("2. Cadastrar usuário\n");
        printf("3. Listar vídeos\n");
        printf("4. Relatório de usuários com vídeos\n");
        printf("5. Atualizar vídeo\n");
        printf("6. Remover vídeo\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrar_video(); break;
            case 2: cadastrar_usuario(); break;
            case 3: listar_videos(); break;
            case 4: listar_usuarios_com_videos(); break;
            case 5: atualizar_video(); break;
            case 6: remover_video(); break;
            case 0: break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

int main() {
    menu();
    return 0;
}
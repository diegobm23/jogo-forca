#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "forca.h"

char palavrasecreta[TAMANH0_PALAVRA];
char chutes[26];
int chutesdados = 0;

void abertura() {
  printf("\n/****************/\n");
  printf("/ Jogo de Forca */\n");
  printf("/****************/\n\n");
}

void chuta() {
    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);

    chutes[chutesdados] = chute;
    chutesdados++;
}

void desenhaforca() {
  int erros = chuteserrados();

  printf("  _______       \n");
  printf(" |/      |      \n");
  printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
  printf(" |      %c%c%c  \n", (erros>=3?'\\':' '),(erros>=2?'|':' '), (erros>=3?'/': ' '));
  printf(" |       %c     \n", (erros>=2?'|':' '));
  printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
  printf(" |              \n");
  printf("_|___           \n");
  printf("\n\n");

  for (int i = 0; i < strlen(palavrasecreta); i++) {

      if (jachutou(palavrasecreta[i])) {
          printf("%c ", palavrasecreta[i]);
      } else {
          printf("_ ");
      }

  }

  printf("\n");
}

FILE* abrirarquivo() {
  FILE* file;
  file = fopen("palavras.txt", "r+");

  if (file == 0) {
    printf("OPS, Arquivo de palavras não encontrado =(");
    exit(1);
  }

  return file;
}

void adicionapalavra() {
  char escolha;

  printf("Você deseja adicionar uma nova palavra ao jogo? (S/N): ");
  scanf(" %c", &escolha);

  if (escolha == 'S') {
    char novapalavra[TAMANH0_PALAVRA];
    printf("Digite a nova palavra: ");
    scanf("%s", novapalavra);

    FILE* file = abrirarquivo();

    int qtd;
    fscanf(file, "%d", &qtd);
    qtd++;
    fseek(file, 0, SEEK_SET);
    fprintf(file, "%d", qtd);

    fseek(file, 0, SEEK_END);
    fprintf(file, "%s", novapalavra);

    fclose(file);
  }
}

void escolhepalavra() {
  FILE* file = abrirarquivo();

  int qtdpalavras;
  fscanf(file, "%d", &qtdpalavras);


  srand(time(0));
  int randomico = rand() % qtdpalavras;

  for (int i = 0; i < randomico; i++) {
    fscanf(file, "%s", palavrasecreta);
  }

  fclose(file);
}

int chuteserrados() {
  int erros = 0;

  for (int i = 0; i < chutesdados; i++) {
    int existe = 0;

    for (int j = 0; j < strlen(palavrasecreta); j++) {
      if (chutes[i] == palavrasecreta[j]) {
        existe = 1;
        break;
      }
    }

    if (!existe) erros++;
  }

  return erros;
}

int enforcou() {
  return chuteserrados() >= 5;
}

int acertou() {
  for (int i = 0; i < strlen(palavrasecreta); i++) {
    if (!jachutou(palavrasecreta[i])) {
      return 0;
    }
  }

  return 1;
}

int jachutou(char letra) {
  int achou = 0;

  for (int j = 0; j < chutesdados; j++) {
    if (chutes[j] == letra) {
      achou = 1;
      break;
    }
  }

  return achou;
}

int main() {
  abertura();
  escolhepalavra();

  do {
    desenhaforca();
    chuta();
  } while (!acertou() && !enforcou());

  if (acertou()) {
    printf("\nParabéns, você ganhou!\n\n");
    printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n\n");
  } else {
    printf("\nPuxa, você foi enforcado!\n");
    printf("A palavra era **%s**\n\n", palavrasecreta);

    printf("    _______________         \n");
    printf("   /               \\       \n");
    printf("  /                 \\      \n");
    printf("//                   \\/\\  \n");
    printf("\\|   XXXX     XXXX   | /   \n");
    printf(" |   XXXX     XXXX   |/     \n");
    printf(" |   XXX       XXX   |      \n");
    printf(" |                   |      \n");
    printf(" \\__      XXX      __/     \n");
    printf("   |\\     XXX     /|       \n");
    printf("   | |           | |        \n");
    printf("   | I I I I I I I |        \n");
    printf("   |  I I I I I I  |        \n");
    printf("   \\_             _/       \n");
    printf("     \\_         _/         \n");
    printf("       \\_______/           \n");
  }

  adicionapalavra();
}

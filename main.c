#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

char jogo[9] = "         ";
bool winner = false, continuaOJogo = true;
int rodada = 1, jogador;

// Mostra o estado atual do jogo na tela
void printJogo(int tipo) {
  if(tipo == 0) {
    for (int i = 0; i < 9; i++) {
      if(i == 6 || i == 7 || i == 8) printf(" %d ", i+1);
      else printf("_%d_", i+1);

      if((i+1)%3 == 0) printf("\n");
      else printf("|");
    }
  }

  if(tipo == 1) {
    for (int i = 0; i < 9; i++) {
      if(i == 6 || i == 7 || i == 8) printf(" %c ", jogo[i]);
      else printf("_%c_", jogo[i]);

      if((i+1)%3 == 0) printf("\n");
      else printf("|");
    }
  }
}

// Pedir a jogada na vez do jogador
bool pedirJogada(int rodada) {
  bool validacao = false;
  int coord;

  do {
    if(rodada%2) {
      printf("Jogador 1: ");
      scanf("%d", &coord);

      if (coord == 0) {
        jogador = coord;
        return false;
      } else {
        if (jogo[coord - 1] == ' ') {
          jogo[coord - 1] = 'x';
          validacao = false;
        } else {
          validacao = true;
          printf("Inválido. Tente de novo!\n");
        }
      }


    } else {
      printf("Jogador 2: ");
      scanf("%d", &coord);

      if (coord == 0) {
        jogador = coord;
        return false;
      } else {
        if (jogo[coord - 1] == ' ') {
          jogo[coord - 1] = 'o';
          validacao = false;
        } else {
          validacao = true;
          printf("Inválido. Tente de novo!\n\n");
        }
      }

    }
  } while(validacao);

  return true;
}

// Verifica se o há um ganhador
void ganhador() {
  if(jogo[0] != ' ' && (
    (jogo[0] == jogo[1] && jogo[1] == jogo[2])
    ||
    (jogo[0] == jogo[3] && jogo[3] == jogo[6])
    ||
    (jogo[0] == jogo[4] && jogo[4] == jogo[8])
  )) {
    jogador = jogo[0];
    winner = true;
  } else if(
    jogo[2] != ' '
    &&
    (jogo[2] == jogo[5] && jogo[5] == jogo[8])
  ) {
    jogador = jogo[2];
    winner = true;
  } else if (jogo[4] != ' ' && (
    (jogo[4] == jogo[6] && jogo[4] == jogo[2])
    ||
    (jogo[4] == jogo[3] && jogo[4] == jogo[5])
    ||
    (jogo[4] == jogo[1] && jogo[4] == jogo[7])
  )) {
    jogador = jogo[4];
    winner = true;
  } else if(
    jogo[6] != ' '
    &&
    (jogo[6] == jogo[7] && jogo[6] == jogo[8])
  ) {
    jogador = jogo[6];
    winner = true;
  }
}

// Inicia o jogo
void rodarJogo() {
  printf("============ Jogo da velha ============\n");
  printf("Para jogar, o jogador deve digitar a posição em que quer colocar 'x' ou 'o', como está representada a seguir:\n\n");
  
  printJogo(0);

  printf("Caso empate ou queira começar de novo, digite '0'.\n");

  for (
    int rodada = 1;
    winner == false && continuaOJogo == true;
    rodada++
  ) {

    printf("\n\n------------ Rodada %d ------------\n", rodada);

    continuaOJogo = pedirJogada(rodada);

    printJogo(1);

    if(rodada > 4) ganhador();
  }

  if(jogador == 0) {
    continuaOJogo = true;
    printf("Parece que ninguém venceu.");
  } else {
    if(jogador == 'x') jogador = 1;
    else if(jogador == 'o') jogador = 2;

    printf("Jogador %i venceu. PARABÉNS!", jogador);
  }
}

int main(void) {
  system("tput reset");
  int continua;
  
  do {

    rodarJogo();

    printf("\n\n[0] Sair\n[1] Jogar novamente\n>");
    scanf("%d", &continua);

    if (continua == 1) {
      system("tput reset");
      winner = false;
      rodada = 1;
      for(int i=0; i<9; i++){
        jogo[i] = ' ';
      }
    }
  } while(!winner);

  printf("\nObrigado por jogar!\n");

  return 0;
}
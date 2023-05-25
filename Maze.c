#include "abdrive360.h" // Include the ActivityBot360 library
#include "ping.h"
#include <stdio.h>

#define MAX_SIZE 12 // Tamanho máximo do labirinto (deve ser ímpar)

void printMaze(char maze[][MAX_SIZE], int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf("%c ", maze[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

int main() {
  int x = 0;
  int y = 0;
  int mazeSize = MAX_SIZE; // Tamanho do labirinto
  char maze[MAX_SIZE][MAX_SIZE]; // Matriz para representar o labirinto

  // Inicializar o labirinto com paredes
  for (int i = 0; i < mazeSize; i++) {
    for (int j = 0; j < mazeSize; j++) {
      if (i == 0 || i == mazeSize - 1 || j == 0 || j == mazeSize - 1) {
        maze[i][j] = '#'; // Bordas
      } else {
        maze[i][j] = ' '; // Espaços vazios dentro do labirinto
      }
    }
  }

  // Main loop
  while (1) {
    // Atualizar a posição do robô no labirinto
    maze[y + mazeSize/2][x + mazeSize/2] = '*';

    // Check surroundings
    int frontDistance = ping_cm(8); // Distância à frente

    // Rotate to check the right side
    drive_goto(-26, 26); // Virar para a direita em 150 graus
    int rightDistance = ping_cm(8); // Distância à direita
    drive_ramp(0, 0); // Parar o robô
    pause(100); // Atraso para garantir que o robô tenha parado

    // Rotate to check the left side
    drive_goto(52, -52); // Virar para a esquerda em 300 graus
    int leftDistance = ping_cm(8); // Distância à esquerda
    drive_ramp(0, 0); // Parar o robô
    pause(100); // Atraso para garantir que o robô tenha parado

    // Rotate back to the original orientation
    drive_goto(-26, 26); // Virar para a direita em 150 graus

    // Debug output
    printf("Front distance: %d cm\n", frontDistance);
    printf("Right distance: %d cm\n", rightDistance);
    printf("Left distance: %d cm\n", leftDistance);
    printf("X: %d\n", x);
    printf("Y: %d\n", y);

    // Verificar se o robô chegou ao final do labirinto
    if (frontDistance > 20 && rightDistance > 20 && leftDistance > 20) {
      printf("Labirinto concluído!\n");
      break; // Sair do loop
    }
    // Escolher o melhor caminho com base nas paredes detectadas
    else if (frontDistance > 10) { // Se não houver parede à frente
      // Go straight
      printf("Going straight\n");
      drive_speed(64, 64);
      pause(1000); // Dirigir por 1 segundo
      drive_ramp(0, 0); // Parar o robô
      pause(100); // Atraso para garantir que o robô tenha parado
      y = y + 1;
    } else if (rightDistance > 10) { // Se não houver parede à direita
      // Turn right
      printf("Turning right\n");
      drive_goto(-26, 26); // Virar para a direita em 150 graus
      drive_speed(64, 64);
      pause(1000); // Dirigir por 1 segundo
      drive_ramp(0, 0); // Parar o robô
      pause(100); // Atraso para garantir que o robô tenha parado
      x = x + 1;
    } else if (leftDistance > 10) { // Se não houver parede à esquerda
      // Turn left
      printf("Turning left\n");
      drive_goto(26, -26); // Virar para a esquerda em 150 graus
      drive_speed(64, 64);
      pause(1000); // Dirigir por 1 segundo
      drive_ramp(0, 0); // Parar o robô
      pause(100); // Atraso para garantir que o robô tenha parado
      x = x - 1;
    } else {
      // Dead-end, turn around
      printf("Dead-end, turning around\n");
      drive_goto(52, -52); // Virar 360 graus
      drive_speed(64, 64);
      pause(1000); // Dirigir por 1 segundo
      drive_ramp(0, 0); // Parar
      y = y - 1;
    }
  }

  // Imprimir o mapa do labirinto
  printMaze(maze, mazeSize);

  return 0;
}

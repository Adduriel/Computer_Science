#include <iostream>
#include <stdio.h>


typedef void MoveFunc(int*, int*);
typedef void ActionFunc(int**, int*, int*);


int** genMatrix(int width, int height) {
  int** m = new int*[height];

  int counter = 0;

  for (int** p = m; p < m + height; p++) {
    *p = new int[width];
    for (int* q = *p; q < *p + width; q++) {
      counter++;
      *q = counter;
    }
  }

  return m;
}


void vertical(int* x, int* y) {
  *y += 1;
}


void horizontal(int* x, int* y) {
  *x += 1;
}


void increase(int** base, int* x, int* y) {
  int** row = base + *y;
  int* col = *row + *x;
  int* ptr = col;

  int tmp = *ptr;
  *ptr += 1;
  
  printf("Posicion: {x:%i, y:%i}\tAumentar(%i): %i\n", *x, *y, tmp, *ptr); 
}


void decrease(int** base, int* x, int* y) {
  int** row = base + *y;
  int* col = *row + *x;
  int* ptr = col;

  int tmp = *ptr;
  *ptr -= 1;
  
  printf("Posicion: {x:%i, y:%i}\tDisminuir(%i): %i\n", *x, *y, tmp, *ptr); 
}

int main() {
  
  int width = 5;
  int height = 12;
  int actionSize = 13; 
  int positionX = 0;
  int positionY = 0;

  
  int** matrix = genMatrix(width, height);
  int* movement  = new int[actionSize] { 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0 };
  int* operation = new int[actionSize] { 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 };

  
  MoveFunc* funcMovements[] = { &vertical, &horizontal };
  ActionFunc* funcActions[] = { &increase, &decrease }; 

  
  for (int* mov = movement; mov < movement + actionSize; mov++, operation++) {
    
    MoveFunc** currentMovement = funcMovements + *mov;
    ActionFunc** currentAction = funcActions + *operation;
    
   
    (*currentAction)(matrix, &positionX, &positionY);
    (*currentMovement)(&positionX, &positionY);
  }
}

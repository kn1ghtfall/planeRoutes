#pragma once
#include "utils.h"



FILE *openFile(char *nume, char *x);
int getIslandIndex(Arhipelag *arhip, char *nume);
int isAlreadyCounted(char **cuvinte, int nr, char *nouCuvant);
void pushStackWords(Stack **stack, char *newWord);
char *popStackWords(Stack **stack);
void dijkstraTrafic(int trafic, int source, int destination, Arhipelag *arhip, int **dist, int **prev);
void freeMem(Arhipelag *arhip);
void freeMemSmallGraph(Arhipelag *arhip);
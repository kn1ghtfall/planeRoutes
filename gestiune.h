#pragma once
#include "utils.h"



int middleMan(Arhipelag *arhip, int pozInsula, int nrAvioanePlus, int *avioanePlus);
void backtracking(Arhipelag *arhip, FILE **output,int i, int pozInsula, int nrAvioanePlus, int *avioanePlus);
void gestiune( FILE **f, FILE **output, int n);
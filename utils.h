#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define ARR_LEN 200
//Structura pentru resurse :
typedef struct Resursa
{
    char *nume;
    int cantitate;
} Resursa;
//Structura pentru insula :
typedef struct Island
{
    char *nume;
    int nrResurse;
    Resursa *inventarResurse;
    int nrAvioane;
    int *avioane;
    int tolAvioane;

} Island;

typedef struct
{
    Island *island;
    int **a; // matricea de adiacenta
    int nrIslands, nrEdges;
} Arhipelag;

typedef struct nod
{
    char *word;
    struct nod *next;
} Stack;
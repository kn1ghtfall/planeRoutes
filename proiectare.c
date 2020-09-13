#include "proiectare.h"
#include "functions.h"

Arhipelag *citire(FILE **output, FILE **f) // citire date din fisier
{
    Arhipelag *arhip = NULL;
    int i, j;
    char sir[ARR_LEN];

    arhip = (Arhipelag *)malloc(sizeof(Arhipelag));

    fscanf(*f, "%d", &arhip->nrIslands);

    arhip->island = (Island *)malloc(arhip->nrIslands * sizeof(Island));
    for (i = 0; i < arhip->nrIslands; i++) // alocare date despre insule din fisier
    {
        fscanf(*f, "%s %d", sir, &arhip->island[i].nrResurse);
        // arhip->island[i].nume = malloc(strlen(sir) + 1);
        // strcpislandy(arhip->island[i].nume, sir);
        arhip->island[i].nume = NULL;
        arhip->island[i].nume = strdup(sir);

        arhip->island[i].inventarResurse = malloc(sizeof(Resursa) * arhip->island[i].nrResurse);
        for (j = 0; j < arhip->island[i].nrResurse; j++)
        {
            fscanf(*f, "%s %d", sir, &arhip->island[i].inventarResurse[j].cantitate);
            arhip->island[i].inventarResurse[j].nume = malloc(strlen(sir) + 1);
            strcpy(arhip->island[i].inventarResurse[j].nume, sir);
        }
    }

    arhip->a = (int **)malloc(arhip->nrIslands * sizeof(int *)); // alocare matrice adiacenta

    for (i = 0; i < arhip->nrIslands; i++)
        arhip->a[i] = calloc(arhip->nrIslands, arhip->nrIslands * sizeof(int));

    int row, column, cost;
    fscanf(*f, "%d", &arhip->nrEdges);
    for (i = 0; i < arhip->nrEdges; i++)
    {
        fscanf(*f, "%s", sir);
        row = getIslandIndex(arhip, sir);
        fscanf(*f, " - %s %d", sir, &cost);
        column = getIslandIndex(arhip, sir);
        arhip->a[row][column] = arhip->a[column][row] = cost;
    }
    return arhip;
}
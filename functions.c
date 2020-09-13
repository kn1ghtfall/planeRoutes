#include "functions.h"

FILE *openFile(char *nume, char *x)
{
    FILE *pfile;
    if ((pfile = fopen(nume, x)) == NULL)
    {
        fprintf(stderr, "Deschiderea fisierului a esuat\n");
        exit(1);
    }

    return pfile;
}

int getIslandIndex(Arhipelag *arhip, char *nume)
{

    int i;
    for (i = 0; i < arhip->nrIslands; i++)
        if (!strcmp(arhip->island[i].nume, nume))
            return i;

    return -1;
}

int isAlreadyCounted(char **cuvinte, int nr, char *nouCuvant)
{

    int i;
    for (i = 0; i < nr; i++)
        if (!strcmp(cuvinte[i], nouCuvant))
            return 1;

    return 0;
}

void pushStackWords(Stack **stack, char *newWord)
{

    Stack *newNode = malloc(sizeof(Stack));
    newNode->word = malloc(strlen(newWord) + 1);
    strcpy(newNode->word, newWord);

    newNode->next = *stack;
    (*stack) = newNode;
}

char *popStackWords(Stack **stack)
{

    if (*stack != NULL)
    {
        Stack *destroy = *stack;
        char *aux = malloc(strlen((*stack)->word) + 1);
        strcpy(aux, (*stack)->word);
        (*stack) = (*stack)->next;
        free(destroy);
        return aux;
    }

    return NULL;
}
void dijkstraTrafic(int trafic, int source, int destination, Arhipelag *arhip, int **dist, int **prev)
{

    int *sps = NULL; // nodurile care au fost relaxate
    int u, i, j;

    (*dist) = malloc(sizeof(int) * arhip->nrIslands);
    sps = malloc(sizeof(int) * arhip->nrIslands);
    (*prev) = malloc(sizeof(int) * arhip->nrIslands);

    for (i = 0; i < arhip->nrIslands; i++)
    {
        (*dist)[i] = INT_MAX;
        sps[i] = 0;
        (*prev)[i] = -1;
    }

    (*dist)[source] = 0;

    for (i = 0; i < arhip->nrIslands; i++)
    {
        int min = INT_MAX, min_index;
        for (int k = 0; k < arhip->nrIslands; k++)
            if (sps[k] == 0 && min >= (*dist)[k])
            {
                min = (*dist)[k];
                min_index = k;
            }

        u = min_index;
        sps[u] = 1; // nod relaxat

        for (j = 0; j < arhip->nrIslands; j++)
            if (j != destination && trafic)
            {
                if (sps[j] == 0 && arhip->a[u][j] && (*dist)[u] + arhip->a[u][j] + 15 < (*dist)[j] && (*dist)[u] != INT_MAX)
                {
                    (*dist)[j] = (*dist)[u] + arhip->a[u][j] + 15;
                    (*prev)[j] = u;
                }
            }
            else if (sps[j] == 0 && arhip->a[u][j] && (*dist)[u] + arhip->a[u][j] < (*dist)[j] && (*dist)[u] != INT_MAX)
            {
                (*dist)[j] = (*dist)[u] + arhip->a[u][j];
                (*prev)[j] = u;
            }
    }
}

void freeMem(Arhipelag *arhip)
{
    int i, j;

    for (i = 0; i < arhip->nrIslands; i++)
    {
         free(arhip->island[i].nume);
          for (j = 0; j < arhip->island[i].nrResurse; j++)
         {
             free(arhip->island[i].inventarResurse[j].nume);
         }
        free(arhip->island[i].inventarResurse);
       
            

       
    }
     free(arhip->island);

     for(i=0;i<arhip->nrIslands;i++)
        free(arhip->a[i]);
    
    free(arhip->a);

free(arhip);
}

void freeMemSmallGraph(Arhipelag *arhip){
 int i;

    for (i = 0; i < arhip->nrIslands; i++)
    {
            free(arhip->island[i].avioane);
       
    }

     free(arhip->island);

     for(i=0;i<arhip->nrIslands;i++)
        free(arhip->a[i]);
    
    free(arhip->a);

    free(arhip);

}
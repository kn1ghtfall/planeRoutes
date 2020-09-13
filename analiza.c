#include "analiza.h"
#include "functions.h"

int analiza(Arhipelag *arhip, FILE **f, FILE **output, int *numberGestiune)
{

    int row, column, i,j,cost, gestionare = 0;
    char sir[ARR_LEN], sir2[ARR_LEN], sir3[ARR_LEN];

    while (fscanf(*f, "%s", sir) == 1)
    {

        if (!strcmp(sir, "conexiune"))
        {
            fscanf(*f, "%s %s", sir2, sir3);

            row = getIslandIndex(arhip, sir2);
            column = getIslandIndex(arhip, sir3);
            if (arhip->a[row][column])
                fprintf(*output, "OK\n");
            else
                fprintf(*output, "NO\n");
            continue;
        }

        if (!strcmp(sir, "legatura"))
        {
            fscanf(*f, "%s", sir2);
            row = getIslandIndex(arhip, sir2);
            for (i = 0; i < arhip->nrIslands; i++)
                if (arhip->a[row][i])
                    fprintf(*output, "Island%d ", i + 1);

            fprintf(*output, "\n");
            continue;
        }

        if (!strcmp(sir, "adauga_zbor"))
        {
            arhip->nrEdges++;
            fscanf(*f, "%s %s %d", sir2, sir3, &cost);
            row = getIslandIndex(arhip, sir2);
            column = getIslandIndex(arhip, sir3);
            arhip->a[row][column] = arhip->a[column][row] = cost;

            continue;
        }

        if (!strcmp(sir, "anulare_zbor"))
        {
            fscanf(*f, "%s %s", sir2, sir3);
            row = getIslandIndex(arhip, sir2);
            column = getIslandIndex(arhip, sir3);
            arhip->a[row][column] = arhip->a[column][row] = 0;
            continue;
        }

        if (!strcmp(sir, "max_resurse"))
        {
            int nrResurseArhip = 0;
            char **resurse = NULL;

            for (i = 0; i < arhip->nrIslands; i++)
            {
                if (nrResurseArhip)
                    resurse = realloc(resurse, sizeof(char *) * (nrResurseArhip + arhip->island[i].nrResurse));
                else
                    resurse = (char **)malloc(sizeof(char *) * arhip->island[i].nrResurse);
                for (j = 0; j < arhip->island[i].nrResurse; j++)
                {

                    if (!isAlreadyCounted(resurse, nrResurseArhip, arhip->island[i].inventarResurse[j].nume))
                    {
                        resurse[nrResurseArhip] = malloc(strlen(arhip->island[i].inventarResurse[j].nume) + 1);
                        strcpy(resurse[nrResurseArhip], arhip->island[i].inventarResurse[j].nume);
                        nrResurseArhip++;
                    }
                }
            }
            char aux[ARR_LEN];

            for (i = 0; i < nrResurseArhip - 1; i++)
                for (j = i + 1; j < nrResurseArhip; j++)
                    if (strcmp(resurse[i], resurse[j]) > 0)
                    {
                        strcpy(aux, resurse[j]);
                        resurse[j] = realloc(resurse[j], strlen(resurse[i]) + 1);
                        strcpy(resurse[j], resurse[i]);
                        resurse[i] = realloc(resurse[i], strlen(aux) + 1);
                        strcpy(resurse[i], aux);
                    }

            fprintf(*output, "%d ", nrResurseArhip);
            for (i = 0; i < nrResurseArhip; i++)
                fprintf(*output, "%s ", resurse[i]);
            fprintf(*output, "\n");

            continue;
        }

        if (!strcmp(sir, "max_cantitate"))
        {
            fscanf(*f, "%s", sir2);
            int max = 0;

            for (i = 0; i < arhip->nrIslands; i++)
                for (j = 0; j < arhip->island[i].nrResurse; j++)
                    if (!strcmp(sir2, arhip->island[i].inventarResurse[j].nume))
                        if (max < arhip->island[i].inventarResurse[j].cantitate)
                            max = arhip->island[i].inventarResurse[j].cantitate;

            for (i = 0; i < arhip->nrIslands; i++)
                for (j = 0; j < arhip->island[i].nrResurse; j++)
                    if (!strcmp(sir2, arhip->island[i].inventarResurse[j].nume))
                        if (max == arhip->island[i].inventarResurse[j].cantitate)
                            fprintf(*output, "%s ", arhip->island[i].nume);

            fprintf(*output, "\n");
            continue;
        }

        if (!strcmp(sir, "drum_zbor"))
        {

            int source, destination;
            int trafic = 0;
            int *prev = NULL, *dist = NULL;
            fscanf(*f, "%s %s", sir2, sir3);
            source = getIslandIndex(arhip, sir2);
            destination = getIslandIndex(arhip, sir3);

            dijkstraTrafic(trafic, source, destination, arhip, &dist, &prev);

            if (prev[destination] == -1)
            {
                fprintf(*output, "NO\n");
                continue;
            }

            Stack *stack = NULL;
            while (prev[destination] != -1)
            {
                pushStackWords(&stack, arhip->island[destination].nume);
                destination = prev[destination];
            }
            char *word = popStackWords(&stack);

            while (word)
            {

                fprintf(*output, "%s ", word);
                word = popStackWords(&stack);
            }

            fprintf(*output, "\n");
            continue;
        }

        if (!strcmp(sir, "timp_zbor"))
        {
            fscanf(*f, "%s %s", sir2, sir3);
            int source, destination;
            int trafic = 0;
            int *dist = NULL, *prev = NULL;

            source = getIslandIndex(arhip, sir2);
            destination = getIslandIndex(arhip, sir3);

            dijkstraTrafic(trafic, source, destination, arhip, &dist, &prev);

            if (dist[destination] == INT_MAX)
                fprintf(*output, "INF\n");
            else
                fprintf(*output, "%d\n", dist[destination]);
            continue;
        }

        if (!strcmp(sir, "min_zbor"))
        {
            fscanf(*f, "%s %s", sir2, sir3);
            int source, destination;
            int *dist = NULL, *prev = NULL;
            int trafic = 1;

            source = getIslandIndex(arhip, sir2);
            destination = getIslandIndex(arhip, sir3);

            dijkstraTrafic(trafic, source, destination, arhip, &dist, &prev);

            if (dist[destination] == INT_MAX)
                fprintf(*output, "INF\n");
            else
                fprintf(*output, "%d\n", dist[destination]);
            continue;
        }

        gestionare = 1;
        (*numberGestiune) = atoi(sir);
        break; // daca nu se executa nici o instructiune din cele de mai sus inseamna ca suntem la faza 3.Gestionare
    }

    return gestionare;
}
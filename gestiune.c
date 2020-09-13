#include "gestiune.h"
#include "functions.h"

int middleMan(Arhipelag *arhip, int pozInsula, int nrAvioanePlus, int *avioanePlus)
{

    int i, j, k, p;

    for (i = 0; i < arhip->nrIslands; i++)
    {
        if (arhip->a[pozInsula][i])
        {
            for (j = 0; j < arhip->nrIslands; j++)
                if (arhip->a[i][j] && arhip->island[j].tolAvioane - arhip->island[j].nrAvioane >= nrAvioanePlus)
                {
                    int index = arhip->island[j].nrAvioane;
                    arhip->island[j].nrAvioane += nrAvioanePlus;
                    arhip->island[j].avioane = realloc(arhip->island[j].avioane, arhip->island[j].nrAvioane);

                    // i este insula ce joaca rol de 'middle man' aceasta primeste surplusul de avioane si da ultimele sale avioane insulei care are locuri disponibile dar nu are legatura la insula cu surplus decat prin 'middle man'
                    // j este insula care are locurile disponibile si face legatura cu insula cu surplus prin insula i
                    for (k = 0; k < nrAvioanePlus; k++)
                    {
                        arhip->island[j].avioane[index + k] = arhip->island[i].avioane[arhip->island[i].nrAvioane - nrAvioanePlus + k];
                        arhip->island[i].avioane[arhip->island[i].nrAvioane - nrAvioanePlus + k] = avioanePlus[k];
                    }
                    int aux;

                    // aranjarea in ordine crescatoare a id urilor avioanelor mutate
                    for (k = 0; k < arhip->island[j].nrAvioane - 1; k++)
                        for (p = k + 1; p < arhip->island[j].nrAvioane; p++)
                            if (arhip->island[j].avioane[k] > arhip->island[j].avioane[p])
                            {
                                aux = arhip->island[j].avioane[k];
                                arhip->island[j].avioane[k] = arhip->island[j].avioane[p];
                                arhip->island[j].avioane[p] = aux;
                            }

                    for (k = 0; k < arhip->island[i].nrAvioane - 1; k++)
                        for (p = k + 1; p < arhip->island[i].nrAvioane; p++)
                            if (arhip->island[i].avioane[k] > arhip->island[i].avioane[p])
                            {
                                aux = arhip->island[i].avioane[k];
                                arhip->island[i].avioane[k] = arhip->island[i].avioane[p];
                                arhip->island[i].avioane[p] = aux;
                            }

                    return 1;
                }
        }
    }
    return 0;
}

void backtracking(Arhipelag *arhip, FILE **output, int i, int pozInsula, int nrAvioanePlus, int *avioanePlus)
{
    int p, k, contor, j;

    fprintf(*output, "Island%d\n", i + 1);
    // creare permutari solutii
    int suma = 0;
    int solPosileLocal = arhip->island[i].tolAvioane - arhip->island[i].nrAvioane;
    for (p = 0; p < nrAvioanePlus; p++) // p = cate avioane sunt scoase tura asta ;se repeta de  cate avioane in plus sunt
    {

        for (j = 0; j < p + 1; j++) // cate 2 , cate 3 cate 4
        {
            int *solutie = malloc(sizeof(int) * (nrAvioanePlus - p));
            for (k = 0; k < nrAvioanePlus - p; k++) // parcurge solutia
            {
                solutie[k] = avioanePlus[p - j + k];
            }

            //pentru avioanele date
            int good;
            //testare solutii
            for (contor = 0; contor < arhip->nrIslands; contor++)
                if (contor != i && arhip->a[pozInsula][contor] == 1 && arhip->island[contor].nrAvioane < arhip->island[contor].tolAvioane)
                {

                    good = 0;
                    suma = 0;
                    suma += arhip->island[contor].tolAvioane - arhip->island[contor].nrAvioane;

                    if (suma >= j)
                        good++;
                    suma = 0;
                    for (k = 0; k < arhip->nrIslands; k++)
                        if (j == 0)
                        {

                            if (k != contor && contor != i && arhip->a[pozInsula][k] == 1 && arhip->island[k].nrAvioane < arhip->island[k].tolAvioane)
                                suma += arhip->island[k].tolAvioane - arhip->island[k].nrAvioane;
                        }
                        else
                        {
                            if (k != i && k != contor && contor != i && arhip->a[pozInsula][k] == 1 && arhip->island[k].nrAvioane < arhip->island[k].tolAvioane)
                                suma += arhip->island[k].tolAvioane - arhip->island[k].nrAvioane;
                        }

                    if (suma >= p - j)
                        good++;

                    if (nrAvioanePlus - p <= solPosileLocal)
                        good++;

                    if (good == 3)
                    {
                        for (k = 0; k < arhip->island[i].nrAvioane; k++)
                            fprintf(*output, "%d ", arhip->island[i].avioane[k]);
                        for (k = 0; k < nrAvioanePlus - p; k++)
                            fprintf(*output, "%d ", solutie[k]);

                        fprintf(*output, "\n");
                        break; // am gasit solutia din tura asta
                    }
                }

            free(solutie);
        }
    }
    suma = 0;
    for (contor = 0; contor < arhip->nrIslands; contor++)
        if (contor != i && arhip->a[pozInsula][contor] == 1 && arhip->island[contor].nrAvioane < arhip->island[contor].tolAvioane)
            suma += arhip->island[contor].tolAvioane - arhip->island[contor].nrAvioane;

    if (suma >= nrAvioanePlus)
    {
        for (k = 0; k < arhip->island[i].nrAvioane; k++)
            fprintf(*output, "%d ", arhip->island[i].avioane[k]);

        fprintf(*output, "\n");
    }
}

void gestiune( FILE **f, FILE **output, int n)
{
    // preluare date fisier
    int i, j;
    int t; // toleranta

    Arhipelag *arhip = NULL;
    arhip = malloc(sizeof(Arhipelag));
    arhip->island = malloc(sizeof(Island) * n);
    arhip->nrIslands = n;

    fscanf(*f, "%d", &t);
    for (i = 0; i < n; i++)
    {
        fscanf(*f, "%d", &arhip->island[i].nrAvioane);

        arhip->island[i].tolAvioane = t;
    }

    for (i = 0; i < n; i++)
    {
        arhip->island[i].avioane = malloc(sizeof(int) * arhip->island[i].nrAvioane);
        for (j = 0; j < arhip->island[i].nrAvioane; j++)
            fscanf(*f, "%d", &arhip->island[i].avioane[j]);
    }

    arhip->a = malloc(sizeof(int *) * n);

    for (i = 0; i < n; i++)
    {
        arhip->a[i] = malloc( sizeof(int) * n);

        for (j = 0; j < n; j++)
        {

            fscanf(*f, "%d", &arhip->a[i][j]);
        }
    }

    //testare in caz ne aflam din cele descrise in cerinta
    arhip->nrIslands = n;

    int k;

    int pozInsula = -1; // nu se va schimba daca nu e nevoie de vreo schimbare in arhipelag pentru a echilibra distributia avioanelor
    int ok = 0;
    int cazVecini = 0;

    int nrAvioanePlus;
    int *avioanePlus = NULL;

    // testare daca suntem in cazul in care o insula cu un surplus de avioane poate sa le dea insulelor vecine
    for (i = 0; i < n; i++)
        if (arhip->island[i].nrAvioane > arhip->island[i].tolAvioane)
        {
            pozInsula = i;
            nrAvioanePlus = arhip->island[i].nrAvioane - arhip->island[i].tolAvioane;
            int locuriLibere = 0;
            for (j = 0; j < n; j++)
                if (arhip->a[i][j] == 1 && arhip->island[j].nrAvioane < arhip->island[j].tolAvioane)
                    locuriLibere += arhip->island[j].tolAvioane - arhip->island[j].nrAvioane;

            if (locuriLibere >= nrAvioanePlus)
                cazVecini = 1;

            avioanePlus = malloc(sizeof(int) * nrAvioanePlus);
            for (j = 0; j < nrAvioanePlus; j++)
                avioanePlus[j] = arhip->island[i].avioane[j + arhip->island[i].tolAvioane];
        }

    //cazul in care exista surplus de avioane dar vecinii nu au locuri libere, insa au legaturi ce pot sa primeasca avioanele
    if (cazVecini == 0 && pozInsula != -1)
        ok = middleMan(arhip, pozInsula, nrAvioanePlus, avioanePlus);

    if (cazVecini || ok)
    {
        arhip->island[pozInsula].nrAvioane = arhip->island[pozInsula].tolAvioane;
        for (i = 0; i < n; i++) // indexul insulei care ar da avioane
            if (arhip->a[pozInsula][i] == 0 || arhip->island[i].nrAvioane >= arhip->island[i].tolAvioane)
            {
                //afisare insula fara permutari
                fprintf(*output, "Island%d\n", i + 1);
                for (j = 0; j < arhip->island[i].nrAvioane; j++)
                    fprintf(*output, "%d ", arhip->island[i].avioane[j]);
                fprintf(*output, "\n");
            }
            else
                backtracking(arhip, output, i, pozInsula, nrAvioanePlus, avioanePlus);
    }
    else if (pozInsula != -1) // caz cand nu sunt destule locuri unde sa ducem avioanele
        fprintf(*output, "Stack overflow!\n");
    else
    {
        // afisare caz in care nu trebuie sa schimam nimic la arhipleag
        for (i = 0; i < arhip->nrIslands; i++)
        {
            fprintf(*output, "Island%d\n", i + 1);
            for (k = 0; k < arhip->island[i].nrAvioane; k++)
                fprintf(*output, "%d ", arhip->island[i].avioane[k]);
            fprintf(*output, "\n");
        }
    }
    free(avioanePlus);
    freeMemSmallGraph(arhip);
}

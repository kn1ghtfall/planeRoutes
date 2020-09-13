#include "utils.h"
#include "functions.h"
#include "proiectare.h"
#include "analiza.h"
#include "gestiune.h"



int main(int argc, char *argv[])
{

    Arhipelag *arhip = NULL;
    int n;

    FILE *f = openFile(argv[1], "r");
    FILE *output = openFile(argv[2], "w");

    arhip = citire(&output, &f);

    int doGestiune = analiza(arhip, &f, &output, &n);

    if(doGestiune)
            gestiune(&f, &output,n);

    freeMem(arhip);
    fclose(f);
    fclose(output);

    return 0;
}
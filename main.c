#include "structs.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *op;
    op = fopen("tema1.txt", "r");
    int countTAB = 0, nr, id;
    page *INPage;
    char aux[256], URL[50], *description;
    fgets(aux, sizeof(nr), op);
    nr = atoi(aux);
    INPage = (page *)malloc(nr * sizeof(page));
    while (nr) {
        fgets(aux, sizeof(aux), op);
        id = atoi(aux);
        fgets(aux, sizeof(aux), op);
        strcpy(URL, aux);
        fgets(aux, sizeof(aux), op);
        description = aux;
        strcpy(INPage->description, description);
        INPage->id = id;  //  pastrez detaliile site-ului
        strcpy(INPage->url, URL);
        nr--;
    }
    return 0;
}
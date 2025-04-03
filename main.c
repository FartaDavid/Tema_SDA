#include "structs.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char aux[256], operations[256][256];
    FILE *op = fopen("tema1.txt", "r");
    fgets(aux, sizeof(aux), op);
    int nrpages = atoi(aux);
    page Pages[nrpages];
    for (int i = 0; i < nrpages; i++) {
        fgets(aux, sizeof(aux), op);
        Pages[i].id = atoi(aux);

        fgets(aux, sizeof(aux), op);
        aux[strlen(aux) - 1] = '\0';
        strcpy(Pages[i].url, aux);

        fgets(aux, sizeof(aux), op);
        aux[strlen(aux) - 1] = '\0';
        Pages[i].description = (char *)malloc(strlen(aux) * (sizeof(char)));
        strcpy(Pages[i].description, aux);
    }
    fgets(aux, sizeof(aux), op);
    int nrop = atoi(aux);
    for (int i = 0; i < nrop; i++) {
        fgets(operations[i], sizeof(operations[i]), op);
        operations[i][strlen(operations[i]) - 1] = '\0';
    }
    for (int i = 0; i < nrop; i++) {
        if (!strcmp(operations[i], "NEW_TAB"))
            NEW_TAB;
    }
    return 0;
}

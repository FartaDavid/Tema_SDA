#include "structs.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char aux[256], operations[256][256];
    FILE *op = fopen("tema4.txt", "r");
    fgets(aux, sizeof(aux), op);
    int nrpages = atoi(aux);
    page Pages[nrpages];
    //  Citesc paginile
    for (int i = 0; i < nrpages; i++) {
        //  Pastrez id-ul
        fgets(aux, sizeof(aux), op);
        Pages[i].id = atoi(aux);

        //  Pastrez url-ul
        fgets(aux, sizeof(aux), op);
        aux[strlen(aux) - 1] = '\0';
        strcpy(Pages[i].url, aux);

        //  Pastrez descrierea
        fgets(aux, sizeof(aux), op);
        aux[strlen(aux) - 1] = '\0';
        Pages[i].description = (char *)malloc((strlen(aux) + 1) * sizeof(char));
        strcpy(Pages[i].description, aux);
    }
    fgets(aux, sizeof(aux), op);
    int nrop = atoi(aux);
    //  Pastrez operatiile ce trb facute intr-un vector de string-uri
    for (int i = 0; i < nrop; i++) {
        fgets(operations[i], sizeof(operations[i]), op);
        operations[i][strlen(operations[i]) - 1] = '\0';
    }
    //  Incep sa initializez/aloc dinamic browserul si santinela
    int k = 0, nr;
    browser *BRW = NULL, *SANTINEL = NULL;
    SANTINEL = (browser *)malloc(sizeof(browser));
    SANTINEL->list = (tabList *)malloc(sizeof(tabList));
    SANTINEL->list->next = (tabList *)malloc(sizeof(tabList));
    SANTINEL->list->prev = (tabList *)malloc(sizeof(tabList));
    //  Incep operatiile
    for (int i = 0; i < nrop; i++) {
        //  Fac un Tab nou
        if (!strcmp(operations[i], "NEW_TAB")) {
            if (k == 0)
                BRW = HEAD(BRW, SANTINEL);
            else
                BRW = NEW_TAB(BRW, SANTINEL, k);
            k++;
        }
        if (!strcmp(operations[i], "CLOSE")) {
            if (k == 0)
                printf("403 Forbidden\n");
            else {
                BRW->list = CLOSE(BRW->list, SANTINEL);
                k--;
            }
        }
        if (strstr(operations[i], "OPEN")) {
            CutNr(operations[i], &nr);
            if (nr > k)
                printf("403 Forbidden\n");
            else
                BRW = OPEN(BRW, nr, SANTINEL);
        }
    }
    return 0;
}

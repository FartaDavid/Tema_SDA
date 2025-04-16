#include "structs.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char aux[256], operations[256][256];
    FILE *op = fopen("tema1.in", "r"), *of = fopen("tema1.out", "w");
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
        if (operations[i][strlen(operations[i]) - 1] == '\n')
            operations[i][strlen(operations[i]) - 1] = '\0';
    }
    //  Incep sa initializez/aloc dinamic browserul si santinela
    int k = 0, nr, nr_tabs = 1;
    browser *BRW = NULL, *SANTINEL = NULL;
    SANTINEL = ALOCARE(SANTINEL);
    SANTINEL->current->id = -1;
    //  Incep operatiile
    BRW = ALOCARE(BRW);
    BRW = HEAD (BRW, SANTINEL);
    for (int i = 0; i < nrop; i++) {
        //  Fac un Tab nou  
        if (!strcmp(operations[i], "NEW_TAB")) {
            BRW = NEW_TAB(BRW, SANTINEL, nr_tabs);
            nr_tabs++;
            k++;
        }
        if (!strcmp(operations[i], "CLOSE")) {
            k--;
            // if (k < 0)
            //     k = 0;
            if (k == 0) {
                fprintf(of, "403 Forbidden\n");
            }
            else {
                BRW->list = CLOSE(BRW->list, SANTINEL);
                BRW->current = BRW->list->currentTab;
            }
        }
        if (strstr(operations[i], "OPEN")) {
            CutNr(operations[i], &nr);
            if (nr > k || nr_tabs == 1)
                fprintf(of, "403 Forbidden\n");
            else {
                // printf("%d %d\n", nr, k);
                BRW = OPEN(BRW, nr);
            }
        }
        if (!strcmp(operations[i], "PREV")) {
            BRW = PREV(BRW, SANTINEL);
        }
        if (!strcmp(operations[i], "NEXT")) {
            BRW = NEXT(BRW, SANTINEL);
        }
        if (strstr(operations[i], "PAGE")) {
            CutNr(operations[i], &nr);
            BRW->current->backwardStack = PAGE(BRW, Pages, nrpages, nr);
            // printf("%s\n", BRW->current->backwardStack->Page->description);
        }
        if (!strcmp(operations[i], "BACKWARD")) {
            BRW->current->forwardStack = BACKWARD(BRW, of);
            // printf("\nBackward: %s\n", BRW->current->backwardStack->Page->description);
        }
        if (!strcmp(operations[i], "FORWARD")) {
            BRW->current->backwardStack = FORWARD(BRW, of);
        }
        if (!strcmp(operations[i], "PRINT")) {
            // printf("%d\n", BRW->current->id);
            PRINT(*BRW, of);
        }
        if (strstr(operations[i], "PRINT_HISTORY")) {
            CutNr(operations[i], &nr);
            PRINT_HISTORY(*BRW, nr, k, of);
        }
        // printf("%d %d %s\n", k, BRW->current->id, operations[i]);
        // printf("%s\n%s\n\n", BRW->current->backwardStack->Page->url, operations[i]);
    }
    // Dau free la memorie
    // FREE(BRW);
    // printf("%s\n", BRW->current->backwardStack->Top->Page->url);

    // printf("\n%s\n", BRW->current->backwardStack->Page->url);
    // printf("\n%s\n", BRW->current->backwardStack->Page->description);
    return 0;
}

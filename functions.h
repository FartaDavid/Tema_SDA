#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

browser *ALOCARE(browser *BRW) {
    BRW = (browser *)malloc(sizeof(browser));
    BRW->current = (tab *)malloc(sizeof(tab));
    BRW->current->backwardStack = NULL;
    BRW->current->forwardStack = NULL;
    BRW->current->currentPage = (page *)malloc(sizeof(page));
    BRW->current->currentPage->description = (char *)malloc(desclen * sizeof(char));
    BRW->list = (tabList *)malloc(sizeof(tabList));
    BRW->list->next = NULL;
    BRW->list->prev = NULL;
    BRW->list->currentTab = BRW->current; // Link the current tab
    return BRW;
}

browser *HEAD (browser *BRW, browser *SANTINEL) {
    BRW->list->next = SANTINEL->list;
    BRW->list->prev = SANTINEL->list;
    SANTINEL->list->next = BRW->list;
    SANTINEL->list->prev = BRW->list;

    BRW->current->id = 0;

    BRW->current->currentPage->id = 0;
    strcpy(BRW->current->currentPage->url, "https://acs.pub.ro");
    strcpy(BRW->current->currentPage->description, "Computer Science");
    return BRW;
}

browser *NEW_TAB (browser *BRW, browser *SANTINEL, int k) {
    //  Aloc un browser
    browser *NEWBRW = ALOCARE(NEWBRW);

    //  Fac lista dublu inlantuita cu santinela
    NEWBRW->list->next = SANTINEL->list;
    NEWBRW->list->prev = BRW->list;
    SANTINEL->list->prev = NEWBRW->list;
    BRW->list->next = NEWBRW->list;

    //  Pun id-ul tab-ului, URL-ul, id-ul si descrierea default
    NEWBRW->current->id = k;
    NEWBRW->current->currentPage->id = 0;
    strcpy(NEWBRW->current->currentPage->url, "https://acs.pub.ro");
    strcpy(NEWBRW->current->currentPage->description, "Computer Science");
    NEWBRW->list->currentTab = NEWBRW->current;
    return NEWBRW;
}

tabList *CLOSE (tabList *LIST, browser *SANTINEL) {
    LIST = LIST->prev;
    free(LIST->next);
    LIST->next = SANTINEL->list->prev;
    SANTINEL->list->prev = LIST;
    return LIST;
}

void CutNr (char operation[], int *nr) {
    int i;
    for (i = 0; i < strlen(operation); i++)
        if (operation[i] == ' ')
            break;
    operation = operation + i;
    *nr = atoi(operation);
}

browser *OPEN (browser *BRW, int nr, browser *SANTINEL) {
    if (nr < BRW->list->currentTab->id) {
        while (nr != BRW->list->currentTab->id) {
            BRW->list = BRW->list->prev;
            BRW->current = BRW->list->currentTab;
        }
    }
    else {
        while (nr != BRW->list->currentTab->id) {
            BRW->list = BRW->list->next;
            BRW->current = BRW->list->currentTab;
        }
    }
    return BRW;
}

browser *PREV (browser *BRW, browser *SANTINEL) {
    if (BRW->list->prev->currentTab->id != -1) {
        BRW->list = BRW->list->prev;
        BRW->current = BRW->list->currentTab;
    }
    else {
        BRW->list = SANTINEL->list->prev;
        BRW->current = BRW->list->currentTab;
    }
    return BRW;
}

browser *NEXT (browser *BRW, browser *SANTINEL) {
    if (BRW->list->next->currentTab->id != -1) {
        BRW->list = BRW->list->next;
        BRW->current = BRW->list->currentTab;
    }
    else {
        BRW->list = SANTINEL->list->next;
        BRW->current = BRW->list->currentTab;
    }
    return BRW;
}

browser *PAGE (browser *BRW, page Pages[], int nrpages, int ID) {
    int ok = 0, i;
    for (i = 0; i < nrpages; i++) {
        if (Pages[i].id == ID) {
            ok = 1;
        }
    }
    if (ok) {
        // BRW->current->backwardStack->Page = (page *)malloc(sizeof(page));
        // BRW->current->backwardStack->Page->description = (char *)malloc(strlen(Pages[i].description) * sizeof(char));
        // BRW->current->backwardStack->Top = (stack *)malloc(sizeof(stack));
        printf("da\n");
    }
    else
        printf("403 Forbidden\n");
}

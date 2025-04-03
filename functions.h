#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

browser *HEAD(browser *BRW, browser *SANTINEL) {
    BRW = (browser *)malloc(sizeof(browser));
    BRW->current = (tab *)malloc(sizeof(tab));
    BRW->current->backwardStack = (stack *)malloc(sizeof(stack));
    BRW->current->forwardStack = (stack *)malloc(sizeof(stack));
    BRW->current->backwardStack = NULL;
    BRW->current->forwardStack = NULL;
    BRW->list = (tabList *)malloc(sizeof(tabList));
    BRW->list->next = (tabList *)malloc(sizeof(tabList));
    BRW->list->prev = (tabList *)malloc(sizeof(tabList));
    BRW->list->next = SANTINEL->list;
    SANTINEL->list->prev = BRW->list;
    BRW->current->id = 0;
    BRW->current->currentPage = (page *)malloc(sizeof(page));
    BRW->current->currentPage->id = 0;
    strcpy(BRW->current->currentPage->url, "https://acs.pub.ro");
    BRW->current->currentPage->description = (char *)malloc(desclen * sizeof(char));
    strcpy(BRW->current->currentPage->description, "Computer Science");
    return BRW;
}

browser *NEW_TAB (browser *BRW, browser *SANTINEL, int k) {
    //  Aloc un browser
    browser *NEWBRW = (browser *)malloc(sizeof(browser));
    //  Aloc tab-ul

    NEWBRW->current = (tab *)malloc(sizeof(tab));
    //  Aloc stiva si o fac NULL
    NEWBRW->current->backwardStack = (stack *)malloc(sizeof(stack));
    NEWBRW->current->forwardStack = (stack *)malloc(sizeof(stack));
    NEWBRW->current->backwardStack = NULL;
    NEWBRW->current->forwardStack = NULL;
    //  Fac lista dublu inlantuita cu santinela
    NEWBRW->list = (tabList *)malloc(sizeof(tabList));
    NEWBRW->list->next = (tabList *)malloc(sizeof(tabList));
    NEWBRW->list->prev = (tabList *)malloc(sizeof(tabList));
    NEWBRW->list->next = SANTINEL->list->prev;
    SANTINEL->list->prev = NEWBRW->list;
    NEWBRW->list->prev = BRW->list;
    BRW->list->next = NEWBRW->list;
    //  Pun id-ul tab-ului, URL-ul, id-ul si descrierea default
    NEWBRW->current->id = k;
    NEWBRW->current->currentPage = (page *)malloc(sizeof(page));
    NEWBRW->current->currentPage->id = 0;
    strcpy(NEWBRW->current->currentPage->url, "https://acs.pub.ro");
    NEWBRW->current->currentPage->description = (char *)malloc(desclen * sizeof(char));
    strcpy(NEWBRW->current->currentPage->description, "Computer Science");
    return NEWBRW;
}

tabList *CLOSE(tabList *LIST, browser *SANTINEL) {
    LIST = LIST->prev;
    free(LIST->next);
    LIST->next = SANTINEL->list->prev;
    SANTINEL->list->prev = LIST;
    return LIST;
}

void CutNr(char operation[], int *nr) {
    char *p = strstr(operation, "OPEN");
    p = p + 5;
    *nr = atoi(p);
}

browser *OPEN(browser *BRW, int nr, browser *SANTINEL) {
    tabList *CURRENT = BRW->list;
    while(BRW->list->next != SANTINEL->list && BRW->current->id != nr) {
        BRW->list = BRW->list->next;
        printf("%d\n", BRW->current->id);
    }
    if (BRW->current->id != nr)
        while(BRW->list->next != CURRENT && BRW->current->id != nr)
            BRW->list = BRW->list->next;
    return BRW;
}
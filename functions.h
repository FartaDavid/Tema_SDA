#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

browser *ALOCARE(browser *BRW) {
    BRW = (browser *)malloc(sizeof(browser));
    BRW->current = (tab *)malloc(sizeof(tab));
    BRW->current->currentPage = (page *)malloc(sizeof(page));
    BRW->current->currentPage->description = (char *)malloc(desclen * sizeof(char));
    BRW->current->backwardStack = (stack *)malloc(sizeof(stack));
    BRW->current->forwardStack = (stack *)malloc(sizeof(stack));
    BRW->current->backwardStack = NULL;
    BRW->current->forwardStack = NULL;
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

stack *PAGE (browser *BRW, page Pages[], int nrpages, int ID) {
    stack *newstack = (stack *)malloc(sizeof(stack));
    newstack->Page = BRW->current->currentPage;
    int ok = 0, i;
    for (i = 0; i < nrpages; i++) {
        if (Pages[i].id == ID) {
            ok = 1;
            break;
        }
    }
    if (ok) {
        if (BRW->current->backwardStack == NULL) {
            BRW->current->backwardStack = newstack;
            BRW->current->backwardStack->Bottom = NULL;
            BRW->current->backwardStack->Top = NULL;
        }
        else {
            BRW->current->backwardStack->Top = newstack;
            newstack->Bottom = BRW->current->backwardStack;
            newstack->Top = NULL;
        }
        BRW->current->currentPage = &Pages[i];
        return newstack;
    }
    else
        printf("403 Forbidden\n");
}

stack *BACKWARD (browser *BRW) {
    if (BRW->current->backwardStack != NULL) {
        stack *newstack = (stack *)malloc(sizeof(stack));
        newstack->Page = BRW->current->currentPage;
        if (BRW->current->forwardStack == NULL) {
            BRW->current->forwardStack = newstack;
            BRW->current->forwardStack->Bottom = NULL;
            BRW->current->forwardStack->Top = NULL;
        }
        else {
            BRW->current->forwardStack->Top = newstack;
            newstack->Bottom = BRW->current->forwardStack;
            newstack->Top = NULL;
        }
        BRW->current->currentPage = BRW->current->backwardStack->Page;
        BRW->current->backwardStack = BRW->current->backwardStack->Bottom;
        return newstack;
    }
    else {
        printf("403 Forbidden\n");
    }
}

stack *FORWARD (browser *BRW) {
    // printf("%s\n", BRW->current->forwardStack->Page->url);
    if (BRW->current->forwardStack != NULL) {
        stack *newstack = (stack *)malloc(sizeof(stack));
        newstack->Page = BRW->current->currentPage;
        if (BRW->current->backwardStack == NULL) {
            BRW->current->backwardStack = newstack;
            BRW->current->backwardStack->Bottom = NULL;
            BRW->current->backwardStack->Top = NULL;
        }
        else {
            BRW->current->backwardStack->Top = newstack;
            newstack->Bottom = BRW->current->backwardStack;
            newstack->Top = NULL;
        }
        BRW->current->currentPage = BRW->current->forwardStack->Page;
        BRW->current->forwardStack = BRW->current->forwardStack->Bottom;
        return newstack;
    } else {
        printf("403 ForbiddenLOL\n");
    }
}

void PRINT(browser BRW) {
    int id = BRW.current->id;
    printf("%d ", id);
    BRW.list = BRW.list->next;
    BRW.current = BRW.list->currentTab;
    while (BRW.current->id != id) {
        if (BRW.current->id != -1)
            printf("%d ", BRW.current->id);
        BRW.list = BRW.list->next;
        BRW.current = BRW.list->currentTab;
    }
    printf("\n%s\n", BRW.current->currentPage->description);
}

void PRINT_HISTORY(browser BRW, int nr, int k) {
    int ok, i = 0;
    while (BRW.current->id != nr) {
        BRW.list = BRW.list->next;
        BRW.current = BRW.list->currentTab;
        i++;
        if (i > k)
            break;
    }
    if (nr == BRW.current->id) {
        if (BRW.current->forwardStack != NULL) {
            while (BRW.current->forwardStack->Bottom != NULL) {
                BRW.current->forwardStack = BRW.current->forwardStack->Bottom;
            }
            while (BRW.current->forwardStack->Top != NULL) {
                printf("forward %s\n", BRW.current->forwardStack->Page->url);
                BRW.current->forwardStack = BRW.current->forwardStack->Top;
            }
            printf("%s\n", BRW.current->forwardStack->Page->url);
        }
        printf("%s\n", BRW.current->currentPage->url);
        if (BRW.current->backwardStack != NULL) {
            while (BRW.current->backwardStack != NULL) {
                printf("%s\n", BRW.current->backwardStack->Page->url);
                BRW.current->backwardStack = BRW.current->backwardStack->Bottom;
            }
        }
    }
    else
        printf("403 Forbidden\n");
}

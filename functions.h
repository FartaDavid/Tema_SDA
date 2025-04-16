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
    strcpy(BRW->current->currentPage->url, "https://acs.pub.ro/");
    strcpy(BRW->current->currentPage->description, "Computer Science");
    return BRW;
}

browser *NEW_TAB (browser *BRW, browser *SANTINEL, int k) {
    //  Aloc un browser
    browser *NEWBRW = ALOCARE(NULL);
    tabList *temp = SANTINEL->list->prev;

    //  Fac lista dublu inlantuita cu santinela
    NEWBRW->list->next = SANTINEL->list;
    // NEWBRW->list->prev = BRW->list;
    NEWBRW->list->prev = temp;
    temp->next = NEWBRW->list;
    SANTINEL->list->prev = NEWBRW->list;
    // BRW->list->next = NEWBRW->list;

    //  Pun id-ul tab-ului, URL-ul, id-ul si descrierea default
    NEWBRW->current->id = k;
    NEWBRW->current->currentPage->id = 0;
    strcpy(NEWBRW->current->currentPage->url, "https://acs.pub.ro/");
    strcpy(NEWBRW->current->currentPage->description, "Computer Science");
    NEWBRW->list->currentTab = NEWBRW->current;
    return NEWBRW;
}

tabList *CLOSE (tabList *LIST, browser *SANTINEL) {
    tabList *temp = LIST;
    LIST = LIST->prev;
    if (temp->next->currentTab->id == -1) {
        LIST->next = SANTINEL->list;
        SANTINEL->list->prev = LIST;
    }
    else {
        LIST->next = temp->next;
        temp->next->prev = LIST;
    }
    free(temp);
    return LIST;
}

void CutNr (char operation[], int *nr) {
    int i;
    for (i = 0; i < (int)strlen(operation); i++)
        if (operation[i] == ' ')
            break;
    operation = operation + i;
    *nr = atoi(operation);
}

browser *OPEN (browser *BRW, int nr) {
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
    int ok = 0, i;
    stack *newstack = (stack *)malloc(sizeof(stack));
    newstack->Page = BRW->current->currentPage;
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
    else {
        printf("403 Forbidden\n");
        return BRW->current->backwardStack;
    }
}

stack *BACKWARD (browser *BRW, FILE *of) {
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
            BRW->current->forwardStack = newstack;
        }
        stack *temp = BRW->current->backwardStack;
        BRW->current->currentPage = BRW->current->backwardStack->Page;
        BRW->current->backwardStack = BRW->current->backwardStack->Bottom;
        free(temp);
        if (BRW->current->backwardStack)
            BRW->current->backwardStack->Top = NULL;
        return newstack;
    }
    else {
        fprintf(of, "403 Forbidden\n");
        return BRW->current->forwardStack;
    }
}

stack *FORWARD (browser *BRW,FILE *of) {
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
            BRW->current->backwardStack = newstack;
        }
        stack *temp = BRW->current->forwardStack;
        BRW->current->currentPage = BRW->current->forwardStack->Page;
        BRW->current->forwardStack = BRW->current->forwardStack->Bottom;
        free(temp);
        if (BRW->current->forwardStack)
            BRW->current->forwardStack->Top = NULL;
        return newstack;
    } else {
        fprintf(of, "403 Forbidden\n");
        return BRW->current->backwardStack;
    }
}

void PRINT(browser BRW, FILE *of) {
    int id = BRW.current->id;
    fprintf(of, "%d", id);
    BRW.list = BRW.list->next;
    BRW.current = BRW.list->currentTab;
    while (BRW.current->id != id) {
        if (BRW.current->id != -1)
            fprintf(of, " %d", BRW.current->id);
        BRW.list = BRW.list->next;
        BRW.current = BRW.list->currentTab;
    }
    fprintf(of, "\n%s\n", BRW.current->currentPage->description);
}

void PRINT_HISTORY(browser NEWBRW, int nr, int k, FILE *of) {
    browser BRW = NEWBRW;
    int i = 0;
    while (BRW.current->id != nr) {
        BRW.list = BRW.list->next;
        BRW.current = BRW.list->currentTab;
        i++;
        if (i > k + 1)
            break;
    }
    if (nr == BRW.current->id) {
        if (BRW.current->forwardStack != NULL) {
            while (BRW.current->forwardStack->Bottom != NULL) {
                BRW.current->forwardStack = BRW.current->forwardStack->Bottom;
            }
            while (BRW.current->forwardStack->Top != NULL) {
                fprintf(of, "%s\n", BRW.current->forwardStack->Page->url);
                BRW.current->forwardStack = BRW.current->forwardStack->Top;
            }
            fprintf(of, "%s\n", BRW.current->forwardStack->Page->url);
        }
        fprintf(of, "%s\n", BRW.current->currentPage->url);
        if (BRW.current->backwardStack != NULL) {
            while (BRW.current->backwardStack->Bottom != NULL) {
                fprintf(of, "%s\n", BRW.current->backwardStack->Page->url);
                BRW.current->backwardStack = BRW.current->backwardStack->Bottom;
            }
            fprintf(of, "%s\n", BRW.current->backwardStack->Page->url);
        }
    }
    else
        fprintf(of, "403 Forbidden\n");
}

void FREE(browser *BRW) {
    if (BRW->current->currentPage) {
        free(BRW->current->currentPage->description);
        BRW->current->currentPage->description = NULL;
        free(BRW->current->currentPage);
        BRW->current->currentPage = NULL;
    }
    while (BRW->current->backwardStack) {
        stack *current = BRW->current->backwardStack;
        BRW->current->backwardStack = BRW->current->backwardStack->Top;
        free(current);
    }
    // free(BRW->current->backwardStack);
    // newstack = BRW->current->forwardStack;
    // while (newstack) {
    //     stack *current = newstack;
    //     newstack = newstack->Top;
    //     free(current);
    // }
    // free(BRW->current->forwardStack);
    // tabList *temp = BRW->list;
    // if (temp->currentTab)
    //     free(temp->currentTab);
    // browser *brw = BRW;
    // BRW->list = BRW->list->next;
    // free(brw->list);
    // free(brw->current);
    // free(brw);
    // brw = NULL;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

page* NEW_PAGE(page *Page, int newID, char newURL, char *newDESCRIPTION) {
    Page = (page*)malloc(sizeof(Page));
    Page->id = newID;
    strcpy(Page->description, newDESCRIPTION);
    strcpy(Page->url, newURL);
    return Page;
}

tab* NEW_TAB (tab *newTab, int newID, page *newPAGE) {
    newTab = (tab*)malloc(sizeof(tab));
    newTab->id = newID;
    newTab->currentPage = newPAGE;
    stacknode *FrontNode = (stacknode *)malloc(sizeof(stacknode));
    stacknode *BackNode = (stacknode *)malloc(sizeof(stacknode));
    FrontNode->top = NULL;
    BackNode->top = NULL;
    newTab->backwardStack = BackNode;
    newTab->forwardStack = FrontNode;
    return newTab;
}
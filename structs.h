#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct page{
    int id;
    char url[50];
    char *description;
} page;

typedef struct stack{
    struct stack *Top;
    page *data;
} stack;

// typedef struct stacknode{
//     page data;
//     stack *top;
// } stacknode;

typedef struct tab{
    int id;
    page *currentPage;
    stack *backwardStack;
    stack *forwardStack;
} tab;

typedef struct tabList{
    tab *current;
    struct tabList *next;
    struct tabList *prev;
} tabList;

typedef struct browser{
    tab *current;
    tabList *list;
} browser;

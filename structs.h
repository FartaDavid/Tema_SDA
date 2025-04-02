#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char url[50];
    char *description;
} page;

typedef struct {
    page data;
    stack *top;
} stacknode;

typedef struct {
    stacknode *Top;
} stack;

typedef struct {
    int id;
    page *currentPage;
    stack *backwardStack;
    stack *forwardStack;
} tab;

typedef struct {
    tab *current;
    tabList *next;
    tabList *prev;
} tabList;

typedef struct {
    tab *current;
    tabList list;
} browser;
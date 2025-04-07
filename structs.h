#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define desclen 30

typedef struct page{
    int id;
    char url[50];
    char *description;
} page;

typedef struct stack{
    struct stack *Top;
    struct stack *Bottom;
    page *Page;
} stack;

typedef struct tab{
    int id;
    page *currentPage;
    stack *backwardStack;
    stack *forwardStack;
} tab;

typedef struct tabList{
    struct tabList *next;
    struct tabList *prev;
    tab *currentTab;
} tabList;

typedef struct browser{
    tab *current;
    tabList *list;
} browser;

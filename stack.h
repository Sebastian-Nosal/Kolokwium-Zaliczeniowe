#pragma once
#include <stdio.h>
#include <stdlib.h>

struct StackElement {
    void* data;
    struct StackElement* next;
};

struct Stack
{
    struct StackElement* top;    
    int index;
};

typedef int (CompData)(void* pcurData, void* pSearchData);

struct Stack initStack();
void clear(struct Stack* stack);
void push(struct Stack* stack, void* data);
struct StackElement pop(struct Stack* stack);
void* search(struct Stack* stack, void* pSearchDat, CompData ptr_comp_fun);
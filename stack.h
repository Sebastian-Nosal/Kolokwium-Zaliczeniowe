#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "error_handler.h"

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
void clear(struct Stack* stack, void(*clearHandler)(void* ptr));
void push(struct Stack* stack, void* data);
struct StackElement pop(struct Stack* stack);
void* search(struct Stack* stack, void* pSearchDat, CompData ptr_comp_fun);
void saveStack(struct Stack* stack, void (*saveElement)(FILE* file, void* data));
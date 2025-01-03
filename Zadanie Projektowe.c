#include <stdio.h>
#include "stack.h",
#include "interface.h",

int main()
{
    struct Stack s1 = {.index=0,.top=NULL};
    menu(&s1);
    return 1;
}


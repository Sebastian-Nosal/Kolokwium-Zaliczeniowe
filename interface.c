#pragma once
#include "interface.h";

struct Stack* currentStack;

static char* InterfaceOptions[] =
{
    "0 - Print",
	"1 - Push",
	"2 - Pop",
	"3 - Clear",
	"4 - Find lastname",
	"5 - Find facility",
	"6 - Find year",
	"7 - Finish",
};

static char* getStringWithUnknownLength() {
    
    int length = 1;      
    char* buffer = (char*)malloc(length*sizeof(char)); 

    char ch;
    while (1) {
        ch = getch();
        
        if (ch == '\n'|| ch=='\r') {
            break; 
        }
        printf("%c", ch);

        buffer[length-1] = ch;
        length++;
        char* newBuffer = (char*)realloc(buffer, length * sizeof(char));
        if (newBuffer == NULL) {
            free(buffer);
            return NULL;
        }
        buffer = newBuffer;
        
    }
    buffer[length - 1] = '\0';
    return buffer;
}

void handlePush() {
    system("cls");
    printf("\tPushing student to the stack\n");
    printf("-------------------------------------------\n");
    printf("Input student's surname and submit with ENTER: ");
    char* surname = getStringWithUnknownLength();
    printf("\nInput student's year of born and submit with ENTER: ");
    int bornYear;
    scanf_s("%d", &bornYear);
    printFacilities();
    printf("\nInput student's facility ID according to table above and submit with ENTER: ");
    enum Schools facility;
    scanf_s("%d", &facility);
    struct MY_STUDENT student = myStudentBuilder(surname, bornYear, facility);
    push(currentStack, &student);
    //printStudentInfo(currentStack->top->data);
    printf("\nPress any key to continue");
    getch();
    system("cls");
}

void handlePop() {
    system("cls");
    pop(currentStack);
    printf("\nPress any key to continue");
    getch();
    system("cls");
}

void handleClear() {
    system("cls");
    printf("\nAttempting to clear stack ");
    clear(currentStack);
    printf("\nPress any key to continue");
    getch();
    system("cls");
}

void handlePrint() {
    system("cls");
    printf("\tDATA\n");
    printf("----------------------\n");
    struct StackElement* currentElement = currentStack->top;
    if (currentElement == NULL) {
        printf("EMPTY");
    }

    while (currentElement != NULL) {
        printStudentInfo(currentElement->data);
        printf("*");
        currentElement = currentElement->next;
    }
    printf("\nPress any key to continue");
    getch();
    system("cls");
}

void menu(void* datastruct) {
    currentStack = (struct STACK*)datastruct;
    int flag = 1;
    while (flag == 1) {

        printf("\t Menu\n");
        printf("----------------------\n");
        for (int i = 0; i < INTERFACE_TOT; i++)
        {
            printf("\n%s\n", InterfaceOptions[i]);
        }
        if (currentStack->top != NULL) {
            printStudentInfo(currentStack->top->data);
        }

        printf("\nSelect action: ");
        int operation;
        scanf_s("%d", &operation);
        switch (operation) {
        case INTERFACE_PRINT:
            handlePrint();
            break;
        case INTERFACE_PUSH:
            handlePush();
            break;
        case INTERFACE_POP:
            handlePop();
            break;
        case INTERFACE_CLEAR:
            handleClear();
            break;
        case INTERFACE_FIND_LASTNAME:
            find_lastname();
            break;
        case INTERFACE_FIND_FACILITY:
            find_facility();
            break;
        case INTERFACE_FIND_YEAR:
            find_year();
            break;
        case INTERFACE_STOP:
            clear(currentStack);
            flag = 0;
            break;
        default:
            printf("\nUnknown action. Press any key to try again");
            getch();

        }
        system("cls");
    }
    
}

void find_lastname() {
    
    system("cls");
    printf("\tFinding student in the stack\n");
    printf("-------------------------------------------\n");
    printf("\ Input surname to search for: ");
    char* criterion = getStringWithUnknownLength();
    system("cls");

    struct StackElement* result = (struct StackElement*) search(currentStack, &criterion, getBySurname);
    if (result == NULL) {
        printf("\nNothing found");
    }
    else {
        printStudentInfo(result);
    }

    printf("\n\nPress any key to continue");
    getch();
    system("cls");
}

void find_year() {
    system("cls");
    printf("\tFinding student in the stack\n");
    printf("-------------------------------------------\n");
    printf("Input surname to search for: ");
    int year;
    scanf_s("%d", &year);
    system("cls");
    struct StackElement* result = (struct StackElement*)search(currentStack, &year, getByBorn);
    if (result == NULL) {
        printf("\n Nothing found");
    }
    else {
        printStudentInfo(result);
    }

    printf("\nPress any key to continue");
    getch();
    system("cls");
}

void find_facility() {
   
    system("cls");
    printf("\tFinding student in the stack\n");
    printf("-------------------------------------------\n");
    printf("Input student's facility ID according to table above and submit with ENTER: ");
    enum Schools facility;
    scanf_s("%d", &facility);
    system("cls");
    struct StackElement* result = (struct StackElement*)search(currentStack, &facility, getByFacility);
    if (result == NULL) {
        printf("\nNothing found");
    }
    else {
        printStudentInfo(result);
    }

    printf("Press any key to continue");
    getch();
    system("cls");
}

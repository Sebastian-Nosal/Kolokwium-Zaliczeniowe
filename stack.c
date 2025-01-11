#include "stack.h";
#include "data.h"
struct Stack initStack() {
	struct Stack stack1 = { .top = NULL,.index = 0 };
	return stack1;
}

void clear(struct Stack* stack, void(* clearHandler)(void*ptr)) {
	if (stack == NULL || stack->top == NULL) {
		return;
	}
	struct StackElement* firstElem = stack->top;
	struct StackElement* tmp = NULL;
	while (firstElem != NULL) {
		tmp = firstElem;
		firstElem = firstElem->next;

		(*clearHandler)(tmp->data);
		free(tmp);
		tmp = NULL;
	}
	stack->top = NULL;
}

void push(struct Stack* stack, void* data) {
	if (stack == NULL) {
		handleErrors(NULL,NULL);
		return;
	}

	struct StackElement* newElement = (struct StackElement*)malloc(sizeof(struct StackElement));
	if (newElement == NULL) {
		handleErrors(NULL,NULL);
		return;
	}

	newElement->data = data;
	newElement->next = stack->top; 

	stack->top = newElement; 
	stack->index++;

	printf("Element added to stack\n");
}

struct StackElement pop(struct Stack* stack) {
	struct StackElement toReturn = { .data = NULL, .next = NULL };
	if (stack->top == NULL) {
		return toReturn;
	}

	struct StackElement* topElement = stack->top;  
	stack->index--;
	toReturn.data = stack->top->data;
	stack->top = topElement->next;  
	printf("Element removed from stack");
	return toReturn;  
}

void* search(struct Stack* stack, void* pSearchDat, CompData ptr_comp_fun) {
	struct StackElement* current = stack->top; 
	void* foundData = NULL;

	while (current != NULL) {
		if (ptr_comp_fun(current->data, pSearchDat) == 1) {
			foundData = current->data;
			break; 
		}
		current = current->next; 
	}

	return foundData;
}

void saveStack(struct Stack* stack, void (*saveElement)(FILE* file, void* data)) {
	if (stack == NULL || stack->top == NULL || saveElement == NULL) {
		return;
	}

	FILE* file = fopen("file.bin", "wb");
	if (file == NULL) {
		handleErrors(NULL,NULL);
		return;
	}

	struct StackElement* current = stack->top;
	size_t numElements = 0;

	while (current != NULL) {
		numElements++;
		current = current->next;
	}

	size_t result1 = fwrite(&numElements, sizeof(size_t), 1, file);
	if (result1 != 1) {
		handleErrors(file,"file");
		return;
	}

	current = stack->top;  
	while (current != NULL) {
		saveElement(file, current->data);

		current = current->next;  
	}

	fclose(file);
	printf("Saved to file %s\n", "file.bin");
}
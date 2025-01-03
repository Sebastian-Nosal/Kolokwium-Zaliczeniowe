#include "stack.h";
#include "data.h"
struct Stack initStack() {
	struct Stack stack1 = { .top = NULL,.index = 0 };
	return stack1;
}

void clear(struct Stack* stack) {
	struct StackElement* firstElem = stack->top;
	struct StackElement* tmp = NULL;
	while (firstElem != NULL) {
		tmp = firstElem;
		firstElem = firstElem->next;
		free(tmp);
	}
	free(stack);
}

void push(struct Stack* stack, void* data) {
	if (stack == NULL) {
		handleErrors();
		return;
	}

	struct StackElement* newElement = (struct StackElement*)malloc(sizeof(struct StackElement));
	if (newElement == NULL) {
		handleErrors();
		return;
	}

	newElement->data = data;
	newElement->next = stack->top; 

	stack->top = newElement; 
	stack->index++;
	printStudentInfo(stack->top->data);

	printf("Element added to stack\n");
}

struct StackElement pop(struct Stack* stack) {
	struct StackElement toReturn = { .data = NULL, .next = NULL };
	if (stack->top == NULL) {
		return toReturn;
	}

	struct StackElement* topElement = stack->top;  
	stack->top = topElement->next;  
	stack->index--; 
	toReturn.data = stack->top->data;
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
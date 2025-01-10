#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "stack.h";
#include "data.h";

enum MY_INTERFACE
{
	INTERFACE_PRINT,
	INTERFACE_PUSH,
	INTERFACE_POP,
	INTERFACE_CLEAR,
	INTERFACE_FIND_LASTNAME,
	INTERFACE_FIND_FACILITY,
	INTERFACE_FIND_YEAR,
	INTERFACE_SAVE,
	INTERFACE_LOAD,
	INTERFACE_STOP,
	INTERFACE_TOT
};

void handlePush();
void handlePop();
void handleClear();
void handlePrint();
void menu(void* datastruct);
void find_lastname();
void find_year();
void find_facility();
void handleSave();
void handleLoad();

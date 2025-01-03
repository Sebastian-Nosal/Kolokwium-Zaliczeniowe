#pragma once
#include <stdio.h>
#include <stdlib.h>

enum Schools {
	WM,
	WA,
	WIT,
	WIS,
	WIEK,
	WIMF,
	WITC,
	WIL,
	END,
};



struct MY_STUDENT {
	char* surname;
	int bornYear;
	enum Schools facility;
};

struct MY_STUDENT myStudentBuilder(char* surname, int bornYear, enum Schools facility);
void saveStudentToDisk(void *student);
struct MY_STUDENT loadStudentFromDisk();
void printStudentInfo(void* student);
int getBySurname(void* student,void* criteria);
int getByFacility(void* student,void* criteria);
int getByBorn(void* student,void* criteria);
void printFacilities();
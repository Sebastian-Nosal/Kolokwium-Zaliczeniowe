#include "data.h"
#include "error_handler.h"
#define FILE_NAME "data.bin"

static char* schoolsNames[] = {
"Wydzial Mechaniczny",
"Wydzial Architektury",
"Wydzial Informatyki i Telekomunikacji",
"Wydzial Inzynierii Srodowiska",
"Wydzial Inzynierii Elektrycznej i Komputerowej",
"Wydzial Inzynierii Materialowej i Fizyki",
"Wydzial Inzynierii i Technologii Chemicznej",
"Wydzial Inzynierii Ladowej",
};

static long lastPosition = 0;

struct MY_STUDENT* myStudentBuilder(char* surname, int bornYear, enum Schools facility) {
	struct MY_STUDENT* newStudent = (struct MY_STUDENT*)malloc(sizeof(struct MY_STUDENT));

	if (newStudent == NULL) {
		handleErrors(NULL,NULL);
		return NULL;
	}

	newStudent->surname = (char*)malloc(strlen(surname) + 1);
	if (newStudent->surname == NULL) {
		handleErrors(newStudent,"ptr");
		return NULL;
	}

	strcpy_s(newStudent->surname, strlen(surname) + 1, surname);
	newStudent->bornYear = bornYear;
	newStudent->facility = facility;

	return newStudent;
}

void freeStudent(void * ptr) {
	struct MY_STUDENT* student = (struct MY_STUDENT*)ptr;
	if (student!=NULL)
	{
		if (student->surname != NULL) {
			free(student->surname);
			student->surname = NULL;
		}
		free(student);
	}
}

void saveStudentToDisk(FILE* file, void* data) {
	struct MY_STUDENT* student = (struct MY_STUDENT*)data;
	size_t surnameLength = strlen(student->surname) + 1;

	size_t result1 = fwrite(&surnameLength, sizeof(size_t), 1, file);
	size_t result2 = fwrite(student->surname, sizeof(char), surnameLength, file);
	size_t result3 = fwrite(&student->bornYear, sizeof(int), 1, file);
	size_t result4 = fwrite(&student->facility, sizeof(enum Schools), 1, file);

	if (result1 != 1 || result2 != surnameLength || result3 != 1 || result4 != 1) {
		handleErrors(file,"file");
	}
}

void loadStudentsFromDisk(struct Stack* stack, void* builder) {
	FILE* file = fopen("file.bin", "rb");
	if (file == NULL) {
		handleErrors(NULL,NULL);
		return;
	}

	size_t numElements;
	size_t result = fread(&numElements, sizeof(size_t), 1, file);
	if (result != 1) {
		handleErrors(file,"file");
	}

	for (size_t i = 0; i < numElements; i++) {
		size_t surnameLength;
		result = fread(&surnameLength, sizeof(size_t), 1, file);
		if (result != 1) {
			handleErrors(file,"file");
			return;
		}

		char* surname = (char*)malloc(surnameLength);
		if (surname == NULL) {
			handleErrors(file,"file");
			return;
		}

		result = fread(surname, sizeof(char), surnameLength, file);
		if (result != surnameLength) {
			handleErrors(file,"file");
			return;
		}

		int bornYear;
		result = fread(&bornYear, sizeof(int), 1, file);
		if (result != 1) {
			handleErrors(file,"file");
			return;
		}

		enum Schools facility;
		result = fread(&facility, sizeof(enum Schools), 1, file);
		if (result != 1) {
			handleErrors(file,"file");
			return;
		}

		struct MY_STUDENT* newStudent = ((struct MY_STUDENT* (*)(char*, int, enum Schools))builder)(surname, bornYear, facility);

		push(stack, newStudent);

		free(surname);
	}

	fclose(file);
}

void printStudentInfo(void* student) {
	struct MY_STUDENT* tmp = (struct MY_STUDENT*)student;
	if (tmp) {
		printf("surname    : %s\n", tmp->surname);
		printf("born       : %d\n", tmp->bornYear);
		printf("facility   : %s\n", schoolsNames[tmp->facility]);
	}
}

int getBySurname(void* student, void* criteria) {
	struct MY_STUDENT* pcur = (struct MY_STUDENT*)student;
	criteria = (char*)criteria;
	if (strcmp(pcur->surname, criteria) == 0)
		return 1;
	return 0;
}

int getByFacility(void* student, void* criteria) {
	struct MY_STUDENT* pcur = (struct MY_STUDENT*)student;
	criteria = (int)criteria;

	if (pcur->facility == criteria)
		return 1;
	return 0;
}

int getByBorn(void* student, void* criteria) {
	struct MY_STUDENT* pcur = (struct MY_STUDENT*)student;
	criteria = (int)criteria;

	if (pcur->bornYear == criteria)
		return 1;
	return 0;
}

void printFacilities() {
	for (int i = 0; i < END; i++) {
		printf("\n%d) %s", i, schoolsNames[i]);
	}
}
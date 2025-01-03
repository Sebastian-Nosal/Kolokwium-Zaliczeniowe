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

struct MY_STUDENT myStudentBuilder(char* surname, int bornYear, enum Schools facility) {
	struct MY_STUDENT newStudent = {.surname=surname,.bornYear=bornYear,.facility=facility};
	return newStudent;
}

void saveStudentToDisk(void* student) {
	struct MY_STUDENT* tmp = (struct MY_STUDENT*)student;
	FILE* file = fopen(FILE_NAME, "wb");
	if (file == NULL) {
		handleErrors();
		return;
	}
	size_t surnameLength = strlen(tmp->surname) + 1; 
	size_t result1 = fwrite(&surnameLength, sizeof(size_t), 1, file);
	size_t result2 = fwrite(tmp->surname, sizeof(char), surnameLength, file);
	size_t result3 = fwrite(&tmp->bornYear, sizeof(int), 1, file);
	size_t result4 = fwrite(&tmp->facility, sizeof(enum Schools), 1, file);
	if (result1 != 1||result2!=surnameLength||result3!=1||result4!=1) {
		handleErrors();
		fclose(file);
		return;
	}
	else {
		lastPosition = 0;
		fclose(file);
		printf("Saved to file stack.bin");
	}

}

struct MY_STUDENT loadStudentFromDisk() {
	struct MY_STUDENT student = {.surname = NULL, .bornYear=NULL};

	FILE* file = fopen(FILE_NAME, "rb");
	if (!file) {
		handleErrors();
		return student;
	}

	if (lastPosition == 0) {
		fseek(file, 0, SEEK_END);
	}
	else {
		fseek(file, lastPosition, SEEK_SET);
	}

	long currentPosition = ftell(file);

	if (currentPosition == 0) { 
		fclose(file);
		return student; 
	}

	fseek(file, -(long)sizeof(size_t), SEEK_CUR);
	size_t surnameLength;
	fread(&surnameLength, sizeof(size_t), 1, file);

	fseek(file, -(long)(sizeof(size_t) + surnameLength), SEEK_CUR);
	student.surname = malloc(surnameLength);
	fread(student.surname, sizeof(char), surnameLength, file);

	fseek(file, -(long)(sizeof(size_t) + surnameLength + sizeof(int) + sizeof(enum Schools)), SEEK_CUR);
	fread(&student.bornYear, sizeof(int), 1, file);
	fread(&student.facility, sizeof(enum Schools), 1, file);

	lastPosition = ftell(file);

	fclose(file);
	return student;
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
	//struct MY_STUDENT* psearch = (struct MY_STUDENT*)criteria;

	//if (strcmp(pcur->surname, psearch->surname) == 0)
	if (strcmp(pcur->surname, criteria) == 0)
		return 1;
	return 0;
}

int getByFacility(void* student, void* criteria) {
	struct MY_STUDENT* pcur = (struct MY_STUDENT*)student;
	//struct MY_STUDENT* psearch = (struct MY_STUDENT*)criteria;

	if (pcur->facility == criteria)//psearch->facility)
		return 1;
	return 0;
}

int getByBorn(void* student, void* criteria) {
	struct MY_STUDENT* pcur = (struct MY_STUDENT*)student;
	//struct MY_STUDENT* psearch = (struct MY_STUDENT*)criteria;

	if (pcur->bornYear == criteria) // psearch->bornYear);
		return 1;
	return 0;
}

void printFacilities() {
	for (int i = 0; i < END; i++) {
		printf("\n%d) %s", i, schoolsNames[i]);
	}
}
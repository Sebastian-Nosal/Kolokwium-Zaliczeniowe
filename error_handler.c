#include "error_handler.h"
#include <signal.h>

const char* errorMessages[] = {
    "Nie mozna otworzyc pliku",
    "Plik Pusty - nie mo¿na odczytaæ",
    "Plik Nie istnieje",
    "Brak uprawnien",
    "Nie mo¿na utworzyæ pliku",
    "Brak pamiêci",
    "Blad segmentacji",
    "Nieznany blad"
};

void handleErrors(void* ptr, void* type) {
    system("color 4");
    system("cls");
    enum ErrorNotification message = mapErrnoToErrorNotification(errno);
    printf("%s", errorMessages[message]);
    if (ptr != NULL && type!=NULL) {
        if (strcmp((char*)type,"file")) {
            if (ptr && ((FILE*)ptr)) {
                fclose((FILE*)ptr);
            }
        }else if(strcmp((char*)type,"ptr")) { 
            free(ptr);
        }
    }
    printf("\nPress any key to continue");
    getch();
    system("color 7");
    system("cls");
}

enum ErrorNotifications mapErrnoToErrorNotification(int err) {
    enum ErrorNotofication notification;
    switch (err) {
        case EIO:               
            notification = FileOpen;
            break;

        case ENOENT:            
            notification = FileNotExist;
            break;

        case EACCES:            
            notification =  NotAllowed;
            break;

        case EROFS:
            notification = NotAllowed;
            break;
        case EEXIST:         
            notification = CannotCreate;
            break;

        case ENOMEM:            
            notification = NoMemory;
            break;

        case SIGSEGV:           
            notification = SegmentationError;
            break;

        default:
            notification = UnknownError; 
    }
    return notification;
}
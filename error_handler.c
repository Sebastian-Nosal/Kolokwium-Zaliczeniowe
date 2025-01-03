#include "error_handler.h"
#include <signal.h>

const char* errorMessages[] = {
    "Nie mo�na otworzy� pliku",
    "Plik Pusty - nie mo�na odczyta�",
    "Plik Nie istnieje",
    "Brak uprawnie�",
    "Nie mo�na utworzy� pliku",
    "Brak pami�ci",
    "B��d segmentacji",
    "Nieznany b��d"
};

void handleErrors() {
    system("color 4");
    system("cls");
    enum ErrorNotification message = mapErrnoToErrorNotification(errno);
    printf("%s", errorMessages[message]);
    printf("Press any key to continue");
    getch();
    system("color 7");
    system("cls");
}

enum ErrorNotifications mapErrnoToErrorNotification(int err) {
    enum ErrorNotofication notification;
    switch (err) {
        case EIO:               
            notification = FileOpen;
        case ENOENT:            
            notification = FileNotExist;
        case EACCES:            
            notification =  NotAllowed;
        case EEXIST:         
            notification = CannotCreate;
        case ENOMEM:            
            notification = NoMemory;
        case SIGSEGV:           
            notification = SegmentationError;
        default:
            notification = UnknownError; 
    }
    return notification;
}
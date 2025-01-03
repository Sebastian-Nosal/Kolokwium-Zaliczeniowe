#include "error_handler.h"
#include <signal.h>

const char* errorMessages[] = {
    "Nie mo¿na otworzyæ pliku",
    "Plik Pusty - nie mo¿na odczytaæ",
    "Plik Nie istnieje",
    "Brak uprawnieñ",
    "Nie mo¿na utworzyæ pliku",
    "Brak pamiêci",
    "B³¹d segmentacji",
    "Nieznany b³¹d"
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
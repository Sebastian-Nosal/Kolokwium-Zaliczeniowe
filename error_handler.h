#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

enum ErrorNotifications {
	FileOpen,
	FileEmpty,
	FileNotExist,
	NotAllowed,
	CannotCreate,
	NoMemory,
	SegmentationError,
	UnknownError,
};

void handleErrors(void* prt, void* type);

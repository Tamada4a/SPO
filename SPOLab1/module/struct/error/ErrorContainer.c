#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ErrorContainer.h"

ErrorContainerItem **allErrors;
int allErrorsCount;

static int startsWith(const char *a, const char *b) {
    return strncmp(a, b, strlen(b)) == 0;
}

static void printError(const ErrorContainerItem *errorItem) {
    if (errorItem->col == -1 && errorItem->line == -1) {
        fprintf(stderr, "Error detected! %s", errorItem->nearToken);
        return;
    }
    fprintf(stderr, "\nError detected!\nFile: %s\nRow: %d\nCol: %d\n", errorItem->fileName, errorItem->line, errorItem->col);
    char *nearToken = errorItem->nearToken;
    const char *targetString = "<missing ";
    if (startsWith(nearToken, targetString)) {
        const int lenOrigin = (int) (strlen(nearToken));
        const int lenTarget = (int) (strlen(targetString));
        const int dif = lenOrigin - lenTarget;
        char *missingChar = malloc(dif * sizeof(char));
        memcpy(missingChar, &nearToken[lenTarget], dif);
        missingChar[dif - 1] = '\0';
        fprintf(stderr, "Missing token: %s(%d)\n\n", missingChar, errorItem->nearTokenType);
        free(missingChar);
    } else {
        fprintf(stderr, "Error near token: '%s'(%d)\n\n", nearToken, errorItem->nearTokenType);
    }
}

ErrorContainerItem *createErrorItem(char *fileName, const int line, const int col, char *nearToken,
                                    const int nearTokenType) {
    ErrorContainerItem *errorItem = malloc(sizeof(ErrorContainerItem));
    errorItem->fileName = fileName;
    errorItem->line = line;
    errorItem->col = col;
    errorItem->nearToken = nearToken;
    errorItem->nearTokenType = nearTokenType;
    allErrors[allErrorsCount] = errorItem;
    allErrorsCount++;

    return errorItem;
}

void printErrors() {
    for (int i = 0; i < allErrorsCount; ++i) {
        printError(allErrors[i]);
    }
}

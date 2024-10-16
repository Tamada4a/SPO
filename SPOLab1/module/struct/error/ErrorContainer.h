#pragma once

#ifndef ERRORCONTAINER_H
#define ERRORCONTAINER_H

typedef struct ErrorContainerItem ErrorContainerItem;

struct ErrorContainerItem {
    char *fileName;
    int line;
    int col;
    char *nearToken;
    int nearTokenType;
};

void printErrors();

ErrorContainerItem *createErrorItem(char *fileName, int line, int col, char *nearToken, int nearTokenType);

#endif

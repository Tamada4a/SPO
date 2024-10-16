#ifndef MODULE_H
#define MODULE_H

#include "struct/result/Result.h"

void printAST(const char *charTree, char *pathToSave);
ResultInfo *parse(char *inputPath);

#endif //MODULE_H

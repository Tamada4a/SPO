#include <stdio.h>
#include "module/module.h"
#include "module/struct/result/Result.h"

int main(int argc, char *argv[]) {

    if (argc == 3) {
        //printf("%s %s", argv[1], argv[2]);
        ResultInfo *resultInfo = parse(argv[1]);

        if (resultInfo == NULL) {
            printErrors();
            return -1;
        }

        if (resultInfo->errorCount != 0) {
            printErrors();
        }

        printAST(resultInfo->charTree, argv[2]);
        clearResultInfo(resultInfo);
    } else {
        fprintf(stderr, "Not enough args!");
        return -1;
    }

    return 0;
}

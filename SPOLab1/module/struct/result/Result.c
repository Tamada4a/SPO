#include "Result.h"

#include <stdlib.h>
#include <antlr3.h>

ResultInfo *createResultInfo(ASTNode *tree, ErrorContainerItem **errors, int errorCount,
                             const char *charTree, pANTLR3_INPUT_STREAM input,
                             pGrammarLexer lxr, pANTLR3_COMMON_TOKEN_STREAM tokenStream, pGrammarParser psr) {
    ResultInfo *result = malloc(sizeof(ResultInfo));
    result->tree = tree;

    result->errors = errors;
    result->errorCount = errorCount;

    result->charTree = charTree;

    result->input = input;
    result->lxr = lxr;
    result->tokenStream = tokenStream;
    result->psr = psr;

    return result;
}

static void clearTree(ASTNode *tree) {
    ASTNode **childs = tree->childs;
    for (int i = 0; i < tree->childsCount; ++i) {
        ASTNode *child = childs[i];
        clearTree(child);
    }
    free(childs);
    free(tree);
}

void clearResultInfo(ResultInfo *resultInfo) {
    ErrorContainerItem **errors = resultInfo->errors;
    for (int i = 0; i < resultInfo->errorCount; ++i) {
        free(errors[i]);
    }
    free(errors);

    clearTree(resultInfo->tree);

    pANTLR3_INPUT_STREAM input = resultInfo->input;
    input->close(input);
    input = NULL;

    pGrammarLexer lxr = resultInfo->lxr;
    lxr->free(lxr);
    lxr = NULL;

    pANTLR3_COMMON_TOKEN_STREAM tokenStream = resultInfo->tokenStream;
    tokenStream->free(tokenStream);
    tokenStream = NULL;

    pGrammarParser psr = resultInfo->psr;
    psr->free(psr);
    psr = NULL;
}

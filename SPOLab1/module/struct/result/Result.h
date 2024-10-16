#ifndef RESULT_H
#define RESULT_H

#include <antlr3.h>

#include "../ast/Ast.h"
#include "../error/ErrorContainer.h"
#include "../../grammar/parser/GrammarParser.h"
#include "../../grammar/lexer//GrammarLexer.h"

typedef struct ResultInfo ResultInfo;

struct ResultInfo {
    ASTNode *tree;

    ErrorContainerItem **errors;
    int errorCount;

    const char *charTree;

    pANTLR3_INPUT_STREAM input;
    pGrammarLexer lxr;
    pANTLR3_COMMON_TOKEN_STREAM tokenStream;
    pGrammarParser psr;
};

ResultInfo *createResultInfo(ASTNode *tree, ErrorContainerItem **errors, int errorCount,
                             const char *charTree, pANTLR3_INPUT_STREAM input,
                             pGrammarLexer lxr, pANTLR3_COMMON_TOKEN_STREAM tokenStream, pGrammarParser psr);

void clearResultInfo(ResultInfo *resultInfo);

#endif //RESULT_H

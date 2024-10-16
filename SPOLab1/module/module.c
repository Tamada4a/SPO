#include <stdio.h>
#include <stdlib.h>
#include <graphviz/gvc.h>
#include <antlr3.h>

#include "grammar/lexer/GrammarLexer.h"
#include "grammar/parser/GrammarParser.h"
#include "struct/error/ErrorContainer.h"
#include "struct/ast/Ast.h"
#include "struct/result/Result.h"
#include "module.h"

extern ErrorContainerItem **allErrors;
extern int allErrorsCount;

static int generateGraph(const char *cp, const char *pathToSave) {
    mkdir(pathToSave, 0700);

    const char *pathToFile = "/result.png";
    char *pathToSaveFile = (char *) malloc((strlen(pathToSave) + strlen(pathToFile) + 1) * sizeof(char));
    strcat(pathToSaveFile, pathToSave);
    strcat(pathToSaveFile, "\\result.png");

    Agraph_t *gr = agmemread(cp);
    GVC_t *gvc = gvContext();
    gvLayout(gvc, gr, "dot");
    gvRender(gvc, gr, "png", fopen(pathToSaveFile, "wb"));

    gvFreeLayout(gvc, gr);
    agclose(gr);
    free(pathToSaveFile);
    return gvFreeContext(gvc);
}

void printAST(const char *charTree, char *pathToSave) {
    printf("%s\n", charTree);
    generateGraph(charTree, pathToSave);
}

static ASTNode *createNodeFromTree(pANTLR3_BASE_TREE tree) {
    pANTLR3_COMMON_TOKEN token = tree->getToken(tree);
    char *tokenName = (char *) (token->getText(token)->chars);
    int count = (int) (tree->getChildCount(tree));
    ASTNode *node = createNode(count, tokenName);
    return node;
}

static void performNodes(pANTLR3_BASE_TREE tree, ASTNode *node) {
    int childs = (int) (tree->getChildCount(tree));
    for (int i = 0; i < childs; ++i) {
        pANTLR3_BASE_TREE childTree = tree->getChild(tree, i);
        ASTNode *childNode = createNodeFromTree(childTree);
        addChild(node, childNode, i);
        performNodes(childTree, childNode);
    }
}

static ASTNode *performTree(pANTLR3_BASE_TREE tree) {
    int childs = (int) (tree->getChildCount(tree));
    ASTNode *node = createNodeFromTree(tree);
    for (int i = 0; i < childs; ++i) {
        pANTLR3_BASE_TREE childTree = tree->getChild(tree, i);
        ASTNode *childNode = createNodeFromTree(childTree);
        addChild(node, childNode, i);
        performNodes(childTree, childNode);
    }
    return node;
}

static void myDisplayRecognitionError(pANTLR3_BASE_RECOGNIZER recognizer, pANTLR3_UINT8 *tokenNames) {
    pANTLR3_EXCEPTION ex = recognizer->state->exception;
    char *fileName = "";
    // Получение названия файла, в котором произошла ошибка
    if (ex->streamName != NULL) {
        pANTLR3_STRING ftext = ex->streamName->to8(ex->streamName);
        fileName = (char *) (ftext->chars);
    }

    // Получение строки, в которой ошибка
    const int line = (int) (recognizer->state->exception->line);
    // Получение столбца, в котором ошибка
    const int col = recognizer->state->exception->charPositionInLine;

    const ANTLR3_UINT32 recognizerType = recognizer->type;
    char *nearToken = "";
    int nearTokenType = -1;
    if (recognizerType == ANTLR3_TYPE_PARSER) {
        pANTLR3_COMMON_TOKEN theToken = (pANTLR3_COMMON_TOKEN) (recognizer->state->exception->token);
        nearToken = (char *) (theToken->getText(theToken)->chars);
        nearTokenType = (int) (theToken->getType(theToken));
    }
    createErrorItem(fileName, line, col, nearToken, nearTokenType);
}

ResultInfo *parse(char *inputPath) {
    allErrors = malloc(1024 * 8 * sizeof(ErrorContainerItem *));
    allErrorsCount = 0;

    if (!allErrors) {
        createErrorItem("", -1, -1, "Unable to alloc memory!\n", -1);
        return NULL;
        //exit(ANTLR3_ERR_NOMEM);
    }

    //char* path = "F:\\ClionProjects\\SPOLab1\\tests\\test1.txt";
    pANTLR3_UINT8 fName = (pANTLR3_UINT8) inputPath;

    pANTLR3_INPUT_STREAM input = antlr3FileStreamNew(fName, ANTLR3_ENC_8BIT);

    if (input == NULL) {
        //ANTLR3_FPRINTF(stderr, "Unable to open file %s due to malloc() failure!\n", (char *) fName);
        createErrorItem("", -1, -1, "Unable to open file due to malloc() failure!\n", -1);
    }

    pGrammarLexer lxr = GrammarLexerNew(input);

    if (lxr == NULL) {
        //ANTLR3_FPRINTF(stderr, "Unable to create the lexer due to malloc() failure!\n");
        createErrorItem("", -1, -1, "Unable to create the lexer due to malloc() failure!\n", -1);
        return NULL;
        //exit(ANTLR3_ERR_NOMEM);
    }

    pANTLR3_COMMON_TOKEN_STREAM tokenStream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lxr));

    if (tokenStream == NULL) {
        //ANTLR3_FPRINTF(stderr, "Out of memory trying to allocate token stream\n");
        createErrorItem("", -1, -1, "Out of memory trying to allocate token stream!\n", -1);
        return NULL;
        //exit(ANTLR3_ERR_NOMEM);
    }

    pGrammarParser psr = GrammarParserNew(tokenStream);

    if (psr == NULL) {
        //ANTLR3_FPRINTF(stderr, "Out of memory trying to allocate parser\n");
        createErrorItem("", -1, -1, "Out of memory trying to allocate parser!\n", -1);
        return NULL;
        //exit(ANTLR3_ERR_NOMEM);
    }

    psr->pParser->rec->displayRecognitionError = myDisplayRecognitionError;

    GrammarParser_source_return langAST = psr->source(psr);
    const char *dotChar = (const char *) (psr->adaptor->makeDot(psr->adaptor, langAST.tree)->chars);

    ASTNode *node = performTree(langAST.tree);
    ResultInfo *resultInfo = createResultInfo(node, allErrors, allErrorsCount, dotChar, input, lxr, tokenStream, psr);

    return resultInfo;
}

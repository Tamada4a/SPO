#pragma once

#ifndef AST_H
#define AST_H

typedef struct ASTNode ASTNode;

struct ASTNode {
    ASTNode **childs;
    int childsCount;
    char *value;
    int id;
};

ASTNode *createNode(int childsCount, char *value);

void addChild(ASTNode *node, ASTNode *child, int i);

#endif

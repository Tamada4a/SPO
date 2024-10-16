#include <stdint.h>
#include <stdlib.h>

#include "Ast.h"

ASTNode* createNode(int childsCount, char* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->childs = malloc(1024 * childsCount * sizeof(ASTNode*));
    node->value = value;
    node->childsCount = childsCount;
    return node;
}

void addChild(ASTNode *node, ASTNode* child, int i) {
    node->childs[i] = child;
}
// Trabalho de Mikael Arnez Schroeder

#ifndef TACS_HEADER
#define TACS_HEADER

#include <stdlib.h>

#include "hash.h"
#include "ast.h"

#define TAC_SYMBOL 1
#define TAC_ADD 2
#define TAC_SUB 3
#define TAC_COPY 4
#define TAC_MUL 5
#define TAC_DIV 6
#define TAC_GE 7
#define TAC_LE 8
#define TAC_EQ 9
#define TAC_DIF 10
#define TAC_PIPE 11
#define TAC_G 12
#define TAC_L 13
#define TAC_AND 14

typedef struct tac_node {
    int type;
    HASH_NODE *res;
    HASH_NODE *op1;
    HASH_NODE *op2;
    struct tac_node *prev;
    struct tac_node *next;
} TAC;

TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2);

void tacPrint(TAC* tac);

void tacPrintBackwards(TAC *tac);

TAC* tacJoin(TAC* l1, TAC* l2);
HASH_NODE* safeGet(TAC* something);

TAC* generateCode(AST *node);
TAC* generateBinOp(int op, TAC* op1, TAC* op2);

#endif
// trabalho de Mikael Arnez schroeder
// tabela hash do video
#include <string.h>
#include <stdlib.h>
#include "hash.h"

HASH_NODE*Table[HASH_SIZE];

void hashInit(void) {
    int i;
    for (i = 0; i < HASH_SIZE; i++) {
        Table[i] = 0;
    }
}

int hashAddress(char *text) {
    int address = 1;
    int i;

    for (i = 0; i < strlen(text); ++i) {
        address = (address * text[i]) % HASH_SIZE + 1;
    }

    return address-1;
}

HASH_NODE *hashFind(char *text) {
    HASH_NODE *node;
    int address = hashAddress(text);

    for (node = Table[address]; node; node = node -> next) {
        if (strcmp(node->text, text) == 0) {
            return node;
        }
    }
    return 0;
}

HASH_NODE *hashInsert(char *text, int type) {
    HASH_NODE  *newNode;
    int address = hashAddress(text);

    newNode = hashFind(text);

    if (newNode != 0) {
        return newNode;
    }

    newNode = (HASH_NODE*) calloc(1, sizeof(HASH_NODE));
    newNode->type = type;
    newNode->text = (char*) calloc(strlen(text)+1, sizeof(char));
    strcpy(newNode->text, text);
    newNode->next = Table[address];
    Table[address] = newNode;

    return newNode;
}

void hashPrint(void) {
    int i;
    HASH_NODE *node;

    for (i = 0; i < HASH_SIZE; ++i) {
        for (node = Table[i]; node; node = node->next) {
            printf("Table[%d] has %s\n", i, node->text);
        }
    }
}

HASH_NODE *makeTemp(void) {
    static int tempSerial = 0;
    char buffer[256] = "";

    sprintf(buffer, "__temp%d", tempSerial++); //todo: nome mais aleatorio

    return hashInsert(buffer, 999);
}

HASH_NODE *makeLabel(void) {
    static int tempLabel = 0;
    char buffer[256] = "";

    sprintf(buffer, "__label%d", tempLabel++); //todo: nome mais aleatorio

    return hashInsert(buffer, 1000);
}

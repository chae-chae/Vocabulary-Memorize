//
//  word.c
//  플밍2 플젝
//
//  Created by 채채 on 19/11/2019.
//  Copyright © 2019 chaechae. All rights reserved.
//

#include "word.h"

BOOL createList(List *lp){
    if (lp == NULL) {
        return FALSE;
    }
    lp->head = (Node *)malloc(sizeof(Node));
    if (lp->head == NULL) {
        return FALSE;
    }
    lp->tail = (Node *)malloc(sizeof(Node));
    if (lp->tail == NULL) {
        free(lp->head);
        return FALSE;
    }
    lp->head->next = lp->tail;
    lp->tail->next = lp->tail;
    lp->head->prev = lp->head;
    lp->tail->prev = lp->head;
    lp->size = 0;
    return TRUE;
}
BOOL addLast(List *lp, char eng[], char k1[], char k2[], char k3[]){
    Node *np;
    if (lp == NULL) {
        return FALSE;
    }
    np = (Node *)malloc(sizeof(Node));
    if (np != NULL) {
        strcpy(np->eng, eng);
        strcpy(np->kr1, k1);
        strcpy(np->kr2, k2);
        strcpy(np->kr3, k3);
        np->next = lp->tail;
        np->prev = lp->tail->prev;
        np->prev->next = np;
        lp->tail->prev = np;
        ++lp->size;
        return TRUE;
    } else {
        return FALSE;
    }
}
void displayList(List *lp){
    Node *cp;
    if (lp == NULL) { /* lp포인터 NULL check */
        return;
    }
    cp = lp->head->next;
    printf("---------단어장----------\n");
    while (cp != lp->tail) {
        printf("%s %s %s %s\n", cp->eng, cp->kr1, cp->kr2, cp->kr3);
        cp = cp->next;
    }
    return;
}
void destroyList(List *lp){
    Node *cp;
    Node *nextp;
    if (lp == NULL) {
        return;
    }
    cp = lp->head->next;
    while (cp != lp->tail) {
        nextp = cp->next;
        free(cp);
        cp = nextp;
    }
    free(lp->head);
    free(lp->tail);
    
    lp->head = lp->tail = NULL;
    lp->size = 0;
    return;
}
void saveList(List *lp, FILE *fp){
    Node *cp;
    if (lp == NULL) { /* lp포인터 NULL check */
        return;
    }
    cp = lp->head->next;
    while (cp != lp->tail) {
        fprintf(fp, "%s %s %s %s\n", cp->eng, cp->kr1, cp->kr2, cp->kr3);
        cp = cp->next;
    }
    return;
}
int separateString(char input[], char **sArr, char std[]){
    memset(sArr, 0, sizeof(sArr));
    int pmove = 0; // 자른 문자열 포인터 옮겨줄 변수
    char *tokptr = strtok(input, std); // 문자열 공백마다 분리
    while (tokptr != NULL) { // 옮겨주면서 분리한거 저장
        sArr[pmove] = tokptr;
        pmove++;
        tokptr = strtok(NULL, std);
    }
    return pmove;
}
int getTotalLine(char *name){
    FILE *fp;
    int line=0;
    char c;
    fp=fopen(name,"r");
    while((c=fgetc(fp))!=EOF)
        if(c=='\n') line++;
    fclose(fp);
    return line;
}
void stringCpy(char temp[], char string[][4][61], int index){
    for (int i = 0; i<4; i++) {
        strcpy(temp, string[index][i]);
        strcpy(string[index][i], string[index+1][i]);
        strcpy(string[index+1][i], temp);
    }
}
void shuffle(char string[][4][61], int line){
    char temp[61];
    int rn;
    for (int i = 0; i< line-1; i++) {
        rn = rand() % (line-i) + i;
        for (int j = 0; j<4; j++) {
            strcpy(string[rn][j], string[i][j]);
            strcpy(string[i][j], string[rn][j]);
//            strcpy(string[rn][j], temp);
//            memmove(temp, string[i][j], sizeof(temp));
//            memmove(string[i][j], string[rn][j], sizeof(temp));
//            memmove(string[rn][j], temp, sizeof(temp));
        }
    }
}
void MyFlush(void){
    while (getchar() != '\n') {
        ;
    }
}

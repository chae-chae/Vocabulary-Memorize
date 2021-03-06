//
//  LL써서 메인.c
//  플밍2 플젝
//
//  Created by 채채 on 19/11/2019.
//  Copyright © 2019 chaechae. All rights reserved.
//

#include <time.h>
#include "word.h"
#include <string.h>

int menuScreen(void);
int input(void);
void quiz(void);
void flashCard(void);
void hangMan(void);
void wordBook(FILE *);
void addNewFile(FILE *);
void addNewWord(FILE* ddlp);
void viewWordBook(void);
void viewFileList(void);

int wordBookCnt;

int main(int argc, const char * argv[]) {
    system("clear");
    srand(time(NULL));
    FILE * dicDotList = fopen("dic.list", "at"); // dic.list파일(n.dic가 들어갈 파일 생성)
    char filename[10];
    int dicCheck = 1;
    while (1) {
        sprintf(filename, "%d", dicCheck);
        strcat(filename, ".dic"); // filename[] = "dicCheck.dic"
        FILE *dcptr = fopen(filename, "r");
        if (dcptr == NULL) { // 파일없음
            wordBookCnt = dicCheck - 1;
            break;
        }
        dicCheck++;
    }
    int menusel;
    menusel = menuScreen();
    while (menusel != 5) {
        switch (menusel) {
            case 1: quiz(); break;
            case 2: flashCard(); break;
            case 3: hangMan(); break;
            case 4: wordBook(dicDotList); break;
            default: break;
        }
        menusel = menuScreen();
    }
    system("clear");
    return 0;
}
int menuScreen(void){
    int sel;
    printf(">> 영어 단어 암기 프로그램 <<\n");
    printf("1. 영어 단어 맞추기\t2. 플래쉬카드\n");
    printf("3. 행맨(hangman)\t4. 단어장 관리\n");
    printf("5. 프로그램 종료\n\n");
    sel = input();
    return sel;
}
int input(void){
    int sel;
    while (1) {
        printf("번호를 입력하세요 : ");
        scanf("%d", &sel);
        if (1<= sel && sel <= 5 && getchar() == '\n') {
            break;
        }
        MyFlush();
    }
    return sel;
}
void wordBook(FILE *ddlp){
    int sel;
    system("clear");
    printf(">> 영어 단어 암기 프로그램 : 단어장 관리 <<\n");
    printf("1. 새 파일 추가하기\t2. 새 단어 추가하기\n");
    printf("3. 단어장 보기\t4. 단어 파일 목록보기\n");
    printf("5. 단어장 관리 종료\n\n");
    sel = input();
    while (sel != 5) {
        switch (sel) {
            case 1: addNewFile(ddlp); break; //단어장 만드는 메뉴
            case 2: addNewWord(ddlp); break;
            case 3: viewWordBook(); break;
            case 4: viewFileList(); break;
            default: break;
        }
        printf(">> 영어 단어 암기 프로그램 : 단어장 관리 <<\n");
        printf("1. 새 파일 추가하기\t2. 새 단어 추가하기\n");
        printf("3. 단어장 보기\t4. 단어 파일 목록보기\n");
        printf("5. 단어장 관리 종료\n\n");
        sel = input();
    }
    system("clear");
    return;
}
void addNewFile(FILE* ddlp){
    system("clear");
    printf(">> 영어 단어 암기 프로그램 : 단어장 관리 : 새 파일 추가 <<\n");
    wordBookCnt++; // 단어장 하나 추가
    char filename[10];
    sprintf(filename, "%d", wordBookCnt);
    strcat(filename, ".dic");
    FILE * numDotDic= fopen(filename, "wt"); //새 파일을 쓰기용으로 연다
    List list;
    List* lp = &list;
    createList(lp); // 링크드리스트 초기화
    int max = 0;
    while (max<20) {
        Node temp = {NULL, "", "", "", "", NULL}; // 여기에 임시적으로 저장하고 후에 lp진퉁에 add해줘야함
        char input[300]; //임시로 입력받을 긴 문자열하나
        char *sArr[4] = {NULL, }; // 자른 문자열 포인터 저장할 배열 4칸(최대치를 위해)
        int pmove = 0; // 자른 문자열 포인터 옮겨줄 변수
        fgets(input, sizeof(input), stdin); // 공백포함해서 쭉받고 마지막개행까지받아서
        unsigned long len = strlen(input);
        input[len-1] = '\0'; // 개행빼주는 작업
        char *tokptr = strtok(input, " "); // 문자열 공백마다 분리
        while (tokptr != NULL) { // 옮겨주면서 분리한거 저장
            sArr[pmove] = tokptr;
            pmove++;
            tokptr = strtok(NULL, " ");
        }
        if (!strcmp(sArr[0], ".add")) {// .add 입력종료조건
            break;
        }
        switch (pmove) {
            case 2: // 한글 뜻 한개적었을때
                strcpy(temp.eng, sArr[0]);
                strcpy(temp.kr1, sArr[1]);
                addLast(lp, temp.eng, temp.kr1, temp.kr2, temp.kr3);
                break;
            case 3: // 뜻 두개
                strcpy(temp.eng, sArr[0]);
                strcpy(temp.kr1, sArr[1]);
                strcpy(temp.kr2, sArr[2]);
                addLast(lp, temp.eng, temp.kr1, temp.kr2, temp.kr3);
                break;
            case 4: // 뜻 세개
                strcpy(temp.eng, sArr[0]);
                strcpy(temp.kr1, sArr[1]);
                strcpy(temp.kr2, sArr[2]);
                strcpy(temp.kr3, sArr[3]);
                addLast(lp, temp.eng, temp.kr1, temp.kr2, temp.kr3);
                break;
            default:
                break;
        }
        max++;
    }
    saveList(lp, numDotDic); // n.dic파일 저장
    if (wordBookCnt%6 == 0){
        fprintf(ddlp, "\n");
    }
    fprintf(ddlp, "%s ", filename); //dic.list 에 n.dic 이라고 이어서 씀
    fflush(ddlp);
    fclose(numDotDic); // n.dic 닫아주기
    system("clear");
    destroyList(lp);
    return;
}
void addNewWord(FILE* ddlp){
    system("clear");
    printf(">> 영어 단어 암기 프로그램 : 단어장 관리 : 새 단어 추가 <<\n");
    int input;
    printf("파일명(일차) : ");
    scanf("%d", &input);
    char filename[10];
    sprintf(filename, "%d", input);
    strcat(filename, ".dic");
    FILE *numDotDic = fopen(filename, "at");
    printf("%s 열기 성공\n", filename);
    MyFlush();
    List list;
    List* lp = &list;
    createList(lp);
    int max = 0;
    while (max<20) {
        char input[300]; //임시로 입력받을 긴 문자열하나
        char *sArr[4] = {NULL, }; // 자른 문자열 포인터 저장할 배열 4칸(최대치를 위해)
        int pmove = 0; // 자른 문자열 포인터 옮겨줄 변수
        Node temp = {NULL, "", "", "", "", NULL}; // 여기에 임시적으로 저장하고 후에 lp진퉁에 add해줘야함
        fgets(input, sizeof(input), stdin); // 공백포함해서 쭉받고 마지막개행까지받아서
        unsigned long len = strlen(input);
        input[len-1] = '\0'; // 개행빼주는 작업
        char *tokptr = strtok(input, " "); // 문자열 공백마다 분리
        while (tokptr != NULL) { // 옮겨주면서 분리한거 저장
            sArr[pmove] = tokptr;
            pmove++;
            tokptr = strtok(NULL, " ");
        }
        if (!strcmp(sArr[0], ".add")) {// .add 입력종료조건
            //            printf(".add로 종료됨\n");
            break;
        }
        switch (pmove) {
            case 2: // 한글 뜻 한개적었을때
                strcpy(temp.eng, sArr[0]);
                strcpy(temp.kr1, sArr[1]);
                addLast(lp, temp.eng, temp.kr1, temp.kr2, temp.kr3);
                break;
            case 3: // 뜻 두개
                strcpy(temp.eng, sArr[0]);
                strcpy(temp.kr1, sArr[1]);
                strcpy(temp.kr2, sArr[2]);
                addLast(lp, temp.eng, temp.kr1, temp.kr2, temp.kr3);
                break;
            case 4: // 뜻 세개
                strcpy(temp.eng, sArr[0]);
                strcpy(temp.kr1, sArr[1]);
                strcpy(temp.kr2, sArr[2]);
                strcpy(temp.kr3, sArr[3]);
                addLast(lp, temp.eng, temp.kr1, temp.kr2, temp.kr3);
                break;
            default:
                break;
        }
        max++;
    }
    saveList(lp, numDotDic); // n.dic파일 저장
    fclose(numDotDic); // n.dic 닫아주기
    system("clear");
    destroyList(lp);
}
void viewWordBook(void){
    int input;
    long long size; // 혹시 모자랄수도 있으니까
    char *wordBook;
    unsigned long whatByte;
    printf("파일명(일차) : ");
    scanf("%d", &input);
    char filename[10];
    sprintf(filename, "%d", input);
    strcat(filename, ".dic");
    FILE *numDotDic= fopen(filename, "r"); //새 파일을 읽기용으로 연다
    if (numDotDic == NULL) {
        printf("%s 읽기 실패\n", filename);
        return;
    }
    fseek(numDotDic, 0, SEEK_END);
    size = ftell(numDotDic);
    wordBook = malloc(size+1); // 널문자
    memset(wordBook, 0, size + 1);  // 파일 크기 + 1바이트만큼 메모리를 0으로 초기화
    fseek(numDotDic, 0, SEEK_SET); // 다시 처음으로 돌리기
    whatByte = fread(wordBook, size, 1, numDotDic);
    printf("\n---------단어장--------\n%s\n", wordBook);
    free(wordBook);
}
void viewFileList(void){
    long long size; // 혹시 모자랄수도 있으니까
    char *wordBookList;
    unsigned long whatByte;
    FILE *dicList= fopen("dic.list", "r"); //새 파일을 읽기용으로 연다
    if (dicList == NULL) {
        printf("읽기 실패\n");
        return;
    }
    fseek(dicList, 0, SEEK_END);
    size = ftell(dicList);
    wordBookList = malloc(size+1); // 널문자
    memset(wordBookList, 0, size + 1);  // 파일 크기 + 1바이트만큼 메모리를 0으로 초기화
    fseek(dicList, 0, SEEK_SET); // 다시 처음으로 돌리기
    whatByte = fread(wordBookList, size, 1, dicList);
    printf("\n---------단어 파일 목록--------\n%s\n", wordBookList);
    free(wordBookList);
}

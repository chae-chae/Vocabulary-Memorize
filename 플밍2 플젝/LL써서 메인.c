//
//  LL써서 메인.c
//  플밍2 플젝
//
//  Created by 채채 on 19/11/2019.
//  Copyright © 2019 chaechae. All rights reserved.
//

#include <time.h>
#include "word.h"

int menuScreen(void);
int input(void);
void MyFlush(void);
//void quiz(void);
//void flashCard(void);
//void hangMan(void);
void wordBook(List *, BOOL*);
void addNewFile(List *, BOOL *);
void addNewWord(void);
void viewWordBook(void);
void viewFileList(void);


//typedef struct _word{
//    char eng[15];
//    char kor1[30], kor2[30], kor3[30];
//} Word;
//typedef struct _list{
//    int cnt;
//    Word *wp;
//} List;
//


int main(int argc, const char * argv[]) {
//    int dicNum = 0;
    
    List list; //dic.list로 저장해야할것
    BOOL bres;
    
    int menusel;
    menusel = menuScreen();
    while (menusel != 5) {
        switch (menusel) {
//            case 1: quiz(); break;
//            case 2: flashCard(); break;
//            case 3: hangMan(); break;
            case 4: wordBook(&list, &bres); break;
            default: break;
        }
        menusel = menuScreen();
    }
//    clear(); // 리눅스에서 해줘야함!! 까먹지말기
    return 0;
}

void MyFlush(void){
    while (getchar() != '\n') {
        ;
    }
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
void wordBook(List *lp, BOOL *bp){
    int sel;
//    clear(); // 리눅스해주기
    
    printf(">> 영어 단어 암기 프로그램 : 단어장 관리 <<\n");
    printf("1. 새 파일 추가하기\t2. 새 단어 추가하기\n");
    printf("3. 단어장 보기\t4. 단어 파일 목록보기\n");
    printf("5. 단어장 관리 종료\n\n");
    
    sel = input();
    while (sel != 5) {
        switch (sel) {
            case 1: addNewFile(lp, bp); break;
            case 2: addNewWord(); break;
            case 3: viewWordBook(); break;
            case 4: viewFileList(); break;
            default: break;
        }
        sel = input();
    }
    return;
}
void addNewFile(List* lp, BOOL* bp){
    *bp = createList(lp);
    if (*bp == TRUE) printf("list 생성 성공\n");
    else printf("list 생성 실패\n");
    
}
void addNewWord(void){
    
}
void viewWordBook(void){
    
}
void viewFileList(void){
    
}

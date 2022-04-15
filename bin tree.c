#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <windows.h>
#include <locale.h>

#define WHITE 15
#define DARKGREY 8
typedef struct Array {
    int data;
    struct Array* left;
    struct Array* right;
} TreeStruct;
typedef TreeStruct* TreeElem;
typedef TreeElem* ElemPtr;
 
int ScanInt(int* valuePtr) {
    int scanCount = scanf("%d", valuePtr);
    if (scanCount) return 1;
    if (getc(stdin) != '\n') return 0;
    return 0;
}


TreeElem CreateElem(int val) {
    TreeElem thisTree = (TreeElem)malloc(sizeof(TreeElem));
    thisTree->data = val;
    thisTree->left = NULL;
    thisTree->right = NULL;
    return thisTree;
}
void DeleteList(ElemPtr head) {
    //
}

int GetValue() {
    int value = -1;
    printf("\n  Enter a value: ");
    while (ScanInt(&value) == 0 || value < 0) {
        system("cls");
        printf("\n  Enter a value: ");
    };
    return value;
}
void Push(ElemPtr head) {
    int value = GetValue();
    if (*head == NULL) {
        *head = CreateElem(2);
        return;
    }


    
}

// General funcs
void PrintMenu(int isEmpty) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("\n"); 
    printf("  1. Append an element to tree.\n");
    if (isEmpty) SetConsoleTextAttribute(hConsole, DARKGREY);
    printf("  2. Delete element by value.\n");
    printf("  3. Print elements goint to width.\n");
    if (isEmpty) SetConsoleTextAttribute(hConsole, WHITE);
    printf("  4. Exit.\n");
    printf("\n  ");
}
void StepBack() {
    printf("\n  Press any button to continue...");
    getch();
}

void Menu(ElemPtr head) {
    while (1) {
        int isEmpty = 0;
        if (*head == NULL) isEmpty = 1;
        system("cls");
        PrintMenu(isEmpty);
        char option;
        scanf("%s", &option);
        system("cls");
        switch (option) {
            case('1'): {
                Push(head);
                break;
            }
            case('2'): {
                if (isEmpty) continue;
                // DeleteByValue(head);
                break;
            }
            case('3'): {
                if (isEmpty) continue;
                // FindMinMax(head);
                break;
            }
            case('4'): {
                // exit
                return;
            }
            default: {
                break;
            }
        }
        StepBack();
    }
}


int main() {
    srand(time(0));
    system("chcp 1251"); 
    system("cls");

    TreeElem head = NULL;
    Menu(&head); 


    system("pause");
   // DeleteList(&head);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <windows.h>

#define WHITE 15 
#define DARKGREY 8
typedef struct Array {
    int val; 
    struct Array* next;
} List;
typedef List* ListPtr;

int  ScanInt(int* valuePtr) {
    int scanCount = scanf("%d", valuePtr);
    if (scanCount) return 1;
    if (getc(stdin) != '\n') return 0;
    return 0;
}


ListPtr CreateElem(int val) {
    ListPtr thisList = (ListPtr)malloc(sizeof(List));
    thisList->val = val;
    thisList->next = NULL;
    return thisList;
} 
void DeleteQueue(ListPtr list) {
    //...
}
 
void Print(ListPtr list) {
    ListPtr temp = list;
    printf("\n  Список: { ");
    while (temp->next != NULL) {
        printf("%d, ", temp->val);
        temp = temp->next;
    }
    printf("%d };", temp->val);
}
void PrintReverse(ListPtr list) {
    printf("\n  Реверснутый список: { ");
    ListPtr tList = list;
    while (tList->next != NULL)
        tList = tList->next;
    // finds last elem and print it;
    while (tList != list) {
        printf("%d, ", tList->val);
        ListPtr tList_2 = list;
        while (tList_2->next != tList)
            tList_2 = tList_2->next;
        tList = tList_2;
    }
    printf("%d", list->val);
    printf(" }; \n");
}

void PushBack(ListPtr list) { 
    if (list->val == -1) {
        *list = *CreateElem(rand() % 100);
        Print(list);
        return;
    }
    ListPtr newElem = CreateElem(rand() % 100);
    ListPtr tList = list; 
    while (tList->next != NULL)
        tList = tList->next;
    tList->next = newElem;
    Print(list);
}
int DeleteElement(ListPtr list, ListPtr elem) {
    if (elem == list) {  
        if (list->next == NULL) {
            list->val = -1;
            return 0;
        }
        *list = *list->next; 
        return 2;
    }
    ListPtr tList = list;
    while (tList->next != elem) {
        tList = tList->next;
        if (tList == NULL) return 1;
    }
    (tList->next) = (tList->next)->next;
    return 0;
}
void DeleteByValue(ListPtr list) {
    int value = -1;
    Print(list);
    printf("\n  Введите значение, по которому будут удалены элементы [0, 99]: ");
    while (ScanInt(&value) < 0 || value > 100 || value < 0) {
        system("cls");
        printf("\n  Введите корректное значение [0, 99]: ");
    }
    int errorCode = 0;
    ListPtr tList = list;
    while (tList != NULL) {
        if (tList->val == value)
            errorCode = DeleteElement(list, tList);
        tList = tList->next;
    }  
    if (errorCode = 2) {
        printf("Список: { }"); 
        return;
    }
    Print(list);
}
void FindMinMax(ListPtr list) {
    Print(list);
    int min = list->val; int max = list->val;
    ListPtr tList = list;
    while (tList != NULL) {
        if (tList->val > max) max = tList->val;
        if (tList->val < min) min = tList->val;
        tList = tList->next;
    }

    printf("\n  Max: %d, Min: %d", max, min);
}

// General funcs
void PrintMenu(int isEmpty) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("\n");
    printf("  1. Добавить в список элемент.\n");
    if (isEmpty) SetConsoleTextAttribute(hConsole, DARKGREY);
    printf("  2. Удалить элементы по значению.\n");
    printf("  3. Найти min/max.\n");
    printf("  4. Поменять min/max.\n");
    printf("  5. Вывести элементы списка.\n");
    printf("  6. Вывести элементы списка reverse.\n");
    if (isEmpty) SetConsoleTextAttribute(hConsole, WHITE);
    printf("  7. Выйти.\n"); 
    printf("\n  ");
}
void StepBack() {
    printf("\n  Для продолжения нажмите любую клавишу...");
    getch();
}

void Menu(ListPtr list) {
    while (1) {
        int isEmpty = 0;
        if (list->val == -1) isEmpty = 1;
        system("cls");
        PrintMenu(isEmpty);
        char option;
        scanf("%s", &option);
        system("cls");
        switch (option) {
            case('1'): { 
                PushBack(list);
                break;
            }
            case('2'): { 
                if (isEmpty) continue;
                DeleteByValue(list);
                break;
            }
            case('3'): { 
                if (isEmpty) continue;
                FindMinMax(list);
                break;
            }
            case('4'): { 
                if (isEmpty) continue;
                break;
            }
            case('5'): { 
                if (isEmpty) continue;
                Print(list);
                break;
            }
            case('6'): { 
                if (isEmpty) continue;
                PrintReverse(list);
                break;
            }
            case('7'): {
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

     
    ListPtr list = CreateElem(-1); 

    Menu(list);


    system("pause");
    DeleteQueue(list);
    return 0;
}

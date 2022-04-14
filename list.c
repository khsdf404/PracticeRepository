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

int ScanInt(int* valuePtr) {
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
void DeleteList(ListPtr head) { 
    while (head != NULL) {
        free(*head);
        head = head->next;
    }
}
 
void Print(ListPtr head) {
    ListPtr elem = head;
    printf("\n  Список: { ");
    while (elem->next != NULL) {
        printf("%d, ", elem->val);
        elem = elem->next;
    }
    printf("%d };", elem->val);
}
void PrintReverse(ListPtr head) {
    printf("\n  Реверснутый список: { ");
    ListPtr elem = head;
    while (elem->next != NULL)
        elem = elem->next;
    // finds last elem and print it;
    while (elem != head) {
        printf("%d, ", elem->val);
        ListPtr tElem = head;
        while (tElem->next != elem)
            tElem = tElem->next;
        elem = tElem;
    }
    printf("%d", head->val);
    printf(" }; \n");
}

void PushBack(ListPtr head) { 
    if (head->val == -1) {
        *head = *CreateElem(rand() % 100);
        Print(head);
        return;
    }
    ListPtr newElem = CreateElem(rand() % 100);
    ListPtr elem = head;
    while (elem->next != NULL)
        elem = elem->next;
    elem->next = newElem;
    Print(head);
}
int DeleteElement(ListPtr head, ListPtr deletingElem) {
    if (deletingElem == head) {
        if (head->next == NULL) {
            head->val = -1;
            return 0;
        }
        *head = *head->next;
        return 2;
    }
    ListPtr elem = head;
    while (elem->next != deletingElem) {
        elem = elem->next;
        if (elem == NULL) return 1;
    }
    (elem->next) = (elem->next)->next;
    return 0;
}
void DeleteByValue(ListPtr head) {
    int value = -1;
    Print(head);
    printf("\n  Введите значение, по которому будут удалены элементы [0, 99]: ");
    while (ScanInt(&value) < 0 || value > 100 || value < 0) {
        system("cls");
        printf("\n  Введите корректное значение [0, 99]: ");
    }
    int errorCode = 0;
    ListPtr elem = head;
    while (elem != NULL) {
        if (elem->val == value)
            errorCode = DeleteElement(head, elem);
        elem = elem->next;
    }  
    if (errorCode = 2) {
        printf("Список: { }"); 
        return;
    }
    Print(head);
}
void FindMinMax(ListPtr head) {
    Print(head);
    int min = head->val; int max = head->val;
    ListPtr elem = head;
    while (elem != NULL) {
        if (elem->val > max) max = elem->val;
        if (elem->val < min) min = elem->val;
        elem = elem->next;
    }

    printf("\n  Min: %d, Max: %d", min, max);
}
void SwapMinMax(ListPtr head) {
    Print(head);
    int min = head->val; int max = head->val;
    ListPtr minPtr = head; ListPtr maxPtr = head;
    ListPtr elem = head;
    while (elem != NULL) {
        if (elem->val > max) {
            max = elem->val;
            maxPtr = elem;
        }
        if (elem->val < min) {
            min = elem->val;
            minPtr = elem;
        }
        elem = elem->next;
    }
    int tVal = minPtr->val;
    minPtr->val = maxPtr->val;
    maxPtr->val = tVal;
    printf("\n  Min: %d, Max: %d", min, max);
    Print(head);
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

void Menu(ListPtr head) {
    while (1) {
        int isEmpty = 0;
        if (head->val == -1) isEmpty = 1;
        system("cls");
        PrintMenu(isEmpty);
        char option;
        scanf("%s", &option);
        system("cls");
        switch (option) {
            case('1'): { 
                PushBack(head);
                break;
            }
            case('2'): { 
                if (isEmpty) continue;
                DeleteByValue(head);
                break;
            }
            case('3'): { 
                if (isEmpty) continue;
                FindMinMax(head);
                break;
            }
            case('4'): { 
                if (isEmpty) continue;
                SwapMinMax(head);
                break;
            }
            case('5'): { 
                if (isEmpty) continue;
                Print(head);
                break;
            }
            case('6'): { 
                if (isEmpty) continue;
                PrintReverse(head);
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

     
    ListPtr head = CreateElem(-1);  
    Menu(head);


    system("pause");
    DeleteList(head);
    return 0;
}

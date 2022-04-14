#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>


typedef struct Array {
    int val; 
    struct Array* next;
} List;
typedef List* ListPtr;


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
void PushBack(ListPtr list) {
    ListPtr temp13 = list;
    printf("\n  Список: { ");
    while (temp13->next != NULL) {
        printf("%d, ", temp13->next);
        temp13 = temp13->next;
    }
    printf("%d };", temp13->next);

    ListPtr newElem = CreateElem(rand() % 100);
    ListPtr temp = list;
    printf("\n%d\n", (list->next)->next);
    printf("\n\n%d\n", temp);
    printf("%d\n", list);
    printf("%d\n", temp->next);
    printf("%d\n", list->next);
    while (temp->next != NULL)
        temp = temp->next;
    printf("%d\n", temp);
    printf("%d\n", list);
    printf("%d\n", list->next);
    printf("%d\n", temp->next);
    temp->next = newElem;
    printf("%d\n", list->next);
    printf("\n%d\n", (list->next)->next);
    printf("\n%d\n", newElem);

    printf("\n%d\n", newElem->next == NULL);
    Print(list);

    Print(list);
}



// General funcs
void PrintMenu() {
    printf("\n");
    printf("  1. Добавить в список элемент.\n");
    printf("  2. Удалить элементы по значению.\n");
    printf("  3. Найти min/max.\n");
    printf("  4. Поменять min/max.\n");
    printf("  5. Вывести элементы списка.\n");
    printf("  6. Вывести элементы списка reverse.\n");
    printf("  7. Выйти.\n");
    printf("\n  ");
}
void StepBack() {
    printf("\n  Для продолжения нажмите любую клавишу...");
    getch();
}
// Menu
void Menu(ListPtr list) {
    while (1) {
        system("cls");
        PrintMenu();
        char option;
        scanf("%s", &option);
        system("cls");
        switch (option) {
            case('1'): { 
                PushBack(list);
                break;
            }
            case('2'): {  
                break;
            }
            case('3'): { 
                break;
            }
            case('4'): { 
                break;
            }
            case('5'): { 
                Print(list);
                break;
            }
            case('6'): { 
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
    ListPtr list2 = CreateElem(99);
    list->next = list2; 

    Menu(list);


    system("pause");
    DeleteQueue(list);
    return 0;
}

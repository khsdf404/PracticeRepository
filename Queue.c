#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <windows.h>

#define WHITE 15 
#define DARKGREY 8
#define SUCCESS 1
#define EMPTY_SIZE_ERROR -1 
#define EMPTY_SIZE_MSG printf("\n  Error: not enough size for it!\n")
#define REALLOC_ERROR -2
#define REALLOC_MSG printf("\n  Error: realloc was finished with NULL ptr!\n")


typedef int* arr_p;
typedef struct Array {
    arr_p ptr;
    int size;
    int head;
    int tale;
} Queue;
typedef Queue* QueuePtr;


// FoolProof get int func
int  ScanInt(int* valuePtr) {
    int scanCount = scanf("%d", valuePtr);
    if (scanCount) return 1;
    return getc(stdin) != '\n';
}


// Dynamic's array funcs

Queue CreateQueue() {
    Queue thisQueue;
    int* dynamicArr = (int*)calloc(1, sizeof(int));
    thisQueue.ptr = dynamicArr;
    thisQueue.size = 0;
    thisQueue.head = 0;
    thisQueue.tale = -1;
    return thisQueue;
    //67012345 
    // (head + size + 1)%head == head => tale bites head
}
int ReallocQueue(QueuePtr queue, int newSize) {
    int* tmp_ptr = (int*)realloc(queue->ptr, newSize * sizeof(int));
    if (tmp_ptr != NULL || newSize == 0) {
        queue->ptr = tmp_ptr;
        queue->size = newSize;
    }
    return (tmp_ptr != NULL || queue->size == 0);
}
void DeleteQueue(QueuePtr queue) {
    queue->size = 0;
    free(queue->ptr);
    queue = NULL;
}

// это база
Queue GetPrimaryState(QueuePtr queue) {
    Queue currQueue = CreateQueue();
    if (!ReallocQueue(&currQueue, queue->size))
        return *queue;
    for (int i = 0; i < queue->size; i++)
        currQueue.ptr[i] = queue->ptr[i];
    return currQueue;
}
int Pop(QueuePtr queue) {
     
}
int Push(QueuePtr queue, int newValue) { 
    // CheckRealloc(queue->size, queue->head);
    int head = queue->head;
    int size = queue->size;
    queue->ptr[(head + size + 1) % head] = newValue;
    return SUCCESS;
}
/*
int WasError(int errorCode, StackPtr stack, StackPtr primaryStack) {
    if (errorCode >= SUCCESS) return 0;
    if (errorCode == REALLOC_ERROR) REALLOC_MSG;
    if (errorCode == EMPTY_SIZE_ERROR) EMPTY_SIZE_MSG;

    printf("%d, %d, %d", errorCode, stack->size, primaryStack->size);

    DeleteStack(stack);
    *stack = CreateStack();
    stack->size = primaryStack->size;
    for (int i = 0; i < stack->size; i++)
        stack->ptr[i] = primaryStack->ptr[i];


    *primaryStack = GetPrimaryState(stack);
    if (primaryStack == stack) return REALLOC_ERROR;

    return 1;
}
*/


// General funcs
void PrintMenu() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("\n");
    printf("  1. Очистить очередь.\n");
    printf("  2. Добавить элемент в очередь.\n");
    printf("  3. Удалить элемент очереди.\n");
    // if (arr->size == 0) SetConsoleTextAttribute(hConsole, DARKGREY);
    printf("  4. Поменять местами два верхних элемента.\n");
    printf("  5. Удалить нижний элемент стека.\n");
    printf("  6. Поменять местами верхний и нижний элементы стека.\n");
    // if (arr->size == 0) SetConsoleTextAttribute(hConsole, WHITE);
    printf("  7. Выйти.\n");
    printf("\n  ");
}
void StepBack() {
    printf("\n  Для продолжения нажмите любую клавишу...");
    getch();
}
// Menu
void Menu(QueuePtr stack, QueuePtr primaryStack) {
    while (1) {
        system("cls");
        PrintMenu();
        char option;
        scanf("%s", &option);
        system("cls");
        switch (option) {
        case('1'): {
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
       // PrintStack(stack);
        StepBack();
    }
}


int main() {
    srand(time(0));
    system("chcp 1251");
    system("cls");


    Queue queue = CreateQueue();
    Queue primaryQueue = CreateQueue();
    Menu(&queue, &primaryQueue);


    system("pause");
    DeleteQueue(&queue);
    DeleteQueue(&primaryQueue);
    return 0;
}


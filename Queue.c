#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

#define WHITE 15 
#define DARKGREY 8
#define SUCCESS 1
#define EMPTY_SIZE_ERROR -1 
#define EMPTY_SIZE_MSG printf("\n  Error: not enough size for it!\n")
#define REALLOC_ERROR -2
#define REALLOC_MSG printf("\n  Error: realloc was finished with NULL ptr!\n")
#define SIZE_MULT 2

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
    int* dynamicArr = (int*)calloc(10, sizeof(int));
    thisQueue.ptr = dynamicArr;
    thisQueue.size = 10;
    thisQueue.head = 0;
    thisQueue.tale = 0;
    return thisQueue;
}
int ReallocQueue(QueuePtr queue, int newSize) {
    int* tmp_ptr = (int*)realloc(queue->ptr, newSize * sizeof(int));
    if (tmp_ptr != NULL || newSize == 0) {
        queue->ptr = tmp_ptr;
        queue->size = newSize;
    }
    return (tmp_ptr != NULL || queue->size == 0);
}
int ReallocChecker() {
    // 340000001
    // s=2; [4]-[1] = 3; 3*2=6;

}
void DeleteQueue(QueuePtr queue) { 
    free(queue->ptr);
    queue->size = 0;
    queue->head = 0;
    queue->tale = 0; 
    queue = NULL;
}

// это база
Queue GetPrimaryState(QueuePtr queue) {
    Queue currQueue = CreateQueue();
    if (!ReallocQueue(&currQueue, queue->size))
        return *queue; 
    for (int i = 0; i < queue->size; i++)
        currQueue.ptr[i] = queue->ptr[i];
    currQueue.size = queue->size;
    currQueue.head = queue->head;
    currQueue.tale = queue->tale;
    return currQueue;
}
int Pop(QueuePtr queue) {
    // CheckRealloc(queue->size, queue->head); 
    if (queue->head == -1) {
        return EMPTY_SIZE_ERROR;
    }
    int head = queue->head;
    int headVal = queue->ptr[head];
    queue->ptr[head] = -1;
    if (queue->head == queue->tale) {
        queue->head = -1;
        queue->tale = -1;
        return headVal;
    }
    queue->head = (head + 1) % queue->size; 
    return headVal; 
}
int Push(QueuePtr queue, int newValue) { 
    // CheckRealloc(queue->size, queue->head);
    // check tale + 1 == head case 
    int size = queue->size;
    int tale = queue->tale;
    queue->ptr[(tale + 1) % size] = abs(newValue);
    queue->tale = (tale + 1) % size;
    return abs(newValue);
}
int WasError(int errorCode, QueuePtr queue, QueuePtr primQueue) {
    if (errorCode >= SUCCESS) return 0;
    if (errorCode == REALLOC_ERROR) REALLOC_MSG;
    if (errorCode == EMPTY_SIZE_ERROR) EMPTY_SIZE_MSG;

    printf("%d, %d, %d", errorCode, queue->size, primQueue->size);

    DeleteQueue(queue);
    *queue = CreateQueue();
    queue->size = primQueue->size; // realloc
    queue->head = primQueue->head;
    queue->tale = primQueue->tale;
    for (int i = 0; i < stack->size; i++)
        queue->ptr[i] = primQueue->ptr[i];


    *primQueue = GetPrimaryState(queue);
    if (primQueue == queue) return REALLOC_ERROR;

    return 1;
} 

int SplitZeros(QueuePtr queue) {
    Queue copyQueue = GetPrimaryState(queue); // check errors
    Queue tempQueue = CreateQueue(); // check errors

    int elem = Pop(copyQueue); // check errors
    while (elem > 0) { // while (Pop != ERROR)
        Push(tempQueue, elem); // check errors
        Push(tempQueue, 0); // check errors
        elem = Pop(copyQueue); // check errors 
    }
    DeleteQueue(queue);
    queue = &copyQueue; 
}
int PopBack(QueuePtr queue) {
    Queue copyQueue = GetPrimaryState(queue); // check errors
    Queue tempQueue = GetPrimaryState(queue); // check errors
    Queue tempQueue2;
    // {1,2,3,4,_,_}
     

     // 1 elem
    tempQueue2 = GetPrimaryState(copyQueue);
    Pop(tempQueue2);
    if (Pop(tempQueue2) < 0) return -3;
    // default
    int elem = Pop(copyQueue);
    while (1) { // while (Pop != ERROR)  
        Push(tempQueue, elem); // check errors 
        elem = Pop(copyQueue); // check errors  
        
        tempQueue2 = GetPrimaryState(copyQueue);
        Pop(tempQueue2);
        if (Pop(tempQueue2) < 0) break;  
    }
    DeleteQueue(tempQueue2);



}



// General funcs
void PrintMenu() {
    printf("\n");
    printf("  1. Очистить очередь.\n");
    printf("  2. Добавить элемент в очередь.\n");
    printf("  3. Удалить элемент очереди.\n");
    printf("  4. После каждого элемента поставить 0.\n");
    printf("  5. Удалить хвост.\n");
    printf("  6. Поменять местами голову и хвост.\n");
    printf("  7. Выйти.\n");
    printf("\n  ");
}
void StepBack() {
    printf("\n  Для продолжения нажмите любую клавишу...");
    getch();
}
// Menu
void Menu(QueuePtr queue, QueuePtr primQueue) {
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


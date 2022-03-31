#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

#define WHITE 15 
#define DARKGREY 8
#define SUCCESS 1
#define EMPTY_SIZE_ERROR -1 
#define EMPTY_SIZE_MSG printf("\n  Error: not enough size for that  !\n")
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
 

Queue CreateQueue() {
    Queue thisQueue;
    int* dynamicArr = (int*)calloc(10, sizeof(int));
    thisQueue.ptr = dynamicArr;
    thisQueue.size = 10;
    thisQueue.head = -1;
    thisQueue.tale = -1;
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
int ReallocChecker(QueuePtr queue) {
    int head = queue->head;
    int tale = queue->tale;
    int size = queue->size;
    // {tale, _, head, zalupa, _, _, _, _}
    if ((tale + 1) % size == head) {
        if (tale > head) 
            return ReallocQueue(queue, size * 2);  
        else {
            if (!ReallocQueue(queue, size * 2)) return REALLOC_ERROR;
            for (int i = 0; (head + i + size) < size * 2; i++) {
                queue->ptr[head + i] = queue->ptr[head + i + size];
            }
        }
    }
    return SUCCESS;
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
    ReallocChecker(queue);
    int size = queue->size;
    int tale = queue->tale;
    queue->ptr[(tale + 1) % size] = abs(newValue);
    queue->tale = (tale + 1) % size;
    if (queue->head == -1) queue->head = queue->tale;
    return abs(newValue);
}
void WasError(int errorCode, QueuePtr queue) {
    if (errorCode >= SUCCESS) return 0;
    if (errorCode == REALLOC_ERROR) REALLOC_MSG;
    if (errorCode == EMPTY_SIZE_ERROR) EMPTY_SIZE_MSG;  
    return 1;
} 

int SplitZeros(QueuePtr queue) {
    Queue copyQueue = GetPrimaryState(queue); // check errors
    Queue tempQueue = CreateQueue(); // check errors

    int elem = Pop(&copyQueue); // check errors
    while (elem > 0) { // while (Pop != ERROR)
        Push(&tempQueue, elem); // check errors
        Push(&tempQueue, 0); // check errors
        elem = Pop(&copyQueue); // check errors 
    }
    DeleteQueue(queue);
    DeleteQueue(&tempQueue);
    queue = &copyQueue; 
    return SUCCESS;
}
int PopBack(QueuePtr queue) {
    Queue tempQueue2 = GetPrimaryState(queue); // check errors
    int maybeTale = Pop(&tempQueue2);
    // 0 elem 
    if (maybeTale < 0) {
        DeleteQueue(&tempQueue2);
        return -3; // need to think of error code here
    }
    // 1 elem
    if (Pop(&tempQueue2) < 0) {
        *queue = CreateQueue(); // check errors
        DeleteQueue(&tempQueue2);
        return maybeTale;
    } 
    // default
    Queue copyQueue = GetPrimaryState(queue); // check errors
    Queue tempQueue = GetPrimaryState(queue); // check errors 
    int elem = Pop(&copyQueue);
    while (1) { // while (Pop != ERROR)   
        Push(&tempQueue, elem); // check errors 
        tempQueue2 = GetPrimaryState(&copyQueue); // check errors
        maybeTale = Pop(&tempQueue2); 
        if (Pop(&tempQueue2) < 0) break;   
        elem = Pop(&copyQueue); // check errors  
    } 
    DeleteQueue(queue);
    DeleteQueue(&copyQueue);
    DeleteQueue(&tempQueue2);
    queue = &tempQueue;
    return maybeTale;
}
int SwapEdges(QueuePtr queue) {
    Queue copyQueue = GetPrimaryState(queue); // check errors
    Queue tempQueue = CreateQueue(); // check errors
    int tale = PopBack(&copyQueue); // check errors
    int head = Pop(&copyQueue);// check errors
    
    Push(&tempQueue, tale);
    int elem = Pop(&copyQueue); // check errors
    while (elem > 0) {
        Push(&tempQueue, elem); // check errors
        Push(&tempQueue, 0); // check errors
        elem = Pop(&copyQueue); // check errors 
    }
    Push(&tempQueue, head); // check errors 

    return SUCCESS;
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
void Menu(QueuePtr queue) {
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
    Menu(&queue);


    system("pause");
    DeleteQueue(&queue);
    return 0;
}


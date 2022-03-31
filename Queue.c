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
 

Queue CreateQueue() {
    Queue thisQueue;
    int* dynamicArr = (int*)calloc(10, sizeof(int)); // idk if this could return an error 
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
        printf("#");
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

// base funcs
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
    if (queue->head == -1) return EMPTY_SIZE_ERROR; 
    int head = queue->head;
    int headVal = queue->ptr[head];
    queue->ptr[head] = 0;
    if (queue->head == queue->tale) {
        queue->head = -1;
        queue->tale = -1;
        return headVal;
    }
    queue->head = (head + 1) % queue->size; 
    return headVal; 
}
int Push(QueuePtr queue, int newValue) { 
    if (!ReallocChecker(queue)) return REALLOC_ERROR;
    int size = queue->size;
    int tale = queue->tale;
    queue->ptr[(tale + 1) % size] = abs(newValue);
    queue->tale = (tale + 1) % size;
    if (queue->head == -1) queue->head = queue->tale;
    return abs(newValue);
}
int WasError(int errorCode) {
    if (errorCode >= 0) return 0;
    if (errorCode == REALLOC_ERROR) REALLOC_MSG;
    if (errorCode == EMPTY_SIZE_ERROR) EMPTY_SIZE_MSG;  
    return 1;
} 

// addit funcs
int SplitZeros(QueuePtr queue) {
    Queue copyQueue = GetPrimaryState(queue);
        if (&copyQueue == queue) return REALLOC_ERROR;
    Queue tempQueue = CreateQueue(); // if (&tempQueue == queue) return REALLOC_ERROR;
     
    int elem = Pop(&copyQueue);  
    while (elem >= 0) {  
        if (Push(&tempQueue, elem) < 0) return REALLOC_ERROR;  
        if (Push(&tempQueue,    0) < 0) return REALLOC_ERROR;
        elem = Pop(&copyQueue);  
    }
    DeleteQueue(queue);
    DeleteQueue(&copyQueue);
    *queue = tempQueue; 
    return SUCCESS;
}
int PopBack(QueuePtr queue) {
    Queue tempQueue2 = GetPrimaryState(queue);
        if (&tempQueue2 == queue) return REALLOC_ERROR;
    int maybeTale = Pop(&tempQueue2); 
    // 0 elem 
    if (maybeTale < 0) {
        DeleteQueue(&tempQueue2);
        return EMPTY_SIZE_ERROR;  
    }
    // 1 elem
    if (Pop(&tempQueue2) < 0) {
        Pop(queue);
        return maybeTale;
    } 
    // default
    Queue copyQueue = GetPrimaryState(queue);
        if (&copyQueue == queue) return REALLOC_ERROR;
    Queue tempQueue = CreateQueue(); // if (&tempQueue == queue) return REALLOC_ERROR;  

    int elem = Pop(&copyQueue); 
    while (1) { 
        if (Push(&tempQueue, elem) < 0) return REALLOC_ERROR; 
        tempQueue2 = GetPrimaryState(&copyQueue); 
            if (&tempQueue2 == &copyQueue) return REALLOC_ERROR;
        maybeTale = Pop(&tempQueue2); 
        if (Pop(&tempQueue2) < 0) break;   
        elem = Pop(&copyQueue); 
    }  
    DeleteQueue(queue);
    DeleteQueue(&copyQueue);
    DeleteQueue(&tempQueue2);  
    *queue = tempQueue; 
    return maybeTale;
}
int SwapEdges(QueuePtr queue) {
    Queue copyQueue = GetPrimaryState(queue); 
        if (&copyQueue == queue) return REALLOC_ERROR;
    Queue tempQueue = CreateQueue(); // if (&tempQueue == queue) return REALLOC_ERROR;
    int tale = PopBack(&copyQueue); 
        if (tale < 0) return tale;
    int head = Pop(&copyQueue); 
        if (head < 0) return head;
    
    if (Push(&tempQueue, tale) < 0) return REALLOC_ERROR;
    int elem = Pop(&copyQueue); // check errors
    while (elem >= 0) {
        if (Push(&tempQueue, elem) < 0) return REALLOC_ERROR; 
        elem = Pop(&copyQueue);
    }
    if (Push(&tempQueue, head) < 0) return REALLOC_ERROR; 

    *queue = tempQueue;
    return tale;
}
int PrintQueue(QueuePtr queue) { 
    Queue copyQueue = GetPrimaryState(queue);
        if (&copyQueue == queue) return REALLOC_ERROR;
    printf("\n  Queue: { ");
    int elem = Pop(&copyQueue); 
    while (elem >= 0) {
        printf("%d", elem);
        elem = Pop(&copyQueue);
        if (elem >= 0) printf(", ");
    }
    printf(" };");
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
        if (queue->size == 0) {
            Queue tempQueue = CreateQueue();
            queue = &tempQueue; 
        }
        system("cls");
        PrintMenu();
        char option;
        scanf("%s", &option);
        system("cls");
        switch (option) {
            case('1'): {
                WasError(PrintQueue(queue));
                DeleteQueue(queue); 
                break;
            }
            case('2'): { 
                WasError(Push(queue, rand() % 100));
                WasError(PrintQueue(queue));
                break;
            }
            case('3'): {  
                WasError(PrintQueue(queue));
                int errorCode = Pop(queue);
                if (!WasError(errorCode)) printf("\n  Deleted elem: %d", errorCode);
                else break;
                WasError(PrintQueue(queue));
                break;
            }
            case('4'): {
                WasError(PrintQueue(queue));
                int errorCode = SplitZeros(queue);
                if (!WasError(errorCode)) 
                    WasError(PrintQueue(queue));  
                break;
            }
            case('5'): {
                WasError(PrintQueue(queue));
                int errorCode = PopBack(queue);
                if (!WasError(errorCode)) printf("\n  Deleted tale: %d", errorCode);
                else break; 
                WasError(PrintQueue(queue));
                break;
            }
            case('6'): { 
                Queue copyQueue = GetPrimaryState(queue);
                if (&copyQueue == queue) {
                    WasError(REALLOC_ERROR);
                    break;
                } 
                WasError(PrintQueue(queue));
                int tale = SwapEdges(queue);
                int head = Pop(&copyQueue); 
                if (!WasError(tale) && !WasError(head)) 
                    printf("\n  Switched elems: %d and %d", head, tale);
                else break;
                WasError(PrintQueue(queue));
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


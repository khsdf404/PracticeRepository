#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <windows.h>
#include <locale.h>

#define WHITE 15
#define DARKGREY 8
#define SUCCESS 1
#define EMPTY_SIZE_ERROR -1 
#define EMPTY_SIZE_MSG printf("\n  Error: not enough size for that  !\n")
#define REALLOC_ERROR -2
#define REALLOC_MSG printf("\n  Error: realloc was finished with NULL ptr!\n")
#define SIZE_MULT 2

typedef struct Array {
    int data;
    struct Array* left;
    struct Array* right;
} TreeStruct;
typedef TreeStruct* TreeElem;
typedef TreeElem* ElemPtr;
 
typedef struct Array2 {
    ElemPtr ptr;
    int size;
    int head;
    int tale;
} Queue;
typedef Queue* QueuePtr;



int ScanInt(int* valuePtr) {
    int scanCount = scanf("%d", valuePtr);
    if (scanCount) return 1;
    if (getc(stdin) != '\n') return 0;
    return 0;
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

Queue CreateQueue() {
    Queue thisQueue;
    ElemPtr dynamicArr = (ElemPtr)calloc(10, sizeof(TreeElem)); // idk if this could return an error 
    thisQueue.ptr = dynamicArr;
    thisQueue.size = 10;
    thisQueue.head = -1;
    thisQueue.tale = -1;
    return thisQueue;
}
int ReallocQueue(QueuePtr queue, int newSize) {
    ElemPtr tmp_ptr = (ElemPtr)realloc(queue->ptr, newSize * sizeof(TreeElem));
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
TreeElem Pop(QueuePtr queue) {
    if (queue->head == -1) return NULL;
    int head = queue->head;
    TreeElem headVal = queue->ptr[head];
    queue->ptr[head] = 0;
    if (queue->head == queue->tale) {
        queue->head = -1;
        queue->tale = -1;
        return headVal;
    }
    queue->head = (head + 1) % queue->size;
    return headVal;
}
TreeElem Push(QueuePtr queue, TreeElem newElem) {
    if (!ReallocChecker(queue)) return NULL;
    int size = queue->size;
    int tale = queue->tale;
    queue->ptr[(tale + 1) % size] = newElem;
    queue->tale = (tale + 1) % size;
    if (queue->head == -1) queue->head = queue->tale;
    return newElem;
}
int WasError(int errorCode) {
    if (errorCode >= 0) return 0;
    if (errorCode == REALLOC_ERROR) REALLOC_MSG;
    if (errorCode == EMPTY_SIZE_ERROR) EMPTY_SIZE_MSG;
    return 1;
}
int QueueEmpty(QueuePtr queue) {
    Queue thisQueue = GetPrimaryState(queue);
    if (Pop(&thisQueue) == NULL) return 1;
    return 0;
}





TreeElem CreateElem(int val) {
    TreeElem thisTree = (TreeElem)malloc(sizeof(TreeStruct));
    thisTree->data = val;
    thisTree->left = NULL;
    thisTree->right = NULL;
    return thisTree;
}
void DeleteList(ElemPtr head) {
    //
}



void Print(ElemPtr head) {
    if (*head == NULL) return;
    //         10
    //        /  \
    //      6     13
    //     / \      \ 
    //    1   8      15
    //         \     /
    //          9   14  
    Queue ParentStack = CreateQueue();
    Queue ChildStack = CreateQueue();
    Push(&ParentStack, *head); 
    //Pop(&ParentStack);
    //printf("  %d  ", Pop(&ParentStack)->data);
    while (0 || !QueueEmpty(&ParentStack)) {
        TreeElem elem = Pop(&ParentStack);
        while (elem != NULL) {
            if (elem->left != NULL)
                Push(&ChildStack, elem->left);
            if (elem->right != NULL)
                Push(&ChildStack, elem->right);
            printf(" | %d | ", elem->data);
            elem = Pop(&ParentStack); 
        }
        ParentStack = GetPrimaryState(&ChildStack);
        ChildStack = CreateQueue();
        printf("\n");
    } 
}



TreeElem GoLeft(ElemPtr elem) {
    if ((*elem)->left == NULL) return NULL;
    return (*elem)->left;
}
TreeElem GoRight(ElemPtr elem) {
    if ((*elem)->right == NULL) return NULL;
    return (*elem)->right;
}
void PushTree(ElemPtr head) {
    int value = GetValue(); 
    if (*head == NULL) {
        *head = CreateElem(value);
        return;
    }
    TreeElem tElem;
    TreeElem nextElem = *head;
    while (nextElem != NULL) {
        tElem = nextElem;
        if (tElem->data == value) return;
        if (tElem->data > value) nextElem = GoLeft(&tElem);
        if (tElem->data < value) nextElem = GoRight(&tElem);
    }
    if (tElem->data > value) tElem->left = CreateElem(value);
    if (tElem->data < value) tElem->right = CreateElem(value);
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
                PushTree(head);
                break;
            }
            case('2'): {
                if (isEmpty) continue;
                // DeleteByValue(head);
                break;
            }
            case('3'): {
                if (isEmpty) continue;
                Print(head);
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

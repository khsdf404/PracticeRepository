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
#define EMPTY_SIZE_MSG printf("\n  Error: not enough size for it!\n")
#define REALLOC_ERROR -2
#define REALLOC_MSG printf("\n  Error: realloc was finished with NULL ptr!\n")

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
} Stack;
typedef Stack* StackPtr;
 
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


Stack CreateStack() {
    Stack thisStack;
    thisStack.ptr = NULL;
    thisStack.size = 0;
    return thisStack;
}
int ReallocStack(StackPtr stack, int newSize) {
    ElemPtr tmp_ptr = (ElemPtr)realloc(stack->ptr, newSize * sizeof(TreeElem));
    if (tmp_ptr != NULL || newSize == 0) {
        stack->ptr = tmp_ptr;
        stack->size = newSize;
    }
    return (tmp_ptr != NULL || stack->size == 0);
}
void DeleteStack(StackPtr stack) {
    stack->size = 0;
    free(stack->ptr);
    stack = NULL;
}


Stack GetPrimaryState(StackPtr stack) {
    Stack currStack = CreateStack();
    if (!ReallocStack(&currStack, stack->size))
        return *stack;
    for (int i = 0; i < stack->size; i++)
        currStack.ptr[i] = stack->ptr[i];
    return currStack;
}
TreeElem Pop(StackPtr stack) {
    if (stack->size == 0) return NULL;
    TreeElem topElem = stack->ptr[stack->size - 1];
    ReallocStack(stack, stack->size - 1);
    return topElem;
}
TreeElem Push(StackPtr stack, TreeElem newElem) {
    ReallocStack(stack, stack->size + 1);
    stack->ptr[stack->size - 1] = newElem;
    return stack->ptr[stack->size - 1];
}
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
int StackEmpty(StackPtr stack) {
    Stack thisStack = GetPrimaryState(stack);
    if (Pop(&thisStack) == NULL) return 1;
    return 0;
}





TreeElem CreateElem(int val) {
    TreeElem thisTree = (TreeElem)malloc(sizeof(TreeStruct));
    thisTree->data = val;
    thisTree->left = NULL;
    thisTree->right = NULL;
    return thisTree;
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
    

    Stack ParentStack = CreateStack(); 
    Stack ChildStack = CreateStack(); 
    Push(&ParentStack, *head);
    printf("  %d  ", StackEmpty(&ParentStack));
    while (!StackEmpty(&ParentStack)) {
        TreeElem elem = CreateElem(1);
        while (elem != NULL) {
            elem = Pop(&ParentStack);
            if (elem->right != NULL) 
                Push(&ChildStack, elem->right);
            if (elem->left != NULL)
                Push(&ChildStack, elem->left);
            printf(" | %d | ", elem->data);
        }
        ParentStack = GetPrimaryState(&ChildStack);
        ChildStack = CreateStack();
    }
    printf("\nhhh\n");
}



void DeleteList(ElemPtr head) {
    //
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
    // check if value already in tree
    if (*head == NULL) {
        *head = CreateElem(value);
        return;
    }
    TreeElem tElem = *head;
    TreeElem nextElem = *head;
    while (nextElem != NULL) {
        tElem = nextElem;
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

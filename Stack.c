#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <windows.h>

#define WHITE 15 
#define DARKGREY 8
#define EMPTY_SIZE_ERROR -1 
#define EMPTY_SIZE_MSG printf("\n  Error: not enough size for it!\n")
#define REALLOC_ERROR -2
#define REALLOC_MSG printf("\n  Error: realloc was finished with NULL ptr!\n")


typedef int* arr_p;
typedef struct Array {
    arr_p ptr;
    int size;
} Stack;
typedef Stack* StackPtr;


// FoolProof get int func
int  ScanInt(int* valuePtr) {
    int scanCount = scanf("%d", valuePtr);
    if (scanCount) return 1; 
    return getc(stdin) != '\n';
}


// Dynamic's array funcs

Stack CreateStack() {
    Stack thisStack;
    int* dynamicArr = (int*)calloc(0, sizeof(int));
    thisStack.ptr = dynamicArr;
    thisStack.size = 0;
    return thisStack;
}
int ReallocStack(StackPtr stack, int newSize) {
    int* tmp_ptr = (int*)realloc(stack->ptr, newSize * sizeof(int));
    if (tmp_ptr != NULL || newSize == 0) {
        stack->ptr = tmp_ptr;
        stack->size = newSize;
    }
    else stack->size = -1;
    return (tmp_ptr != NULL || stack->size == 0);
}
void DeleteStack(StackPtr stack) {
    stack->size = 0;
    free(stack->ptr);
}

// это база
int Pop(StackPtr stack) {
    if (stack->size == 0) return EMPTY_SIZE_ERROR;
    int topElem = stack->ptr[0];
    for (int i = 0; i < stack->size - 1; i++)
        stack->ptr[i] = stack->ptr[i+1];
    if (!ReallocStack(stack, stack->size - 1))
        return REALLOC_ERROR; 
    return topElem;
}
int Push(StackPtr stack, int newValue) { 
    if (!ReallocStack(stack, stack->size + 1))
        return REALLOC_ERROR;
    for (int i = 0; i < stack->size - 1; i++)
        stack->ptr[i + 1] = stack->ptr[i];
    stack->ptr[0] = newValue;
    return stack->ptr[0];
}
Stack GetPrimaryState(StackPtr stack) {
    Stack currStack = CreateStack();
    if (!ReallocStack(&currStack, stack->size))
        return stack;
    for (int i = 0; i < stack->size; i++)
        currStack[i] = stack->ptr[i];
    return currStack;
}

// not BASE
void FreeStack(StackPtr stack) {
    Stack primaryState = GetPrimaryState(stack);
    if (&primaryState == stack) // realloc error
        return; 
    printf("\n  {");
    int peakElem = Pop(stack);
    while (peakElem > 0) {
        printf("%d", peakElem);
        peakElem = Pop(stack);
        if (peakElem > 0)
            printf(", ");
    }
    if (peakElem == REALLOC_ERROR) {
        printf(" ...");
        REALLOC_MSG;
        DeleteStack(stack);
        stack = &primaryState;
    }
    printf(" };\n");
}
void SwapTop(StackPtr stack) {
    Stack primaryState = GetPrimaryState(stack);
    if (&primaryState == stack) // realloc error
        return;
    int a = Pop(stack);
    if (a == EMPTY_SIZE_ERROR) {
        EMPTY_SIZE_MSG;
        return;
    }
    if (a == REALLOC_ERROR) {
        REALLOC_MSG;
        DeleteStack(stack);
        stack = &primaryState;
        return;
    }
        
    int b = Pop(stack);
    if (b == EMPTY_SIZE_ERROR) {
        EMPTY_SIZE_MSG;
        DeleteStack(stack);
        stack = &primaryState;
        return;
    }
    if (b == REALLOC_ERROR) {
        REALLOC_MSG;
        DeleteStack(stack);
        stack = &primaryState;
        return;
    }
    
    a = Push(stack, a);
    if (a == REALLOC_ERROR) {
        REALLOC_MSG;
        DeleteStack(stack);
        stack = &primaryState;
        return;
    }
    b = Push(stack, b);
    if (b == REALLOC_ERROR) {
        REALLOC_MSG;
        DeleteStack(stack);
        stack = &primaryState;
        return;
    }
    printf("%d, %d", a, b);
}
void PopBack(StackPtr stack) {
    Stack tempStack = CreateStack();
    // { 1, 2, 3 } => { 3, 2, 1 }
    int peakElem = Pop(stack);
    while (peakElem > 0) {
        Push(&tempStack, peakElem);
        peakElem = Pop(stack);
    }
    Pop(&tempStack); // check -2 error
    
    peakElem = Pop(&tempStack);
    while (peakElem > 0) {
        Push(stack, peakElem);
        peakElem = Pop(&tempStack);
    }
}



// General funcs
void PrintMenu(StackPtr arr) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("\n");
    printf("  1. Очистить стек.\n");
    printf("  2. Добавить элемент в стек.\n");
    printf("  3. Извлечь из стека верхушку.\n");
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
void Menu(StackPtr arr) {
    while (1) {
        system("cls");
        PrintMenu(arr);
        char option;
        scanf("%s", &option);
        system("cls");
        switch (option) {
        case('1'): { 
            continue;
        }
        case('2'): { 
            continue;
        }
        case('3'): { 
            continue;
        }
        case('4'): {
            printf("\n"); 
            continue;
        }
        case('5'): { 
            continue;
        }
        case('6'): { 
            continue;
        }
        case('7'): {
            // exit
            return;
        }
        default: {
            continue;
        }
        }
        StepBack();
    }
}


int main() {
    srand(time(0));
    system("chcp 1251");
    system("cls"); 


    Stack stack = CreateStack();
    Menu(&stack);


    system("pause");
    DeleteStack(&stack);
    return 0;
}


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
    int* dynamicArr = (int*)calloc(1, sizeof(int));
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
    return (tmp_ptr != NULL || stack->size == 0);
}
void DeleteStack(StackPtr stack) {
    stack->size = 0;
    free(stack->ptr);
    stack = NULL;
}

// это база
Stack GetPrimaryState(StackPtr stack) {
    Stack currStack = CreateStack();
    if (!ReallocStack(&currStack, stack->size))
        return *stack;
    for (int i = 0; i < stack->size; i++)
        currStack.ptr[i] = stack->ptr[i];
    return currStack;
}
int Pop(StackPtr stack) {
    if (stack->size == 0) return EMPTY_SIZE_ERROR;
    int topElem = stack->ptr[stack->size - 1];
    if (!ReallocStack(stack, stack->size - 1)) return REALLOC_ERROR;  
    return topElem;
}
int Push(StackPtr stack, int newValue) { 
    if (!ReallocStack(stack, stack->size + 1)) return REALLOC_ERROR;
    stack->ptr[stack->size-1] = newValue;
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


 // not BASE
int FreeStack(StackPtr stack, StackPtr primaryStack) {
    DeleteStack(primaryStack);
    *primaryStack = GetPrimaryState(stack);
    if (primaryStack == stack) return REALLOC_ERROR;
    printf("\n  {");
    int peakElem = Pop(stack);
    while (peakElem > 0) {
        printf("%d", peakElem);
        peakElem = Pop(stack);
        if (peakElem > 0)
            printf(", ");
    } 
    if (peakElem == REALLOC_ERROR) return REALLOC_ERROR; 
    printf(" };\n");
    return SUCCESS;
}
int SwapTop(StackPtr stack, StackPtr primaryStack) {
    DeleteStack(primaryStack);
    *primaryStack = GetPrimaryState(stack);
    if (primaryStack == stack) return REALLOC_ERROR;

    int first = Pop(stack);
    if (first < 0) return first;
        
    int second = Pop(stack);
    if (second < 0) return second;
  
    if (Push(stack, first) == REALLOC_ERROR) return REALLOC_ERROR;
    if (Push(stack, second) == REALLOC_ERROR) return REALLOC_ERROR;
    printf("%d, %d", first, second);
    return SUCCESS;
}
int PopBack(StackPtr stack, StackPtr primaryStack) {
    DeleteStack(primaryStack);
    *primaryStack = GetPrimaryState(stack);
    if (primaryStack == stack) return REALLOC_ERROR;

    int peakElem = Pop(stack);
    if (peakElem < 0) return peakElem;
    Stack tempStack = CreateStack();
    while (peakElem > 0) {
        if (Push(&tempStack, peakElem) == REALLOC_ERROR) {
            peakElem = REALLOC_ERROR;
            break;
        }
        peakElem = Pop(stack);
    }
    if (peakElem == REALLOC_ERROR) {
        DeleteStack(tempStack);
        return REALLOC_ERROR;
    }
    int deletedElem = Pop(&tempStack);
    if (deletedElem == REALLOC_ERROR) {
        DeleteStack(tempStack);
        return REALLOC_ERROR;
    }

    peakElem = Pop(&tempStack);
    while (peakElem > 0) {
        Push(stack, peakElem);
        peakElem = Pop(&tempStack);
    }
    if (peakElem == REALLOC_ERROR) {
        DeleteStack(tempStack);
        return REALLOC_ERROR;
    }
    return deletedElem;
}
int SwapEdges(StackPtr stack, StackPtr primaryStack) { 
    DeleteStack(primaryStack);
    *primaryStack = GetPrimaryState(stack);
    if (primaryStack == stack) return REALLOC_ERROR; 
    int errorCode;
    Stack tempStack = CreateStack();
    // {1,2,3,4} => {2,3,4}
    int topElem = Pop(stack);
    if (topElem < 0) { DeleteStack(&tempStack); return topElem; } 
    // {2,3,4} => {2,3} 
    int bottomElem = PopBack(stack, &tempStack);
    if (bottomElem < 0) { DeleteStack(&tempStack); return bottomElem; }
    // {} => {4}
    errorCode = Push(&tempStack, bottomElem); 
    if (errorCode == REALLOC_ERROR) { DeleteStack(&tempStack); return REALLOC_ERROR; }
    // {4} => {3,2,4}
    int peakElem = Pop(stack);
    while (peakElem > 0) {
        errorCode = Push(&tempStack, peakElem);
        if (errorCode == REALLOC_ERROR) { DeleteStack(&tempStack); return REALLOC_ERROR; }
        peakElem = Pop(stack);
    }
    if (peakElem == REALLOC_ERROR) { DeleteStack(&tempStack); return REALLOC_ERROR; }
    // {3,2,4} => {1,3,2,4}
    errorCode = Push(&tempStack, topElem); 
    if (errorCode == REALLOC_ERROR) { DeleteStack(&tempStack); return REALLOC_ERROR; }
    // {1,3,2,4} => {4,2,3,1}
    peakElem = Pop(&tempStack);
    while (peakElem > 0) {
        errorCode = Push(stack, peakElem);
        if (errorCode == REALLOC_ERROR) { DeleteStack(&tempStack); return REALLOC_ERROR; }
        peakElem = Pop(&tempStack);
    }
    if (peakElem == REALLOC_ERROR) { DeleteStack(&tempStack); return REALLOC_ERROR; }
    printf("\n  %d, %d", topElem, bottomElem);
    return SUCCESS; 
}
void PrintStack(StackPtr stack) {
    printf("  \n{ ");
    for (int i = stack->size-1; i >= 0; i--)
        printf("%d, ", stack->ptr[i]); 
    printf(" } ");
}

// General funcs
void PrintMenu() {
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
void Menu(StackPtr stack, StackPtr primaryStack) {
    while (1) {
        system("cls");
        PrintMenu();
        char option;
        scanf("%s", &option);
        system("cls"); 
        switch (option) {
            case('1'): {
                int errorCode = FreeStack(stack, primaryStack);
                if (!WasError(errorCode, stack, primaryStack))
                    printf("\n  Stack was free successfully!\n");
                break;
            }
            case('2'): {
                int errorCode = Push(stack, abs(rand() % 100));
                WasError(errorCode, stack, primaryStack); 
                break;
            }
            case('3'): { 
                int peakElem = Pop(stack);
                if (peakElem == EMPTY_SIZE_ERROR) EMPTY_SIZE_MSG;
                printf("\n  %d", peakElem);
                break;
            }
            case('4'): {
                int errorCode = SwapTop(stack, primaryStack);
                WasError(errorCode, stack, primaryStack);
                break;
            } 
            case('5'): {
                int deletedElem = PopBack(stack, primaryStack);
                WasError(deletedElem, stack, primaryStack);
                printf("\n  %d", deletedElem);
                break;
            }
            case('6'): {
                int errorCode = SwapEdges(stack, primaryStack);
                WasError(errorCode, stack, primaryStack);
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
        PrintStack(stack);
        StepBack();
    }
}


int main() {
    srand(time(0));
    system("chcp 1251");
    system("cls"); 


    Stack stack = CreateStack();
    Stack primaryStack = CreateStack();
    Menu(&stack, &primaryStack);


    system("pause");
    DeleteStack(&stack);
    DeleteStack(&primaryStack);
    return 0;
}


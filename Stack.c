#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <windows.h>

#define WHITE 15 
#define DARKGREY 8
#define MALLOC_ERROR printf("\n  Error: malloc was finished with NULL ptr!\n")

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
Stack CreateStack(int size) {
    Stack thisStack;
    int* dynamicArr = (int*)calloc(size * sizeof(int), sizeof(int));
    thisStack.ptr = dynamicArr;
    if (dynamicArr == NULL) {
        thisStack.size = -1;
        return thisStack;
    }
    thisStack.size = size;
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
    free(stack->ptr);
}

void PopTop(StackPtr stack) {
    // {1,2,3,4}  
    printf("\n  %d", stack->ptr[stack->size - 1]);
    for (int i = 0; i < stack->size; i++) {
        stack->ptr[i] = stack->ptr[i+1];
    }
    ReallocStack(stack, stack->size - 1); // check errors 
}
void PushTop(StackPtr stack) {
    int newValue = 2; // getValue func
    ReallocStack(stack, stack->size + 1); // check errors  
    for (int i = 0; i < stack->size; i++) {
        stack->ptr[i + 1] = stack->ptr[i];
    }
    stack->ptr[0] = newValue;
}

void FreeStack(StackPtr stack) {
    printf("\n  {");
    while (stack->size > 0) {
        printf("%d, ", stack->ptr[0]);
        PopTop(stack);
    } 
    printf(" }"); 
}

int CheckSize(int stackSize) {
    Stack tempStack = CreateStack(stackSize);
    if (stackSize == 0)
        return 0;
    PopTop(tempStack);
    if (tempStack.size == 0)
        return 1;
}
void SwapTop(StackPtr stack) { 
    if ()
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

    Stack s1 = CreateStack(10);
    Stack s2 = s1;
    s1.size = 8;
    printf("\n %d \n", (&s1.ptr[0]));
    printf("\n %d \n", (&s2.ptr[0]));
    system("pause");
    return 0;


    int out = 1;
    Stack stack;
    while (out != 0) {
        stack = CreateStack(0);
        if (stack.size == -1) {
            MALLOC_ERROR;
            printf("\n  Try again? 1/0: ");
            while (ScanInt(&out) == 0 || (out != 0 && out != 1)) {
                system("cls");
                printf("\n  Try again? 1/0: ");
            };
            system("pause");
            // ? DeleteArray(&arr);
            return;
        }
        else {
            Menu(&stack);
            break;
        };
    }
    system("pause");
    DeleteStack(&stack);
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <windows.h>

#define WHITE 15 
#define DARKGREY 8

typedef int* arr_p;
typedef struct Array {
    arr_p ptr;
    int size;
} Array;
typedef Array* ArrayPtr;


// FoolProof get int func
int  ScanInt(int* valuePtr) {
    int scanCount = scanf("%d", valuePtr);
    if (scanCount) return 1;
    getc(stdin) != '\n';
    return 0;
}


// Dynamic's array funcs
Array CreateArray(int size) {
    Array thisArr;
    int* dynamicArr = (int*)calloc(size * sizeof(int), sizeof(int));
    thisArr.ptr = dynamicArr;
    if (dynamicArr == NULL) {
        thisArr.size = -1;
        return thisArr;
    }
    thisArr.size = size;
    return thisArr;
}
int ReallocArray(ArrayPtr arr, int newSize) {
    int* tmp_ptr = (int*)realloc(arr->ptr, newSize * sizeof(int));
    if (tmp_ptr != NULL || newSize == 0) {
        arr->ptr = tmp_ptr;
        arr->size = newSize;
    }
    return (tmp_ptr != NULL || arr->size == 0);
}
void DeleteArray(ArrayPtr arr) {
    free(arr->ptr);
}


// 4.
void PrintArrayPart(ArrayPtr arr, int start, int end) {
    for (int k = start; k < end; k++) {
        printf("%d", arr->ptr[k]);
        if (k != end - 1)
            printf(", ");
    }
}
void PrintArray(ArrayPtr arr) {
    printf("  Массив: [ ");
    PrintArrayPart(arr, 0, arr->size);
    printf(" ];\n");
}
// 1.
void PushBack(ArrayPtr arr) {
    if (!ReallocArray(arr, arr->size + 1)) {
        printf("Error: realloc finished with NULL ptr!\n");
        return;
    }
    int newValue;
    printf("\n  Введите значение: ");
    while (ScanInt(&newValue) == 0) {
        system("cls");
        printf("\n  Введите значение: ");
    };
    arr->ptr[arr->size - 1] = newValue;
    PrintArray(arr);
}
// 2.
int  GetNewSize() {
    int newSize = -1;
    printf("\n  Введите длину массива: ");
    while (ScanInt(&newSize) == 0 || newSize < 0) {
        system("cls");
        printf("\n  Введите корректную длину массива: ");
    };
    return newSize;
}
void ChangeArray(ArrayPtr arr) {
    int newSize = GetNewSize();
    system("cls");
    if (!ReallocArray(arr, newSize) && newSize != 0) {
        printf("Error: realloc finished with NULL ptr!\n");
        return;
    }
    for (int i = 0; i < newSize; i++) {
        system("cls");
        int nextValue;
        printf("\n  Введите %d чисел: ", (newSize - i));
        PrintArrayPart(arr, 0, i);
        if (i != 0) printf(", ");
        while (ScanInt(&nextValue) == 0) {
            system("cls");
            printf("\n  Введите %d чисел: ", (newSize - i));
            PrintArrayPart(arr, 0, i);
            if (i != 0) printf(", ");
        };
        arr->ptr[i] = nextValue;
    }
    system("cls");
    printf("\n  Введённые числа: ");
    PrintArrayPart(arr, 0, newSize);
    printf("\n");
    PrintArray(arr);
}
// 3.
int  GetRandomValue(int edge, int chance) {
    int negativeChance = rand() % 100;
    int rndValue = rand() % edge;
    if (negativeChance >= chance)
        rndValue *= -1;
    return rndValue;
}
void RandomArray(ArrayPtr arr) {
    int newSize = GetNewSize();
    if (!ReallocArray(arr, newSize) && newSize != 0) {
        printf("Error: realloc finished with NULL ptr!\n");
        return;
    }
    for (int i = 0; i < newSize; i++)
        arr->ptr[i] = GetRandomValue(13, 70);
    PrintArray(arr);
}
// 5 & 6.
void RemoveByValue(ArrayPtr arr) {
    int value;
    printf("\n");
    PrintArray(arr);
    printf("\n  Введите значение, элементы с которым хотите удалить: ");
    while (ScanInt(&value) == 0) {
        system("cls");
        printf("\n");
        PrintArray(arr);
        printf("\n  Введите значение, элементы с которым хотите удалить: ");
    };
    int offset = 0;
    for (int i = 0; i < arr->size; i++)
        if (arr->ptr[i] == value)
            offset++;
    if (!ReallocArray(arr, arr->size - offset) && arr->size != 0) {
        printf("Error: realloc finished with NULL ptr!\n");
        return;
    }
    offset = 0;
    for (int i = 0; i < arr->size - offset; i++) {
        arr->ptr[i] = arr->ptr[i + offset];
        if (arr->ptr[i] == value) {
            offset++;
            i--;
        }
    }
    printf("  Удалено элементов: %d\n", offset);

    PrintArray(arr);
}
void RemoveByIndex(ArrayPtr arr) {
    int index;
    printf("\n");
    PrintArray(arr);
    printf("  Введите индекс, по которому удалится элемент массива: ");
    while (ScanInt(&index) == 0 || !(index >= 0 && arr->size > index)) {
        system("cls");
        printf("\n");
        PrintArray(arr);
        printf("  Введите индекс, по которому удалится элемент массива: ");
    };
    if (!ReallocArray(arr, arr->size - 1) && arr->size != 0) {
        printf("Error: realloc finished with NULL ptr!\n");
        return;
    }
    for (int k = index; k < arr->size; k++)
        arr->ptr[k] = arr->ptr[k + 1];

    printf("\n");
    PrintArray(arr);
}

// General funcs
void PrintMenu(ArrayPtr arr) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("\n");
    printf("  1. Вставить элемент в конец массива\n");
    printf("  2. Перезаписать массив вручную.\n");
    printf("  3. Перезаписать массив рандомно.\n");
    if (arr->size == 0) SetConsoleTextAttribute(hConsole, DARKGREY);
    printf("  4. Вывести массив на экран.\n");
    printf("  5. Удалить элемент по индексу.\n");
    printf("  6. Удалить элемент по значению.\n");
    if (arr->size == 0) SetConsoleTextAttribute(hConsole, WHITE);
    printf("  7. Выйти.\n");
    printf("\n  ");
}
void StepBack() {
    printf("\n  Для продолжения нажмите любую клавишу...");
    getch();
}
// Menu
void Menu(ArrayPtr arr) {
    while (1) {
        system("cls");
        PrintMenu(arr);
        char option;
        scanf("%s", &option);
        system("cls");
        switch (option) {
        case('1'): {
            PushBack(arr);
            break;
        }
        case('2'): {
            ChangeArray(arr);
            break;
        }
        case('3'): {
            RandomArray(arr);
            break;
        }
        case('4'): {
            printf("\n");
            if (arr->size != 0)
                PrintArray(arr);
            continue;
        }
        case('5'): {
            if (arr->size != 0)
                RemoveByIndex(arr);
            continue;
        }
        case('6'): {
            if (arr->size != 0)
                RemoveByValue(arr);
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

    Array arr = CreateArray(0);
    if (arr.size == -1) {
        printf("Error: malloc was finished with NULL ptr!\n");
        system("pause");
        DeleteArray(&arr);
        return;
    }


    Menu(&arr);


    system("pause");
    DeleteArray(&arr);
    return 0;
}


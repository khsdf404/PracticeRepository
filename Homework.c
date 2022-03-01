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


// Dynamic's array funcs
Array CreateArray(int size) {
    Array thisArr;
    int* dynamicArr = (int*)malloc(size * sizeof(int));
    thisArr.ptr = dynamicArr;
    thisArr.size = size;
    for (int i = 0; i < size; i++) *(dynamicArr + i) = 0;
    return thisArr;
}
void ReallocArray(ArrayPtr arr) {
    int* tmp_ptr = (int*)realloc(arr->ptr, arr->size * sizeof(int));
    if (tmp_ptr != NULL) arr->ptr = tmp_ptr;
}
void DeleteArray(ArrayPtr arr) {
    free(arr);
}

// FoolProof get int func
int  ScanInt(int* valuePtr) {
    int scanCount = scanf("%d", valuePtr);
    if (scanCount) return 1;
    while (getc(stdin) != '\n') {
        return 0;
        scanCount = scanf("%d", valuePtr);
    }
    return 0;
}


// 4.
void PrintArrayPart(ArrayPtr arr, int start, int end) {
    for (int k = start; k < end; k++) {
        printf("%d", *(arr->ptr + k));
        if (k != end - 1)
            printf(", ");
    }
}
void PrintArray(ArrayPtr arr) {
    printf("\n  Массив: [ ");
    PrintArrayPart(arr, 0, arr->size);
    printf(" ];\n");
} 
// 1.
void PushBack(ArrayPtr arr) {
    arr->size++;
    ReallocArray(arr); 
    int newValue;
    printf("\n  Введите значение: "); 
    while (ScanInt(&newValue) == 0) {
        system("cls");
        printf("\n  Введите значение: ");
    }; 
    *(arr->ptr + arr->size - 1) = newValue; 
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

    arr -> size = newSize;
    ReallocArray(arr);

    for (int i = 0; i < newSize; i++) {
        system("cls");
        int nextValue; 
        printf("\n  Введите %d чисел: ", (newSize - i));
        PrintArrayPart(arr, 0, i);
        if (i != 0 ) printf(", ");
        while (ScanInt(&nextValue) == 0) {
            system("cls");
            printf("\n  Введите %d чисел: ", (newSize - i));
            PrintArrayPart(arr, 0, i);
            if (i != 0) printf(", ");
        };  
        *(arr->ptr + i) = nextValue; 
    }
    system("cls");
    printf("\n  Введите 0 чисел: ");
    PrintArrayPart(arr, 0, newSize); 
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

    arr->size = newSize;
    ReallocArray(arr); 
    for (int i = 0; i < newSize; i++)
        *(arr->ptr + i) = GetRandomValue(13, 70); 
    PrintArray(arr);
}
// 5 & 6.
void RemoveByValue(ArrayPtr arr) {
    int value;
    PrintArray(arr);
    printf("\n  Введите значение, элементы с которым хотите удалить: ");
    while (ScanInt(&value) == 0) {
        system("cls");
        PrintArray(arr);
        printf("\n  Введите значение, элементы с которым хотите удалить: ");
    }; 
    int offset = 0;
    for (int i = 0; i < arr->size; i++) {
        *(arr->ptr + i) = *(arr->ptr + i + offset);
        if (*(arr->ptr + i) == value) {
            offset++;
            i--;
            arr->size--;
        }
    } 
    printf("  Удалено элементов: %d\n", offset);
    ReallocArray(arr);
    PrintArray(arr);
}
void RemoveByIndex(ArrayPtr arr) { 
    int index;
    PrintArray(arr);
    printf("  Введите индекс, по которому удалится элемент массива: ");
    while (ScanInt(&index) == 0 || !(index >= 0 && arr->size > index)) { 
        system("cls");
        PrintArray(arr);
        printf("  Введите индекс, по которому удалится элемент массива: ");
    };
    for (int k = index; k < arr->size; k++)
        *(arr->ptr + k) = *(arr->ptr + k + 1);
    arr->size--;
    ReallocArray(arr);
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
    printf("\n");
    system("pause");
}
// Menu
void Menu(ArrayPtr arr) {
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
            if (arr->size == 0) {
                Menu(arr);
                return;
            }
            PrintArray(arr); 
            break;
        } 
        case('5'): {
            if (arr->size == 0) {
                Menu(arr);
                return;
            }
            RemoveByIndex(arr);
            break;
        }
        case('6'): {
            if (arr->size == 0) {
                Menu(arr);
                return;
            }
            RemoveByValue(arr);
            break;
        } 
        case('7'): {
            // exit
            return;
        }
        default: {
            Menu(arr);
            return;
        }
    } 
    StepBack();
    Menu(arr);
}



int main() {
    srand(time(0));
    system("chcp 1251");
    system("cls"); 
    
    Array arr = CreateArray(0);
    Menu(&arr);
      
    DeleteArray(&arr); 
	return 0;
}


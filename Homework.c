#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
 
typedef int* arr_p; 
typedef struct Array {
    arr_p ptr;
    int size;
} Array;
typedef Array* ArrayPtr;


// FoolProof func
int ScanInt(int* valuePtr) {
    int scanCount = scanf("%d", valuePtr);
    if (scanCount) return 1;
    while (getc(stdin) != '\n') {
        return 0;
        scanCount = scanf("%d", valuePtr);
    }
    return 0;
}

void PrintMenu() {
    printf("\n  1. Вставить элемент в конец массива\n");
    printf("  2. Перезаписать массив полностью.\n");
    printf("  3. Вывести массив на экран.\n");
    printf("  4. Удалить элемент по значению.\n");
    printf("  5. Удалить элемент по индексу.\n");
    printf("  6. Выйти.\n\n  ");
}
void StepBack() {
    printf("\n");
    system("pause");
}




Array CreateArray(int len) {
    Array thisArr;
    int* dynamicArr = (int*)malloc(len * sizeof(int));
    thisArr.ptr = dynamicArr;
    thisArr.size = len;
    for (int i = 0; i < len; i++) *(dynamicArr + i) = 0;
    return thisArr;
}
void ReallocArray(ArrayPtr arr_s) {
    int* tmp_ptr = (int*)realloc(arr_s -> ptr, arr_s-> size * sizeof(int));
    if (tmp_ptr != NULL) arr_s -> ptr = tmp_ptr;
}
void DeleteArray(ArrayPtr arr_s) {
    free(arr_s);
}


void PrintArray(ArrayPtr arr_s) {
    printf("\n  Массив: [ ");
    for (int i = 0; i < arr_s->size; i++) {
        printf("%d", *(arr_s->ptr + i));
        if (i + 1 != arr_s->size)
            printf(", ");
    }
    printf(" ];\n");
} 
void PushBack(ArrayPtr arr_s) {
    arr_s->size++;
    ReallocArray(arr_s); 
    int newValue;
    printf("\n  Введите значение: "); 
    while (ScanInt(&newValue) == 0) {
        system("cls");
        printf("\n  Введите значение: ");
    }; 
    *(arr_s->ptr + arr_s->size - 1) = newValue; 
}
/*
void DynamicChangeArray(int* mas, int* dynamicSize) {
    int newLen = -1; 
    while (newLen < 0 || newLen > 21) {
        printf("Введите длину массива [0, 20]\n");
        scanf("%d", &newLen); 
    }  
    for (int i = 0; i < newLen; i++) {
        int value;
        // system("cls");
        printf("Введите %d чисел:\n", (newLen - i));
        for (int k = 0; k < i; k++) {
            printf("%d", *(mas + k));
            if (k != newLen - 1)
                printf(", ");
        } 
        scanf("%d", &value);  
        *(mas + i) = value;
        printf("%d\n", *(mas + i));
    }
    system("cls");  
    *dynamicSize = newLen;
}

void DynamicDeleteByValue(int* mas, int* dynamicSize) {
    int value;
    printf("Введите значение, по которому удялятся элементы массива: \n");
    scanf("%d", &value); 
    for (int i = 0; i < *dynamicSize; i++) { 
        if (*(mas + i) == value) {
            for (int k = i; k < *dynamicSize; k++) {
                *(mas + k) = *(mas + k + 1);
            }
            i--;
            *dynamicSize = *dynamicSize - 1;
        }
    } 
    // DynamicPrintArray(mas, dynamicSize);
}
void DynamicDeleteByIndex(int* mas, int* dynamicSize) {
    int index = -1;  
    while (index < 0 || index >= *dynamicSize) {
        DynamicPrintArray(mas, dynamicSize);
        printf("Введите индекс, по которому удялятся элементы массива: \n");
        scanf("%d", &index);
    } 
    for (int k = index; k < *dynamicSize; k++)  
        *(mas + k) = *(mas + k + 1); 
    *dynamicSize = *dynamicSize - 1; 
    // DynamicPrintArray(mas, dynamicSize);
}

*/

void DynamicMenu(ArrayPtr arr_s) {
    system("cls");  
    PrintMenu();
    char option;
    scanf("%s", &option); 
    system("cls"); 
    switch (option) {
        case('1'): {
            PushBack(arr_s);
            break;
        }
        case('2'): {
            // DynamicChangeArray(arr_s);
            break;
        }
        case('3'): {
            PrintArray(arr_s); 
            break;
        } 
        case('4'): {
            // DynamicDeleteByValue(mas, dynamicSize);
            break;
        }
        case('5'): {
            // DynamicDeleteByIndex(mas, dynamicSize);
            break;
        }
        case('6'): {
            // exit
            return;
        }
        default: {
            DynamicMenu(arr_s);
            return;
        }
    } 
    StepBack();
    DynamicMenu(arr_s);
}

 

 


int main() {
    system("chcp 1251");
    system("cls"); 
    
    Array arr_s = CreateArray(0);
    DynamicMenu(&arr_s); 

	system("pause");
	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
 
typedef int* arr_p; 
typedef struct Array {
    arr_p ptr;
    int size;
} Array;
typedef Array* ArrayPtr;


// Dynamic's array funcs
Array CreateArray(int len) {
    Array thisArr;
    int* dynamicArr = (int*)malloc(len * sizeof(int));
    thisArr.ptr = dynamicArr;
    thisArr.size = len;
    for (int i = 0; i < len; i++) *(dynamicArr + i) = 0;
    return thisArr;
}
void ReallocArray(ArrayPtr arr_s) {
    int* tmp_ptr = (int*)realloc(arr_s->ptr, arr_s->size * sizeof(int));
    if (tmp_ptr != NULL) arr_s->ptr = tmp_ptr;
}
void DeleteArray(ArrayPtr arr_s) {
    free(arr_s);
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
void PrintArrayPart(ArrayPtr arr_s, int start, int end) {
    for (int k = start; k < end; k++) {
        printf("%d", *(arr_s->ptr + k));
        if (k != end - 1)
            printf(", ");
    }
}
void PrintArray(ArrayPtr arr_s) {
    printf("\n  ������: [ ");
    PrintArrayPart(arr_s, 0, arr_s->size);
    printf(" ];\n");
} 
// 1.
void PushBack(ArrayPtr arr_s) {
    arr_s->size++;
    ReallocArray(arr_s); 
    int newValue;
    printf("\n  ������� ��������: "); 
    while (ScanInt(&newValue) == 0) {
        system("cls");
        printf("\n  ������� ��������: ");
    }; 
    *(arr_s->ptr + arr_s->size - 1) = newValue; 
    PrintArray(arr_s);
}
// 2.
int  GetNewSize() {
    int newSize = -1; 
    printf("\n  ������� ����� �������: ");
    while (ScanInt(&newSize) == 0 || newSize < 0) {
        system("cls");
        printf("\n  ������� ���������� ����� �������: ");
    };
    return newSize;
}
void ChangeArray(ArrayPtr arr_s) {
    int newSize = GetNewSize();
    system("cls");

    arr_s -> size = newSize;
    ReallocArray(arr_s);

    for (int i = 0; i < newSize; i++) {
        system("cls");
        int nextValue; 
        printf("\n  ������� %d �����: ", (newSize - i));
        PrintArrayPart(arr_s, 0, i);
        if (i != 0 ) printf(", ");
        while (ScanInt(&nextValue) == 0) {
            system("cls");
            printf("\n  ������� %d �����: ", (newSize - i));
            PrintArrayPart(arr_s, 0, i);
            if (i != 0) printf(", ");
        };  
        *(arr_s->ptr + i) = nextValue; 
    }
    system("cls");
    printf("\n  ������� 0 �����: ");
    PrintArrayPart(arr_s, 0, newSize); 
    PrintArray(arr_s);
}
// 3.
int  GetRandomValue(int edge, int chance) {
    int negativeChance = rand() % 100;
    int rndValue = rand() % edge;
    if (negativeChance >= chance)
        rndValue *= -1; 
    return rndValue;
}
void RandomArray(ArrayPtr arr_s) {
    int newSize = GetNewSize(); 

    arr_s->size = newSize;
    ReallocArray(arr_s); 
    for (int i = 0; i < newSize; i++)
        *(arr_s->ptr + i) = GetRandomValue(13, 70); 
    PrintArray(arr_s);
}
// 5 & 6.
void RemoveByValue(ArrayPtr arr_s) {
    int value;
    PrintArray(arr_s);
    printf("\n  ������� ��������, �������� � ������� ������ �������: ");
    while (ScanInt(&value) == 0) {
        system("cls");
        printf("\n  ������� ��������, �������� � ������� ������ �������: ");
    }; 
    int offset = 0;
    for (int i = 0; i < arr_s->size; i++) {
        *(arr_s->ptr + i) = *(arr_s->ptr + i + offset);
        if (*(arr_s->ptr + i) == value) {
            offset++;
            i--;
            arr_s->size--;
        }
    } 
    ReallocArray(arr_s);
    PrintArray(arr_s);
}
void RemoveByIndex(ArrayPtr arr_s) { 
    int index;
    PrintArray(arr_s);
    printf("  ������� ������, �� �������� �������� ������� �������: ");
    while (ScanInt(&index) == 0 || !(index >= 0 && arr_s->size > index)) { 
        system("cls");
        PrintArray(arr_s);
        printf("  ������� ������, �� �������� �������� ������� �������: ");
    };
    for (int k = index; k < arr_s->size; k++)
        *(arr_s->ptr + k) = *(arr_s->ptr + k + 1);
    arr_s->size--;
    ReallocArray(arr_s);
    PrintArray(arr_s);
} 

// General funcs
void PrintMenu() {
    printf("\n");
    printf("  1. �������� ������� � ����� �������\n");
    printf("  2. ������������ ������ �������.\n");
    printf("  3. ������������ ������ ��������.\n");
    printf("  4. ������� ������ �� �����.\n");
    printf("  5. ������� ������� �� �������.\n");
    printf("  6. ������� ������� �� ��������.\n");
    printf("  7. �����.\n");
    printf("\n  ");
}
void StepBack() {
    printf("\n");
    system("pause");
}
// Menu
void Menu(ArrayPtr arr_s) {
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
            ChangeArray(arr_s);
            break;
        }
        case('3'): {
            RandomArray(arr_s);
            break;
        }
        case('4'): {
            PrintArray(arr_s); 
            break;
        } 
        case('5'): {
            RemoveByIndex(arr_s);
            break;
        }
        case('6'): {
            RemoveByValue(arr_s);
            break;
        } 
        case('7'): {
            // exit
            return;
        }
        default: {
            Menu(arr_s);
            return;
        }
    } 
    StepBack();
    Menu(arr_s);
}



int main() {
    srand(time(0));
    system("chcp 1251");
    system("cls"); 
    
    Array arr_s = CreateArray(0);
    Menu(&arr_s);

	system("pause");
	return 0;
}


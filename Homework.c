#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
 

void PrintMenu() {
    printf("1. �������� ������� � ������\n");
    printf("2. ������������ ������ ���������.\n");
    printf("3. ������� ������.\n");
    printf("4. ������� ������� �� ��������.\n");
    printf("5. ������� ������� �� �������.\n");
    printf("6. �����.\n");
}
void StepBack() {
    int stepBack; 
    printf("\n������� 1 ����� ���������\n");  
    while (1) { 
        scanf("%d", &stepBack);  
        if (stepBack == 1)
            return; 
    } 
}


void DynamicPrintArray(int* mas, int* dynamicSize) { 
    printf("������: \n[ "); 
    for (int i = 0; i < *dynamicSize; i++) {
        printf("%d", *(mas+i));
        if (i + 1 != *dynamicSize)
            printf(", ");
    }
    printf(" ]\n");
} 
void DynamicPushBack(int* mas, int* dynamicSize) {
    printf("������� ��������\n"); 
    int newValue;
    *dynamicSize = *dynamicSize + 1; 
    scanf("%d", &newValue);
    *(mas+*dynamicSize-1) = newValue;
}
void DynamicChangeArray(int* mas, int* dynamicSize) {
    int newLen = -1; 
    while (newLen < 0 || newLen > 21) {
        printf("������� ����� ������� [0, 20]\n");
        scanf("%d", &newLen); 
    }  
    for (int i = 0; i < newLen; i++) {
        int value;
        // system("cls");
        printf("������� %d �����:\n", (newLen - i));
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
    printf("������� ��������, �� �������� �������� �������� �������: \n");
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
        printf("������� ������, �� �������� �������� �������� �������: \n");
        scanf("%d", &index);
    } 
    for (int k = index; k < *dynamicSize; k++)  
        *(mas + k) = *(mas + k + 1); 
    *dynamicSize = *dynamicSize - 1; 
    // DynamicPrintArray(mas, dynamicSize);
}

void DynamicMenu(int* mas, int* dynamicSize) {
    system("cls");  
    PrintMenu();
    char option;
    scanf("%s", &option); 
    system("cls"); 
    switch (option) {
        case('1'): {
            DynamicPushBack(mas, dynamicSize);
            break;
        }
        case('2'): {
            DynamicChangeArray(mas, dynamicSize);
            break;
        }
        case('3'): {
            DynamicPrintArray(mas, dynamicSize);
            printf("\n");
            int stepBack;
            printf("\n������� 1 ����� ���������\n");
            while (1) {
                scanf("%d", &stepBack);
                if (stepBack == 1)
                    break;
            }
            break;
        } 
        case('4'): {
            DynamicDeleteByValue(mas, dynamicSize);
            break;
        }
        case('5'): {
            DynamicDeleteByIndex(mas, dynamicSize);
            break;
        }
        case('6'): {
            // exit
            return;
        }
        default: {
            // DynamicMenu(mas, dynamicSize);
            return;
        }
    } 
    
    DynamicMenu(mas, dynamicSize);
}

int main() {
    system("chcp 1251");


    int *dynamicList;
    dynamicList = (int*)malloc(0 * sizeof(int));
    int dynamicSize = 0;   
    DynamicMenu(dynamicList, &dynamicSize);


	system("pause");
	return 0;
}


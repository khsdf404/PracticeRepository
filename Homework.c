#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
 

void PrintMenu() {
    printf("1. �������� ������� � ������\n");
    printf("2. ������������ ������ ���������.\n");
    printf("3. ������� ������.\n");
    printf("7. �����.\n");
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
    int* tmpmas = (int*)realloc(mas, (*dynamicSize) * sizeof(int));
    mas = tmpmas; 
    scanf("%d", &newValue);
    *(mas+*dynamicSize-1) = newValue;
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
            //DynamicChangeArray(mas, dynamicSize);
            break;
        }
        case('3'): {
            // print array
            break;
        } 
        case('4'): {
            // exit
            return;
        }
        default: {
            // DynamicMenu(mas, dynamicSize);
            return;
        }
    }
    DynamicPrintArray(mas, dynamicSize);
    printf("\n");
    StepBack();
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


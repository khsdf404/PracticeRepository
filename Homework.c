#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
 

void PrintMenu() {
    printf("1. �������� ������� � ������\n");
    printf("2. ������������ ������ ���������.\n");
    printf("3. ������� ������.\n");
    printf("7. �����.\n");
} 

void DynamicMenu(int* mas, int* dynamicSize) {
    system("cls");
    PrintMenu();
    char option;
    scanf("%s", &option); 
    system("cls"); 
    switch (option) {
        case('1'): {
            // DynamicPushBack(mas, dynamicSize);
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
            DynamicMenu(mas, dynamicSize);
            return;
        }
    }
    // DynamicPrintArray(mas, dynamicSize);
    // printf("\n");
    // StepBack();
    // DynamicMenu(mas, dynamicSize);
}


int main() {
    system("chcp 1251");


    int *dynamicList;
    dynamicList = (int*)malloc(5 * sizeof(int));
    int dynamicSize = 5;  
    DynamicMenu(&dynamicList[0], &dynamicSize); 


	system("pause");
	return 0;
}


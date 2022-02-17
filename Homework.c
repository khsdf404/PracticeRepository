#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
 

void PrintMenu() {
    printf("1. Вставить элемент в массив\n");
    printf("2. Перезаписать массив полностью.\n");
    printf("3. Вывести массив.\n");
    printf("7. Выйти.\n");
}
void StepBack() {
    char stepBack; 
    printf("\nВведите 1 чтобы вернуться\n");  
    while (1) { 
        scanf("%s", &stepBack);  
        if (stepBack == '1')
            break; 
    } 
}


void DynamicPrintArray(int* mas, int* dynamicSize) {
    printf("Массив: \n[ "); 
    for (int i = 0; i < *dynamicSize; i++) {
        printf("%d", *(mas + i));
        if (i + 1 != *dynamicSize)
            printf(", ");
    }
    printf(" ]\n");
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
    DynamicPrintArray(mas, dynamicSize);
    printf("\n");
    StepBack();
    DynamicMenu(mas, dynamicSize);
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


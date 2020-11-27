#include <stdio.h>
#include "..//controllers//controller.h"

int main()
{
    int patients, cure;
    scanf("%d %d", &patients, &cure);
    getchar();

    int day, year;
    char name[255], month[20];
    for (int i = 0; i < patients; i++) {
        scanf("%d %s %d - %[^\n]", &day, month, &year, name);
        getchar();
        pushMid(name, day, month, year);
    }

    for (int i = 0; i < cure; i++) {
        popHead();
    }

    if (!head) {
        int left = cure - patients;
        printf("All patients get the cure, %d cure left\n", left);
    } else {
        printAll();
    }


    return 0;
}
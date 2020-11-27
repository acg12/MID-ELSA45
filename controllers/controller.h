#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "..//models//model.h"

struct patients *head, *tail, *current;

int compareMonth(char *month1, char *month2)
{
    int mth1, mth2;
    for (int i = 1; i <= 12; i++)
    {
        if (strcmp(days[i], month1) == 0)
        {
            mth1 = i;
            break;
        }
    }

    for (int i = 1; i <= 12; i++)
    {
        if (strcmp(days[i], month2) == 0)
        {
            mth2 = i;
            break;
        }
    }

    if (mth1 > mth2)
        return -1;
    else if (mth1 < mth2)
        return 1;
    else
        return 0;
}

patients *createNewPatient(char *name, int day, char *month, int year) {
    patients *temp = (patients *)malloc(sizeof(patients));
    strcpy(temp->name, name);
    temp->day = day;
    strcpy(temp->month, month);
    temp->year = year;
    return temp;
}

void pushHead(char *name, int day, char *month, int year) {
    patients *newPat = createNewPatient(name, day, month, year);
    if (!head) {
        head = tail = newPat;
    } else {
        head->prev = newPat;
        newPat->next = head;
        head = newPat;
        head->prev = NULL;
    }
}

void pushTail(char *name, int day, char *month, int year) {
    patients *newPat = createNewPatient(name, day, month, year);
    if (!head) {
        head = tail = newPat;
    } else {
        tail->next = newPat;
        newPat->prev = tail;
        tail = newPat;
        tail->next = NULL;
    }
}

void pushMid(char *name, int day, char *month, int year) {
    patients *newPat = createNewPatient(name, day, month, year);
    if (!head) {
        head = tail = newPat;
    } else if (head->year > year) {
        pushHead(name, day, month, year);
    } else if (head->year == year) {
        if (compareMonth(head->month, month) == -1) {
            pushHead(name, day, month, year);
        }
        else if (compareMonth(head->month, month) == 0) {
            if (head->day > day) {
                pushHead(name, day, month, year);
            }
        }
    } else if (tail->year < year) {
        pushTail(name, day, month, year);
    } else if (tail->year == year) {
        if (compareMonth(tail->month, month) == 1) {
            pushTail(name, day, month, year);
        } else if (compareMonth(tail->month, month) == 0) {
            if (tail->day < day) {
                pushTail(name, day, month, year);
            }
        }
    } else {
        patients *temp = head;
        while (temp != NULL && temp->year < year) {
            temp = temp->next;
        }
        while (temp != NULL && temp->year == year && compareMonth(temp->month, month) == 1) {
            temp = temp->next;
        }
        while (temp != NULL && temp->year == year && compareMonth(temp->month, month) == 0 && temp->day > day) {
            temp = temp->next;
        }

        temp = temp->prev;
        temp->next->prev = newPat;
        newPat->next = temp->next;
        temp->next = newPat;
        newPat->prev = temp;
    }
}

void popHead() {
    if (!head) return;
    else if (head == tail) {
        head = tail = NULL;
        free(head);
    } else {
        patients *newhead = head->next;
        head->next->prev = NULL;
        head->next = NULL;
        free(head);
        head = newhead;
    }
}

void printAll() {
    if (!head) return;
    else {
        patients *temp = head;
        int ctr = 0;
        while (temp != NULL) {
            ctr++;
            temp = temp->next;
        }

        printf("Need %d more cure\n", ctr);
        temp = head;
        while (temp != NULL) {
            printf("%d %s %d - %s\n", temp->day, temp->month, temp->year, temp->name);
            temp = temp->next;
        }
    }
}
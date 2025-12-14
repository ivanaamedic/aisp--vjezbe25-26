#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Number number;
typedef struct Number* position;
struct Number {
    int el;
    position next;
};

int readFromFile(const char*, position);
int pushSorted(position*, int);
position getUnion(position, position);
position getIntersection(position, position);
int printList(position);
void freeList(position);

int main() {
    position l1 = NULL, l2 = NULL; //umisto position napisat Number l1, u drugoj liniji l1.Nexy=NULL
    int i = 0, j = 0;
    for (i = 10; i > 0; i--) {
        pushSorted(&l1, i);
    }
    for (j = 6; j < 16; j++) {
        pushSorted(&l2, j);
    }

    printf("List l1: ");
    printList(l1);
    printf("List l2: ");
    printList(l2);
    printf("Union: ");
    position unionList = getUnion(l1, l2);
    printList(unionList);
    printf("Intersection: ");
    position intersectionList = getIntersection(l1, l2);
    printList(intersectionList);

    freeList(l1);
    freeList(l2);
    freeList(unionList);
    freeList(intersectionList);

    return 0;
}

int pushSorted(position *head, int el) {
    position newList = (position)malloc(sizeof(number));
    if (!newList) {
        fprintf(stderr, "Memory allocation failed!\n");
        free(newList);
    }
    newList->el = el;
    newList->next = NULL;

    if (*head == NULL || (*head)->el >= el) {
        newList->next = *head;
        *head = newList;
    }
    else {
        position current = *head;
        while (current->next != NULL && current->next->el < el)
            current = current->next;
        newList->next = current->next;
        current->next = newList;
    }
    return 0;
}

int printList(position head) {
    if (head == NULL) {
        printf("Blank list!\n");
        return 0;
    }
    else {
        while (head != NULL) {
            printf("%d, ", head->el);
            head = head->next;
        }
        printf("\n");
    }
    return 0;
}

position getUnion(position l1, position l2) {
    position result = NULL;
    while (l1 != NULL || l2 != NULL) {
        if (l1 == NULL) {
            pushSorted(&result, l2->el);
            l2 = l2->next;
        }
        else if (l2 == NULL) {
            pushSorted(&result, l1->el);
            l1 = l1->next;
        }
        else {
            if (l1->el < l2->el) {
                pushSorted(&result, l1->el);
                l1 = l1->next;
            }
            else if (l2->el < l1->el) {
                pushSorted(&result, l2->el);
                l2 = l2->next;
            }
            else {
                pushSorted(&result, l1->el);
                l1 = l1->next;
                l2 = l2->next;
            }
        }
    }
    return result;
}

position getIntersection(position l1, position l2) {
    position result = NULL;
    while (l1 != NULL && l2 != NULL) {
        if (l1->el < l2->el) {
            l1 = l1->next;
        }
        else if (l2->el < l1->el) {
            l2 = l2->next;
        }
        else {
            pushSorted(&result, l1->el);
            l1 = l1->next;
            l2 = l2->next;
        }
    }
    return result;
}

void freeList(position head) {
    position temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
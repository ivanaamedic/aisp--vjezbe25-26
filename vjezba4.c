#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX (512)

typedef struct poly* Position;
typedef struct poly{
    int k; //koeficijent
    int e; //eksponent
    Position Next;
} polinom;

int createPoly(Position head) {
    char filename[MAX];
    printf("Enter filename: ");
    scanf(" %s", filename);
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("ERROR while opening file!!");
        return 2;
    }

    int k, e;
    Position current = head;
    while (fscanf(fp, " %d %d", &k, &e) == 2) {
        Position new = (Position)malloc(sizeof(polinom));
        if (new == NULL) {
            fclose(fp);
            return 1;
        }
        new->k = k;
        new->e = e;
        new->Next = NULL;

        // Insert in sorted order
        while (current->Next != NULL && e < current->Next->e) {
            current = current->Next;
        }
        // If same exponent, sum the coefficients
        if (current->Next != NULL && current->Next->e == e) {
            current->Next->k += k;
            free(new); // Free the newly created node
        } else {
            new->Next = current->Next;
            current->Next = new;
        }
        current = head; // Reset to start for next iteration
    }
    fclose(fp);
    return 0;
}

int print(Position head) {
    while (head != NULL) {
        printf(" %d*x^%d", head->k, head->e);
        if (head->Next != NULL) {
            printf(" +");
        }
        head = head->Next;
    }
    printf("\n");
    return 0;
}

Position add(Position head1, Position head2) {
    Position result = (Position)malloc(sizeof(polinom));
    if (result == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    result->Next = NULL;
    Position temp = result;

    while (head1 != NULL && head2 != NULL) {
        Position new = (Position)malloc(sizeof(polinom));
        if (new == NULL) {
            printf("Memory allocation failed!\n");
            return NULL;
        }
        if (head1->e == head2->e) {
            new->k = head1->k + head2->k;
            new->e = head1->e;
            head1 = head1->Next;
            head2 = head2->Next;
        } else if (head1->e > head2->e) {
            new->k = head1->k;
            new->e = head1->e;
            head1 = head1->Next;
        } else {
            new->k = head2->k;
            new->e = head2->e;
            head2 = head2->Next;
        }
        new->Next = NULL;
        temp->Next = new;
        temp = temp->Next;
    }

    // Append remaining terms
    Position remaining = head1 ? head1 : head2;
    while (remaining != NULL) {
        Position new = (Position)malloc(sizeof(polinom));
        new->k = remaining->k;
        new->e = remaining->e;
        new->Next = NULL;
        temp->Next = new;
        temp = temp->Next;
        remaining = remaining->Next;
    }

    return result->Next;
}

int main() {
    Position head1 = (Position)malloc(sizeof(polinom));
    if (head1 == NULL) {
        printf("Memory allocation failed!!");
        return 1;
    }
    head1->Next = NULL;

    Position head2 = (Position)malloc(sizeof(polinom));
    if (head2 == NULL) {
        printf("Memory allocation failed!!");
        free(head1);
        return 1;
    }
    head2->Next = NULL;

    printf("Creating first polynomial:\n");
    createPoly(head1);
    printf("First Polynomial:");
    print(head1->Next);

    printf("Creating second polynomial:\n");
    createPoly(head2);
    printf("Second Polynomial:");
    print(head2->Next);

    Position sum = add(head1->Next, head2->Next);
    printf("Sum Polynomial:");
    print(sum);

    // Free allocated memory (not shown here)
    return 0;
}
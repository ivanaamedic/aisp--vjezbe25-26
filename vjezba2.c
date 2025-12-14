#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person* Position;

typedef struct Person {
    char name[20];
    char surname[20];
    int BirthYear;
    Position next;
} Person;

Position CreatePerson() {
    Position newPerson = malloc(sizeof(Person));
    if (newPerson == NULL) {
        printf("Dinamička alokacija neuspjela!\n");
        return NULL;
    }
    printf("Unesite ime, prezime i godinu rođenja: ");
    if (scanf(" %19s %19s %d", newPerson->name, newPerson->surname, &newPerson->BirthYear) != 3) {
        printf("Format unosa pogrešan.\n");
        free(newPerson);
        return NULL;
    }
    newPerson->next = NULL;
    return newPerson;
}

int insertToFront(Position head) {
    Position newPerson = CreatePerson();
    if (newPerson == NULL) {
        return 1;
    }
    newPerson->next = head->next;  // Postavljamo novog na prvo mjesto
    head->next = newPerson;
    return 0;
}

void printAll(Position head) {
    Position current = head->next;  // Početak liste je head->next
    while (current != NULL) {
        printf("\n%s %s %d", current->name, current->surname, current->BirthYear);
        current = current->next;
    }
}

int insertToEnd(Position head) {
    Position current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    Position newPerson = CreatePerson();
    if (newPerson == NULL) {
        return 1;
    }

    current->next = newPerson;  // Dodavanje na kraj
    return 0;
}

int findsurname(Position head) {
    Position current = head->next;  // Krećemo od prvog čvora
    char c[20];
    printf("unesite prezime koje želite naći\n");
    scanf("%s", c);
    while (current != NULL) {
        if (strcmp(current->surname, c) == 0) {
            printf("Tražena osoba je:\n %s %s %d", current->name, current->surname, current->BirthYear);
            return 0;
        }
        current = current->next;
    }
    printf("Prezime nije na listi\n");
    return 1;
}

void DeleteList(Position head) {
    Position temp;
    while (head->next != NULL) {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }
}

int main() {
    int choice = 1;
    Position head = malloc(sizeof(Person));  // Kreiramo head
    if (head == NULL) {
        printf("Alokacija memorije nije uspjela.\n");
        return 1;
    }
    head->next = NULL;  // Inicijaliziramo listu kao praznu

    while (choice != 0) {
        printf("\nUnesite broj za opciju koju želite:\n1: Dodaj na početak\n2: Dodaj na kraj\n3: Ispiši listu\n4: Pronađi osobu po prezimenu\n5: Izbrisi listu\n0: Prekini program\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (insertToFront(head) != 0) {
                printf("Greška prilikom dodavanja na početak.\n");
                DeleteList(head);
                return 1;
            }
            break;

        case 2:
            if (insertToEnd(head) != 0) {
                printf("Greška prilikom dodavanja na kraj.\n");
                DeleteList(head);
                return 1;
            }
            break;

        case 3:
            printAll(head);
            break;

        case 4:
            if (findsurname(head) != 0) {
                printf("Greška prilikom pretrage po prezimenu.\n");
            }
            break;

        case 5:
            DeleteList(head);
            printf("Lista izbrisana\n");
            break;

        case 0:
            DeleteList(head);  // Oslobađanje memorije na kraju
            break;

        default:
            printf("Krivi unos. Ponovite!\n");
            continue;
        }
    }

    return 0;
}
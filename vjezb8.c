#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Cvor
{
    int br;
    struct Cvor* next;
} Cvor;

typedef Cvor* Pozicija;

int Push(Pozicija stog, int broj)
{
    Pozicija novi = (Pozicija)malloc(sizeof(Cvor));
    if (!novi) {
        printf("Greska: Ne mogu alocirati memoriju!\n");
        exit(1);
    }
    novi->br = broj;
    novi->next = stog->next;
    stog->next = novi;
    return 0;
}

int Pop(Pozicija stog, int* broj) {
    if (stog->next == NULL) {
        return -1;
    }
    Pozicija temp = stog->next;
    *broj = temp->br;
    stog->next = temp->next;
    free(temp);
    return 0;
}

int IzracunajPostfiksni(const char* izraz)
{
    Cvor stog;
    stog.next = NULL;
    int i = 0;

    while (izraz[i] != '\0') {
        if (isdigit(izraz[i])) {
            Push(&stog, izraz[i] - '0');
    }
        else if (strchr("+-*/", izraz[i])) {
            int b, a;
        if (Pop(&stog, &b) == -1 || Pop(&stog, &a) == -1) {

            printf("Greska: Premalo operanda za operaciju");
            exit(1);
}
    int rezultat;
    switch (izraz[i]) {
    case '+': rezultat = a + b; break;
    case '-': rezultat = a - b; break;
    case '*': rezultat = a * b; break;
    case '/':
    if (b == 0) {
        printf("Greska: Dijeljenje s nulom!\n");
        exit(1);
    }
    rezultat = a / b;
    break;
    }
    Push(&stog, rezultat);
    }
        i++;
    }

    int rezultat;
    if (Pop(&stog, &rezultat) == -1 || stog.next != NULL) {
        printf("Greska: Neispravan izraz! Na kraju treba ostati samo jedan broj.\n");
        exit(1);
    }

    return rezultat;
}

int main() {
    char izraz[100];
    FILE* datoteka = fopen("postfix.txt", "r");
    if (datoteka == NULL) {
        printf("Greska: Ne mogu otvoriti datoteku 'racun.txt'!\n");
        return 1;
    }

    if (fgets(izraz, sizeof(izraz), datoteka) == NULL) {
        printf("Greska: Ne mogu procitati izraz iz datoteke!\n");
        fclose(datoteka);
        return 1;
    }

    fclose(datoteka);

    int rezultat = IzracunajPostfiksni(izraz);
    printf("Rezultat postfiksnog izraza: %d\n", rezultat);

    return 0;
}
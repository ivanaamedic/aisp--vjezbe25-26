#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct _elem;
typedef struct _elem* Position;
typedef struct _elem {
    int el;
    int prioritet;
    Position Next;
}Elem;
Position createelem() {
    Position new = (Position)malloc(sizeof(Elem));
    if (new == NULL) {
        printf("Memory allocation fail !!");
        return 1;

    }
    new->Next = NULL;
    new->el = (rand() % 100) + 10;

    return new;
}
Position createred() {
    Position new = (Position)malloc(sizeof(Elem));
    if (new == NULL) {
        printf("Memory allocation fail!!");
        return 1;
    }
    new->Next = NULL;
    new->el = (rand() % 100) + 10;
    new->prioritet = (rand() % 5) + 1;
    return new;
}
int pushstog(Position head) {
    Position new = createelem();
    if (new == NULL) {
        printf("FAIL!!");
        return 1;
    }
    new->Next = head->Next;
    head->Next = new;

    return 0;
}
int printstog(Position head) {
    while (head->Next != NULL) {
        printf("%d\t", head->Next->el);
        head = head->Next;
    }
    return 0;


}


int popstog(Position head) {
    Position temp = head;
    temp = head->Next;
    head->Next = temp->Next;
    free(temp);
    return 0;
}
//b
int pushred(Position head2) {
    Position new = createred();
        if (new == NULL) {
        printf("Memory allocation fail 1!");
        return 1;
    }

    Position temp = head2;

    while (temp->Next != NULL && temp->Next->prioritet >= new->prioritet) {
    temp = temp->Next;
}


    new->Next = temp->Next;
        temp->Next = new;

    return 0;
}
int printred(Position head2) {
    while (head2->Next != NULL) {
        printf("%d (%d) \t", head2->Next->el,head2->Next->prioritet);
        head2 = head2->Next;
    }
    return 0;

}
int popred(Position head2) {
    Position temp = head2;
    temp = head2->Next;
    head2->Next = temp->Next;
    free(temp);

    return 0;
}


int freelist(Position head) {
    Position temp = head;
    while (head->Next != NULL) {
        temp = head->Next;
        head->Next = temp->Next;
        free(temp);
    }

    return 0;
}

int freelist2(Position head2) {
    Position temp = head2;
    while (head2->Next != NULL) {
        temp = head2->Next;
        head2->Next = temp->Next;
        free(temp);
    }

    return 0;
}
int main() {
    Position head = (Position)malloc(sizeof(Elem));
    if (head == NULL) {
        printf("Memory allocation fail !!");
        return 1;
    }
    head->Next = NULL;
    Position head2 = (Position)malloc(sizeof(Elem));
    if (head2 == NULL) {
        printf("Memory allocation fail !!");
        return 1;
    }
    head2->Next = NULL;

    int x = 1;
    /*int limit;
      int brojac = 0;
      printf("Unesite maksimalan broj  elemenata  za stog !!");
      scanf(" %d", &limit);*/
    while (x != 0) {
        printf("\n1-Push stog\n2-Print stog\n3-Pop stog\n4-Push red\n5-Print red\n6-Pop red\n0-Exit\n");
        scanf("%d", &x);
        int result = 0;

    switch (x) {

        case 1:
            /*if (brojac == limit) {
                        printf("\nStog je popunjen !!\n");
                        printstog(head);
                        printf("\nAko zelite ubaciti novi element izabacite postojece !\n");

                  }
                  else {
                        result = pushstog(head);
                        brojac++;
                  }*/
            result = pushstog(head);
                break;
        case 2:
            result = printstog(head);
            break;
        case 3:
            //brojac--;
            result = popstog(head);
            break;
        case 4:
            result = pushred(head2);
            break;
        case 5:
            result = printred(head2);
            break;
        case 6:
            result = popred(head2);
            break;


        }

        if (result == 1) {
            printf("Naredba nije uspjela !!\n");
            freelist(head);
            freelist2(head2);
            return 1;
        }
    }
    freelist2(head2);
    freelist(head);
    return 0;
}
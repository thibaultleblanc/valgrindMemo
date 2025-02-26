#include <stdio.h>
#include "linkedlist.h"
#include <valgrind/memcheck.h>

int main() {
    struct Node* head = NULL;

    appendNode(&head, 1);
    appendNode(&head, 2);
    appendNode(&head, 3);
    appendNode(&head, 4);

    printf("Liste chaînée initialisée : 1,2,3,4 ");
    printList(head);

    // Premier point de vérification Valgrind
    VALGRIND_DO_LEAK_CHECK;

    printf("Ajout et retraits de noeuds\n");
    removeNode(&head, 2);
    insertNode(&head, 2, 12);
    removeNode(&head, 1);
    insertNode(&head, 3, 7);
    insertNode(&head, 0, 52);
    removeNode(&head, 4);

    // Deuxième point de vérification Valgrind
    VALGRIND_DO_ADDED_LEAK_CHECK;

    printf("Liste chaînée: 51,1,12,4 --> 2 alloc en plus  ");
    printList(head);

    removeAllNodes(&head);
    printf("Liste chaînée: vide ");
    printList(head);

    return 0;
}
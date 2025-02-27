#include <stdio.h>
#include "linkedlist.h"

int main() {
    struct Node* head = NULL;

    appendNode(&head, 1);
    appendNode(&head, 2);
    appendNode(&head, 3);
    appendNode(&head, 4);

    printf("Liste chaînée: 1234 ");
    printList(head);

    removeNode(&head, 2);

    printf("Liste chaînée: 124 ");
    printList(head);

    return 0;
}
#include <stdio.h>
#include "linkedlist.h"

int main() {
    struct Node* head = NULL;

    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);

    printf("Liste chaînée: 1234 ");
    printList(head);

    removeNode(&head, 2);

    printf("Liste chaînée: 124 ");
    printList(head);

    return 0;
}
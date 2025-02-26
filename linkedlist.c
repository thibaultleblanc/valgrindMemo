#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

// Fonction pour insérer un nœud à une position spécifique
struct Node* insertNode(struct Node** head_ref, int pos, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;

    if (pos == 0) {
        new_node->next = *head_ref;
        *head_ref = new_node;
        return new_node;
    }

    struct Node* temp = *head_ref;
    for (int i = 0; temp != NULL && i < pos - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position invalide\n");
        free(new_node);
        return NULL;
    }

    new_node->next = temp->next;
    temp->next = new_node;

    return new_node;
}

// Fonction pour supprimer un nœud à une position spécifique
struct Node* removeNode(struct Node** head_ref, int pos) {
    if (*head_ref == NULL) {
        return NULL;
    }

    struct Node* temp = *head_ref;

    if (pos == 0) {
        *head_ref = temp->next;
        free(temp);
        return *head_ref;
    }

    for (int i = 0; temp != NULL && i < pos - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Position invalide\n");
        return NULL;
    }

    struct Node* next = temp->next->next;
    free(temp->next);
    temp->next = next;

    return *head_ref;
}

void removeAllNodes(struct Node** head_ref) {
    struct Node* current = *head_ref;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head_ref = NULL;
}

// Fonction pour ajouter un nœud à la fin de la liste
struct Node* appendNode(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head_ref;

    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return new_node;
    }

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new_node;
    return new_node;
}

// Fonction pour supprimer le premier nœud de la liste
struct Node* popNode(struct Node** head_ref) {
    if (*head_ref == NULL) {
        return NULL;
    }

    struct Node* temp = *head_ref;
    *head_ref = (*head_ref)->next;
    free(temp);

    return *head_ref;
}

// Fonction pour afficher la liste chaînée
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}
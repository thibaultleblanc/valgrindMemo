#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Définition de la structure pour un nœud de la liste chaînée
struct Node {
    int data;
    struct Node* next;
};

// Fonction pour insérer un nœud à une position spécifique
struct Node* insertNode(struct Node** head_ref, int pos, int new_data);

// Fonction pour supprimer un nœud à une position spécifique
struct Node* removeNode(struct Node** head_ref, int pos);

// Fonction pour supprimer tous les nœuds de la liste
void removeAllNodes(struct Node** head_ref);

// Fonction pour ajouter un nœud à la fin de la liste
struct Node* appendNode(struct Node** head_ref, int new_data);

// Fonction pour supprimer le premier nœud de la liste
struct Node* popNode(struct Node** head_ref);

// Fonction pour afficher la liste chaînée
void printList(struct Node* node);

#endif // LINKEDLIST_H
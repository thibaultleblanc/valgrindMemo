#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour représenter un objet
typedef struct {
    char *name;
    int age;
} Person;

// Fonction pour libérer la mémoire d'un objet Person
void free_person(gpointer data) {
    Person *person = (Person *)data;
    free(person->name);
    free(person);
}

int main() {
    // Créer une table de hachage
    GHashTable *hash_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_person);

    // Ajouter des objets alloués dynamiquement
    Person *person1 = malloc(sizeof(Person));
    person1->name = strdup("Alice");
    person1->age = 30;
    g_hash_table_insert(hash_table, strdup("key1"), person1);

    Person *person2 = malloc(sizeof(Person));
    person2->name = strdup("Bob");
    person2->age = 25;
    g_hash_table_insert(hash_table, strdup("key2"), person2);

    // Accéder à un objet
    Person *retrieved_person = g_hash_table_lookup(hash_table, "key1");
    if (retrieved_person) {
        printf("Name: %s, Age: %d\n", retrieved_person->name, retrieved_person->age);
    }

    // Libérer la mémoire de la table de hachage
    g_hash_table_destroy(hash_table);

    // // Nettoyer les allocations internes de GLib
    // g_hash_table_unref(hash_table);

    return 0;
}
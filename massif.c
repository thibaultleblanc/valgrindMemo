#include <stdlib.h>

void g(void)
{
    void *ptr = malloc(4000); // Stocker le pointeur retourné
    if (ptr == NULL) {
        // Gérer une éventuelle erreur d'allocation
        exit(EXIT_FAILURE);
    }
}

void f(void)
{
    void *ptr = malloc(2000); // Stocker le pointeur retourné
    if (ptr == NULL) {
        // Gérer une éventuelle erreur d'allocation
        exit(EXIT_FAILURE);
    }
    g();
}

int main(void)
{
    int i;
    int *a[10];

    for (i = 0; i < 10; i++)
    {
        a[i] = malloc(1000);
        if (a[i] == NULL) {
            // Gérer une éventuelle erreur d'allocation
            exit(EXIT_FAILURE);
        }
    }

    f();

    g();

    for (i = 0; i < 10; i++)
    {
        free(a[i]);
    }

    return 0;
}
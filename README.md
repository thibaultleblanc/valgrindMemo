# README

## Tuto valgrind

Objectif manipuler avec Valgrind

Prérequis : docker + accès aux dépôts (vim, gcc, gdb, valgrind)

## Start

```bash
docker run -ti \
            --rm \
            --name valgrind \
            --volume $PWD:/app \
            --workdir /app \
            --entrypoint /app/install.sh \
            debian:latest
```

## Basic examples

```bash
# readelf -S affiche les symboles présents dans le header
readelf -S helloworld.o | grep ".debug_info"
valgrind ./helloworld.o
echo -e '\n\e[32m *** PAS DE FUITE *** \e[0m\n\n'
```

```bash
# readelf -S affiche les symboles présents dans le header
readelf -S neverfree.o | grep ".debug_info"
valgrind ./neverfree.o
echo -e '\n\e[31m *** JAMAIS DE FREE --> definitely lost *** \e[0m\n\n'

valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./neverfree.o

# Rapport en XML --> --xml-file=rapport.xml
```

## Observer le tas avec massif

```bash
valgrind --tool=massif --massif-out-file=./massif-result.out ./massif.o
ms_print massif-result.out


valgrind --tool=massif --time-unit=B --massif-out-file=./massif-result.out ./massif.o
ms_print massif-result.out
```

## Valgrind entre 2 points

compile with : gcc [...] -I/usr/include/valgrind

```c
#include <valgrind/memcheck.h>
/* YOUR CODE HERE */
VALGRIND_DO_LEAK_CHECK; // --> reference check
/* YOUR CODE HERE */
VALGRIND_DO_ADDED_LEAK_CHECK; // --> delta
```


```bash
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         ./addremove.o
```

## Usefull links and documentation

https://valgrind.org/docs/manual/ms-manual.html
https://docs.redhat.com/fr/documentation/red_hat_enterprise_linux/6/html/performance_tuning_guide/ch05s03s03#idm139680962952352

## glib examples

### g_hash_table

A l'instanciation du programme la glib initialise des objets en mémoire. Cette mémoire apparait comme "still reachable dans les rapports valgrind". Il est possible de fournir à valgrind une liste d'erreur à supprimer de son rapport. Ces suppressions sont généralement dans un fichier ".supp".

Il est également possible de demander à valgrind de générer des blocs suppression pour chaque erreur trouvée :
```bash
valgrind  --gen-suppressions=yes \
          --leak-check=full \
          --show-leak-kinds=all \
          --track-origins=yes \
          ./g_hash_table.o
```

Valgrind devient interractif et demande s'il faut générer une suppression pour chaque erreur.

```
==5078==
==5078== HEAP SUMMARY:
==5078==     in use at exit: 18,804 bytes in 9 blocks
==5078==   total heap usage: 22 allocs, 13 frees, 20,232 bytes allocated
==5078==
==5078== 4 bytes in 1 blocks are still reachable in loss record 1 of 9
==5078==    at 0x48850C8: malloc (vg_replace_malloc.c:381)
==5078==    by 0x496CE77: ??? (in /usr/lib/aarch64-linux-gnu/libglib-2.0.so.0.7400.6)
==5078==    by 0x496D5EF: g_private_get (in /usr/lib/aarch64-linux-gnu/libglib-2.0.so.0.7400.6)
==5078==    by 0x4936457: g_slice_alloc (in /usr/lib/aarch64-linux-gnu/libglib-2.0.so.0.7400.6)
==5078==    by 0x4902BCB: g_hash_table_new_full (in /usr/lib/aarch64-linux-gnu/libglib-2.0.so.0.7400.6)
==5078==    by 0x4927747: ??? (in /usr/lib/aarch64-linux-gnu/libglib-2.0.so.0.7400.6)
==5078==    by 0x48DDFCB: ??? (in /usr/lib/aarch64-linux-gnu/libglib-2.0.so.0.7400.6)
==5078==    by 0x4004447: call_init (dl-init.c:74)
==5078==    by 0x4004447: call_init (dl-init.c:26)
==5078==    by 0x4004553: _dl_init (dl-init.c:121)
==5078==    by 0x401AD37: (below main) (dl-start.S:46)
==5078==
==5078==
==5078== ---- Print suppression ? --- [Return/N/n/Y/y/C/c] ---- y
{
   <insert_a_suppression_name_here>
   Memcheck:Leak
   match-leak-kinds: reachable
   fun:malloc
   obj:/usr/lib/aarch64-linux-gnu/libglib-2.0.so.0.7400.6
   fun:g_private_get
   fun:g_slice_alloc
   fun:g_hash_table_new_full
   obj:/usr/lib/aarch64-linux-gnu/libglib-2.0.so.0.7400.6
   obj:/usr/lib/aarch64-linux-gnu/libglib-2.0.so.0.7400.6
   fun:call_init
   fun:call_init
   fun:_dl_init
   fun:(below main)
}
```

En fournissant le fichier, g_hash_table.supp les erreurs ne sont plus présentes dans le rapport.

```bash
valgrind --suppressions=g_hash_table.supp --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         ./g_hash_table.o
```
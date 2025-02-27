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
         ./addremov.o
```

## Usefull links and documentation

https://valgrind.org/docs/manual/ms-manual.html
https://docs.redhat.com/fr/documentation/red_hat_enterprise_linux/6/html/performance_tuning_guide/ch05s03s03#idm139680962952352

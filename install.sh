#! /bin/bash

set -euo pipefail

apt update && apt install -y gcc gdb valgrind git tmux vim libglib2.0-dev

gcc -Werror -g -o helloworld.o helloworld.c
gcc -Werror -g -o neverfree.o neverfree.c linkedlist.c
gcc -Werror -g -o addremove.o addremove.c linkedlist.c -I/usr/include/valgrind
gcc -Werror -g -o massif.o massif.c

gcc -Werror -g -o g_hash_table.o g_hash_table.c $(pkg-config --cflags --libs glib-2.0)

alias ll="ls -larth"

bash
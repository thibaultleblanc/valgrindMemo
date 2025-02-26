#! /bin/bash

apt update && apt install -y gcc gdb valgrind git tmux vim

gcc -Werror -g -o helloworld.o helloworld.c
gcc -Werror -g -o neverfree.o neverfree.c linkedlist.c
gcc -Werror -g -o addremove.o addremove.c linkedlist.c -I/usr/include/valgrind
gcc -o massif.o massif.c

alias ll="ls -larth"

bash
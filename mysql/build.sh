#!/bin/bash

gcc -g -c -I/usr/include/mysql int_main.c
gcc int_main.o -lmysqlclient -o a.out

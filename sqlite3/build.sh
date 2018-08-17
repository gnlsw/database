#!/bin/bash

if [ $# -ne 1 ]
then
    echo "input parameter: build | run | clean"
    exit 1
fi

if [ $1 == "build"  ]
then
    gcc -g -c sqlite3_api.c 
    gcc sqlite3_api.o -l sqlite3 -o test_api
elif [ $1 == "clean"  ]
then
    rm -rf test_api
    rm -rf *.o
elif [ $1 == "run"  ]
then
    gcc -g -c sqlite3_api.c 
    gcc sqlite3_api.o -l sqlite3 -o test_api
    ./test_api database.db "select * from COMPANY"
else
    echo "input parameter: build | run | clean"
    exit 1
fi

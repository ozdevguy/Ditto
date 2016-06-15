#!/bin/bash
clang++ -I/home/users/bcrawford/Development/src/compiler/ test.cpp -o test
chmod 0777 test
./test

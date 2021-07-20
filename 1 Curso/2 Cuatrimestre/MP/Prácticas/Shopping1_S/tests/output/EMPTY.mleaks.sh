#!/bin/bash
/usr/bin//valgrind --leak-check=full ./dist/Debug/GNU-Linux/shopping1_s < ./tests/validation/EMPTY.keyboard 1> /dev/null 2>> ./tests/output/EMPTY.mleaks.full

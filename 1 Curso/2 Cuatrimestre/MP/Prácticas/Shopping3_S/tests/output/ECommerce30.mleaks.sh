#!/bin/bash
/usr/bin//valgrind --leak-check=full ./dist/Debug/GNU-Linux/shopping2_s -noargs < ./tests/validation/ECommerce30.keyboard 1> /dev/null 2>> ./tests/output/ECommerce30.mleaks.full

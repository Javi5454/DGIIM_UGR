#!/bin/bash
/usr/bin//valgrind --leak-check=full ./dist/Debug/GNU-Linux/shopping2_s < ./tests/validation/ECommerce_all_all_500.keyboard 1> /dev/null 2>> ./tests/output/ECommerce_all_all_500.mleaks.full

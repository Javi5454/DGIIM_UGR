#!/bin/bash
/usr/bin//valgrind --leak-check=full ./dist/Debug/GNU-Linux/shopping2_s -input ./data/PrimerCaso.dataset -events 20 -K 100 -type cart < ./tests/validation/PrimerCaso.keyboard 1> /dev/null 2>> ./tests/output/PrimerCaso.mleaks.full

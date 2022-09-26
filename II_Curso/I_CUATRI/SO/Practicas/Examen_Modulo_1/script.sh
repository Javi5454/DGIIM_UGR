#!/bin/bash
# Titulo: Script Exámen Prácticas Módulo I
# Fecha: 19/10/2021
# Autor: Javier Gomez Lopez
# Version: 1.0

if [ $# != 1 ]
then 
echo "Argument error <PID>"
exit 1
fi

exist=$(ps v c | grep $1)

case "$exist" in
    "") echo "Process does not exist";;
    *) show1=$(ps v c $1 | cut -d' ' -f12)
    show2=$(ps v c $1 | cut -d' ' -f9)
    echo $show1 $show2
    show3=$(ps v c $1 | cut -d' ' -f26)
    show4=$(ps v c $1 | cut -d' ' -f25)
    echo $show3 " " $show4
    show5=$(ps v c $1 | cut -d' ' -f29)
    echo $show5;;
esac
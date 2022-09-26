#!/bin/bash
# Titulo: Actividad 3.2 SO
# Fecha: 5/10/2021
# Autor: Javier Gómez López
# Versión: 1.0

if [ $# != 1 ]
then 
    echo "Argument error <number of iterations>"
    exit 1
fi

i=0
while [ $i -lt $1 ]
do
    let resultado=10+7
    ((i++))
done

echo "El valor de la variable es $1"
echo $resultado
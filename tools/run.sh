#!/bin/bash

#run make in commandline before running this file
 
out="result.txt"
if [[ ! -e "$out" ]]; then
	touch "result.txt"
fi 


options=("Ingresar una matriz de entrada (manual)"  \
"Indicar archivo de salida (result.txt por defecto)" "Sumar Matrices" \
"Multiplicar Dos Matrices" "Transponer Matriz" \
"Duplicar Matrices" "Comparar Matrices" "Multiplicar por Escalar" \
"Crear Matriz Nula" "Crear Matriz Identidad" "Imprimir Matriz" \
"Imprimir Resultado de Operaciones" "Ayuda" "Terminar")

echo "LIBRERIA MATRICES"
echo "MENU DE OPCIONES: "
PS3="Seleccione una opcion:"
select action in "${options[@]}"
do 
	case $action in 
	  "Ingresar una matriz de entrada (manual)")
		  echo "Ingrese nombre de archivo para la matriz"
		  read matriz_uno
		  echo -n > $matriz_uno
		  echo "M1" >> $matriz_uno
		  echo "Ingrese las dimensiones de la matriz"
		  echo "ingrese filas: "
		  read filas 
		  echo "Ingrese columnas: "
		  read columnas
		  echo "$filas $columnas" >> $matriz_uno
		  dim=$(  bc <<< "$filas*$columnas" )
		  for (( i=1; i <= $dim; i++ )); do
			 echo "Ingresar proximo valor de la matrix: "
			 read value
			 echo -n "$value "  >> $matriz_uno
		  done
		  echo >> $matriz_uno
	  ;;
	  "Indicar archivo de salida (result.txt por defecto)")
		  echo "Indicar si quiere especificar un archivo de salida."
		  echo "El resultado se guarda por defecto en result.txt. Ingrese s/n"
		  read bool 
		  if [[ $bool == "s" ]]; then 
			  echo "Ingrese nombre de archivo de salida"
			  read out
		  else 
			  echo "El archivo de salida es result.txt"
		  fi
	  ;;
	  "Sumar Matrices")
		  echo "Ingrese nombre de archivo de primera matriz"
		  read matriz_uno
		  echo "Ingrese nombre de archivo de segunda matriz"
		  read matriz_dos
		  ./main -1 $matriz_uno -2 $matriz_dos -p sum -o $out
	  ;;
	  "Multiplicar Dos Matrices")
		  echo "Ingrese nombre de archivo de primera matriz"
		  read matriz_uno
		  echo "Ingrese nombre de archivo de segunda matriz"
		  read matriz_dos
		  ./main -1 $matriz_uno -2 $matriz_dos -p mult -o $out
	  ;;
	  "Transponer Matriz")
		  echo "Ingrese nombre de archivo de la matriz a transponer"
		  read matriz_uno 
		  ./main -1 $matriz_uno -p trans -o $out
	   ;;
	  "Duplicar Matrices")
		  echo "Ingrese nombre de archivo de la matriz"
		  read matriz_uno
		  ./main -1 $matriz_uno -p dup -o $out
	  ;;
	  "Comparar Matrices")
		  echo "Ingrese nombre de archivo de primera matriz"
		  read matriz_uno
		  echo "Ingrese nombre de archivo de segunda matriz"
		  read matriz_dos
		  ./main -1 $matriz_uno -2 $matriz_dos -p cmp -o $out
	  ;;
	  "Multiplicar por Escalar")
		   echo "Ingrese archivo de matriz de entrada : "
		   read matriz_uno
		   echo "Ingrese valor escalar: " 
		   read escalar
		   ./main -1 $matriz_uno -p mult_scalar -s $escalar -o $out
	  ;;
	   "Crear Matriz Nula")
		   echo "Ingrese archivo de matriz de entrada : "
		   read matriz_uno
		   ./main -1 $matriz_uno -p null -o $out
	  ;;
	  "Crear Matriz Identidad")
			echo "Ingrese archivo de matriz de entrada : "
			read matriz_uno
			./main -1 $matriz_uno -p idty -o $out
	  ;;
	  "Ayuda")
			./main --help
		;;
	  "Imprimir Matriz")
			echo "Ingrese archivo de matriz para imprimir : "
			read matriz_uno
			echo "La matriz $matriz_uno es: "
			tail -n +2 $matriz_uno 
	  ;;
	  "Imprimir Resultado")
			tail -n +2 "$out" 
	  ;;
	  "Terminar")
			echo "Finalizando"
			exit 0
	  ;;
	 esac
done

exit 0

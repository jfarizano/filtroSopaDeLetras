rm palabras.txt;
echo "Filtrando palabras.";
if ./filtro.out; then
	echo "Creando sopa de letras.";
	python3 sopaDeLetras.py 1;
	echo "Programado finalizado";
	sleep 2
else
	echo "No se lleno un archivo satisfactorio, abortando."
fi

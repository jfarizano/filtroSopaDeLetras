if [ -f "palabras.txt" ]; then
	rm palabras.txt;
fi
if [ -f "aFiltrar.txt" ]; then
	echo "Filtrando palabras.";
	if ./filtro.out; then
		echo "Creando sopa de letras.";
		python3 sopaDeLetras.py 1;
		echo "Programado finalizado";
		sleep 2
	else
		echo "No se lleno un archivo satisfactorio, abortando."
	fi
	else
		echo "aFiltrar.txt no enconctrado, no se pueden cargar palabras"
fi

echo "Filtrando palabras."
gcc filtro.c -o filtro.out && ./filtro.out
echo "Creando sopa de letras."
python3 sopaDeLetras.py 1
echo "Programado finalizado"
sleep 2

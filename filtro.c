#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/*
    sumaArr: int[] int -> int
    Dado un array de enteros y la longitud del mismo, devuelve la suma
    de sus elementos
*/
int sumaArr(int array[], int len){
    
    int suma = 0;

    for (int i = 0; i < len; i++){
        suma += array[i];
    }

    return suma;
}

/* 
    revertirPalabra(): char[] -> char[]
    Dada un array de caracteres (string) y un array vacío de tamaño longitud de string+1, reemplaza
    el segundo array por el reverso del primero (string al revés).
*/
void revertirPalabra(char str[], char reversa[]){
    
    int len = strlen(str);
    
    for (int i = 0; i < len; i++){
        reversa[i] = str[len-i-1];
    }
}

/*
    stringContenido: char[] char[] -> Int
    Dado dos arrays de char, devuelve 1 si el segundo array esta contenido dentro del primero,
    en caso contrario devuelve 0
*/
int stringContenido(char strExt[], char strInt[]){
    // Ext: String exterior, Int: String interior.
    int lenExt = strlen(strExt), lenInt = strlen(strInt);
    int flag = 0, coincidencias;

    for(int i = 0; i <= lenExt-lenInt; i++){
        coincidencias = 0;
        for(int j = i; j < lenInt+i; j++){
            if(strExt[j] == strInt[j-i]){
                coincidencias += 1;
            }
        }

        if (coincidencias == lenInt){
            flag = 1;
        }
    }

    return flag;
}

/*                               
   __                             _         
   \ \      ███╗   ███╗ █████╗ ██╗███╗   ██╗
    \ \     ████╗ ████║██╔══██╗██║████╗  ██║
     > \    ██╔████╔██║███████║██║██╔██╗ ██║
    / ^ \   ██║╚██╔╝██║██╔══██║██║██║╚██╗██║
   /_/ \_\  ██║ ╚═╝ ██║██║  ██║██║██║ ╚████║
            ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝                                                                                                       

    main(): None -> Int
    Inicializa el programa 
*/
int main(){

    // Declaración de variables
    FILE *archivo;
    int contadorInicial = 0, contadorElegidas = 0, tamanioFinal, tamanioRand;
    char palabras[100][16];

    // Inicializa el generador aleatorio de números
    srand(time(NULL));
    
    // Array cuyos elementos son 1 (TRUE) si la palabra que se encuentra
    // en el mismo índice en palabras cumple las condiciones.
    int cumpleCondicion[100]; 
    // Se inicializa el array con todos los elementos iguales a 0 para
    // evitar errores por basura en memoria.
    for (int i = 0; i < 100; i++){
        cumpleCondicion[i] = 0;
    }

    // Apertura del archivo de entrada
    archivo = fopen("aFiltrar.txt", "r");

    // Lectura inicial del archivo a un array. (Primer filtro por longitud)
    if (archivo) {
        char buff[50];
        while (fscanf(archivo, "%s", buff) != EOF)
            if (strlen(buff) >= 4 && strlen(buff) <= 16){
                strcpy(palabras[contadorInicial], buff);
                cumpleCondicion[contadorInicial] = 1;
                contadorInicial++; // Cuenta la cantidad de palabras que cumplan la primer condición.
           }
        fclose(archivo);
    }

    // Segundo y tercer filtro.
    for (int i = 0; i < contadorInicial; i++){
        if(cumpleCondicion[i]){
            
            // Inicializa la variable reversa
            char reversa[strlen(palabras[i])+1];
            revertirPalabra(palabras[i], reversa);

            for (int j = 0; j < contadorInicial; j++){
                if (i != j && cumpleCondicion[j] != 0){
                    // Segundo filtro (Eliminar palabras repetidas y su reversa)
                    if (strcmp(palabras[i], palabras[j]) == 0 || strcmp(palabras[i], reversa) == 0){
                        cumpleCondicion[j] = 0;
                    // Tercer filtro (Eliminar palabras contenidas dentro de la otra)
                    }else if (stringContenido(palabras[i], palabras[j]) || stringContenido(reversa, palabras[j])){
                        cumpleCondicion[j] = 0;
                    }
                }
            }
        }
    }
    
    // Revisa la cantidad de palabras que pasaron todos los filtors
    tamanioFinal = sumaArr(cumpleCondicion, 100);
    // Crea un array cuyos elementos son los indices de las palabras que cumplieron las condiciones
    int cumplen[tamanioFinal];
    int test = 0;
    for (int i = 0; i < 100; i++){
        if (cumpleCondicion[i]){
            cumplen[test] = i;
            test++;
        }
    }
    
    // Seleccionar aleatoriamente entres las palabras restantes.
    tamanioRand = (rand() % tamanioFinal)+1;
    char palabrasElegidas[tamanioRand][16];

    while(contadorElegidas != tamanioRand){
        int random = cumplen[rand() % tamanioFinal];
        if (strlen(palabras[random]) != 0){
            strcpy(palabrasElegidas[contadorElegidas], palabras[random]);
            contadorElegidas++;
            strcpy(palabras[random], "");
        }
    }

    // Escritura del archivo de salida
    archivo = fopen("palabras.txt", "w");
    for (int i = 0; i < tamanioRand-1; i ++){
        fputs(palabrasElegidas[i], archivo);
        fputs("\n", archivo);
    }
    fputs(palabrasElegidas[tamanioRand-1], archivo);
    fclose(archivo);
    
    return 0;
}
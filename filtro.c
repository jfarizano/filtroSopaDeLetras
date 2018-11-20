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
    filtros: char[] char[] Int -> None
    Dado un array de strings, filtra las palabras y coloca las que cumplan los requisitos dados en un array, devuelve
    la cantidad de palabras que cumplieron con los requisitos
*/


int filtros(char palabras[][], char palabrasFiltradas[][], int cumpleCondicion[]){

    int cantFiltradas;

    for (int i = 0; i < 100; i++){
        if (cumpleCondicion[i]){
            // Primer filtro (Eliminar palabras cuya longitud sea menor a 4 o mayor a 15) 
            if (strlen(palabras[i]) < 4 || strlen(palabras[i]) > 15){
                cumpleCondicion[i] = 0;
            }else{
                // Inicializa la variable reversa
                char reversa[strlen(palabras[i])+1];
                revertirPalabra(palabras[i], reversa);

                for (int j = 0; j < cantInicial; j++){
                    if (i != j && cumpleCondicion[j]){
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
    }

    // Calcula la cantidad de palabras que pasaron todos los filtros
    cantFiltradas = sumaArr(cumpleCondicion, 100);

    return cantFiltradas;
}


//========================================================================================================
//========================================================================================================
//========================================================================================================
//========================================================================================================
//========================================================================================================

/*                               
        __                             _         
        \ \        ███╗   ███╗ █████╗ ██╗███╗   ██╗
         \ \       ████╗ ████║██╔══██╗██║████╗  ██║
          > \      ██╔████╔██║███████║██║██╔██╗ ██║
         / ^ \     ██║╚██╔╝██║██╔══██║██║██║╚██╗██║
        /_/ \_\    ██║ ╚═╝ ██║██║  ██║██║██║ ╚████║
                   ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝                                                                                                       

    main(): None -> Int
    Inicializa el programa 
*/
int main(){

    // Declaración de variables
    FILE *archivo;
    char palabras[100][50];
    int cantInicial = 0, contadorElegidas = 0, cantFiltradas = 0, cantPalabrasRestantes;
    int tamRandom;

    // Inicializa el generador de números aleatorios
    srand(time(NULL));

    // Apertura del archivo de entrada
    archivo = fopen("aFiltrar.txt", "r");

    // Lectura inicial del archivo a un array.
    if (archivo) {
        char buff[50]; // Almacenamiento temporal de la palabra
        while (fscanf(archivo, "%s", buff) != EOF){
                strcpy(palabras[cantInicial], buff);
                cantInicial++; // Cuenta la cantidad de palabras que se ingresaron.
        }
        fclose(archivo);
	}

    // Definición del array con la selección de palabras elegidas aleatoriamente y su tamaño
    tamRandom = (rand() % cantInicial) + 1;
    char palabrasRandom[tamRandom][50];

    // Primera selección de palabras aleatorias
    while (contadorElegidas != tamRandom){
        int random = rand() % cantInicial; // Selección de un índice aleatorio
        if (palabras[random][0] != '\0'){
            strcpy(palabrasRandom[contadorElegidas], palabras[random]);
            palabras[random][0] = '\0';
            contadorElegidas++;
            cantPalabrasRestantes--;
        }
    }

    // Array cuyos elementos son 1 (TRUE) si la palabra que se encuentra
    // en el mismo índice en palabras cumple las condiciones.
    int cumpleCondicion[100]; 
    // Se inicializa el array con todos los elementos iguales a 1 para
    // ir igualando a 0 a medida que una palabra no cumpla con los requisitos
    for (int i = 0; i < cantInicial; i++){
        cumpleCondicion[i] = 1;
    }
    // Los restantes elementos (indices donde no se encuentran palabras) se igualan a 0
    for (int i = cantInicial; i < 100; i++){
        cumpleCondicion[i] = 0;
    }
    

    // Mientras la cantidad de palabras que cumplen los requisitos sea distinto a la cantidad elegida
    // eligirá nuevas palabras
    cantFiltradas = 0;
    while (contadorElegidas != tamRandom && cantPalabrasRestantes != 0){
        cantFiltradas = filtros(palabras, palabrasRandom, cumpleCondicion);
    }


    /*
    // Escritura del archivo de salida
    archivo = fopen("palabras.txt", "w");
    for (int i = 0; i < tamanioRand-1; i ++){
        fputs(palabrasElegidas[i], archivo);
        fputs("\n", archivo);
    }
    fputs(palabrasElegidas[tamanioRand-1], archivo);
    fclose(archivo);
    */

    return 0;
}
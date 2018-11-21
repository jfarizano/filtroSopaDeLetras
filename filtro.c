#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/* 
    revertirPalabra(): char[] char[] -> None
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
    en caso contrario devuelve 0.
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
    filtros: char[] int -> None
    Dado un array de strings, si un string no cumple con los criterios se reemplaza por un string vacío, devuelve
    la cantidad de palabras que cumplieron con los criterios.
*/
int filtros(char palabrasElegidas[][50], int cantAElegir){

    int cantElegidas = 0;

    for (int i = 0; i < cantAElegir; i++){
        if (strlen(palabrasElegidas[i]) != 0){
            // Primer filtro (Eliminar palabras cuya longitud sea menor a 4 o mayor a 15) 
            if (strlen(palabrasElegidas[i]) < 4 || strlen(palabrasElegidas[i]) > 15){
                palabrasElegidas[i][0] = '\0';
            }else{
                // Inicializa la variable reversa
                char reversa[strlen(palabrasElegidas[i])+1];
                revertirPalabra(palabrasElegidas[i], reversa);

                for (int j = 0; j < cantAElegir; j++){
                    if (i != j && strlen(palabrasElegidas[j]) != 0){
                        // Segundo filtro (Eliminar palabras repetidas tanto al derecho como al revés)
                        if (strcmp(palabrasElegidas[i], palabrasElegidas[j]) == 0 || strcmp(palabrasElegidas[i], reversa) == 0){
                            palabrasElegidas[j][0] = '\0';
                        // Tercer filtro (Eliminar palabras contenidas dentro de la otra)
                        }else if (stringContenido(palabrasElegidas[i], palabrasElegidas[j]) || stringContenido(reversa, palabrasElegidas[j])){
                            palabrasElegidas[j][0] = '\0';
                        }
                    }
                }
            }
        }
    }

    // Cuenta cuantas palabras cumplieron con los criterios
    for (int i = 0; i < cantAElegir; i++){
        if (strlen(palabrasElegidas[i]) != 0){
            cantElegidas++;
        }
    }

    return cantElegidas;
}

/*
    elegirAleatoriamente: char[][] char[][] int int int -> int
    Dado los arrays con las palabras ingresadas, las palabras ya elegidas (o strings vacíos en caso de que sea la primer iteración),
    la cantidad de palabras ingresadas, la cantidad que quedan para elegir entre estas mismas y la cantidad de palabraas que hay que elegir.
    Mientras haya palabras para elegir y haya un lugar disponible en palabrasElegidas, coloca una palabra al azar del primer array
    en el segundo en una posición donde haya un string vacío.
    Devuelve la cantidad de palabras restantes que quedan para elegir
*/
int elegirAleatoriamente(char palabras[][50], char palabrasElegidas[][50], int cantPalabrasIngresadas, int cantPalabrasRestantes, int cantAElegir){
    for (int i = 0; i < cantAElegir; i++){
        while (strlen(palabrasElegidas[i]) == 0 && cantPalabrasRestantes != 0){
            int random = rand() % cantPalabrasIngresadas; // Selección de un índice aleatorio
            if (strlen(palabras[random]) != 0){
                strcpy(palabrasElegidas[i], palabras[random]);
                palabras[random][0] = '\0'; // Evita que se vuelva a elegir la misma palabra
                cantPalabrasRestantes--;
            }
        }
    }

    return cantPalabrasRestantes;
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

    main(): None -> int
    Abre el archivo con las palabras a filtrar, las escribe en un array, elige al azar una cantidad aleatoria, 
    y las filtra. Cuando cumpla con la cantidad aleatoria de palabras a elegir, las escribe en un archivo de salida,
    en caso contrario printea un mensaje de error.
*/
int main(){

    // Declaración de variables
    FILE *archivo;
    char palabras[100][50];
    int cantPalabrasIngresadas = 0; // Representa la cantidad de palabras ingresadas en el archivo
    int cantPalabrasRestantes; // Representa la cantidad de palabras restantes que quedan para ser elegidas aleatoriamente
    int cantAElegir; // Este número aleatorio en el rango [1, cantPalabrasIngresadas] representa la cantidad de palabras que se 
    // van a elegir aleatoriamente
    int cantElegidas = 0; // Representa la cantidad de palabras elegidas que cumplen con los criterios dados 
    

    // Inicializa el generador de números aleatorios
    srand(time(NULL));

    // Lectura inicial del archivo a un array.
    if (access("aFiltrar.txt", F_OK) == 0){ // Comprueba si el archivo con las palabras a filtrar existe
        
        archivo = fopen("aFiltrar.txt", "r"); // Apertura del archivo de entrada
        
        char buff[50]; // Almacenamiento temporal de la palabra
        while (fscanf(archivo, "%s", buff) != EOF){
                strcpy(palabras[cantPalabrasIngresadas], buff);
                cantPalabrasIngresadas++; // Cuenta la cantidad de palabras que se ingresaron.
        }
        fclose(archivo);
	

        // Al principio la cantidad de palabras que pueden ser elegidas va a ser a la cantidad total de palabras ingresadas
        cantPalabrasRestantes = cantPalabrasIngresadas;

        // Definición del array con la selección de palabras elegidas aleatoriamente y su tamaño
        cantAElegir = (rand() % cantPalabrasIngresadas) + 1;
        char palabrasElegidas[cantAElegir][50];
        // Inicialización del array con todos sus elementos iguales al string vacío
        for (int i = 0; i < cantAElegir; i++){
            palabrasElegidas[i][0] = '\0';
        } 
    

        // Primera selección de palabras aleatorias
        cantPalabrasRestantes = elegirAleatoriamente(palabras, palabrasElegidas, cantPalabrasIngresadas, cantPalabrasRestantes, cantAElegir);
    
        // Se filtran las palabras hasta que obtengan la cantidad requerida o ya no haya palabras restantes para elegir
        while (cantElegidas != cantAElegir && cantPalabrasRestantes != 0){
            cantElegidas = filtros(palabrasElegidas, cantAElegir);
            if (cantElegidas != cantAElegir){
                cantPalabrasRestantes = elegirAleatoriamente(palabras, palabrasElegidas, cantPalabrasIngresadas, cantPalabrasRestantes, cantAElegir);
           }
        }

        for (int i = 0; i < cantPalabrasIngresadas; i++){
            printf("%d %s\n",i, palabras[i]);
        }
        for (int i = 0; i < cantAElegir; i++){
            printf("%d %s\n", i, palabrasElegidas[i]);
        }
        printf("%d %d %d\n", cantAElegir, cantElegidas, cantPalabrasRestantes);

        // Condiciones finales
        if (cantAElegir == cantElegidas){
            // Escritura al archivo de salida
            archivo = fopen("palabras.txt", "w");
            for (int i = 0; i < cantAElegir-1; i ++){
                fputs(palabrasElegidas[i], archivo);
                fputs("\n", archivo);
            }
            fputs(palabrasElegidas[cantAElegir-1], archivo);
            fclose(archivo);
        }else{
            printf("No se pudo obtener la cantidad necesaria de palabras\n");
        }

    }else{
        printf("No existe el archivo de entrada (aFiltrar.txt)\n");
    }
    return 0;
}
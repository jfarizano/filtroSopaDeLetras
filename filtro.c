#include <stdio.h>
#include <string.h>

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
    reversa[len] = '\0';
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
    int contador = 0;
    char palabras[100][16];
    
    // Array cuyos elementos son 1 (TRUE) si la palabra que se encuentra
    // en el mismo índice en palabras cumple las condiciones.
    int cumpleCondicion[100]; 
    // Se inicializa el array con todos los elementos iguales a 0 para
    // evitar errores por basura en memoria.
    for (int i = 0; i < 100; i++){
        cumpleCondicion[i] = 0;
    }

    // Apertura del archivo
    archivo = fopen("aFiltrar.txt", "r");

    // Lectura inicial del archivo a un array. (Primer filtro por longitud)
    if (archivo) {
        char buff[16];
        while (fscanf(archivo, "%s", buff) != EOF)
            if (strlen(buff) > 4 && strlen(buff) <= 16){
                strcpy(palabras[contador], buff);
                cumpleCondicion[contador] = 1;
                contador++; // Cuenta la cantidad de palabras que cumplan la primer condición.
           }
        fclose(archivo);
    }

    // Segundo y tercer filtro.
    for (int i = 0; i < contador; i++){
        if(cumpleCondicion[i]){
            
            // Inicializa la variable reversa
            char reversa[strlen(palabras[i])+1];
            revertirPalabra(palabras[i], reversa);

            for (int j = 0; j < contador; j++){
                if (i != j){
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

    return 0;
}
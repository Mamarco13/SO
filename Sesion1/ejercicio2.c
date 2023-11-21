/*
Ejercicio2.c
Pagina 3 de la primera sesion del modulo 2
Implementa un programa que realice la siguiente funcionalidad. El programa
acepta como argumento el nombre de un archivo (pathname), lo abre y lo lee en bloques de
tamaño 80 Bytes, y crea un nuevo archivo de salida, salida.txt, en el que debe aparecer la
siguiente información:
Bloque 1
// Aquí van los primeros 80 Bytes del archivo pasado como argumento.
Bloque 2
// Aquí van los siguientes 80 Bytes del archivo pasado como argumento.
...
Bloque n
// Aquí van los siguientes 80 Bytes del archivo pasado como argumento.
Si no se pasa un argumento al programa se debe utilizar la entrada estándar como archivo de
entrada.
*/


#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

int main(int argc, char* argv[]){
    //descriptores de los archivos de ficheros entrada y salida
    int entrada, salida;
    //bytes leidos/escritos
    int bytes = 80;
    //contador de bloques 
    int bl;
    //buffer del que veamos a leer y escribir
    char buffer[81];
    //vamos a guardar el bloque n para escribirlo en el fichero
    char bloque[10];
    //escribimos el salto de linea
    char salto_linea[3];

    //Si el programa tiene argumentos....
    if(argc == 2){
        //abrir el fichero en solo lectura
        entrada = open(argv[1], O_RDONLY);
    }    

    //en caso de no haberle pasado argumentos
    else{
        //cogemos entrada estandar
        entrada = open(argv[1], O_RDONLY);
    }
    //vemos si hemos tenido un problema al abrir el archivo
    if(entrada<0){
        printf("Error en la apertura del archivo de entrada");
        exit(-1);
    }
    //creamos el archivo de salida
    salida = open("salida.txt", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
    //vemos si hemos tenido un problema al crear el archivo
    if(salida <0){
        printf("Error en la apertura del archivo de salida");
        exit(-2);
    }

    //vamos leyendo hasta que lleguemos a fin de fichero, la condición de parada del for es hasta que
    //read devuelva 0 que será cuando llegue  afinal de fichero
    for(int i = 0; read(entrada,buffer,bytes);i++){
        //para escribir en el archivo Bloque numero cuando vamos a escribir un bloque
        sprintf(bloque, "Bloque %d", i);
        write(salida, bloque, sizeof(bloque));

         //para escribir salto de linea
         write(salida, "\n", sizeof("\n"));

         //escribimos lo que hemos leido de entrada
         write(salida, buffer, bytes);

         //para escribir salto de linea
         write(salida, "\n", sizeof("\n"));
    }

    //ESTA REGULAR LO ADICIONAL
    /*Modificación adicional. ¿Cómo tendrías que modificar el programa para que una vez finalizada la escritura
    en el archivo de salida y antes de cerrarlo, pudiésemos indicar en su primera línea el número de etiquetas
    ''Bloque i'' escritas de forma que tuviese la siguiente apariencia?:
    El número de bloques es <no_bloques>
    Bloque 1
    // Aquí van los primeros 80 Bytes del archivo pasado como argumento.
    ..*/

    //hacemos espacio para escribir el numero de etiquetas al principio del fcihero con lo que avanzamos al current file offset
    lseek(salida,sizeof("El numero de bloques es 100"), SEEK_SET);

    //for de escritura en salida
    for(int i = 0; read(entrada, buffer, bytes); i++){
        sprintf(bloque, "Bloque %d", i);
        write(salida, bloque, sizeof(bloque));
        write(salida,"\n", sizeof("\n"));
        write(salida, buffer, bytes);
        write(salida,"\n", sizeof("\n"));
        bl = i;
    }
    //al terminar de escribir nos posicionamos al principio del fichero
    lseek(salida,0,SEEK_SET);
    //escribimos la linea con el numero de bloques
    printf(bloque, "El numero de bloques es %d", bl);
    //escribimos la frase al principio del fichero
    write(salida, bloque,sizeof(bloque));
}


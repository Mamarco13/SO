/*
    Cambia los permisos de los archivos de un directorio y devuelve los arcgivos con sus permisos antiguos y sus permisos nuevos.
    Todos los permisos se expresan en octal.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <c++/11/bits/ranges_util.h>


int main(int argc, char *argv[]) {
    char *pathname;          //Argumento 1
    int permisos;            //Argumento 2 (formato octal)
    DIR *directorio;         //Directorio pathname
    struct dirent *archivo;  //Cada entrada del directorio
    char nom_dir[1000];      //Nombre de cada entrada del directorio
    struct stat atributos;   //Atributos de nom_dir
    mode_t antiguos;         //Permisos antiguos de las entradas

    //Comprobamos que el formato de ejecucion es ejecutable+pathname+permisos
    if(argc !=3){
        printf("ERROR en argumentos. \nEl formato es ./ejercicio2 nombre_directorio permisos");
        exit(-1);
    }
    //En caso de haber ejecutado correctamente:
    else{
        //guardamos el nombre del fichero 
        pathname = argv[1];

        //guardamos los permisos de la cadena de char en un long int en octal
        /*la funcion strtol(cadena a convertir, NULL, base)*/
        permisos = strtol(argv[2], NULL, 8);

        //abrimos el directorio
        directorio = opendir(pathname);

        //comprobamos si ha habido error en la apertura
        if(directorio == NULL){
            printf("ERROR en la aperturadel directorio %s", pathname);
            exit (-2);
        }
    }

    //leemos mientras no haya error o no llegue al final del stream del directorio
    while((archivo = readdir(directorio)) != NULL){
        //si el directorio padre o actual ignoramos
        if(strcmp(archivo->d_name,".") != 0&& strcmp(archivo->d_name, "..") != 0){
            //almacenamos la ruta con el nombre de la carpeta y el archivo en pathname
            //de forma que quedaría carpeta/archivo
            sprintf(nom_dir, "%s/%s", nom_dir, archivo->d_name);

            //obtenemos los atributos del archivo: si hay error, lo mostramos por pantalla
            if(stat(pathname, &atributos)<0){
                printf("ERROR en la obtencion de los atributos de %s - %s \n", nom_dir, strerror(errno));
            }
            //si no ha habido problema al obtener los atributos
            else{
                //guardamos los permisos
                antiguos = atributos.st_mode;
                //modificamos los permisos de pathname a permisos (argumento 2)
                if(chmod(pathname, permisos)<0){
                    //si hay error, mostramos el nombre + error + permisos antiguos
                    printf("%s: %o %s \n", archivo->d_name, antiguos, strerror(errno));
                }
                else{
                    //obtenemos los atributos actualizados
                    stat(pathname, &atributos);

                    //si no ha habido error mostramos:
                    //nombre + permisos antiguos + permisos nuevos
                    printf("%s: %o %o \n", archivo->d_name, antiguos, atributos.st_mode);
                }
            }
        }
    }
    return 0;
}

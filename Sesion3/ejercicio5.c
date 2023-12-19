#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>	
#include<sys/wait.h>	
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
    //intervalo 0 (i0) para los argumentos; intervalo 1 (i1) para el hijo 1, intervalo 2 (i2) para el hijo 2
    int i0[2], i1[2], i2[2];

    pid_t h1, h2;
    int c1[2], c2[2];
    int mensaje = 0;
    char primo[4], arg1[4], arg2[4];

    if(argc < 3){
    perror("ERROR en argumentos. \n El formato es ./maestro limite_inferior limite_superior.\n");
    exit(-1);
    }


    /*Creacion de intervalos*/
    //obtenemos el intervalo
    i0[0] = atoi(argv[1]);
    i0[1] = atoi(argv[2]);
    //comprobamos si han insertado primero el límite sup y después el límite inf
    if(i0[0] > i0[1]){
    i0[0] = i0[1];
    i0[1] = atoi(argv[1]);
    }
    //hacemos la división de intervalos el intervalo1 será para el hijo1
    i1[0] = i0[0];
    i1[1] = ((i0[0] + i0[1])/2);
    //el intervalo2 será para el hijo2
    i2[0] = i1[1] + 1;
    i2[1] = i0[1];


    /* CAUCE 1, PRIMER HIJO */
    //creamos el cauce1
    pipe(c1);
    //Primer hijo
    if((h1 = fork())<0){
        perror("Problema creando el fork");
        exit(-1);
    }
    else if(h1 == 0){
        close(c1[0]);
        dup2(c1[1],STDOUT_FILENO);

        //pasamos los límites a cadena para pasarlos como argumento a exec
        sprintf(arg1, "%i", i1[0]);
        sprintf(arg2, "%i", i1[1]);

        //ejecutamos el esclavo y comprobamos que no ha habido error
        if( execl("./esclavo", "./esclavo", arg1, arg2, NULL) < 0 ){
            perror("ERROR al ejecutar esclavo1\n");
            exit(-3);
        }
    }
    else{
            close(c1[1]);
            dup2(c1[0], STDIN_FILENO);
            printf("Hijo 1: \n");
            //LEE DE LA ENTRADA ESTANDAR
            while( mensaje = read(c1[0], primo, sizeof(int)) > 0)
                printf("\t%s es primo\n", primo); 
            close(c1[0]);
        }
    /*CAUCE 2, SEGUNDO HIJO */
    //creamos el cauce 2
    pipe(c2);
    //segundo hijo
    if((h2 = fork()) < 0){
        perror("Error en la creacion del fork");
        exit(-1);
    }
    else if(h2 == 0){
        close(c2[0]);
        dup2(c2[1], STDOUT_FILENO);

        //pasar los limites como argumento por lo tanto mutarlos a char
        sprintf(arg1, "%i", i2[0]);
        sprintf(arg2, "%i", i2[1]);

        //ejecutamos el esclavo y comprobamos que no ha habido error
        if( execl("./esclavo", "./esclavo", arg1, arg2, NULL) < 0 ){
            perror("ERROR al ejecutar esclavo1\n");
            exit(-3);
        }
    }
    else{
            close(c2[1]);
            dup2(c2[0], STDIN_FILENO);
            printf("Hijo 2: \n");
            //LEE DE LA ENTRADA ESTANDAR
            while( mensaje = read(c2[0], primo, sizeof(int)) > 0)
                printf("\t%s es primo\n", primo); 
            close(c2[0]);
        }
    return 0;
}

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
int esPrimo(int n){
    int primo = 1;
    //recorremos desde 2 < k <= sqrt(n)
    for(int i = 2; i <= sqrt(n) && primo; i++){
        //si es divisible, ya no es primo
        if(n%i == 0){
            primo = 0;
        }
    }
    return primo;
}
int main(int argc, char *argv[]){
    int lim_inf, lim_sup;
    char primo[4];
    //comprobamos que se ha pasado como argumento el intervalo
    if(argc < 3){
        perror("ERROR en argumentos. \n  El formato es ./esclavo limite_inferior limite_superior.\n");
        exit(-1);
    }
    //obtenemos el intervalo
    lim_inf = atoi(argv[1]);
    lim_sup = atoi(argv[2]);
    //comprobamos si han insertado primero el lim sup y después el lim inf
    if(lim_inf > lim_sup){
        lim_inf = lim_sup;
        lim_sup = atoi(argv[1]);
    }
    //calculamos los primos en dicho intervalo
    for(int i = lim_inf; i <= lim_sup; i++){
        //vemos si es primo
        if(esPrimo(i)){
            sprintf(primo, "%i", i);
            //si es primo, lo escribimos por la salida estándar para que lo lea el padre
            write(STDOUT_FILENO, primo, sizeof(int));
        }
    }
    return 0;
}
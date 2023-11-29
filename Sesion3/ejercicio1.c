/*Implementa un programa en C que tenga como argumento un número entero. Este
programa debe crear un proceso hijo que se encargará de comprobar si dicho número es un
número par o impar e informará al usuario con un mensaje que se enviará por la salida estándar.
A su vez, el proceso padre comprobará si dicho número es divisible por 4, e informará si lo es o
no usando igualmente la salida estándar.*/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void padre_hijo(int n) {
    pid_t pid;
    pid = fork();
    
    if (pid < 0) {
        perror("\nError al crear el proceso hijo\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("\nSoy el hijo\n");
        if (n % 2 == 0)
            printf("Este numero es par\n");
        else
            printf("Este numero es impar\n");
    } else if (pid > 0) {
        printf("\nSoy el padre\n");
        if (n % 4 == 0)
            printf("Este numero es divisible entre 4\n");
        else
            printf("Este numero no es divisible entre 4\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <numero>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int numero = atoi(argv[1]); // Convertir el argumento a entero

    if (numero <= 0) {
        printf("Por favor, ingrese un número entero positivo.\n");
        exit(EXIT_FAILURE);
    }

    padre_hijo(numero);

    return 0;
}

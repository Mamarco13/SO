#define _XOPEN_SOURCE 500 // Es posible que necesites definir esto para habilitar la función nftw

#include <stdio.h>
#include <ftw.h>
#include <stdlib.h>
#include <sys/stat.h>

// Contadores para la cuenta total
int total_archivos = 0;
long long total_tamanio = 0;

// Función que se llama para cada archivo/directorio encontrado
int visitar(const char *ruta, const struct stat *info, int tipo, struct FTW *flags) {
    if (tipo == FTW_F) {  // Si es un archivo regular
        // Comprobar si tiene permisos de ejecución para grupo y otros
        if ((info->st_mode & S_IXGRP) && (info->st_mode & S_IXOTH)) {
            // Imprimir información sobre el archivo
            printf("%s %lu\n", ruta, (unsigned long)info->st_ino);

            // Actualizar contadores
            total_archivos++;
            total_tamanio += info->st_size;
        }
    }
    return 0; // Devuelve 0 para continuar la exploración del árbol
}

int main(int argc, char *argv[]) {
    const char *directorio;

    // Establecer el directorio de inicio según los argumentos
    if (argc > 1) {
        directorio = argv[1];
    } else {
        directorio = ".";  // Directorio actual si no se proporciona argumento
    }

    // Llama a la función nftw
    if (nftw(directorio, visitar, 20, FTW_PHYS) == -1) {
        perror("nftw");
        return 1;
    }

    // Imprimir el total al final
    printf("Existen %d archivos regulares con permiso x para grupo y otros\n", total_archivos);
    printf("El tamaño total ocupado por dichos archivos es %lld bytes\n", total_tamanio);

    return 0;
}

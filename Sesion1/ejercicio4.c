/*El programa determina el tipo de fichero de los archivos pasados como argumento. El programa hace lo
siguiente:
• Comprueba que hay argumentos de entrada; si no los hay, sale del programa (primer if(argc < 2);
• Si hay argumentos, recorre todos los argumentos, que son nombres de ficheros, y para cada uno de
ellos:
◦ imprime el nombre;
◦ comprueba si puede acceder a sus atributos;
◦ comprueba el tipo de archivo con el flag que tiene activado (S_ISREG, S_ISDIR);
◦ imprime el tipo de fichero.
3.5 Ejercicio 4
Ejercicio 4. Define una macro en lenguaje C que tenga la misma funcionalidad que la macro S_ISREG(mode)
usando para ello los flags definidos en <sys/stat.h> para el campo st_mode de la struct stat, y comprueba
que funciona en un programa simple. Consulta en un libro de C o en Internet cómo se especifica una macro
con argumento en C.
#define S_ISREG2(mode) ...*/
#define S_ISREG2(mode) (mode & S_IFMT == S_IFREG)
/*Para ver si un fichero es de tipo regular, tomamos S_IFMT, que es la máscara para el tipo de fichero, y le
hacemos un AND con el modo recibido. Si el resultado es igual a S_IFREG, es que es regular; en caso
contrario, es de otro tipo.*/
/*Indica qué tipo de jerarquías de procesos se generan mediante la ejecución de cada
uno de los siguientes fragmentos de código. Comprueba tu solución implementando un código
para generar 20 procesos en cada caso, en donde cada proceso imprima su PID y el del padre,
PPID.*/
/*
Jerarquía de procesos tipo 1
*/
for (i=1; i < nprocs; i++) {
    if ((childpid = fork()) == -1) {
        fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
        exit(-1);
    }
    if (childpid)
    break;
}
/*
Jerarquía de procesos tipo 2
*/
for (i=1; i < nprocs; i++) {
    if ((childpid = fork()) == -1) {
        fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
        exit(-1);
    }
    if (!childpid)
    break;
}
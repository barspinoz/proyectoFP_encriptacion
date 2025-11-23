#include <stdio.h>
#define MAX 3

void leerTexto () {
    /*matriz de entrada*/
    char palabra[MAX][MAX];
    int numeroTexto[MAX][MAX] = {0};

    /*abrir archivo de texto*/
    FILE * texto;
    texto = fopen("texto.txt", "r");

    /*comprobar que se abra correctamente el archivo texto.txt*/
    if (texto == NULL) {
        printf("Error al abrir el archivo\n");
    }
    /*guardar valores del archivo en la matriz*/
    else {
        fscanf(texto, "%c %c %c %c", &palabra[0][0], &palabra[0][1], &palabra[0][2], &palabra[1][0]);
        //printf("%c %c %c\n", palabra[0][0], palabra[0][1], palabra[0][2]);//debug 1
        //printf("%c %c %c\n", palabra[1][0], palabra[1][1], palabra[1][2]);//debug 2
        fclose(texto);
    }
}
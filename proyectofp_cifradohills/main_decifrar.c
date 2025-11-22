#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 100
#define FILAS 3
#define COLUMNAS 1

/*funcion para obtener valor a partir de letra*/
int obtenerValor(char letra, int abecedario[26]) {
    if (letra >= 'a' && letra <= 'z') {
        return abecedario[letra - 'a'];
    }
    return 0; //para valores invalidos
}

/*funcion para obtener letra a partir de valor*/
int obtenerLetra(int valor, int abecedario[26]) {
    for (int i = 0; i < 26; i++) {
        if (abecedario[i] == valor) {
            return 'a' + i;
        }
    }
    return '?'; //para valores invalidos
}

/*funcion para calcular la inversa de la matriz clave*/
void matrizInversa(int clave[FILAS][FILAS], float inversa[FILAS][FILAS]) {
    float a00 = clave[0][0], a01 = clave[0][1], a02 = clave[0][2];
    float a10 = clave[1][0], a11 = clave[1][1], a12 = clave[1][2];
    float a20 = clave[2][0], a21 = clave[2][1], a22 = clave[2][2];

    float det = a00*(a11*a22 - a12*a21) - a01*(a10*a22 - a12*a20) + a02*(a10*a21 - a11*a20);
    if (fabsf(det) < 1e-6f) {
        printf("La matriz clave no es invertible.\n");
        exit(1);
    }
    float invDet = 1.0f / det;

    inversa[0][0] = invDet * (a11*a22 - a12*a21);
    inversa[0][1] = invDet * (-(a01*a22 - a02*a21));
    inversa[0][2] = invDet * (a01*a12 - a02*a11);

    inversa[1][0] = invDet * (-(a10*a22 - a12*a20));
    inversa[1][1] = invDet * (a00*a22 - a02*a20);
    inversa[1][2] = invDet * (-(a00*a12 - a02*a10));

    inversa[2][0] = invDet * (a10*a21 - a11*a20);
    inversa[2][1] = invDet * (-(a00*a21 - a01*a20));
    inversa[2][2] = invDet * (a00*a11 - a01*a10);
}

int main () {
    /*abecedario*/
    int abecedario[26];

    /*matriz de entrada*/
    char palabra[MAX];
    char matriz[MAX][FILAS][COLUMNAS] = {0}; //MAX representa el numero maximo de matrices

    /*intermedias*/
    char palabraIndex[MAX] = {0};
    int i = 0;
    int j = 0;
    int k = 0;
    int m = 0;
    int n = 0;
    int longitud = 0;
    int numeroMatrices = 0;
    int capacidadMatriz = FILAS * COLUMNAS;
    int claveHill[FILAS][FILAS] = {{1,2,3},{0,4,5},{1,0,6}}; //matriz clave
    float inversaClave[FILAS][FILAS];
    int matrizDecifrada[MAX][FILAS][COLUMNAS] = {0}; //MAX representa el numero maximo de matrices

    /*leer archivo con valores de las letras*/
    FILE * valores;
    valores = fopen("valores.txt", "r");
    fscanf(valores, "%d %d %d %d %d %d %d %d %d %d %d %d %d", &abecedario[0], &abecedario[1], &abecedario[2], &abecedario[3], &abecedario[4], &abecedario[5], &abecedario[6], &abecedario[7], &abecedario[8], &abecedario[9], &abecedario[10], &abecedario[11], &abecedario[12]);
    fscanf(valores, "%d %d %d %d %d %d %d %d %d %d %d %d %d", &abecedario[13], &abecedario[14], &abecedario[15], &abecedario[16], &abecedario[17], &abecedario[18], &abecedario[19], &abecedario[20], &abecedario[21], &abecedario[22], &abecedario[23], &abecedario[24], &abecedario[25]);
    fclose(valores);
    
    /*abrir archivo de texto*/
    FILE * cifrado;
    cifrado = fopen("cifrado.txt", "r");

    /*comprobar que se abra correctamente el archivo texto.txt*/
    if (cifrado == NULL) {
        printf("Error al abrir el archivo\n");
    }

    else {
        /*leer sin espacios*/
        while (fscanf(cifrado, "%99s", palabraIndex) == 1)
        {
            strcat(palabra, palabraIndex);
        }
        fclose(cifrado);

        /*calcular numero de matrices*/
        longitud = strlen(palabra);
        numeroMatrices = longitud / capacidadMatriz;
        if (longitud % capacidadMatriz != 0) {
            numeroMatrices++;
        }
        
        /*llenar matriz*/
        for(m = 0; m < numeroMatrices; m++) {
            for(i = 0; i < FILAS; i++) {
                for(j = 0; j < COLUMNAS; j++) {
                    if(k < longitud) {
                        matriz[m][i][j] = palabra[k++];
                    }
                    else {
                        matriz[m][i][j] = 'x'; //marcador para posiciones vacias
                    }
                }
            }
        }

        /*decifrado de hills*/
        matrizInversa(claveHill, inversaClave);
        for(m = 0; m < numeroMatrices; m++) {
            for(i = 0; i < FILAS; i++) {
                for(j = 0; j < COLUMNAS; j++) {
                    matrizDecifrada[m][i][j] = 0;
                    for(n = 0; n < FILAS; n++) {
                        matrizDecifrada[m][i][j] += inversaClave[i][n] * obtenerValor(matriz[m][n][j], abecedario);
                    }
                    matrizDecifrada[m][i][j] %= 26;
                }
            }
        }
        

    }

    /*imprimir matriz decifrada (debug)*/
    for(m = 0; m < numeroMatrices; m++) {
        for(i = 0; i < FILAS; i++) {
            for(j = 0; j < COLUMNAS; j++) {
                printf("%c", obtenerLetra(matrizDecifrada[m][i][j], abecedario));
            }
        }
    }
    printf("\n");

    /*guardar en archivo*/
    FILE * decifrado;
    decifrado = fopen("decifrado.txt", "w");
    for(m = 0; m < numeroMatrices; m++) {
        for(i = 0; i < FILAS; i++) {
            for(j = 0; j < COLUMNAS; j++) {
                fprintf(decifrado, "%c", obtenerLetra(matrizDecifrada[m][i][j], abecedario));
            }
        }
    }
    fprintf(decifrado, "\n");
    fclose(decifrado);

    return 0;
}

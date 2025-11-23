#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 100
#define FILAS 3
#define COLUMNAS 3

int obtenerValor(char letra, int abecedario[26]) {
    if (letra >= 'a' && letra <= 'z') {
        return abecedario[letra - 'a'];
    }
    return 0; //para valores invalidos
}

int obtenerLetra(int valor, int abecedario[26]) {
    for (int i = 0; i < 26; i++) {
        if (abecedario[i] == valor) {
            return 'a' + i;
        }
    }
    return '?'; //para valores invalidos
}

int main () {
    /*abecedario*/
    int abecedario[26];

    /*matriz de entrada*/
    char palabra[MAX];
    char matriz[FILAS][COLUMNAS] = {0};

    /*intermedias*/
    int i = 0;
    int j = 0;
    int k = 0;
    int longitud = 0;
    int matrizCifrada[FILAS][COLUMNAS] = {0};

    /*leer archivo con valores de las letras*/
    FILE * valores;
    valores = fopen("valores.txt", "r");
    fscanf(valores, "%d %d %d %d %d %d %d %d %d %d %d %d %d", &abecedario[0], &abecedario[1], &abecedario[2], &abecedario[3], &abecedario[4], &abecedario[5], &abecedario[6], &abecedario[7], &abecedario[8], &abecedario[9], &abecedario[10], &abecedario[11], &abecedario[12]);
    fscanf(valores, "%d %d %d %d %d %d %d %d %d %d %d %d %d", &abecedario[13], &abecedario[14], &abecedario[15], &abecedario[16], &abecedario[17], &abecedario[18], &abecedario[19], &abecedario[20], &abecedario[21], &abecedario[22], &abecedario[23], &abecedario[24], &abecedario[25]);
    fclose(valores);
    /*imprimir abecedario (debug)*/
    printf("Abecedario (DEBUG):\n");
    for (int i = 0; i < 26; i++) {
        printf("DEBUG: %c: %d\n", 'a' + i, abecedario[i]);
    }

    /*abrir archivo de texto*/
    FILE * texto;
    texto = fopen("texto.txt", "r");

    /*comprobar que se abra correctamente el archivo texto.txt*/
    if (texto == NULL) {
        printf("Error al abrir el archivo\n");
    }
    /*guardar valores del archivo en la matriz*/
    else {
        fscanf(texto, "%s", palabra);
        fclose(texto);

        /*llenar matriz*/
        longitud = strlen(palabra);

        for(i = 0; i < FILAS; i++) {
            for(j = 0; j < COLUMNAS; j++) {
                if(k < longitud) {
                    matriz[i][j] = tolower(palabra[k++]); //se convierte a minuscula
                }
                else {
                    matriz[i][j] = '-'; //marcador para posiciones vacías
                }
            }
        }

        /*mostrar matriz (con letras) (debug)*/
        printf("\nMatriz (DEBUG):\n");
        for(i = 0; i < FILAS; i++) {
            for(j = 0; j < COLUMNAS; j++) {
                printf("[%c] ", matriz[i][j]);
            }
            printf("\n");
        }
    
        /*mostrar matriz (con numeros) (debug)*/
        printf("\nMatriz (DEBUG):\n");
        for(i = 0; i < FILAS; i++) {
            for(j = 0; j < COLUMNAS; j++) {
                printf("[%d] ", obtenerValor(matriz[i][j], abecedario));
            }
            printf("\n");
        }

        /*cifrado de hills*/
        for(i = 0; i < FILAS; i++) {
            for(j = 0; j < COLUMNAS; j++) {
                matrizCifrada[i][j] = 0;
                for(k = 0; k < COLUMNAS; k++) {
                    matrizCifrada[i][j] += (obtenerValor(matriz[i][j], abecedario)) % 26;
                }
                matrizCifrada[i][j] = matrizCifrada[i][j] % 26;
            }
        }

        /*mostrar matriz cifrada (con numeros) (debug)*/
        printf("\nMatriz cifrada (DEBUG):\n");
        for(i = 0; i < FILAS; i++) {
            for(j = 0; j < COLUMNAS; j++) {
                printf("[%d] ", matrizCifrada[i][j]);
            }
            printf("\n");
        }

        /*mostrar matriz cifrada (con letras) (debug)*/
        printf("\nMatriz cifrada (DEBUG):\n");
        for(i = 0; i < FILAS; i++) {
            for(j = 0; j < COLUMNAS; j++) {
                printf("[%c] ", obtenerLetra(matrizCifrada[i][j], abecedario));
            }
            printf("\n");
        }

    }
    
    return 0;
}
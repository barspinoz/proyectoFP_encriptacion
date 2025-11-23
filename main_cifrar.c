#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100
#define FILAS 3
#define COLUMNAS 1

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
    char matriz[MAX][FILAS][COLUMNAS] = {0}; //MAX representa el numero maximo de matrices

    /*intermedias*/
    char palabraIndex[MAX] = {0};
    int i = 0;
    int j = 0;
    int k = 0;
    int m = 0;
    int n = 0;
    int ene = 0;
    int longitud = 0;
    int numeroMatrices = 0;
    int capacidadMatriz = FILAS * COLUMNAS;
    int claveHill[FILAS][FILAS] = {{1,2,2},{0,1,4},{5,0,1}}; //matriz clave
    int matrizCifrada[MAX][FILAS][COLUMNAS] = {0}; //MAX representa el numero maximo de matrices

    /*leer archivo con valores de las letras*/
    FILE * valores;
    valores = fopen("valores.txt", "r");
    fscanf(valores, "%d %d %d %d %d %d %d %d %d %d %d %d %d", &abecedario[0], &abecedario[1], &abecedario[2], &abecedario[3], &abecedario[4], &abecedario[5], &abecedario[6], &abecedario[7], &abecedario[8], &abecedario[9], &abecedario[10], &abecedario[11], &abecedario[12]);
    fscanf(valores, "%d %d %d %d %d %d %d %d %d %d %d %d %d", &abecedario[13], &abecedario[14], &abecedario[15], &abecedario[16], &abecedario[17], &abecedario[18], &abecedario[19], &abecedario[20], &abecedario[21], &abecedario[22], &abecedario[23], &abecedario[24], &abecedario[25]);
    fclose(valores);
    
    /*abrir archivo de texto*/
    FILE * texto;
    texto = fopen("texto.txt", "r");

    /*comprobar que se abra correctamente el archivo texto.txt*/
    if (texto == NULL) {
        printf("Error al abrir el archivo\n");
    }
    /*guardar valores del archivo en la matriz*/
    else {
        /*leer sin espacios*/
        while (fscanf(texto, "%99s", palabraIndex) == 1)
        {
            strcat(palabra, palabraIndex);
        }
        fclose(texto);

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
                        matriz[m][i][j] = tolower(palabra[k++]); //se convierte a minuscula
                    }
                    else {
                        matriz[m][i][j] = 'x'; //marcador para posiciones vacias
                    }
                }
            }
        }

        /*cifrado de hills*/
        for(m = 0; m < numeroMatrices; m++) {
            for(i = 0; i < FILAS; i++) {
                for(j = 0; j < COLUMNAS; j++) {
                    matrizCifrada[m][i][j] = 0;
                    for(n = 0; n < FILAS; n++) {
                        matrizCifrada[m][i][j] += claveHill[i][n] * obtenerValor(matriz[m][n][j], abecedario);
                    }
                    matrizCifrada[m][i][j] %= 26;
                }
            }
        }
    
    }

    /*guardar en archivo*/
    FILE * cifrado;
    cifrado = fopen("cifrado.txt", "w");
    for(m = 0; m < numeroMatrices; m++) {
        for(i = 0; i < FILAS; i++) {
            for(j = 0; j < COLUMNAS; j++) {
                fprintf(cifrado, "%c", obtenerLetra(matrizCifrada[m][i][j], abecedario));
            }
        }
    }
    fprintf(cifrado, "\n");
    fclose(cifrado);

    return 0;
}
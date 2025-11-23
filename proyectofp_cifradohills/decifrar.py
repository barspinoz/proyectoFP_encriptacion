import numpy as np

def main():
    matriz_clave = np.array([[1, 2, 3],
                       [0, 4, 5],
                       [1, 0, 6]]) # matriz clave
    print("Matriz Clave:")
    print(matriz_clave)
    
    # encontrar la matriz inversa de la matriz clave
    matriz_inversa = np.linalg.inv(matriz_clave)
    print("Matriz Inversa:")
    print(matriz_inversa)
    
    # verificar la matriz inversa multiplicando la matriz original por su inversa
    identidad = np.dot(matriz_clave, matriz_inversa)
    print("Producto de la matriz original y su inversa (debería ser la matriz identidad):")
    print(identidad)

    # descifrar Hills
    texto_cifrado = open("texto_cifrado.txt", "r").read().strip()
    print("Texto Cifrado:")
    print(texto_cifrado)

    # convertir el texto cifrado en bloques de 3 caracteres
    bloques = [texto_cifrado[i:i+3] for i in range(0, len(texto_cifrado), 3)]
    print("Bloques de Texto Cifrado:")
    print(bloques)

    texto_descifrado = ""
    for bloque in bloques:
        # convertir cada bloque en un vector numérico
        vector_bloque = np.array([[ord(char) - ord('A')] for char in bloque])
        print(f"Vector del bloque '{bloque}':")
        print(vector_bloque)
        
        # multiplicar el vector por la matriz inversa y tomar módulo 26
        vector_descifrado = np.dot(matriz_inversa, vector_bloque) % 26
        print(f"Vector descifrado del bloque '{bloque}':")
        print(vector_descifrado)
        
        # convertir el vector descifrado de vuelta a caracteres
        for num in vector_descifrado:
            texto_descifrado += chr(int(num) + ord('A'))

    # mostrar el texto descifrado
    print("Texto Descifrado:")
    print(texto_descifrado)

if __name__ == "__main__":
    main()

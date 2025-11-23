import numpy as np

# calcular inverso modular de un entero
def modinv(a, m):
    # extended gcd
    a = a % m
    if a == 0:
        return None
    t, newt = 0, 1
    r, newr = m, a
    while newr != 0:
        q = r // newr
        t, newt = newt, t - q * newt
        r, newr = newr, r - q * newr
    if r > 1:
        return None
    if t < 0:
        t += m
    return t

# inverso de matriz 3x3 modulo m
def matrix_mod_inv_3x3(mat, m):
    mat = np.asarray(mat, dtype=int) % m
    # determinante entero
    det = int(round(np.linalg.det(mat)))  # safe for 3x3 small integers
    det = det % m
    det_inv = modinv(det, m)
    if det_inv is None:
        raise ValueError("La matriz no es invertible módulo {}".format(m))
    # calcular matriz de cofactores (adjunta transpuesta)
    cof = np.zeros((3, 3), dtype=int)
    for i in range(3):
        for j in range(3):
            # construir submatriz 2x2
            sub = np.delete(np.delete(mat, i, axis=0), j, axis=1)
            # determinante 2x2
            sub_det = int(sub[0,0]*sub[1,1] - sub[0,1]*sub[1,0])
            cof[i, j] = ((-1) ** (i + j)) * sub_det
    adj = cof.T
    inv_mat = (det_inv * adj) % m
    return inv_mat.astype(int)

def decifrarHills():
    matriz_clave = np.array([[1, 2, 3],
                       [0, 4, 5],
                       [1, 0, 6]]) # matriz clave
    print("Matriz Clave:")
    print(matriz_clave)

    # calcular la inversa modular de la matriz clave modulo 26
    try:
        matriz_inversa = matrix_mod_inv_3x3(matriz_clave, 26)
    except ValueError as e:
        print("Error al invertir la matriz clave:", e)
        return None
    print("Matriz Inversa (mod 26):")
    print(matriz_inversa)

    # darle valor numerico a cada letra del alfabeto (empezando en 0)
    alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    def letra_a_numero(letra):
        return alfabeto.index(letra) # letra a numero
    def numero_a_letra(numero):
        return alfabeto[numero % 26] # numero a letra

    # leer y sanitizar texto cifrado (solo letras, en mayúsculas)
    try:
        texto_cifrado = open("cifrado.txt", "r").read().strip()
    except FileNotFoundError:
        print("Archivo 'cifrado.txt' no encontrado.")
        return None
    print("Texto Cifrado (raw):")
    print(texto_cifrado)
    texto_cifrado = "".join([c for c in texto_cifrado.upper() if c in alfabeto])
    if len(texto_cifrado) == 0:
        print("No hay letras válidas en el archivo cifrado.")
        return None
    # rellenar con 'X' para que la longitud sea múltiplo de 3
    while len(texto_cifrado) % 3 != 0:
        texto_cifrado += "X"
    print("Texto Cifrado (procesado, padded):")
    print(texto_cifrado)

    # pasar el texto cifrado a numeros
    numeros_cifrados = [letra_a_numero(letra) for letra in texto_cifrado]

    # pasar los numeros cifrados a matrices de 3x1
    bloques_cifrados = [np.array(numeros_cifrados[i:i+3], dtype=int).reshape(3, 1) for i in range(0, len(numeros_cifrados), 3)]

    # descifrar cada bloque multiplicando por la matriz inversa modulo 26
    bloques_descifrados = []
    for bloque in bloques_cifrados:
        vec = bloque.reshape(3)
        res = np.dot(matriz_inversa, vec) % 26
        bloques_descifrados.append(res)

    # pasar los bloques descifrados a texto
    texto_descifrado = ""
    for bloque in bloques_descifrados:
        for numero in bloque:
            texto_descifrado += numero_a_letra(int(numero))

    # mostrar el texto descifrado
    print("Texto Descifrado:")
    print(texto_descifrado)

    # guardar el texto descifrado en un archivo
    with open("descifrado.txt", "w") as f:
        f.write(texto_descifrado)
    print("El texto descifrado ha sido guardado en 'descifrado.txt'.")
    return texto_descifrado

if __name__ == "__main__":
    decifrarHills()

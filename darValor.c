#include <stdio.h>
void darValor () {
    /*abecedario*/
    char a, b, c, d, e, f, g, h, i, j, k, l, m;
    char n, o, p, q, r, s, t, u, v, w, x, y, z;

    /*leer archivo con valores de las letras*/
    FILE * valores;
    valores = fopen("valores.txt", "r");
    fscanf(valores, "%c %c %c %c %c %c %c %c %c %c %c %c %c", &a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k, &l, &m);
    fscanf(valores, "%c %c %c %c %c %c %c %c %c %c %c %c %c", &n, &o, &p, &q, &r, &s, &t, &u, &v, &w, &x, &y, &z);
    fclose(valores);
}
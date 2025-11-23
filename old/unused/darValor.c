#include <stdio.h>
void darValor () {
    /*abecedario*/
    int a, b, c, d, e, f, g, h, i, j, k, l, m;
    int n, o, p, q, r, s, t, u, v, w, x, y, z;

    /*leer archivo con valores de las letras*/
    FILE * valores;
    valores = fopen("valores.txt", "r");
    fscanf(valores, "%d %d %d %d %d %d %d %d %d %d %d %d %d", &a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k, &l, &m);
    fscanf(valores, "%d %d %d %d %d %d %d %d %d %d %d %d %d", &n, &o, &p, &q, &r, &s, &t, &u, &v, &w, &x, &y, &z);
    fclose(valores);
}
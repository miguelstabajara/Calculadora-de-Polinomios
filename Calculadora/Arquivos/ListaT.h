#ifndef LISTAT_H_INCLUDED
#define LISTAT_H_INCLUDED

typedef struct termo{
    int exp;
    float coef;
} Termo;

typedef struct listaT ListaT;

typedef struct noT NoT;

ListaT *criarT();

void limparT(ListaT *l);

int reinicializar(ListaT *l);

int listaVaziaT(ListaT *l);

int inserirNovo(ListaT *l, Termo it);

int inserirIncrementar(ListaT *l, Termo it);

int somarValor(ListaT *l, Termo it);

int substituir(ListaT *l, Termo it);

void mostrarT(ListaT *l);

int removerInicioT(ListaT *l);

int removerFimT(ListaT *l);

int removerExp(ListaT *l, int pos);

int contemExp(ListaT *l, int exp);

int buscarPosicaoT(ListaT *l, int pos, Termo *ret);

int buscarCoef(ListaT *l, int exp, float *ret);

int somarPolT(ListaT *l1, ListaT *l2, ListaT *ret);

int calcPx(ListaT *l, float x, float *ret);

float pot(int exp, float base);

float mod(float x);

#endif // LISTAT_H_INCLUDED
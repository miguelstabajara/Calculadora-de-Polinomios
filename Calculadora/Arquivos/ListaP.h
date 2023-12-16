#ifndef LISTAP_H_INCLUDED
#define LISTAP_H_INCLUDED

typedef struct listaP ListaP;

typedef struct listaT ListaT;

typedef struct noP NoP;

ListaP *criar();

void limpar(ListaP *l);

int listaVazia(ListaP *l);

int tamanho(ListaP *l);

int inserir(ListaP *l, char *str);

void mostrar(ListaP *l);

int removerInicio(ListaP *l);

int removerFim(ListaP *l);

int removerPosicao(ListaP *l, int pos);

int buscarNome(ListaP *l, int pos, char *ret);

int buscarPosicao(ListaP *l, char *str);

int somarPol(ListaP *l, char *str1, char *str2, char *res);

ListaT *buscarLista(ListaP *l, int pos);

ListaT *buscarListaNome(ListaP *l, char *nome);

#endif // LISTAP_H_INCLUDED
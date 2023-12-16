#include"ListaP.h"
#include"ListaT.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct listaP{
    NoP *inicio;
}ListaP;

typedef struct noP{
    char nome[30];
    NoP *prox;
    ListaT *ListaTermos;
} NoP;

ListaP *criar(){
    ListaP *l = (ListaP*)malloc(sizeof(ListaP));
    l->inicio = NULL;
    return l;
}

void limpar(ListaP *l){
    while (listaVazia(l)==1) removerInicio(l);
}

int tamanho(ListaP *l){
    if (l == NULL) return -1;
    NoP *no = l->inicio;
    int cont = 0;
    while (no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int listaVazia(ListaP *l){
    if (l == NULL) return 2;
    if (l->inicio == NULL) return 0;
    else return 1;
}

int inserir(ListaP *l, char *str){
    if (l == NULL) return 2;
    if(buscarListaNome(l,str)!=NULL){
        return 1;
    }
    NoP *no = (NoP*)malloc(sizeof(NoP));
    strcpy(no->nome,str);
    no->ListaTermos=criarT();
    no->prox = l->inicio;
    l->inicio = no;
    return 0;
}

void mostrar(ListaP *l){
    int cont = 1;
    if(l != NULL){
        NoP *no = l->inicio;
        while(no != NULL){
            printf("%d - \"%s\": ",cont,no->nome);
            mostrarT(no->ListaTermos);
            printf("\n");
            no = no->prox;
            cont++;
        }
    }
}

int removerInicio(ListaP *l){
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    NoP *no = l->inicio;
    l->inicio = no->prox;
    limparT(no->ListaTermos);
    free(no);
    return 0;
}

int removerFim(ListaP *l){
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    NoP *no = l->inicio, *aux=NULL;
    while(no->prox!=NULL){
        aux=no;
        no = no->prox;
    }
    if(aux==NULL) l->inicio = NULL;
    else aux->prox = NULL;
    limparT(no->ListaTermos);
    free(no);
    return 0;
}

int removerPosicao(ListaP *l, int pos){
    if (l == NULL) return 2;
    if (listaVazia(l) == 0) return 1;
    if(pos<0) return 3;
    NoP *aux = NULL, *no = l->inicio;
    while(no->prox!=NULL && (pos>=0)){
        aux = no;
        no = no->prox;
        pos--;
    }
    if(aux==NULL){
        limparT(no->ListaTermos);
        free(no);
        l->inicio = NULL;
    }else{
        aux->prox = no->prox;
        limparT(no->ListaTermos);
        free(no);
    }
    return 0;
}

int buscarNome(ListaP *l, int pos, char *ret){
    if(l==NULL) return 1;
    if(listaVazia(l)==0) return 2;
    NoP *no=l->inicio;
    while(pos>0&&no!=NULL){
        pos--;
        no=no->prox;
    }
    if(no!=NULL){
        strcpy(ret, no->nome);
        return 0;
    }
    return 3;
}

int buscarPosicao(ListaP *l, char *str){
    if(l == NULL) return -1;
    NoP *no = l->inicio;
    int p = 0;
    while(strcmp(str,no->nome)!=0){
        p++;
        no = no->prox;
        if(no==NULL){
            p=-2;
            break;
        }
    }
    return p;
}

int somarPol(ListaP *l, char *str1, char *str2, char *nome){
    if(l==NULL) return 2;
    ListaT *a=buscarListaNome(l, str1), *b=buscarListaNome(l, str2);
    if(a==NULL||b==NULL) return 3;
    if(listaVazia(l)==0) return 1;
    if(inserir(l, nome)==1) return 4; 
    somarPolT(a, b, l->inicio->ListaTermos);
    return 0;
}

ListaT *buscarLista(ListaP *l, int pos){
    if(l==NULL){
        return NULL;
    }
    if(listaVazia(l)==0){
        return NULL;
    }
    NoP *no=l->inicio;
    while(no->prox!=NULL&&pos>0){
        no=no->prox;
        pos--;
    }
    return no->ListaTermos;
}

ListaT *buscarListaNome(ListaP *l, char *nome){
    if(l==NULL) return NULL;
    if(listaVazia(l)==0) return NULL;
    NoP *n=l->inicio;
    while(strcmp(nome, n->nome)!=0){
        if(n->prox==NULL) return NULL;
        n=n->prox;
    }
    return n->ListaTermos;
}
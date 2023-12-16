#include"ListaT.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct listaT {
    NoT *inicio;
}ListaT;

typedef struct noT {
    Termo x;
    NoT *prox;
}NoT;

ListaT *criarT(){
    ListaT *l = (ListaT *)malloc(sizeof(ListaT));
    NoT *no=(NoT *)malloc(sizeof(NoT));
    no->prox=NULL;
    no->x.coef=0;
    no->x.exp=0;
    l->inicio=no;
    return l;
}

void limparT(ListaT *l){
    while(listaVaziaT(l)==1) removerInicioT(l);
    free(l->inicio);
    l->inicio=NULL;
}

int reinicializar(ListaT *l){
    //limpa o polinomio e o cria novamente, zerado
    if(l==NULL) return 2;
    if(listaVaziaT(l)==0) return 1;
    limparT(l);
    NoT *n=(NoT *)malloc(sizeof(NoT));
    n->prox=NULL;
    n->x.coef=0;
    n->x.exp=0;
    l->inicio=n;
    return 0;
}

int listaVaziaT(ListaT *l){
    if(l==NULL) return 2;
    if(l->inicio==NULL) return 0;
    if(l->inicio->x.exp==0&&l->inicio->x.coef==0) return 0;
    else return 1;
}

int inserirNovo(ListaT *l, Termo it){
    if(l==NULL) return 2;
    if(it.coef==0) return 3;
    NoT *aux=l->inicio;
    if(it.exp==0){
        while(aux->prox!=NULL){
            aux=aux->prox;
        }
        aux->x.coef=it.coef;
        return 0;
    }
    NoT *no=(NoT *)malloc(sizeof(NoT));
    no->x.coef=it.coef;
    no->x.exp=it.exp;
    if(it.exp>aux->x.exp){
        l->inicio=no;
        no->prox=aux;
        return 0;
    }
    while(aux->prox!=NULL&&aux->prox->x.exp>it.exp){
        aux=aux->prox;
    }
    no->prox=aux->prox;
    aux->prox=no;
    return 0;
}

int inserirIncrementar(ListaT *l, Termo it){
    if(l==NULL) return 2;
    if(listaVaziaT(l)==0) return 1;
    NoT *no=l->inicio;
    while(no->x.exp>=it.exp){
        if(no->x.exp==it.exp||no->prox==NULL){ //nao escrever o no->x.exp++ antes dessa comparacao eh importante para nao precisarmos fazer -1 no valor antes de comparar
            no->x.exp++;
            break;
        }
        no->x.exp++;
        no=no->prox;
    }
    NoT *aux=(NoT *)malloc(sizeof(NoT));
    aux->prox=no->prox;
    no->prox=aux;
    aux->x.coef=it.coef;
    aux->x.exp=it.exp;
    return 0;
}

int somarValor(ListaT *l, Termo it){
    if(l==NULL) return 2;
    if(listaVaziaT(l)==0) return 1;
    NoT *no=l->inicio;
    while(no!=NULL){
        if(no->x.exp==it.exp){
            no->x.coef+=it.coef;
            if(no->x.coef==0) return removerExp(l, no->x.exp);
            return 0;
        }
        no=no->prox;
    }
    return 1;
}

int substituir(ListaT *l, Termo it){
    if(l==NULL) return 2;
    if(listaVaziaT(l)==0) return 1;
    if(it.coef==0) return removerExp(l, it.exp);
    NoT *no=l->inicio;
    while(no!=NULL){
        if(no->x.exp==it.exp){
            no->x.coef=it.coef;
            return 0;
        }
        no=no->prox;
    }
    return 1;
}

void mostrarT(ListaT *l){
    if(l != NULL){
        NoT *No = l->inicio;
        printf("P(x) = ");
	    if(No->x.coef < 0) printf("- ");
        if(No->x.exp==0){
            printf("%.2f", No->x.coef);
        } else{
            while(No->x.exp > 1){
                printf("%.2fx^%d", mod(No->x.coef), No->x.exp);
                No = No->prox;
                if(No->x.coef < 0) printf(" - ");
                else if(No->x.coef!=0) printf(" + "); //Apenas util para o caso onde exp=0, a lista não guarda nenhum outro coeficiente 0 sem ser esse
            }
            if(No->x.exp == 1){
                printf("%.2fx", mod(No->x.coef));
                No = No->prox;
                if(No->x.coef!=0){
                    if(No->x.coef < 0) printf(" - ");
                    else printf(" + ");
                }
            }
            if(No->x.coef!=0){
                printf("%.2f", mod(No->x.coef));
            }
        }
        printf("\n");
    }
}

int removerInicioT(ListaT *l){
    if(l==NULL) return 2;
    if(listaVaziaT(l)==0) return 1;
    NoT *no = l->inicio;
    if(no->x.exp==0){
        no->x.coef=0;
        return 0;
    }
    l->inicio = no->prox;
    free(no);
    return 0;
}

int removerFimT(ListaT *l){
    if(l==NULL) return 2;
    if(listaVaziaT(l)==0) return 1;
    NoT *no = l->inicio;
    while(no->prox!=NULL){
        no = no->prox;
    }
    no->x.coef=0;
    return 0;
}

int removerExp(ListaT *l, int exp){
    if (l == NULL) return 2;
    if (listaVaziaT(l) == 0) return 1;
    if(exp==0){
        NoT *no = l->inicio;
        while(no->prox!=NULL){
            no=no->prox;
        }
        no->x.coef=0;
        return 0;
    }
    NoT *aux = NULL, *no = l->inicio;
    while(no->x.exp>exp && no->prox!=NULL){
        aux = no;
        no = no->prox;
    }
    if(no->x.exp==exp){
        if(aux==NULL){
            l->inicio=no->prox;
            free(no);
        }else{
            aux->prox = no->prox;
            free(no);
        }
        return 0;
    }
    return 3;
}

int contemExp(ListaT *l, int exp){
    if(l==NULL) return 2;
    if(l->inicio==NULL) return 1;
    NoT *n=l->inicio;
    while(n->x.exp!=exp){
        n=n->prox;
        if(n==NULL) return 3;
    }
    if(n->x.coef==0) return 3;
    return 0;
}

int buscarPosicaoT(ListaT *l, int pos, Termo *ret){
    if(l==NULL) return 1;
    NoT *no=l->inicio;
    while(no!=NULL&&pos>0){
        pos--;
        no=no->prox;
    }
    if(no!=NULL&&ret!=NULL){
        ret->coef=no->x.coef;
        ret->exp=no->x.exp;
        return 0;
    }
    return 2;
}

int buscarCoef(ListaT *l, int exp, float *ret){
    if(l==NULL) return 2;
    if(listaVaziaT(l)==0){
        *ret=0;
        return 1;
    }
    for(NoT *no=l->inicio; no!=NULL; no=no->prox){
        if(no->x.exp==exp){
            *ret=no->x.coef;
            return 0;
        }
    }
    *ret=0;
    return 3;
}

int somarPolT(ListaT *l1, ListaT *l2, ListaT *ret){
    if(l1 == NULL || l2 == NULL || ret == NULL) return 2;
    if(listaVaziaT(l1) == 0){
        NoT *p=l2->inicio;
        while(p!=NULL){
            inserirNovo(ret, p->x);
            p=p->prox;
        }
        return 1;
    }
    if(listaVaziaT(l2) == 0){
        NoT *p=l1->inicio;
        while(p!=NULL){
            inserirNovo(ret, p->x);
            p=p->prox;
        }
        return 1;
    }
    NoT *pol1 = l1->inicio, *pol2 = l2->inicio;
    
    while(pol1 != NULL && pol2 != NULL){
        /*adiciona no novo polinomio o maior expoente dos dois até que
        estejam no mesmo expoente*/
        if(pol2->x.exp > pol1->x.exp){
            inserirNovo(ret, pol2->x);
            pol2 = pol2->prox;
        }else if(pol2->x.exp < pol1->x.exp){
            inserirNovo(ret, pol1->x);
            pol1 = pol1->prox;
        }else{
            /*adiciona a soma dos expoentes coincidentes em ambos os polinomios*/
            Termo temp;
            temp.exp = pol1->x.exp;
            temp.coef = pol1->x.coef + pol2->x.coef;
            if(temp.coef != 0) inserirNovo(ret, temp);
            pol1 = pol1->prox;
            pol2 = pol2->prox;
        }
    }
    return 0;
}

int calcPx(ListaT *l, float x, float *ret){
    if(l==NULL) return 2;
    if(listaVaziaT(l)==0){
        *ret=0;
        return 1;  
    }
    NoT *no=l->inicio;
    while(no!=NULL){
        *ret+=no->x.coef*pot(no->x.exp, x);
        no=no->prox;
    }
    return 0;
}

float pot(int exp, float base){
    if(base==0) return 0;
    float res=1;
    for(;exp>0; exp--) res*=base;
    return res;
}

float mod(float x){
    if(x<0){
        return -x;
    }
    return x;
}
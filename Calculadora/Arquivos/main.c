#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"ListaP.h"
#include"ListaT.h"

void carregar(FILE *fp, ListaP *l);
void salvar(ListaP *l);
void inicializar(ListaT *l);
void inserirTermo(ListaP *l);
void mostraPol(ListaP *l, char *nome);
void somarPolinomios(ListaP *l);
void Px(ListaP *l);

int main(){
    ListaP *lista=criar();
    int op=0;
    char nome[31];
    FILE *fp;
    if((fp=fopen("polinomios.bin", "r"))==NULL){
        printf("Nao foi encontrado o arquivo com polinomios salvos, criando um novo\n\n");
        if((fp=fopen("polinomios.bin", "w"))==NULL){
            exit(1);
        }
        fclose(fp);
    } else{
        printf("Foram encontrados polinomios salvos, deseja carrega-los no programa?(Y/N): ");
        scanf("%c", nome);
        if(nome[0]=='Y'||nome[0]=='y'){
            carregar(fp, lista);
        }
        fclose(fp);
    }
    while(op!=12){
        printf("Insira uma opcao:\n\n1- Criar um polinomio\n2- Remover um polinomio\n3- Inserir um termo em um polinomio\n4- Mostrar\n5- Eliminar um termo\n6- Reinicializar um polinomio\n7- Salvar um polinomio\n8- Somar dois polinomios\n9- Calcular o valor do polinomio para um x\n10- Limpar todos os polinomios da memoria\n11- Apagar os polinomios salvos em disco\n12- Sair\n\nOpcao: ");
        fflush(stdin);
        scanf("%d", &op);
        printf("\n");
        switch(op){
            case 1:
                //inicializar o polinomio
                printf("Insira o nome do polinomio: ");
                fflush(stdin);
                fgets(nome, 31, stdin);
                nome[strlen(nome)-1]='\0';
                if(inserir(lista, nome)==1){
                    printf("Esse polinomio ja existe\n");
                } else{
                    printf("\nInsira os termos desse polinomio:\n\n");
                    inicializar(buscarLista(lista, 0));
                }
                printf("\n");
                break;
            case 2:
                printf("Insira o nome do polinomio que deve ser removido: ");
                fflush(stdin);
                fgets(nome, 31, stdin);
                nome[strlen(nome)-1]='\0';
                if(removerPosicao(lista, buscarPosicao(lista, nome))==3){
                    printf("\nO polinomio nao foi encontrado\n");
                }
                printf("\n");
                break;
            case 3:
                //inserir termo
                inserirTermo(lista);
                break;
            case 4:
                //mostrar
                printf("Voce deseja:\n1- Imprimir todos os polinomios salvos\n2- Imprimir apenas um polinomio\n\nOpcao: ");
                scanf("%d", &op);
                printf("\n");
                if(op==1){
                    mostrar(lista);
                }else if(op==2){
                    printf("Insira o nome do polinomio que deseja visualizar: ");
                    fflush(stdin);
                    fgets(nome, 31, stdin);
                    nome[strlen(nome)-1]='\0';
                    mostraPol(lista,nome);
                    printf("\n");
                } else{
                    printf("Nao foi inserido uma opcao valida\n\n");
                }
                break;
            case 5:
                //Eliminar potencia
                printf("Insira o nome do polinomio em que se deseja remover uma potencia: ");
                fflush(stdin);
                fgets(nome, 31, stdin);
                nome[strlen(nome)-1]='\0';
                printf("Insira a potencia que deve ser removida: ");
                scanf("%d", &op);
                switch(removerExp(buscarListaNome(lista, nome), op)){
                    case 2:
                        printf("\nNao foi encontrado o polinomio digitado\n");
                        break;
                    case 1:
                    case 3:
                        printf("\nNao foi encontrado essa potencia\n");
                }
                printf("\n");
                op=1;
                break;
            case 6:
                //Reinicializar
                    printf("Insira o nome do polinomio que deseja reinicializar: ");
                    fflush(stdin);
                    fgets(nome, 31, stdin);
                    nome[strlen(nome)-1]='\0';
                    if(reinicializar(buscarListaNome(lista, nome))==2)
                        printf("\nNao foi encontrado esse polinomio\n");
                    printf("\n");
                break;
            case 7:
                salvar(lista);
                break;
            case 8:
                //Somar dois polinomios
                somarPolinomios(lista);
                break;
            case 9:
                //Calcular P(x)
                Px(lista);
                break;
            case 10:
                limpar(lista);
                break;
            case 11:
                fp=fopen("polinomios.bin", "w");
                fclose(fp);
                break;
            case 12:
                //Sair
                printf("Saindo...");
                break;
            default:
                printf("Opcao invalida, tente novamente\n\n");
        }
    }
    return 0;
}

void carregar(FILE *fp, ListaP *l){
    char nome[30];
    Termo it;
    ListaT *p;
    while(1){
        fread(nome, sizeof(char), 30, fp);
        if(feof(fp)) break;
        inserir(l, nome);
        p=buscarLista(l, 0);
        it.exp=1;
        while(it.exp!=0){
            fread(&it.coef, sizeof(float), 1, fp);
            fread(&it.exp, sizeof(int), 1, fp);
            inserirNovo(p, it);
        }
    }
}

void salvar(ListaP *l){
    ListaP *aux=criar();
    ListaT *p;
    FILE *fp;
    Termo it;
    char nome[31];
    int op;
    printf("Voce deseja:\n1- Sobreescrever todos os polinomios salvos\n2- Adicionar todos os polinomios criados\n3- Adicionar apenas um polinomio\n\nOpcao: ");
    scanf("%d", &op);
    if(op==1){
        if((fp=fopen("polinomios.bin", "w"))!=NULL){
            for(int j=0; buscarNome(l, j, nome)==0; j++){
                p=buscarListaNome(l, nome);
                fwrite(nome, sizeof(char), 30, fp);
                for(int i=0; buscarPosicaoT(p, i, &it)==0; i++){
                    fwrite(&it.coef, sizeof(float), 1, fp);
                    fwrite(&it.exp, sizeof(int), 1, fp);
                }
            }
            fclose(fp);
        }
    }else if(op==2){
        if((fp=fopen("polinomios.bin", "r"))!=NULL){
        carregar(fp, aux);
        fclose(fp);
        }
        if((fp=fopen("polinomios.bin", "a"))!=NULL){
            for(int j=0; buscarNome(l, j, nome)==0; j++){
                if(buscarListaNome(aux, nome)==NULL){
                    p=buscarListaNome(l, nome);
                    fwrite(nome, sizeof(char), 30, fp);
                    for(int i=0; buscarPosicaoT(p, i, &it)==0; i++){
                        fwrite(&it.coef, sizeof(float), 1, fp);
                        fwrite(&it.exp, sizeof(int), 1, fp);
                    }
                }
            }
            fclose(fp);
        }
    } else if(op==3){
        if((fp=fopen("polinomios.bin", "r"))!=NULL){
        carregar(fp, aux);
        fclose(fp);
        }
        printf("\nInsira o polinomio que deve ser inserido: ");
        fflush(stdin);
        fgets(nome, 31, stdin);
        nome[strlen(nome)-1]='\0';
        if(buscarListaNome(aux, nome)==NULL){
            p=buscarListaNome(l, nome);
            if((fp=fopen("polinomios.bin", "a"))!=NULL){
                fwrite(nome, sizeof(char), 30, fp);
                for(int i=0; buscarPosicaoT(p, i, &it)==0; i++){
                    fwrite(&it.coef, sizeof(float), 1, fp);
                    fwrite(&it.exp, sizeof(int), 1, fp);
                }
                fclose(fp);
            }
        } else{
            printf("\nJa existe um polinomio salvo com esse nome\n");
        }
    } else{
        printf("\nNao foi digitado uma opcao valida\n");
    }
    printf("\n");
}

void inicializar(ListaT *l){
    Termo it;
    int opcao;
    do{
        printf("Insira o expoente do termo que se deseja inserir(Digite um numero negativo para sair): ");
        it.exp=-1; //util para garantir que o usuario nao digite algo invalido que o scanf nao leia
        fflush(stdin);
        scanf("%d", &it.exp);
        if(it.exp>=0){
            if(contemExp(l , it.exp)==0){
                printf("\nEsse termo ja existe, voce deseja:\n1 - Somar um valor para esse termo\n2 - Substituir esse valor\n3 - Incrementar os outros expoentes\n\nOpcao: ");
                scanf("%d", &opcao);
                printf("\n");
                switch(opcao){
                    case 1:
                        printf("Insira o valor que deve ser somado: ");
                        scanf("%f", &it.coef);
                        somarValor(l , it);
                        break;
                    case 2:
                        printf("Insira o coeficiente que deve ser substituido: ");
                        scanf("%f", &it.coef);
                        substituir(l, it);

                        break;
                    case 3:
                        printf("Insira o coeficiente que deve ser inserido: ");
                        scanf("%f", &it.coef);
                        inserirIncrementar(l, it);
                        break;
                    default:
                        printf("Nao foi inserido uma opcao valida");
                }
            } else{
                printf("Insira o coeficiente do polinomio: ");
                scanf("%f", &it.coef);
                inserirNovo(l, it);
            }
        }
    printf("\n");
    } while(it.exp>=0);
}

void inserirTermo(ListaP *lista){
    ListaT *p;
    char nome[31];
    Termo it;
    int opcao;
    printf("Insira o nome do polinomio em que se deseja fazer a insercao: ");
    fflush(stdin);
    fgets(nome, 31, stdin);
    nome[strlen(nome)-1]='\0';
    p=buscarListaNome(lista, nome);
    if(p==NULL){
        printf("\nO polinomio %s nao foi encontrado\n\n", nome);
    } else{
        printf("Insira o expoente do polinomio: ");
        scanf("%d", &it.exp);
        if(it.exp>=0){
            if(contemExp(p , it.exp)==0){
                printf("\nEsse termo ja existe, voce deseja:\n1 - Somar um valor para esse termo\n2 - Substituir esse valor\n3 - Incrementar os outros expoentes\n\nOpcao: ");
                scanf("%d", &opcao);
                printf("\n");
                switch(opcao){
                    case 1:
                        printf("Insira o valor que deve ser somado: ");
                        scanf("%f", &it.coef);
                        somarValor(p , it);
                        break;
                    case 2:
                        printf("Insira o coeficiente que deve ser substituido: ");
                        scanf("%f", &it.coef);
                        substituir(p, it);

                        break;
                    case 3:
                        printf("Insira o coeficiente que deve ser inserido: ");
                        scanf("%f", &it.coef);
                        inserirIncrementar(p, it);
                        break;
                    default:
                        printf("Nao foi inserido uma opcao valida");
                }
            } else{
                printf("Insira o coeficiente do polinomio: ");
                scanf("%f", &it.coef);
                inserirNovo(p, it);
            }
        } else{
            printf("Nao foi digitado um expoente valido\n");
        }
    }
    printf("\n");
}

void mostraPol(ListaP *l, char *nome){
    ListaT *p=buscarListaNome(l, nome);
    if(p!=NULL){
        printf("\n\"%s\": ", nome);
        mostrarT(p);
    } else{
        printf("\nNao foi encontrado esse polinomio\n");
    }
}

void Px(ListaP *l){
    int i=0, j;
    ListaT *p;
    float x, maior, menor;
    char cond;
    float *valores=(float *)malloc(sizeof(float));
    char **nomes=(char **)malloc(sizeof(char *));
    nomes[0]=(char *)malloc(31*sizeof(char));
    printf("Insira o valor de x: ");
    scanf("%f", &x);
    printf("\nInsira o nome de um polinomio(Digite \"sair\" para parar de calcular): ");
    fflush(stdin);
    fgets(nomes[0], 31, stdin);
    nomes[0][strlen(nomes[0])-1]='\0';
    while(strcmp(nomes[i], "sair")!=0){
        p=buscarListaNome(l, nomes[i]);
        if(p==NULL){
            printf("\nO polinomio nao foi encontrado\n\n");
        } else{
            calcPx(p, x, valores+i);
            i++;
            valores=(float *)realloc(valores, (i+1)*sizeof(float));
            nomes=(char **)realloc(nomes, (i+1)*sizeof(char *));
            nomes[i]=(char *)malloc(31*sizeof(char));
        }
        printf("\nInsira o nome de um polinomio(Digite \"sair\" para parar de calcular): ");
        fflush(stdin);
        fgets(nomes[i], 31, stdin);
        nomes[i][strlen(nomes[i])-1]='\0';
    }
    if(i!=0){
        for(j=0; j<i; j++)
            printf("\"%s\": P(%.2f) = %.2f\n", nomes[j], x, valores[j]);
        printf("\n");
        for(j=0, maior=valores[j], menor=valores[j]; j<i; j++){
            if(valores[j]>maior) maior=valores[j];
            else if(valores[j]<menor) menor=valores[j];
        }
        printf("Os maiores sao: ");
        for(cond=0, j=0; j<i; j++){
            if(maior==valores[j]){
                if(cond==0){
                    printf("%s", nomes[j]);
                    cond++;
                }else{
                    printf(", %s", nomes[j]);
                }
            }
        }
        printf("\nOs menores sao: ");
        for(cond=0, j=0; j<i; j++){
            if(menor==valores[j]){
                if(cond==0){
                    printf("%s", nomes[j]);
                    cond++;
                }else{
                    printf(", %s", nomes[j]);
                }
            }
        }
        printf("\n");
    }
    for(j=0; j<=i; j++){
        free(nomes[j]);
    }
    free(nomes);
    free(valores);
    printf("\n");
}

void somarPolinomios(ListaP *l){
    char nome1[31], nome2[31], nome[31];
    int ret;
    printf("Insira o nome do polinomio 1: ");
    fflush(stdin);
    fgets(nome1, 31, stdin);
    nome1[strlen(nome1)-1]='\0';
    printf("Insira o nome do polinomio 2: ");
    fflush(stdin);
    fgets(nome2, 31, stdin);
    nome2[strlen(nome2)-1]='\0';
    printf("Insira o nome do polinomio resultante: ");
    fflush(stdin);
    fgets(nome, 31, stdin);
    nome[strlen(nome)-1]='\0';
    ret=somarPol(l, nome1, nome2, nome);
    if(ret==4){
        printf("\nO nome do polinomio resultante ja existe\n");
    } else if(ret==3){
        printf("\nNao foram encontrados os polinomios buscados\n");
    }
    printf("\n");
}
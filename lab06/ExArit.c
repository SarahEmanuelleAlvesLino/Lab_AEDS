#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct no_aux{
    char op[50];
    int res;
    struct no_aux *pai,*esq,*dir;
}NoArv;
typedef NoArv *Arvore;

typedef struct aux{
    NoArv* pontei;
    struct aux * topo;
}No;
typedef No *Pilha;

void criaPilha(Pilha * p){
    Pilha pil = (Pilha)malloc(sizeof(No));
    (*p) = pil;
    pil->topo = NULL;
    return;
}

void desalocaPilha(Pilha *p){
    while (*p != NULL) {
        Pilha temp = *p;      
        *p = (*p)->topo;      
        free(temp);           
    }
}

void desaloca(NoArv * raiz){
    if(raiz == NULL)
        return;
    desaloca(raiz->esq);
    desaloca(raiz->dir);
    free(raiz);
}

Arvore criaArvore(char x[], int n, bool op){
    Arvore novono = (Arvore)malloc(sizeof(NoArv));
    novono->pai = novono->esq = novono->dir = NULL;

    if(op){
        novono->op[0] = *x;
        return novono;
    }

    novono->op[0] = '.';
    novono->res = n;
    return novono;
}

void empilha(Pilha * p, Arvore x){
    Pilha novono = (Pilha)malloc(sizeof(No));
    novono->pontei = x;

    if(*p == NULL)
        novono->topo = NULL;
    else
        novono->topo = *p;
    *p = novono;
}

Arvore desempilha(Pilha *p){
    if(*p == NULL)
        return NULL;

    Pilha rem = *p;
    Arvore no = (*p)->pontei;
    *p = (*p)->topo;
    free(rem);
    return no;
}

Arvore colocaNo(Arvore esq, Arvore mei, Arvore dir){
    mei->dir = dir;
    mei->esq = esq;
    dir->pai = esq->pai = mei;
    switch (mei->op[0]){
        case '*':
            mei->res = esq->res * dir->res;
            break;
        case '/':
            mei->res = esq->res / dir->res;
            break;
        case '+':
            mei->res = esq->res + dir->res;
            break;
        case '-':
            mei->res = esq->res - dir->res;
            break;
        case '%':
            mei->res = esq->res % dir->res;
            break;
    }

    return mei;
}

int precedencia(char x[]){
    if(x[0] == '*' || x[0] == '/')
        return 3;
    if(x[0] == '+' || x[0] == '-')
        return 2;
    if(x[0] == '%')
        return 1;
    return -1;
}

void imprimiPre(Arvore raiz, int n){
    if(raiz == NULL)
        return;
    if(raiz->op[0] != '.'){
        if(n != 0)
            printf(" %s", raiz->op);
        else
            printf ("%s",raiz->op);
    }else
        printf(" %d", raiz->res);

    imprimiPre(raiz->esq,1);
    imprimiPre(raiz->dir,1);
}

void imprimiPos(Arvore raiz, int n){
    if(raiz == NULL)
        return;

    imprimiPos(raiz->esq,1);
    imprimiPos(raiz->dir,1);

    if(n == 1){
        if(raiz->op[0] != '.')
            printf("%s ",raiz->op);
        else
            printf("%d ", raiz->res); 
    }
    else
        printf("%s", raiz->op);
}

int main(){
    int x, prio = 0;
    char y[50];

    Pilha p;
    criaPilha(&p);
    scanf("%d", &x);

    Arvore raiz = criaArvore(y,x,false);
    empilha(&p,raiz);

    while(scanf("%s%d", y,&x) > 1){
        while(prio >= precedencia(y)){
            Arvore dir = desempilha(&p);
            Arvore meio = desempilha(&p);
            Arvore esq = desempilha(&p);
            empilha(&p, colocaNo(esq, meio, dir));
            raiz = meio;

            if (p->topo->topo != NULL)               
                prio = precedencia(((p)->topo)->pontei->op);
            else
                break;
        }

        empilha(&p, criaArvore(y,x,true));
        empilha(&p, criaArvore(y,x,false));
        prio = precedencia(y);
    }

    while((p)->topo->topo != NULL){
        Arvore dir = desempilha(&p);
            Arvore meio = desempilha(&p);
            Arvore esq = desempilha(&p);
            empilha(&p, colocaNo(esq, meio, dir));
            raiz = meio;
    }

    imprimiPre(raiz,0);
    printf("\n");
    imprimiPos(raiz,0);
    printf("\n");
    printf("%d\n", raiz->res);

    desaloca(raiz);
    desalocaPilha(&p); 

    return 0;
}


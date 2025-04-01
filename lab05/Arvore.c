#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"

No * aloca(int x){
    No * Nonovo = malloc(sizeof(No));
    Nonovo->valor = x;
    Nonovo->dir = Nonovo->esq = NULL;
    return Nonovo;
}

void imprimeArvore(Arvore arv){
    if(arv == NULL){
        printf(".");
        return;
    }
    printf("[%d:e=", arv->valor);
    imprimeArvore(arv->esq);
    printf(",d=");
    imprimeArvore(arv->dir);
    printf("]");
}

/** Insere valor x na árvore de busca binária */
bool insere(Arvore* ap_arv, int x){
    if(*ap_arv == NULL){
        *ap_arv = aloca(x);
        return true;
    }
    if(x < ((*ap_arv)->valor))
        return insere(&((*ap_arv)->esq), x);
    else
    if(x > ((*ap_arv)->valor))
        return insere(&((*ap_arv)->dir), x);
    else
        return false;

}

/** Remove valor x da árvore de busca binária. Em caso de nó com dois filhos, deve-se trocar de posição com o antecessor do nó removido e o remover então.  */
bool remove_(Arvore* ap_arv, int x){
    if(*ap_arv == NULL) //arvore vazia
        return false;
    if(x > (*ap_arv)->valor)
        return remove_(&((*ap_arv)->dir),x);
    else
    if(x < (*ap_arv)->valor)
        return remove_(&((*ap_arv)->esq),x);
    else{
        if((*ap_arv)->dir == NULL && (*ap_arv)->esq == NULL){
            free(*ap_arv);
            *ap_arv = NULL;
            return true;
        }
        else
        if((*ap_arv)->esq == NULL){
            No * aux = *ap_arv;
            *ap_arv = (*ap_arv)->dir;
            free(aux);
            return true;
        }
        else
        if((*ap_arv)->dir == NULL){
            No * aux = *ap_arv;
            *ap_arv = (*ap_arv)->esq;
            free(aux);
            return true;
        }
        else{
            No * aux = (*ap_arv)->esq;
            while(aux->dir != NULL){
                aux = aux->dir;
            }
            (*ap_arv)->valor = aux->valor;
            return remove_(&((*ap_arv)->esq), aux->valor);
        }

    }
}
/** Busca valor x na árvore de busca binária */
bool busca(Arvore arv, int x){
    if(arv == NULL)
        return false;
    if(x > arv->valor)
        return busca(arv->dir, x);
    else
    if(x < arv->valor)
        return busca(arv->esq, x);

    return true;
}

/** Imprime a árvore de busca binária */
void imprime(Arvore arv){
    imprimeArvore(arv);
    printf("\n");
}

void desaloca(Arvore* ap_arv){
    if(*ap_arv == NULL)
        return;
    desaloca(&(*ap_arv)->esq);
    desaloca(&(*ap_arv)->dir);
    free(*ap_arv);
}



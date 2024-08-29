#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "polinomio.h"
/*
 * Implemente as seguintes funcoes de um Tipo Abstrato de Dados de um 
 * Polinômio de coeficientes inteiros. Utilize uma lista circular
 * duplamente ligada com no cabeca, mantendo sempre os coeficientes 
 * ordenados por grau. Somente os coeficientes nao zero devem ser armazenados.
 */

void alocar (Polinomio *aloca, int coef, int grau){
	(*aloca) = (Polinomio)malloc(sizeof(No));
	(*aloca) ->antec = (*aloca);
	(*aloca)->prox = (*aloca);
	(*aloca)->valor.coef = coef;
	(*aloca)->valor.grau = grau;
}

void cria_res(Polinomio * polC,int coef,int grau){
	Polinomio novo_no;
	alocar(&novo_no,coef,grau);
	(*polC)->prox = novo_no;
	novo_no->antec = *polC;
	*polC = (*polC)->prox;
	
}

/* Inicializa um polinômio vazio. */
void inicializa_polinomio(Polinomio * ap_pol){
    *ap_pol = (Polinomio)malloc(sizeof(No));
    (*ap_pol)->prox = *ap_pol;
    (*ap_pol)->antec = *ap_pol;
}

/* Define que o coeficiente de grau grau do polinomio pol eh igual a coef. Deve manter os 
 * coeficientes ordenados por grau. */
void define_coeficiente(Polinomio pol, int grau, int coef){
	Polinomio aux, novo;
	aux = pol;
	if(coef == 0){
		return;
	}
	if(pol->prox==pol){
		alocar(&novo,coef,grau);
		pol->antec = novo;
		pol->prox = novo;
		novo->prox = pol;
		pol->antec = pol;
	}
	while (aux->prox != pol)
	{
		if(aux->prox->valor.grau == grau){
			aux->prox->valor.coef = coef;
			return;
		}
		aux = aux->prox;

	}
	alocar(&novo,coef,grau);
	aux->prox = novo;
	novo->antec=aux;
	novo->prox = pol;
	pol->antec = novo;
	return;
	
}

/* Zera o polinomio, tornando-o um polinomio inicializado, mas igual a zero. Desaloca a memória liberada. */
void zera(Polinomio pol){
	Polinomio aux, remove;
	aux = pol->prox;
	while(aux->prox != pol){
		remove = aux;
		free(remove);
		aux = aux->prox;
	}
	pol->prox = pol;
	pol->antec = pol;
}

/* Computa a soma dos polinomios a e b colocando o resultado em res. 
 * Libera a memória anteriormente utilizada pelos nos descartados de res, e sobreescreve res. */
void soma(Polinomio res, Polinomio a, Polinomio b){
	int soma_coef = 0;
	Polinomio Aaux, Baux, polC;
	Aaux = a->prox;
	Baux = b->prox;
	polC = res;
	while (Aaux != a && Baux != b){
		if(Aaux->valor.grau == Baux->valor.grau){
			soma_coef = Aaux->valor.coef + Baux->valor.coef;
			if(soma_coef == 0){
				Baux = Baux->prox;
				Aaux = Aaux->prox;
				continue;
			}
			cria_res(&polC, soma_coef,Baux->valor.grau);
			Aaux = Aaux->prox;
			Baux = Baux->prox;
			continue;

		}
		if(Aaux->valor.grau > Baux->valor.grau){
			cria_res(&polC,Baux->valor.coef,Baux->valor.grau);
			Baux = Baux->prox;
		}
		else{
			cria_res(&polC,Aaux->valor.coef,Aaux->valor.grau);
			Aaux = Aaux->prox;
		}
	}
	if(Aaux == a){
		while(Baux != b){
			cria_res(&polC, Baux->valor.coef, Baux->valor.grau);
			Baux = Baux->prox;
		}
	}
	else{
		while(Aaux != a){
			cria_res(&polC, Aaux->valor.coef, Aaux->valor.grau);
			Aaux = Aaux->prox;
		}

	}
	polC->prox = res;
	res	->antec = polC;

}

/* Computa a subtracao dos polinomios a e b colocando o resultado em res. 
 * Libera a memória anteriormente utilizada pelos nos descartados de res, e sobreescreve res. */
void subtrai(Polinomio res, Polinomio a, Polinomio b){
	int soma_coef = 0;
	Polinomio Aaux, Baux, polC;
	Aaux = a->prox;
	Baux = b->prox;
	polC = res;
	while (Baux != b && Aaux != a){
		if(Baux->valor.grau == Aaux->valor.grau){
			soma_coef = (Aaux->valor.coef - Baux->valor.coef);
			if(soma_coef == 0){
				Aaux = Aaux->prox;
				Baux = Baux->prox;
				
				continue;
			}
			cria_res(&polC, soma_coef,Baux->valor.grau);
			Aaux = Aaux->prox;
			Baux = Baux->prox;
			
			continue;

		}
		if(Aaux->valor.grau > Baux->valor.grau){
			cria_res(&polC,-Baux->valor.coef,Baux->valor.grau);
			Baux = Baux->prox;
		}
		else{
			cria_res(&polC,Aaux->valor.coef,Aaux->valor.grau);
			Aaux = Aaux->prox;
		}
	}
	if(Aaux == a){
		while(Baux != b){
			cria_res(&polC, -Baux->valor.coef, Baux->valor.grau);
			Baux = Baux->prox;
		}
	}
	else{
		while(Aaux != a){
			cria_res(&polC, Aaux->valor.coef, Aaux->valor.grau);
			Aaux = Aaux->prox;
		}

	}
	polC->prox = res;
	res	->antec = polC;
}


/* Imprime o polinomio pol no formato do exemplo abaixo
 * [(0,2),(3,-2),(10,5)]
 * onde este polinomio tem 3 coeficientes, o de grau 0 com valor 2, o de grau 3 com valor -2 e o de
 * grau 10 com valor 5. 
 */
void imprime(Polinomio pol){
	Polinomio aux = pol->prox;
	printf("[");
	while (aux->prox != pol)
	{
		printf("(%d,%d),", aux->valor.grau,aux->valor.coef);
		aux = aux->prox;
	}
	if(aux != pol){
		printf("(%d,%d)", aux->valor.grau, aux->valor.coef);
	}
	printf("]\n");
	return;

}

/* Desaloca toda a memória alocada da lista.
 */
void desaloca_polinomio(Polinomio *ap_pol){
    Polinomio aux,remove;
	aux = (*ap_pol)->prox;
	while(aux != *ap_pol){
		remove = aux;
		aux = aux->prox;
		free(remove);
	}
	free(aux);
	*ap_pol = NULL;
	return;
}

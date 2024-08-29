#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "lista.h"

/* Inicializa a lista como lista vazia. */
void inicializa_lista(Lista * ap_lista){
    *ap_lista = NULL;
}

/* Insere valor no fim da lista apontada por ap_lista. ap_lista aponta para o inicio da lista. */
void insere_fim(Lista * ap_lista, int valor){
   No* atual;
   No * novo =  malloc(sizeof(No));
   novo -> valor = valor;
   novo -> proximo = NULL;
   if(*ap_lista == NULL){
      *ap_lista = novo;
      return;
   }
   atual = *ap_lista;
   while(atual -> proximo != NULL){
      atual = atual -> proximo;
   }
   atual -> proximo = novo; 
}

/* Insere valor no inicio da lista apontada por ap_lista. */
void insere_inicio(Lista * ap_lista, int valor){
   No * novo = malloc(sizeof(No));
   novo -> valor = valor;
   novo ->proximo = *ap_lista;
   (*ap_lista) = novo;
}

/* Remove valor do fim da lista apontada por ap_lista e retorna este valor. */
int remove_fim(Lista * ap_lista){
   int val;
   Lista aux, remove;
	if((*ap_lista) == NULL){ /*lista vazia*/
      return -1;
   }
   if((*ap_lista)->proximo == NULL){ /*lista que tenha 1 elemento*/
      val = (*ap_lista)->valor;
      free(*ap_lista);
      *ap_lista= NULL;
      return val;
   }
   else { /*lista para mais de 1 elemento*/
      remove = (*ap_lista);
      while (remove->proximo != NULL){
         aux = remove;
         remove = remove->proximo;
      }
      val = remove->valor;
      free(remove);
      aux->proximo = NULL;
      return val;
   }
}

/* Remove valor do inicio da lista apontada por ap_lista e retorna este valor. */
int remove_inicio(Lista * ap_lista){
   Lista remove = *ap_lista;
   int valor;
   if((*ap_lista) == NULL){ 
      return -1;
   }
   valor= remove->valor;
   (*ap_lista) = remove->proximo;
   free(remove);
   return valor;
}

/* Remove o i-ésimo elemento da lista, caso ele exista. Retorna se o elemento 
foi removido. As posições são contadas a partir de 1, sendo 1 a primeira posição. */
bool remove_i_esimo(Lista * ap_lista, int i){
   Lista auxiliar = *ap_lista;
   int contador = 2;
   Lista remove;
   if((*ap_lista) == NULL){ /*lista vazia*/
      return false;
   }
   if(i == 1){
      *ap_lista = auxiliar->proximo;
      free(auxiliar);
      return true;
   }
   while (auxiliar->proximo != NULL && contador != i){
      auxiliar = auxiliar->proximo;
      contador++;
   }
   if(auxiliar->proximo == NULL){
      return false;
   }
   remove = auxiliar->proximo;
   auxiliar->proximo = remove->proximo;
   free(remove);
   return true;
}

/* Retorna o valor do i-ésimo elemento da lista, caso ele exista. 
Retorna -1 caso contrário. As posições são contadas a partir de 1, sendo 1 a primeira posição. */
int recupera_i_esimo(Lista lista, int i){
   int contador;
   if(lista == NULL){
      return -1;
   }
   if(i == 1){
      return lista->valor;
   }
   contador = 2;
   while (lista->proximo != NULL && contador != i)
   {
      lista = lista->proximo;
      contador++;
   }
   if(lista->proximo == NULL){
      return -1;
   }
   return lista->proximo->valor;
}

/* Retorna o tamanho da lista. */
int tamanho(Lista lista){
   int contador = 0;
	for(contador=0;lista!=NULL;contador++)
	{
		lista=lista->proximo;
	}
	return contador;
}

/* Remove todas as ocorrências de valor da lista apontada por ap_lista. 
 * Retorna o numero de ocorrências removidas.
 */
int remove_ocorrencias(Lista *ap_lista, int valor){
   Lista auxiliar;
	int contador;
   Lista remove;
   auxiliar=*ap_lista;
   contador=0;
   if(*ap_lista==NULL)
	{
	   return 0;
	}
	while(*ap_lista!=NULL&&(*ap_lista)->valor==valor)
	{
		*ap_lista=(*ap_lista)->proximo;
		free(auxiliar);
		auxiliar=*ap_lista;
		contador++;
	}
	if(*ap_lista==NULL)
	{
	   return contador;
	}
	while(auxiliar->proximo!=NULL)
	{
		if(auxiliar->proximo->valor==valor)
		{
		contador++;
		remove=auxiliar->proximo;
		auxiliar->proximo=auxiliar->proximo->proximo;
		free(remove);
		continue;
		}
		auxiliar=auxiliar->proximo;
	}
	return contador;
}

/* Busca elemento valor na lista. 
   Retorna a posição na lista, começando de 1=primeira posição.
   Retorna -1 caso não encontrado.
*/
int busca(Lista lista, int valor){
   int posicao;
   for(posicao = 1; lista != NULL; posicao++){
      if(lista->valor == valor)
         return posicao;
      lista = lista->proximo;
   }
   return -1;
}

/* Imprime a lista na saida padrão, no formato:
   (1,3,2,3,4,2,3,1,4)
   em uma linha separada.
 */
void imprime(Lista lista){
   printf("(");
   while (lista != NULL){
		if(lista->proximo==NULL){
			printf("%d",lista->valor);
		}else{
			printf("%d,",lista->valor);
		}
		lista=lista->proximo;
	}
	printf(")\n");
	return; 
}

/* Desaloca toda a memória alocada da lista.
 */
void desaloca_lista(Lista *ap_lista){
   Lista remove;
   while (*ap_lista != NULL)
   {
      remove = *ap_lista;
      *ap_lista = (*ap_lista)->proximo;
      free(remove);
   }
}

/* for ((i =1; i <14; i = i+1)); do ./a.out <ins/$i.in> $i.meu; diff $i.meu ins/$i.out; done */
/*gcc -Wall -ansi -pedantic lab01.c lista.c -o exec
gcc -Wall -ansi -pedantic lab01.c lista.c lista.h 
diff ins/13.out 13.meu
valgrind ./a.out <ins/13.in
for((i = 1; i < 8; i++)); do ./a.out <ins/$i.meu; done
 for((i = 1; i < 8; i++)); do valgrind ./a.out <ins/$i.in; done  
}*/

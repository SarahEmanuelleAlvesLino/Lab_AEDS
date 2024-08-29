#include <stdio.h>
#include <stdlib.h>
#define ultimo_bit (sizeof(int)*8 - 1)
#define insoluvel (1<<ultimo_bit)


typedef struct subconj{
    int elemento;
    int tam;
}ConjConjuto;

ConjConjuto *subconj;
int qtdSubconj;
int n;
int n_bits;

int uns(int conjunto){
    int qtd = 0;
    for(int i = 0; i < qtdSubconj; ++i){
        if((conjunto & (1<<i)) != 0)
            ++qtd;
    }
    return qtd;
}


void imprime (int conjunto){
    printf("%i\n", uns(conjunto) );
    for(int i = 0; i < qtdSubconj; ++i){
        if((conjunto & (1 << i)) != 0){
            printf("%i", subconj[i].tam);
            for (int j = 0; j <= ultimo_bit; ++j){
                if((subconj[i].elemento & (1 << j)) != 0)
                    printf (" %i", j);
            }
            printf("\n");
        }
    }

}


int calculaSolucao(int subconjunto, int pos, int naoSolucao){
    if(pos >= qtdSubconj){
        if(naoSolucao == n_bits){
            return subconjunto;
        }
        return insoluvel;
    }

    int hold_subconjunto0 = insoluvel;
    int hold_subconjunto1 = insoluvel;

    hold_subconjunto0 = calculaSolucao(subconjunto, pos+1, naoSolucao);
    subconjunto = subconjunto | (1 << pos);
    if((naoSolucao & subconj[pos].elemento) == 0){
        naoSolucao = naoSolucao | subconj[pos].elemento;
        hold_subconjunto1 = calculaSolucao(subconjunto,pos+1, naoSolucao);
    }

    if(hold_subconjunto0 != insoluvel)
        return hold_subconjunto0;
        else
            return hold_subconjunto1;
}


int main(){
    n_bits = 0;
    scanf("%i", &n);
    int pos_bit, val;

    for(pos_bit = 0; pos_bit < n; ++pos_bit){
        n_bits = n_bits | (1 << pos_bit);
    }

    scanf("%i", &qtdSubconj);
    subconj = (ConjConjuto *)malloc(qtdSubconj * sizeof(ConjConjuto));

    for(pos_bit = 0; pos_bit < qtdSubconj; ++pos_bit){
        subconj[pos_bit].elemento = 0;
    }

    for(int i = 0; i < qtdSubconj; ++i){ // criando cada subconjunto
        scanf("%i", &subconj[i].tam);
        for(int j = 0; j < subconj[i].tam; ++j){//inserir valores 
            scanf("%i", &val);
            subconj[i].elemento = subconj[i].elemento | (1<<val);
        }
    }

    int resultado = calculaSolucao(0,0,0);
    if(resultado == insoluvel)
        printf("Insoluvel\n");
        else
            imprime(resultado);
    
    free(subconj);
    return 0;

}

/* for ((i =1; i <14; i = i+1)); do ./a.out <ins/$i.in> $i.meu; diff $i.meu ins/$i.out; done */
/*gcc -Wall -ansi -pedantic lab01.c lista.c -o exec
gcc -Wall -ansi -pedantic lab01.c lista.c lista.h 
diff ins/13.out 13.meu
valgrind ./a.out <ins/13.in
for((i = 1; i < 8; i++)); do ./a.out <ins/$i.meu; done
 for((i = 1; i < 8; i++)); do valgrind ./a.out <ins/$i.in; done  
}*/

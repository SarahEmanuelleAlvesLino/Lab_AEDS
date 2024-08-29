#include <stdio.h>

    int n1,n2;

int main(){
    scanf("%d",&n1);
    scanf("%d",&n2);

    int soma1 = 0, soma2 = 0;

    if(n1 > 1 && n1 < 1000000 && n2 > 1 && n2 < 1000000){

        for(int i=1; i<n1; i++){
            if((n1 % i) == 0)
            soma1 += i;
        }

        for(int i=1; i<n2; i++){
            if((n2 % i) == 0)
            soma2 += i;
        }

        if(soma1 == n2 && soma2 == n1)
            printf("amigos\n");
            else
                printf("nao amigos\n");
    }

    return 0;
}

/*for((i=1; i<21; i=i+1))
> do ./a.out <Lab0/ins-outs-lab0/$i.in> $i.meu;
> diff $i.meu Lab0/ins-outs-lab0/$i.out;
> done */

/* for(( i=1; i<21;i=i+1)); do mv $i.meu ./pasta_meu; done*/

#include <stdio.h>

#define MAXIMO_N 20
#define MAXIMO_M 1000000

int qualMaior(int x, int y){
    return (x > y) ? x : y;
}

int main(){
    int M, N,i,j;
    int peso[MAXIMO_N], valor[MAXIMO_M];

    scanf("%d %d", &N, &M);

    for (i = 0; i < N; i++){
        scanf("%d %d", &peso[i], &valor[i]);
    }

    int res[MAXIMO_M + 1] = {0};

    for(i = 0; i < N;i++){
        for(j = M; j >= peso[i]; j--){
            res[j] = qualMaior(res[j], res [ j - peso[i]]+ valor[i]);
        }
    }

    printf("%d\n", res[M]);

    return 0;
}



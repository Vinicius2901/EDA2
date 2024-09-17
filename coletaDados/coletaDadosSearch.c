#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct medias {
    int seq;
    int seqSent;
    int bin;
    int inter;
} Medias;

int seqSearch( int chave, int v[], int n );
int* criaVetor( int *n );
int* geraVetor( int n );
int binSearch( int chave, int v[], int n );
int seqSearchSentinela( int chave, int v[], int n );
int compara( const void* a, const void* n );
int pesquisaInterpolacao(int chave, int v[], int n);

int main() {
    int n = 25, tam = 0;
    // printf("Digite o tamanho do vetor: ");
    // scanf("%i", &n);
    // int *v = criaVetor(&n);
    // int key;
    // printf("Digite o valor que deseja procurar: ");
    // scanf("%i", &key);
    // printf("O total de iteracoes foi %i", seqSearch(key, v, n));
    int *v = geraVetor(n);
    FILE *f = fopen("dados.txt", "rt");
    if( f == NULL ) {
        printf("Falha ao abrir arquivo");
        return 1;
    }
    fscanf( f, "%d", &tam );
    Medias *medias = malloc((tam+1)*sizeof(Medias));
    for( int i = 0; i < tam; i++ ) {
        fscanf( f, "%d,%d,%d,%d", &(medias[i]).seq, &(medias[i]).seqSent, &(medias[i]).bin, &(medias[i]).inter );
    }
    fclose(f);
    medias[tam].seq = seqSearch(v[rand() % n], v, n);
    medias[tam].seqSent = seqSearchSentinela(v[rand() % n], v, n);
    medias[tam].bin = binSearch(v[rand() % n], v, n);
    medias[tam].inter = pesquisaInterpolacao(v[rand() % n], v, n);
    // printf("Pesquisa sequencial\n");
    // printf("Melhor caso: %d\n", seqSearch(v[0], v, n));
    // printf("Pior caso: %d\n", seqSearch(n+1, v, n));
    // printf("Caso medio: %d\n\n", seqSearch(v[rand() % n], v, n));

    // printf("Pesquisa sequencial com sentinela\n");
    // printf("Melhor caso: %d\n", seqSearchSentinela(v[0], v, n));
    // printf("Pior caso: %d\n", seqSearchSentinela(n+1, v, n));
    // printf("Caso medio: %d\n\n", seqSearchSentinela(v[rand() % n], v, n));

    // printf("Pesquisa binaria\n");
    // printf("Melhor caso: %d\n", binSearch(v[n/2], v, n));
    // printf("Pior caso: %d\n", binSearch(n+1, v, n));
    // printf("Caso medio: %d\n\n", binSearch(v[rand() % n], v, n));

    // printf("Pesquisa interpolação\n");
    // printf("Caso medio: %d\n", binSearch(v[rand() % n], v, n));
    f = fopen("dados.txt", "wt");
    if( f == NULL ) {
        printf("Erro no arquivo de saida!\n");
        return 1;
    }
    fprintf( f, "%d\n", tam+1);
    for( int i = 0; i < tam+1; i++ ) {
        fprintf( f, "%d,", medias[i].seq);
        fprintf( f, "%d,", medias[i].seqSent);
        fprintf( f, "%d,", medias[i].bin);
        fprintf( f, "%d\n", medias[i].inter);
    }
    fclose(f);
    free(v);
    return 0;
}

int compara( const void* a, const void* b ) {
    return *(int*)a - *(int*)b;
}

int seqSearch( int chave, int v[], int n ) {
    int i, contador = 1;
    for( i = 0; i < n; i++ ) {
        contador++;
        if( v[i] == chave ) {
            return contador; // return i
        }
        contador++;
    }
    return contador; // return -1
}

int seqSearchSentinela( int chave, int v[], int n ) {
    int i = 0;
    int contador = 1;
    v[n] = chave; // ultima posicao do vetor possui o sentinela
    while( v[i] != chave ) {
        contador++;
        i++;
    }
    contador++;
    if( i < n) return contador; // return i;
    return contador; // indice invalido // return -1;
}

int binSearch( int chave, int v[], int n ) {
    int inicio = 0, meio, fim = n-1, contador = 1;
    while( inicio <= fim ) {
        meio = (inicio+fim)/2;
        contador++;
        if( chave == v[meio] ) {
            return contador; // return meio;
        } else if( chave < v[meio] ) {
            fim = meio-1;
        } else {
            inicio = meio+1;
        }
        contador+=2;
    }
    return contador; // return -1;
}

int* criaVetor( int *n ) {
    int i;
    int *v = malloc( *n * sizeof(int));
    printf("Digite os termos do vetor: ");
    for( i = 0; i < *n; i++ ) {
        scanf("%i", &v[i] );
    }
    return v;
}

int* geraVetor( int n ) {
    int *v = malloc((n+1)*sizeof(int));
    int i;
    srand(time(0));
    for( i = 0; i < n; i++ ) {
        v[i] = rand() % n;
    } // para vetor nao ordenado

    qsort(v, n, sizeof(int), compara );
    // for( i = 0; i < n; i++ ) {
    //     v[i] = i;
    // }
    return v;
}

int pesquisaInterpolacao(int chave, int v[], int n) {
    int ini = 0, meio, fim = n - 1, contador = 3;
    while (ini <= fim && chave >= v[ini] && chave <= v[fim]) {
        contador++;
        if (ini == fim) {
            contador++;
            if(v[ini] == chave) {
                return contador; // return ini;
            } else {
                return contador; // return -1;
            }
        }
        meio = ini + (((double) (fim - ini) / (v[fim] - v[ini])) * (chave - v[ini]));
        contador++;
        if (chave == v[meio]) {
            return contador; // return meio;
        } else if (chave < v[meio]) {
            fim = meio - 1;
        } else {
            ini = meio + 1;
        }
        contador += 4;
    }
    return contador; // return -1; //Índice impossível
}
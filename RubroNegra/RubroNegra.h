#include <stdio.h>
#include <stdlib.h>

#ifndef RUBRO_NEGRA
#define RUBRO_NEGRA
typedef enum coloracao
{
    Preto,
    Vermelho
} Cor;

typedef struct no
{
    struct no *pai;
    struct no *esquerda;
    struct no *direita;
    int valor;
    Cor cor;
} No;

typedef struct rubroNegra
{
    No *raiz;
    No *nulo;
} Arvore;

No* criarNo(Arvore *arvore, No* pai, int valor);
Arvore* criar();
void rotacionarEsquerda(Arvore *arvore, No *no);
void rotacionarDireita(Arvore *arvore, No *no);
int vazia(Arvore* arvore);
No* adicionarNo(Arvore *arvore, No* no, int valor);
No* localizar(Arvore *arvore, No* no, int valor);
void percorrer(Arvore *arvore, No* no, void (*callback)(int) /*Ponteiro de função: aponta para o dendereço da função. Nesse caso, a função deve ser void e tem como parametro um int*/);
void visitar( int a );
void balancear(Arvore *arvore, No *no);
No* adicionar(Arvore* arvore, int valor);
int altura(Arvore *arvore, No* no);


#endif
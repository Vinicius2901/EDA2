#include "RubroNegra.h"

No* criarNo(Arvore *arvore, No* pai, int valor) {
    No* no = malloc(sizeof(No));
    no->valor = valor;
    no->pai = pai;
    no->esquerda = arvore->nulo;
    no->direita = arvore->nulo;
    no->cor = Vermelho;
    return no;
}

Arvore* criar() {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
    arvore->nulo = criarNo(arvore, NULL, 0);
    arvore->nulo->cor = Preto;
  
    return arvore;
}

void rotacionarEsquerda(Arvore *arvore, No *no)
{
    No *direita = no->direita;
    no->direita = direita->esquerda;
    if (direita->esquerda != arvore->nulo)
        direita->esquerda->pai = no;        // Se houver filho à esquerda em direita, ele será pai do nó
    direita->pai = no->pai;                 // Ajusta no pai do nó à direita
    if (no->pai == arvore->nulo)
        arvore->raiz = direita;             // Se nó for raiz, o nó direita será a nova raiz da árvore
    else if (no == no->pai->esquerda)
        no->pai->esquerda = direita;        // Corrige relação pai-filho do novo pai (esquerda)
    else
        no->pai->direita = direita;         // Corrige relação pai-filho do novo pai (direita)
    direita->esquerda = no;                 // Corrige relação pai-filho entre o nó pivô e o nó à direita
    no->pai = direita;
}

void rotacionarDireita(Arvore *arvore, No *no)
{
    No *esquerda = no->esquerda;
    no->esquerda = esquerda->direita;
    if (esquerda->direita != arvore->nulo)
        esquerda->direita->pai = no;        // Se houver filho à direita em esquerda, ele será pai do nó
    esquerda->pai = no->pai;                // Ajusta no pai do nó à esquerda
    if (no->pai == arvore->nulo)
        arvore->raiz = esquerda;            // Se nó for raiz, o nó esquerda será a nova raiz da árvore
    else if (no == no->pai->esquerda)
        no->pai->esquerda = esquerda;       // Corrige relação pai-filho do novo pai (esquerda)
    else
        no->pai->direita = esquerda;        // Corrige relação pai-filho do novo pai (direita)
    esquerda->direita = no;                 // Corrige relação pai-filho entre o nó pivô e o nó à esquerda
    no->pai = esquerda;
}

int vazia(Arvore* arvore) {
    return arvore->raiz == NULL;
}

No* adicionarNo(Arvore *arvore, No* no, int valor) {
    if (valor > no->valor) {
        if (no->direita == arvore->nulo) {
            printf("Adicionando %d\n",valor);
            No* novo = criarNo(arvore, no, valor);
            no->direita = novo;
				
            return novo;
        } else {
            return adicionarNo(arvore, no->direita, valor);
        }
    } else {
        if (no->esquerda == arvore->nulo) {
            printf("Adicionando %d\n",valor);
            No* novo = criarNo(arvore, no, valor);
            no->esquerda = novo;
			
            return novo;
        } else {
            return adicionarNo(arvore, no->esquerda, valor);
        }
    }
}

No* localizar(Arvore *arvore, No* no, int valor) {
    if (no->valor == valor) {
        return no;
    } else {
        if (valor < no->valor) {
            if (no->esquerda != arvore->nulo) {
                return localizar(arvore, no->esquerda, valor);
            }
        } else {
            if (no->direita != arvore->nulo) {
                return localizar(arvore, no->direita, valor);
            }
        }
    }

    return NULL;
}

void percorrer(Arvore *arvore, No* no, void (*callback)(int) /*Ponteiro de função: aponta para o dendereço da função. Nesse caso, a função deve ser void e tem como parametro um int*/) {
    if (no != arvore->nulo) {
        percorrer(arvore, no->esquerda,callback);
        callback(no->valor);
        percorrer(arvore, no->direita,callback);
    }
}

void visitar( int a ) {
    printf("%i ", a);
}

void balancear(Arvore *arvore, No *no)
{
    while (no->pai->cor == Vermelho)
    { // Garante que todos os níveis foram balanceados
        if (no->pai == no->pai->pai->esquerda)
        {
            No *tio = no->pai->pai->direita;
            if (tio->cor == Vermelho)
            {
                tio->cor = Preto; // Resolve caso 2
                no->pai->cor = Preto;
                no->pai->pai->cor = Vermelho;
                no = no->pai->pai; // Vai para o nível anterior
            }
            else
            {
                if (no == no->pai->direita)
                {
                    no = no->pai;                   // Vai para o nível anterior
                    rotacionarEsquerda(arvore, no); // Resolve caso 3
                }
                else
                {
                    no->pai->cor = Preto; // Resolve caso 4
                    no->pai->pai->cor = Vermelho;
                    rotacionarDireita(arvore, no->pai->pai);
                }
            }
        }
        else
        {
            // Repete o mesmo código do bloco if, invertendo o lado dos direita e esquerda
            No *tio = no->pai->pai->esquerda;
            if (tio->cor == Vermelho)
            {
                tio->cor = Preto; // Resolve caso 2
                no->pai->cor = Preto;
                no->pai->pai->cor = Vermelho;
                no = no->pai->pai; // Vai para o nível anterior
            }
            else
            {
                if (no == no->pai->esquerda)
                {
                    no = no->pai;                   // Vai para o nível anterior
                    rotacionarDireita(arvore, no); // Resolve caso 3
                }
                else
                {
                    no->pai->cor = Preto; // Resolve caso 4
                    no->pai->pai->cor = Vermelho;
                    rotacionarEsquerda(arvore, no->pai->pai);
                }
            }
        }
    }
    arvore->raiz->cor = Preto; // Resolve caso 1
}

No* adicionar(Arvore* arvore, int valor) {
    if (vazia(arvore)) {
        printf("Adicionando %d\n",valor);
        arvore->raiz = criarNo(arvore, arvore->nulo, valor);
        arvore->raiz->cor = Preto;
			
        return arvore->raiz;
    } else {
        No* no = adicionarNo(arvore, arvore->raiz, valor);
        balancear(arvore, no);
        return no;
    }
}

int altura(Arvore *arvore, No* no){
	if (no == arvore->nulo) {
		return 0;
	}
	
    int esquerda = altura(arvore, no->esquerda) + 1;
    int direita = altura(arvore, no->direita) + 1;

    return esquerda > direita ? esquerda : direita;
}

int main() {
    Arvore* a = criar();
    int n = 7;
    int i;

    adicionar(a, 3);
    adicionar(a, 6);
    adicionar(a, 2);
    adicionar(a, 1);
    adicionar(a, 7);
    adicionar(a, 5);
    adicionar(a, 4);
    

    printf("In-order: ");
    percorrer(a, a->raiz,visitar);
    printf("\n");
    printf("Altura da arvore: %d\n", altura(a, a->raiz));
}

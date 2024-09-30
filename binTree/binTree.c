#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    struct node *up;
    struct node *left;
    struct node *right;
    int value;
} Node;

typedef struct binTree {
    Node *root;
    int size;
} binTree;

void adiciona( binTree *tree, Node *up, int value ) {
    if( tree != NULL ) {
        if( tree->root == NULL ) {
            Node *node = malloc( sizeof( Node ));
            node->up = NULL;
            node->value = value;
            node->left = NULL;
            node->right = NULL;
            tree->root = node;
            tree->size = 1;
        }
        else {
            if( value < up->value ) {
                if( up->left != NULL ) {
                    adiciona( tree, up->left, value );
                } else {
                    Node *node = malloc(sizeof(Node));
                    node->up = up;
                    node->value = value;
                    node->left = NULL;
                    node->right = NULL;
                    up->left = node;
                    tree->size++;
                }
            } else if( value > up->value ) {
                if( up->right != NULL ) {
                    adiciona( tree, up-> right, value );
                } else {
                    Node *node = malloc(sizeof(Node));
                    node->up = up;
                    node->value = value;
                    node->left = NULL;
                    node->right = NULL;
                    up->right = node;
                    tree->size++;
                }
            }
        }
    }
}

void preOrd( Node *node, int list[], int *i ) {
    if( node != NULL ) {
        list[*i] = node->value;
        (*i)++;
        preOrd( node->left, list, i );
        preOrd( node->right, list, i );
    }
}

void inOrd( Node *node, int list[], int *i ) {
    if( node != NULL ) {
        inOrd( node->left, list, i );
        list[*i] = node->value;
        (*i)++;
        inOrd( node->right, list, i );
    }
}

void posOrd( Node *node, int list[], int *i ) {
    if( node != NULL ) {
        posOrd( node->left, list, i );
        posOrd( node->right, list, i );
        list[*i] = node->value;
        (*i)++;
    }
}

int *horOrd( binTree *tree ) {
    if( tree == NULL ) return NULL;
    int *list = malloc(tree->size*sizeof(int));
    Node *aux = malloc(sizeof(Node));
    for( int i = 0; i < tree->size; i++) {
        if( i = 0 ) {
            list[i] = tree->root;
        }
        
    }
}

int main() {
    binTree *tree = malloc( sizeof(binTree) );
    tree->root = NULL;
    tree->size = 0;
    adiciona( tree, tree->root, 4 );
    adiciona( tree, tree->root, 2 );
    adiciona( tree, tree->root, 8 );
    adiciona( tree, tree->root, 1 );
    adiciona( tree, tree->root, 3 );
    adiciona( tree, tree->root, 6 );
    adiciona( tree, tree->root, 9 );
    adiciona( tree, tree->root, 5 );
    adiciona( tree, tree->root, 7 );
    int listPre[tree->size], listIn[tree->size], listPos[tree->size];
    int n = 0;
    preOrd( tree->root, listPre, &n );
    n = 0;
    inOrd( tree->root, listIn, &n );
    n = 0;
    posOrd( tree->root, listPos, &n );

    printf("Pre-Order: ");
    for( int i = 0; i < tree->size; i++ ) {
        printf("%i ", listPre[i] );
    }
    printf("\nIn-Order: ");
    for( int i = 0; i < tree->size; i++ ) {
        printf("%i ", listIn[i] );
    }
    printf("\nPos-Order: ");
    for( int i = 0; i < tree->size; i++ ) {
        printf("%i ", listPos[i] );
    }
    printf("\n");
    return 0;
}

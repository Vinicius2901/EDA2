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
} binTree;

void adiciona( binTree *tree, Node *up, int value ) {
    if( tree != NULL ) {
        if( tree->root == NULL ) {
            Node *node = malloc( sizeof( Node ));
            node->up = NULL;
            node->left = NULL;
            node->right = NULL;
            tree->root = node;
        }
        else {
            if( value < up->value ) {
                if( up->left != NULL ) {
                    adiciona( tree, up->left, value );
                } else {
                    Node *node = malloc(sizeof(node));
                    node->up = up;
                    node->left = NULL;
                    node->right = NULL;
                    up->left = node;
                }
            } else if( value > up->value ) {
                if( up->right != NULL ) {
                    adiciona( tree, up-> right, value );
                } else {
                    Node *node = malloc(sizeof(node));
                    node->up = up;
                    node->left = NULL;
                    node->right = NULL;
                    up->right = node;
                }
            }
        }
    }
}

void preOrd( Node *node, int **list, int *i ) {
    if( node != NULL ) {
        *list = realloc( *list, ((*i)+1)*sizeof(int) );
        (*list)[(*i)] = node->value;
        (*i)++;
        preOrd( node->left, list, i );
        preOrd( node->right, list, i );
    }
}

int main() {
    binTree *tree = malloc( sizeof(binTree) );
    tree->root = NULL;
    adiciona( tree, tree->root, 4 );
    adiciona( tree, tree->root, 2 );
    adiciona( tree, tree->root, 8 );
    adiciona( tree, tree->root, 1 );
    adiciona( tree, tree->root, 3 );
    adiciona( tree, tree->root, 6 );
    adiciona( tree, tree->root, 9 );
    adiciona( tree, tree->root, 5 );
    adiciona( tree, tree->root, 7 );
    int *list = NULL;
    int n = 0;
    preOrd( tree->root, &list, &n );
    for( int i = 0; i < n+1; i++ ) {
        printf("%i ", list[i] );
    }
    printf("\n");
    return 0;
}

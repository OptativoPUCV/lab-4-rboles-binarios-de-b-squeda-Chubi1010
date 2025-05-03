#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * nuevo = (TreeMap *)malloc(sizeof(TreeMap));
    if (nuevo == NULL) return NULL;
    nuevo->root = NULL;
    nuevo->current = NULL;
    nuevo->lower_than = lower_than;
    if (lower_than == NULL) return NULL;
    return nuevo;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    if (tree == NULL) return;
    TreeNode * nuevo = createTreeNode(key, value);
    if (nuevo == NULL) return;
    if (tree->root == NULL) 
    {
        tree->root = nuevo;
        tree->current = nuevo;
        return;
    }
    TreeNode * x = tree->root;
    TreeNode * y = NULL;
    while (x != NULL) 
    {
        y = x;
        if (tree->lower_than(nuevo->pair->key, x->pair->key)) 
        {
            x = x->left;
        } else if (tree->lower_than(x->pair->key, nuevo->pair->key)) 
        {
            x = x->right;
        } else 
        {
            free(nuevo);
            return;
        }
    }
    nuevo->parent = y;
    if (tree->lower_than(nuevo->pair->key, y->pair->key)) 
    {
        y->left = nuevo;
    } else 
    {
        y->right = nuevo;
    }
    tree->current = nuevo;
    nuevo->left = nuevo->right = NULL;
}

TreeNode * minimum(TreeNode * x){
    if (x == NULL) return NULL;
    while(x->left != NULL) 
    {
        x = x->left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    if (node == NULL) return;
    TreeNode * nodo1 = NULL;
    TreeNode * nodo2 = NULL;
    if (node->left == NULL || node->right == NULL) 
    {
        nodo1 = node;
    } else 
    {
        nodo1 = minimum(node->right);
    }
    if (nodo1->left != NULL) 
    {
        nodo2 = nodo1->left;
    } else 
    {
        nodo2 = nodo1->right;
    }
    if (nodo2 != NULL) 
    {
        nodo2->parent = nodo1->parent;
    }
    if (nodo1->parent == NULL) 
    {
        tree->root = nodo2;
    } else if (nodo1 == nodo1->parent->left) 
    {
        nodo1->parent->left = nodo2;
    } else 
    {
        nodo1->parent->right = nodo2;
    }
    
    if (nodo1 != node) 
    {
        node->pair->key = nodo1->pair->key;
        node->pair->value = nodo1->pair->value;
        
    }
    
    free(nodo1);    
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    if (tree == NULL || tree->root == NULL) return NULL;
    TreeNode * nodo = tree->root;
    while (nodo != NULL) 
    {
        if (tree->lower_than(key, nodo->pair->key)) 
        {
            nodo = nodo->left;
        } else if (tree->lower_than(nodo->pair->key, key)) 
        {
            nodo = nodo->right;
        } else 
        {
            tree->current = nodo;
            return nodo->pair;
        }
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    if (tree == NULL || tree->root == NULL) return NULL;

    // Inicializar variables
    TreeNode * nodo = tree->root;
    TreeNode * ub_node = NULL; 

    while (nodo != NULL) {
        if (tree->lower_than(key, nodo->pair->key)) 
        {
            ub_node = nodo;
            nodo = nodo->left;
        }
        else if (tree->lower_than(nodo->pair->key, key)) 
        {
            nodo = nodo->right; 
        }
        else 
        {
            tree->current = nodo;
            return nodo->pair;        
        }
    }
    if (ub_node != NULL) {
        tree->current = ub_node;
        return ub_node->pair;
    }

    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->root == NULL) return NULL;
    TreeNode * nodo = tree->root;
    while (nodo->left != NULL) 
    {
        nodo = nodo->left;
    }
    tree->current = nodo;
    return nodo->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->current == NULL) return NULL;
    TreeNode * nodo = tree->current;
    if (nodo->right != NULL) 
    {
        nodo = nodo->right;
        while (nodo->left != NULL) 
        {
            nodo = nodo->left;
        }
        tree->current = nodo;
        return nodo->pair;
    } else 
    {
        TreeNode * parent = nodo->parent;
        while (parent != NULL && parent->right == nodo) 
        {
            nodo = parent;
            parent = parent->parent;
        }
        tree->current = parent;
        if (parent != NULL) return parent->pair;
    }
    return NULL;
}

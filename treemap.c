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

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}

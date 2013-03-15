/* 
 * File:   binarytree.c
 * Author: jorisgirardot
 *
 * Created on 15 mars 2013, 15:42
 */

#include "header/binarytree.h"

/*
 * Créaton des noeuds pour l'arbre binaire
 */

//TODO: Intégration de la hauteur du noeud directement
BinaryTree* createNode(int val)
{
    BinaryTree *res = NULL;
    
    res = malloc(sizeof(BinaryTree));
    
    if(res != NULL)
    {
        BinaryTree tmp = {0};
        *res = tmp;
        
        res->value = val;
    }
    else
    {
        fprintf(stderr, "Allocation impossible");
        //exit(EXIT_FAILURE);
    }
    
    return res;
}

BinaryTree* createNodeWithChilds(BinaryTree *left, int val, BinaryTree *right)
{
    BinaryTree *res = createNode(val);
    
    if(res != NULL)
    {
        res->Left = left;
        res->Right = right;
    }
    
    return res;
}


/*
 * Accesseurs
 */

int nodeValue(BinaryTree *tree)
{
    return (tree != NULL) ? tree->value : NULL;
}

// Renvoie la différence de hauteur entre le fils droit et le fils gauche
int nodeDifference(BinaryTree *tree)
{
    return abs(height(rightChild(tree)) - height(leftChild(tree)));
}

BinaryTree* leftChild(BinaryTree *tree)
{
    return (tree != NULL && tree->Left != NULL) ? tree->Left : NULL;
}

BinaryTree* rightChild(BinaryTree *tree)
{
    return (tree != NULL && tree->Right != NULL) ? tree->Right : NULL;
}


/*
 * Vérificateur
 */
Bool isBTree(BinaryTree* tree)
{
     if(isLeaf(tree))
        return TRUE;
    
    int sizeLeft = height(leftChild(tree));
    int sizeRight = height(rightChild(tree));
    
    printf("(%d - %d) = %d\n", sizeLeft, sizeRight, abs(sizeLeft - sizeRight));
    
    return abs(sizeLeft - sizeRight) <= 1 && isBTree(leftChild(tree)) && isBTree(rightChild(tree));
}


Bool isEmpty(BinaryTree *tree)
{
    return tree == NULL;
}

Bool isLeaf(BinaryTree *tree)
{
    return (leftChild(tree) == NULL && rightChild(tree) == NULL);
}


/*
 * Calcul de la hauteur de l'arbre
 */
int height(BinaryTree* tree)
{
    if(tree == NULL)
        return 0;
    
    if(isLeaf(tree))
        return 1;
    else
        return 1 + (max(height(leftChild(tree)), height(rightChild(tree))));
}


/*
 * Affichage préfixé
 */
void preorderTraversal(BinaryTree  *tree)
{
    printf("%d ", tree->value);
    
    if(isEmpty(leftChild(tree)) == FALSE)
        preorderTraversal(leftChild(tree));
    
    if(isEmpty(rightChild(tree)) == FALSE)
        preorderTraversal(rightChild(tree));

}


BinaryTree* rotateLeft(BinaryTree *tree)
{
    BinaryTree *b = rightChild(tree);
    tree->Right = leftChild(b);
    b->Left = tree;
    
    return b;
}
BinaryTree* rotateRight(BinaryTree *tree)
{
    BinaryTree* b = leftChild(tree);
    tree->Left = rightChild(b);
    b->Right = tree;
    
    return b;
}
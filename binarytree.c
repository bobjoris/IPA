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


BinaryTree* insertNode(int val, BinaryTree *tree)
{
    if(tree == NULL)
        return createNodeWithChilds(NULL, val, NULL);
    
    if(val <= nodeValue(tree))
        tree->Left = insertNode(val, tree->Left);
    else if(val > nodeValue(tree))
        tree->Right = insertNode(val, tree->Right);
    
    return rotate(tree);
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
    return height(rightChild(tree)) - height(leftChild(tree));
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


BinaryTree* rotate(BinaryTree *tree)
{
    int nodeDiff = nodeDifference(tree);
    if(nodeDiff == -2)
    {
        BinaryTree *left = leftChild(tree);
        if(height(leftChild(left)) < height(rightChild(left)))
            tree->Left = rotateLeft(tree->Left);
        
        return rotateRight(tree);
    }
    
    if(nodeDiff == 2)
    {
         BinaryTree *right = rightChild(tree);
        if(height(leftChild(right)) > height(rightChild(right)))
            tree->Right = rotateRight(tree->Right);
        
        return rotateLeft(tree);
    }
    
    return tree;
}

BinaryTree* rotateLeft(BinaryTree *tree)
{
    BinaryTree *pivot = tree->Right;
    if(pivot != NULL)
    {
        tree->Right = pivot->Left;
        pivot->Left = tree;
        tree = pivot;
    }
    return tree;
}
BinaryTree* rotateRight(BinaryTree *tree)
{
    BinaryTree *pivot = tree->Left;
    if(pivot != NULL)
    {
    tree->Left = pivot->Right;
    pivot->Right = tree;
    tree = pivot;
    }
    return tree;
}
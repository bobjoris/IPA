/* 
 * File:   binarytree.h
 * Author: jorisgirardot
 *
 * Created on 15 mars 2013, 15:48
 */

#ifndef BINARYTREE_H
#define	BINARYTREE_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef struct BinaryTree_
{
    int value;
    struct BinaryTree_ *Left;
    struct BinaryTree_ *Right;
}BinaryTree;

/*
 * Création / Insertion de noeuds
 */
// Crée un noeud avec la valeur passé en paramètre
BinaryTree* createNode(int val);
// Crée un noedu avec deux fils passé en paramètre
BinaryTree* createNodeWithChilds(BinaryTree *left, int val, BinaryTree *right);
// Insère un noeud dans l'arbre passé en paramètre
BinaryTree* insertNode(int val, BinaryTree *tree);
// Supprime une feuille dans un arbre
BinaryTree* deleteLeaf(int val, BinaryTree *tree);


/*
 * Accesseurs
 */
// Fils gauche et droit
BinaryTree* leftChild(BinaryTree *tree);
BinaryTree* rightChild(BinaryTree *tree);

// Valeur du noeud
int nodeValue(BinaryTree *tree);

// La différence entre la hauteur du fils droit et du fils gauche
int nodeDifference(BinaryTree *tree);

/*
 * Vérificateur
 */
// Verifie la présence du noeud dans l'arbre
Bool haveNode(int val, BinaryTree* tree);
// Verifie si la valeur val est une feuille dans l'arbre
Bool isLeafInTree(int val, BinaryTree* tree);
// Vérifie si l'arbre est vide
Bool isEmpty(BinaryTree *tree);
// Vérifie si l'arbre est équilibré
Bool isBTree(BinaryTree *tree);
// Vérifie si l'arbre est une feuille
Bool isLeaf(BinaryTree *tree);

// Calcul de la hauteur de l'arbre
int height(BinaryTree *tree);

/*
 * Affichage de l'arbre
 */
// Affiche préfixé
void preorderTraversal(BinaryTree  *tree);

/*
 * Rotations
 */

// Transforme un arbre binaire, en un arbre binaire 
BinaryTree* transformBTree(BinaryTree *tree);

// Définit la rotation à appliquer
BinaryTree* rotate(BinaryTree *tree);

// Effectue une rotation gauche
BinaryTree* rotateLeft(BinaryTree *tree);
// Effectue une rotation droite
BinaryTree* rotateRight(BinaryTree *tree);


#endif	/* BINARYTREE_H */


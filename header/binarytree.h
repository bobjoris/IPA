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
    int height;
    struct BinaryTree_ *Left;
    struct BinaryTree_ *Right;
}BinaryTree;

BinaryTree* createNode(int val);
BinaryTree* createNodeWithChilds(BinaryTree *left, int val, BinaryTree *right);

BinaryTree* leftChild(BinaryTree *tree);
BinaryTree* rightChild(BinaryTree *tree);

int nodeValue(BinaryTree *tree);
int nodeDifference(BinaryTree *tree);

Bool isEmpty(BinaryTree *tree);
Bool isBTree(BinaryTree *tree);
Bool isLeaf(BinaryTree *tree);

int height(BinaryTree *tree);

void preorderTraversal(BinaryTree  *tree);

void rotate(BinaryTree *tree);
BinaryTree* rotateLeft(BinaryTree *tree);
BinaryTree* rotateRight(BinaryTree *tree);


#endif	/* BINARYTREE_H */


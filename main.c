/* 
 * File:   main.c
 * Author: jorisgirardot
 *
 * Created on 15 mars 2013, 15:42
 */

#include <stdio.h>
#include <stdlib.h>

#include "header/main.h"

/*
 * 
 */
int main(int argc, char** argv) {


    BinaryTreeTest();
    
    return (EXIT_SUCCESS);
}

void BinaryTreeTest()
{
    BinaryTree *treeL, *treeR, *tree;
    
    treeL = createNode(17);
    treeL->Left = createNode(9);
    treeL->Left->Right = createNode(14);
    treeL->Left->Right->Left = createNode(12);
    
    treeR = createNode(76);
    treeR->Left = createNode(54);
    treeR->Left->Right = createNode(72);
    
    tree = createNodeWithChilds(treeL, 50, treeR);
    printf("%d\n", height(tree));
    preorderTraversal(tree);

}


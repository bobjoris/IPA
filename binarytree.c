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
    
    return tree;
}

BinaryTree *insertNodeWithRotation(int val, BinaryTree* tree)
{
    return transformBTree(insertNode(val, tree));
}

BinaryTree* copyTree(BinaryTree * tree){
    BinaryTree* res = malloc(sizeof(BinaryTree));
    
    res->value = tree->value;
    if(leftChild(tree) != NULL)
        res->Left = copyTree(tree->Left);
    else
        res->Left = NULL;
    
    if(rightChild(tree) != NULL)
        res->Right = copyTree(tree->Right);
    else
        res->Right = NULL;
    
    return res;
}

int numberOfLeaf(BinaryTree* tree, int val)
{
	int res;
	if(nodeValue(tree)==val)//une fois le noeud touvé
	{
		if(rightChild(tree)==NULL && leftChild(tree)==NULL)//cas d'une feuille
		{res=0;}
		else if(rightChild(tree)==NULL && leftChild(tree)!=NULL)//cas d'un noeud à 1 fils
		{res=1;}
		else if(rightChild(tree)!=NULL && leftChild(tree)==NULL)//cas d'un noeud à 1 fils
		{res=1;}
		else//cas d'un noeud à 2 fils
		{res=2;}
	}
	else//on cherche le noeud de valeur val
	{
		if(val>=nodeValue(tree))
		{res=numberOfLeaf(rightChild(tree),val);}//en se deplacant à droite
		else
		{res=numberOfLeaf(leftChild(tree),val);}//en se deplacant à gauche
	}
	return res;
}

int maxNode(BinaryTree* tree)
{
	int res;
	if(rightChild(tree)!=NULL)
	{
		res=maxNode(rightChild(tree));//la valeur maximale n'st pas encore atteinte, donc on fait un appel recursif
	}
	else
	{
		res=nodeValue(tree);//on a atteint la valeur max	
	}
	return res;
}

BinaryTree* setNode(int val, int intoval, BinaryTree* tree)
{
	BinaryTree *res=NULL;
	res = malloc(sizeof(BinaryTree));
	if(tree!=NULL){
		if(nodeValue(tree)==val)//une fois le noeud trouvé, on remplace sa valeur
		{
			tree->value=intoval;
		}
		else//sinon on parcoure les sous arbres droits et gauches
		{
			setNode(val,intoval,rightChild(tree));
			setNode(val,intoval,leftChild(tree));
		}
	}
	return tree;
}

BinaryTree* switchNode(int val1, int val2, BinaryTree* tree)
{
	//on utilise 3 fois la fonction setNode pour faire l'échange de valeurs
	int intoval2=1000;//valeur intermédiaire de remplacement d'un noeud
	setNode(val1, intoval2, tree);
	setNode(val2, val1, tree);
	setNode(intoval2, val2, tree); 
	return tree;
}

BinaryTree* deleteLeaf(int val, BinaryTree *tree)
{
	BinaryTree *res=NULL;
	res = malloc(sizeof(BinaryTree));
	if((haveNode(val,tree))&&(isLeafInTree(val,tree)))//condition : le noeud est present et c'est une feuille
	{
		if(nodeValue(tree)==val)//lorsque la valeur est trouvée, on supprime la feuille
		{
			res=NULL;		
		}
		else// sinon on cherche dans les sous arbres droits et gauches
		{
			res=createNodeWithChilds(deleteLeaf(val,leftChild(tree)),nodeValue(tree),deleteLeaf(val,rightChild(tree)));
		}
	}
	else//la valeur n'est pas présente, on retourne l'arbre d'entrée
	{
		res=tree;
	}
	return res;
}

BinaryTree* deleteNode1(int val, BinaryTree *tree)
{
	BinaryTree *res=NULL;
	res = malloc(sizeof(BinaryTree));
	if(haveNode(val,tree))//condition : le noeud est présent
	{
		if(nodeValue(tree)==val)// si le noeud est trouvée
		{
			if(rightChild(tree)==NULL)// sous arbre droit nul on retourne le sous arbre gauche
			{
				res=leftChild(tree);
			}
			else// sous arbre gauche nul on retourne le sous arbre droit
			{
				res=rightChild(tree);
			}		
		}
		else// sinon on cherche dans les sous arbres droits et gauches
		{
			res=createNodeWithChilds(deleteNode1(val,leftChild(tree)),nodeValue(tree),deleteNode1(val,rightChild(tree)));
		}
	}
	else// si le noeud n'est pas présent, on retourne l'arbre d'entrée
	{
		res=tree;
	}
	return res;
}

BinaryTree* deleteNode2(int val, BinaryTree *tree)
{
	BinaryTree *res=NULL;
	res = malloc(sizeof(BinaryTree));
	if(haveNode(val,tree))//condition : le noeud est présent
	{
		//on supprime le noeud val dans l'arbre ou a été effectue un échange entre val et le noeud de valeur maximale dans le sous arbre gauche
		res=deleteNode1(val,switchNode(val,maxNode(leftChild(tree)),tree));
	}
	else// si le noeud n'est pas présent, on retourne l'arbre d'entrée
	{
		res=tree;
	}
	return res;
}

BinaryTree* deleteNode(int val, BinaryTree *tree)
{
	if(haveNode(val,tree))//condition : le noeud est présent
	{
		switch(numberOfLeaf(tree,val)){//test du nombre de fils et appel de la fonction adequate
			case 0:
			return deleteLeaf(val,tree);
			break;
				
			case 1:
			return deleteNode1(val,tree);
			break;
			
			case 2:
			return deleteNode2(val,tree);
			break;
			
			default:
			return tree;
			break;
		}
	}
	else
	{
		return tree;
	}
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
Bool haveNode(int val, BinaryTree* tree)
{
	Bool res;
	if(isLeaf(tree))//si l'arbre est une feuille
	{
		if(nodeValue(tree)==val)//si la feuille est presente, on retourne vrai
		{
			res=TRUE;
		}
		else // sinon faux
		{
			res=FALSE;
		}
	}
	else
	{
		if(nodeValue(tree)==val)//si le noeud est present, on retourne vrai
		{
			res=TRUE;
		}
		else// appel recursif : la valeur est presente dans le sous arbre droit OU dans le sous arbre gauche
		{
			res=(haveNode(val,rightChild(tree)))||(haveNode(val,leftChild(tree)));
		}
	}
	return res;
} 

Bool isLeafInTree(int val, BinaryTree* tree)
{
	Bool res;
	if(isLeaf(tree))
	{
		if(nodeValue(tree)==val)
		{
			res=TRUE;
		}
		else
		{
			res=FALSE;
		}
	}
	else
	{
		res=(isLeafInTree(val,rightChild(tree)))||(isLeafInTree(val,leftChild(tree)));
	}
	return res;	
} 

Bool isBTree(BinaryTree* tree)
{
     if(isLeaf(tree))
        return TRUE;
    
    int sizeLeft = height(leftChild(tree));
    int sizeRight = height(rightChild(tree));
    
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


BinaryTree* transformBTree(BinaryTree *tree)
{
    while(isBTree(tree) !=  1)
    {
        tree->Left = transformBTree(tree->Left);
        tree->Right = transformBTree(tree->Right);
        
        tree = rotate(tree);
    }
    
    return tree;
}

/*
 * Affichage préfixés
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

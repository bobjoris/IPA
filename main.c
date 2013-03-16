/* 
 * File:   main.c
 * Author: jorisgirardot
 *
 * Created on 15 mars 2013, 15:42
 */

#include "header/main.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    SDL_Surface *screen;
    BinaryTree *tree;
    
    tree = BinaryTreeTest();
    

    screen = initSDLWindow();
    drawTree(screen, tree, 600, 50, 30, height(tree));
    
    SDL_Flip(screen);
    pause(); 
  
    SDL_Quit(); 

    
    return (EXIT_SUCCESS);
}

BinaryTree* BinaryTreeTest()
{
    BinaryTree *treeL, *treeR, *tree;
    
    
    int i=0;
    tree = insertNode(1, NULL);
    for(i = 2; i < 10; i++)
    {
        tree = insertNode(i, tree);
    }

    /*treeL = createNode(17);
    treeL->Left = createNode(9);
    treeL->Left->Right = createNode(14);
    treeL->Left->Right->Left = createNode(12);
    
    treeR = createNode(76);
    treeR->Left = createNode(54);
    treeR->Left->Right = createNode(72);
    
    tree = createNodeWithChilds(treeL, 50, treeR); */
    
   /* tree = insertNode(7, NULL); 
    

    tree = insertNode(9, tree);

    tree = insertNode(14, tree);
    tree = insertNode(12, tree);
    tree = insertNode(76, tree);
    tree = insertNode(54, tree);
    tree = insertNode(72, tree);
    tree = insertNode(50, tree); */
    
    printf("%d\n", isBTree(tree));
    preorderTraversal(tree);
    
    tree = transformBTree(tree);

    return tree;
}


SDL_Surface* initSDLWindow()
{
    SDL_Surface *screen;
    
    SDL_Init(SDL_INIT_VIDEO); 
  
    screen = SDL_SetVideoMode(1300, 768, 32, SDL_HWSURFACE);
    
    if (screen == NULL) 
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    

    
    SDL_Flip(screen);
    
    SDL_WM_SetCaption("IPA : Rotation sur les Arbres Binaires", NULL);
    
    return screen;
}


void pause()
{
    int continuer = 1;
    SDL_Event event;
  
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
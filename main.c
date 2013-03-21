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
    BinaryTree *tree = NULL;
    
    BinaryTree *tabTree[16];

    int val[] = {76, 7, 9, 14, 12, 72, 54, 50};
    int i = 0, j = 0;
    for (i; i < 8; i++) {
        tree = insertNode(val[i], tree);

        tabTree[j++] = copyTree(tree);

        tree = transformBTree(tree);
        tabTree[j++] = copyTree(tree);
    }

    screen = initSDLWindow();
    waitEvent(screen, tabTree);
    SDL_Quit(); 


    return (EXIT_SUCCESS);
}

BinaryTree* BinaryTreeTest() {
    BinaryTree *treeL, *treeR, *tree;


    /* int i=0;
     tree = insertNode(1, NULL);
     for(i = 2; i < 10; i++)
     {
         tree = insertNode(i, tree);
     } */

    treeL = createNode(17);
    treeL->Left = createNode(9);
    treeL->Left->Right = createNode(14);
    treeL->Left->Right->Left = createNode(12);
    treeL->Right = createNode(23);
    treeL->Right->Left = createNode(19);

    treeR = createNode(76);
    treeR->Left = createNode(54);
    treeR->Left->Right = createNode(72);
    treeR->Left->Right->Left = createNode(67);

    tree = createNodeWithChilds(treeL, 50, treeR);

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

SDL_Surface* initSDLWindow() {
    SDL_Surface *screen;

    SDL_Init(SDL_INIT_VIDEO);
    //SDL_EnableKeyRepeat(10, 10);
    screen = SDL_SetVideoMode(1300, 768, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if (screen == NULL) {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    SDL_Flip(screen);

    SDL_WM_SetCaption("IPA : Rotation sur les Arbres Binaires", NULL);

    return screen;
}

void waitEvent(SDL_Surface *screen, BinaryTree *tabTree[]) {
    int continuer = 1;
    int posX = 700, posY = 50;
    int index = 0;
    SDL_Event event;
    BinaryTree* tree = NULL;
    char textDisplay[255];

    while (continuer) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                        continuer = 0;
                        break;
                    case SDLK_DOWN: // Flèche bas
                        posY++;
                        break;
                    case SDLK_UP : // Flèche du hat
                        posY--;
                        break;
                    case SDLK_LEFT :
                        index--;
                        break;
                    case SDLK_RIGHT :
                        index++;
                        break;
                }
                break;
        }
        clearScreen(screen);
        posX = ( posX < 30) ? 30 : posX;
        posY = ( posX < 30) ? 30 : posY;
        index = (index < 0) ? 0 : index;
        tree = tabTree[index];
        sprintf(textDisplay, "Indice : %d", index);
        drawTree(screen, tree, posX, posY, 30, height(tree));
        drawText(screen, 700, 700, 20, textDisplay);
        SDL_Flip(screen);
    }
}
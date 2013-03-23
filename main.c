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

    BinaryTree * tabTree[16];

    //int val[] = {76, 7, 9, 14, 12, 72, 54, 50};
    int i = 0, j = 0;
    for (i; i < 8; i++) {
        tree = insertNode(i, tree);

        tabTree[j++] = copyTree(tree);

        tree = transformBTree(tree);
        tabTree[j++] = copyTree(tree);
    }

    screen = initSDLWindow();
    editEvent(screen);
    //waitEvent(screen, tabTree);
    SDL_Quit();


    return (EXIT_SUCCESS);
}

BinaryTree* BinaryTreeTest() {
    BinaryTree *treeL, *treeR, *tree;

    return tree;
}

SDL_Surface* initSDLWindow() {
    SDL_Surface *screen;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_EnableKeyRepeat(100, 100);
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

int displayMenu() {
    int res = 0;
    printf("\n**Menu**\n--------------\n\n");
    printf("1. Ajouter un noeud\n");
    printf("2. Supprimer un noeud\n");
    printf("3. Parcourir les étapes\n\n");

    printf("Votre choix : ");
    scanf("%d", &res);

    return res;
}

void editEvent(SDL_Surface *screen) {
    BinaryTree *tree = NULL;
    BinaryTree *tabTree[128] = {0};

    int posX = 700, posY = 50, i = 0;
    int menuChoice = 0, option = 0;
    Bool endWhile = FALSE;

    do {
        menuChoice = displayMenu();

        switch (menuChoice) {
            case 1:
                endWhile = FALSE;
                while (!endWhile) {
                    printf("\nValeur du noeud : ");
                    scanf("%d", &option);

                    if(option < 0)
                        endWhile = TRUE;
                    else
                    {
                        tree = insertNode(option, tree);
                        tabTree[i++] = copyTree(tree);
                        tree = transformBTree(tree);
                        tabTree[i++] = copyTree(tree);
                    }

                    clearScreen(screen);
                    drawTree(screen, tabTree[i - 1], posX, posY, 30, height(tree));
                    SDL_Flip(screen);
                }
                break;
            case 2:
                printf("\nValeur du noeud : ");
                scanf("%d", &option);
                tree = deleteNode(option, tree);
                tabTree[i++] = copyTree(tree);
                
                clearScreen(screen);
                drawTree(screen, tabTree[i - 1], posX, posY, 30, height(tree));
                SDL_Flip(screen);
                break;
            case 3:
                waitEvent(screen, tabTree);
                break;

        }

    } while (menuChoice != 0);
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
                        posX -= 10;
                        break;
                    case SDLK_UP: // Flèche du hat
                        posX += 10;
                        break;
                    case SDLK_LEFT:
                        index--;
                        break;
                    case SDLK_RIGHT:
                        index++;
                        break;
                }
                break;
        }
        clearScreen(screen);
        posX = (posX < 30) ? 30 : posX;
        posY = (posX < 30) ? 30 : posY;
        index = (index < 0) ? 0 : index;
        tree = tabTree[index];
        sprintf(textDisplay, "Indice : %d", index);
        drawTree(screen, tree, posX, posY, 30, height(tree));
        drawText(screen, 700, 700, 20, textDisplay);
        SDL_Flip(screen);
    }
}
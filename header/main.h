/* 
 * File:   main.h
 * Author: jorisgirardot
 *
 * Created on 15 mars 2013, 16:10
 */

#ifndef MAIN_H
#define	MAIN_H


#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "utils.h"
#include "binarytree.h"
#include "binarytree_sdl.h"

BinaryTree* BinaryTreeTest();

SDL_Surface* initSDLWindow();
void waitEvent(SDL_Surface*, BinaryTree *tabTree[]);

#endif	/* MAIN_H */


/* 
 * File:   binarytree_sdl.h
 * Author: joris
 *
 * Created on March 15, 2013, 3:02 PM
 */

#ifndef BINARYTREE_SDL_H
#define	BINARYTREE_SDL_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "utils.h"
#include "binarytree.h"


void drawTree(SDL_Surface *surface, BinaryTree *tree, int x, int y, int circleSize, int offsetCoeff);

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

void drawLine(SDL_Surface *surface, Uint32 x1, Uint32 y1, Uint32 x2, Uint32 y2, Uint32 color);

void drawCircle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel);

#endif	/* BINARYTREE_SDL_H */


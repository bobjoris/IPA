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

/*
 * Gestion de l'affichage graphique des arbres
 */

// Permet de vider l'écran
void clearScreen(SDL_Surface *surface);

// Dessine un arbre
void drawTree(SDL_Surface *surface, BinaryTree *tree, int x, int y, int circleSize, int offsetCoeff);

// Inscrit un pixel sur la surface
void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

// Dessine une ligne du point (x1,y1) au point (x2,y2) sur la surface
void drawLine(SDL_Surface *surface, Uint32 x1, Uint32 y1, Uint32 x2, Uint32 y2, Uint32 color);

// Dessine un cercle sur la surface
void drawCircle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel);

void drawText(SDL_Surface *surface, int x, int y, int size, char* str);

#endif	/* BINARYTREE_SDL_H */


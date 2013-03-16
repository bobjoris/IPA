#include "header/binarytree_sdl.h"
#include <math.h>
#define M_PI 3.14159265358979323846
#define SGN(x) ((x)>0 ? 1 : ((x)==0 ? 0:(-1)))

void drawTree(SDL_Surface *surface, BinaryTree *tree, int x, int y, int circleSize, int offsetCoeff)
{   
    
    // Initialisation du texte
    TTF_Font *font = NULL;
    SDL_Surface *texte;
    char strNodeValue[255];
    SDL_Rect position;
    SDL_Color blackColor = {0, 0, 0};
    
    TTF_Init();
    font = TTF_OpenFont("font.ttf", 13);
    sprintf(strNodeValue, "%d", nodeValue(tree));
    texte = TTF_RenderText_Blended(font, strNodeValue, blackColor);
    position.x = x - 5; position.y = y - 15;
    //Affichage du texte
    SDL_BlitSurface(texte, NULL, surface, &position); 
    
    position.y += 15;
    sprintf(strNodeValue, "%d", nodeDifference(tree));
    texte = TTF_RenderText_Blended(font, strNodeValue, blackColor);
     SDL_BlitSurface(texte, NULL, surface, &position); 
    
    // Calcul du déport des cercles des enfants
    int offset = circleSize + ((circleSize / 2) * offsetCoeff);
    
    // Sélection de la couleur et affichage du cercle
    Uint32 color = SDL_MapRGB(surface->format, 0, 0, 0);
    drawCircle(surface, x, y, circleSize, color);
    
    if(leftChild(tree) != NULL)
    {
        // Calcul des coordonnées de l'arete
        float x1 = x + (circleSize) * cos(120 * (M_PI / 180));
        float y1 = y + (circleSize) * sin(120 * (M_PI / 180));
        float x2 = (x - offset) + (circleSize) * cos(300 * (M_PI / 180));
        float y2 = (y + offset) + (circleSize) * sin(300 * (M_PI / 180));
        drawLine(surface, (int) x1, (int) y1, (int)x2, (int)y2, color);
        drawTree(surface, leftChild(tree), x - offset, y + offset, circleSize, offsetCoeff - 1);
    }
    if(rightChild(tree) != NULL)
    {
        // Calcul des coordonnées de l'arete
        float x1 = x + (circleSize) * cos(60 * (M_PI / 180));
        float y1 = y + (circleSize) * sin(60 * (M_PI / 180));
        float x2 = (x + offset) + (circleSize) * cos(250 * (M_PI / 180));
        float y2 = (y + offset) + (circleSize) * sin(250 * (M_PI / 180));
        drawLine(surface, (int) x1, (int) y1, (int)x2, (int)y2, color);
        drawTree(surface, rightChild(tree), x + offset, y + offset, circleSize, offsetCoeff - 1);
    }
}

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
    *(Uint32 *)target_pixel = pixel;
}

void drawLine(SDL_Surface *surface, Uint32 x1, Uint32 y1, Uint32 x2, Uint32 y2, Uint32 color)
{
  int lg_delta, sh_delta, cycle, lg_step, sh_step;

  lg_delta = x2 - x1;
  sh_delta = y2 - y1;
  lg_step = SGN(lg_delta);
  lg_delta = abs(lg_delta);
  sh_step = SGN(sh_delta);
  sh_delta = abs(sh_delta);
  if (sh_delta < lg_delta) {
    cycle = lg_delta >> 1;
    while (x1 != x2) {
      setPixel(surface, x1, y1, color);
      cycle += sh_delta;
      if (cycle > lg_delta) {
	cycle -= lg_delta;
	y1 += sh_step;
      }
      x1 += lg_step;
    }
    setPixel(surface, x1, y1, color);
  }
  cycle = sh_delta >> 1;
  while (y1 != y2) {
    setPixel(surface, x1, y1, color);
    cycle += lg_delta;
    if (cycle > sh_delta) {
      cycle -= sh_delta;
      x1 += lg_step;
    }
    y1 += sh_step;
  }
  setPixel(surface, x1, y1, color);
}

void drawCircle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel)
{
    double error = (double)-radius;
    double x = (double)radius -0.5;
    double y = (double)0.5;
    double cx = n_cx - 0.5;
    double cy = n_cy - 0.5;
 
    while (x >= y)
    {
        setPixel(surface, (int)(cx + x), (int)(cy + y), pixel);
        setPixel(surface, (int)(cx + y), (int)(cy + x), pixel);
 
        if (x != 0)
        {
            setPixel(surface, (int)(cx - x), (int)(cy + y), pixel);
            setPixel(surface, (int)(cx + y), (int)(cy - x), pixel);
        }
 
        if (y != 0)
        {
            setPixel(surface, (int)(cx + x), (int)(cy - y), pixel);
            setPixel(surface, (int)(cx - y), (int)(cy + x), pixel);
        }
 
        if (x != 0 && y != 0)
        {
            setPixel(surface, (int)(cx - x), (int)(cy - y), pixel);
            setPixel(surface, (int)(cx - y), (int)(cy - x), pixel);
        }
 
        error += y;
        ++y;
        error += y;
 
        if (error >= 0)
        {
            --x;
            error -= x;
            error -= x;
        }
    }
}


#include "header/binarytree_sdl.h"
#include <math.h>
#define M_PI 3.14159265358979323846
#define SGN(x) ((x)>0 ? 1 : ((x)==0 ? 0:(-1)))

void clearScreen(SDL_Surface *surface) {
    SDL_FillRect(surface, NULL, 0xfffffff);
}

void drawTree(SDL_Surface *surface, BinaryTree *tree, int treeDepth, int depth, int px, int py, int index, int prevDiff) {

    if (isEmpty(tree)) {
        return;
    }

    double x, y, rH, rL, radius;
    int nodeDiff = nodeDifference(tree);

    rH = ((float) surface->h / (float) (depth)) / 2.0;
    rL = ((float) surface->w / (pow(2, depth - 1))) / 3.0;

    radius = min(rH, rL);


    x = ((index * surface->w) / (pow(2, treeDepth) + 1));
    y = ((treeDepth * surface->h) / depth) + radius;

    // Sélection de la couleur et affichage du cercle
    Uint32 color, colorLine;
    color = SDL_MapRGB(surface->format, 0, 0, 0);
    colorLine = SDL_MapRGB(surface->format, 0, 0, 0);


    if (nodeDiff == 2 || nodeDiff == -2)
        color = SDL_MapRGB(surface->format, 255, 0, 0);


    // Si c'est la ligne droite
    if (prevDiff == 2 && index % 2 == 0)
        colorLine = SDL_MapRGB(surface->format, 255, 0, 0);
    if (prevDiff == -2 && index % 2 == 1) // Si c'est la ligne gauche
        colorLine = SDL_MapRGB(surface->format, 255, 0, 0);


    drawCircle(surface, (int) x, (int) y, radius, color);

    // Initialisation du texte
    char strNodeValue[255];

    sprintf(strNodeValue, "%d :: %d", nodeValue(tree), nodeDifference(tree));
    //Affichage du texte
    drawText(surface, x, y, radius / 2.5, strNodeValue);

    //px = ligne départ
    // x = ligne d'arrivé
    if (px != 0) {
        if (index % 2 == 0) {
            double x1, y1, x2, y2;
            x1 = px + (radius) * cos(60 * (M_PI / 180));
            y1 = py + (radius) * sin(60 * (M_PI / 180));
            x2 = x + (radius) * cos(250 * (M_PI / 180));
            y2 = y + (radius) * sin(250 * (M_PI / 180));

            drawLine(surface, (int) x1, (int) y1, (int) x2, (int) y2, colorLine);
        } else {
            double x1, y1, x2, y2;
            x1 = px + (radius) * cos(120 * (M_PI / 180));
            y1 = py + (radius) * sin(120 * (M_PI / 180));
            x2 = x + (radius) * cos(300 * (M_PI / 180));
            y2 = y + (radius) * sin(300 * (M_PI / 180));

            drawLine(surface, (int) x1, (int) y1, (int) x2, (int) y2, colorLine);
        }

    }

    drawTree(surface, tree->Left, treeDepth + 1, depth, (int) x, (int) y, index * 2 - 1, nodeDiff);
    drawTree(surface, tree->Right, treeDepth + 1, depth, (int) x, (int) y, index * 2, nodeDiff);
}

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixelColor) {
    Uint8 *target_pixel = (Uint8 *) surface->pixels + y * surface->pitch + x * 4;
    *(Uint32 *) target_pixel = pixelColor;
}

void drawLine(SDL_Surface *surface, Uint32 x1, Uint32 y1, Uint32 x2, Uint32 y2, Uint32 color) {
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

void drawCircle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixelColor) {
    double error = (double) -radius;
    double x = (double) radius - 0.5;
    double y = (double) 0.5;
    double cx = n_cx - 0.5;
    double cy = n_cy - 0.5;

    while (x >= y) {
        setPixel(surface, (int) (cx + x), (int) (cy + y), pixelColor);
        setPixel(surface, (int) (cx + y), (int) (cy + x), pixelColor);

        if (x != 0) {
            setPixel(surface, (int) (cx - x), (int) (cy + y), pixelColor);
            setPixel(surface, (int) (cx + y), (int) (cy - x), pixelColor);
        }

        if (y != 0) {
            setPixel(surface, (int) (cx + x), (int) (cy - y), pixelColor);
            setPixel(surface, (int) (cx - y), (int) (cy + x), pixelColor);
        }

        if (x != 0 && y != 0) {
            setPixel(surface, (int) (cx - x), (int) (cy - y), pixelColor);
            setPixel(surface, (int) (cx - y), (int) (cy - x), pixelColor);
        }

        error += y;
        ++y;
        error += y;

        if (error >= 0) {
            --x;
            error -= x;
            error -= x;
        }
    }
}

void drawText(SDL_Surface *surface, int x, int y, int size, char* str) {
    // Initialisation du texte
    TTF_Font *font = NULL;
    SDL_Surface *texte;
    SDL_Rect position;
    SDL_Color blackColor = {0, 0, 0};

    TTF_Init();
    font = TTF_OpenFont("font.ttf", size);
    texte = TTF_RenderText_Blended(font, str, blackColor);
    position.x = x;
    position.y = y;
    //Affichage du texte
    SDL_BlitSurface(texte, NULL, surface, &position);

    TTF_CloseFont(font);
    free(texte);
    TTF_Quit();
}

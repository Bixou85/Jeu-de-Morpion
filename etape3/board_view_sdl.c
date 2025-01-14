/**
 * @file board_view_text.c
 *
 * @date 7 oct. 2016
 * @author jilias
 */

#include "board_view.h"
#include <assert.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "tictactoe_errors.h"

#if defined CONFIG_SDLUI

static SDL_Window *MainWindow;
static SDL_Renderer *MainRenderer;
static SDL_Surface *BackgroundImage;
static SDL_Surface *SpriteO;
static SDL_Surface *SpriteX;

static void renderImage (SDL_Surface *image, int x, int y)
{
	SDL_Texture *aTexture;
	aTexture = SDL_CreateTextureFromSurface(MainRenderer, image);
	assert (aTexture != NULL);
	SDL_Rect pos = {x, y, image->w, image->h};
	SDL_RenderCopy(MainRenderer, aTexture, 0, &pos);
	SDL_RenderPresent(MainRenderer);
	SDL_DestroyTexture(aTexture);
}

void BoardView_init (void)
{
		int result;

		// Initialize SDL
		result = SDL_Init (SDL_INIT_VIDEO);
		if (result != 0)
		{
			fatalError (SDL_GetError ());
		}
		atexit (SDL_Quit);

		// Initialize SDL_image
		int initted=IMG_Init(IMG_INIT_PNG);
		if (initted != IMG_INIT_PNG)
		{
			fatalError(IMG_GetError ());
		}

		// Loads images
		BackgroundImage = IMG_Load ("../etape3/background.png");
		if (BackgroundImage == NULL)
					fatalError(IMG_GetError ());
		SpriteO = IMG_Load ("../etape3/sprite_O.png");
		if (SpriteO == NULL)
					fatalError(IMG_GetError ());
		SpriteX = IMG_Load ("../etape3/sprite_X.png");
		if (SpriteX == NULL)
			fatalError(IMG_GetError ());

		// Creates the window
		MainWindow = SDL_CreateWindow ("Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 480, 480, 0);
		if (MainWindow == NULL)
		{
			fatalError (SDL_GetError ());
		}

		// Creates the main renderer
		MainRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_ACCELERATED);
		if (MainRenderer == NULL)
		{
			fatalError(SDL_GetError());
		}
		BoardView_displayAll();
}

void BoardView_free (void)
{
	SDL_DestroyRenderer(MainRenderer);
	SDL_DestroyWindow(MainWindow);
	SDL_FreeSurface(SpriteX);
	SDL_FreeSurface(SpriteO);
	SDL_FreeSurface(BackgroundImage);
	IMG_Quit ();
	SDL_Quit ();
}

void BoardView_displayAll (void)
{
    // Utiliser "renderImage" pour afficher l'image de fond "BackgroundImage"
    renderImage(BackgroundImage, 0, 0); // Ajuster les coordonnées si nécessaire

    // Afficher l'ensemble des cases à l'aide de la fonction BoardView_displaySquare
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            BoardView_displaySquare(i, j, Board_getSquareContent(i, j));
        }
    }
}

void BoardView_displaySquare (Coordinate x, Coordinate y, PieceType kindOfPiece)
{
    SDL_Surface *currentSprite = NULL;
    switch (kindOfPiece) {
        case CROSS:
            currentSprite = SpriteX;
            break;
        case CIRCLE:
            currentSprite = SpriteO;
            break;
        default:
            return; // Si la case est vide, ne rien afficher
    }
    renderImage(currentSprite, x * 160, y * 160); // Ajuster les coordonnées si nécessaire
}

void BoardView_displayEndOfGame (GameResult result)
{
    const char *message = NULL;
    switch (result) {
        case CIRCLE_WINS:
            message = "Les cercles ont gagné !";
            break;
        case CROSS_WINS:
            message = "Les croix ont gagné !";
            break;
        case DRAW:
            message = "Match nul !";
            break;
        default:
            message = "Résultat inconnu";
            break;
    }
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Fin du jeu", message, MainWindow);
    SDL_Delay(2000); // Attente de 2 secondes avant de continuer
}

void BoardView_displayPlayersTurn (PieceType thisPlayer)
{
    const char *message = (thisPlayer == CROSS) ? "Tour des croix" : "Tour des cercles";
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Tour du joueur", message, MainWindow);
}

void BoardView_sayCannotPutPiece (void)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", "Placement interdit !", MainWindow);
}

#endif // defined CONFIG_SDLUI

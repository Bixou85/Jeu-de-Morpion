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
    assert (aTexture != NULL);  // Ensure the texture was created successfully
    SDL_Rect pos = {x, y, image->w, image->h};  // Define the position and size of the image
    SDL_RenderCopy(MainRenderer, aTexture, 0, &pos);  // Copy the image to the renderer
    SDL_RenderPresent(MainRenderer);  // Update the screen with the rendered image
    SDL_DestroyTexture(aTexture);  // Clean up the texture
}

void BoardView_init (void)
{
    int result;

    // Initialize SDL
    result = SDL_Init (SDL_INIT_VIDEO);
    if (result != 0) {
        fatalError (SDL_GetError ());
    }
    atexit (SDL_Quit);  // Ensure SDL quits when the program exits

    // Initialize SDL_image
    int initted = IMG_Init(IMG_INIT_PNG);
    if (initted != IMG_INIT_PNG) {
        fatalError(IMG_GetError ());
    }

    // Load images
    BackgroundImage = IMG_Load ("../etape3/background.png");
    if (BackgroundImage == NULL) {
        fatalError(IMG_GetError ());
    }
    SpriteO = IMG_Load ("../etape3/sprite_O.png");
    if (SpriteO == NULL) {
        fatalError(IMG_GetError ());
    }
    SpriteX = IMG_Load ("../etape3/sprite_X.png");
    if (SpriteX == NULL) {
        fatalError(IMG_GetError ());
    }

    // Create the window
    MainWindow = SDL_CreateWindow ("Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 480, 480, 0);
    if (MainWindow == NULL) {
        fatalError (SDL_GetError ());
    }

    // Create the main renderer
    MainRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_ACCELERATED);
    if (MainRenderer == NULL) {
        fatalError(SDL_GetError());
    }
    BoardView_displayAll();  // Display the initial board
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
    // Render the background image
    renderImage(BackgroundImage, 0, 0);

    // Display all board squares
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
            return;  // If the square is empty, do nothing
    }
    renderImage(currentSprite, x * 160, y * 160);
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
    // Show a message box with the end of game result
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Fin du jeu", message, MainWindow);
    SDL_Delay(2000);  // Wait for 2 seconds before continuing
}

void BoardView_displayPlayersTurn (PieceType thisPlayer)
{
    const char *message = (thisPlayer == CROSS) ? "Tour des croix" : "Tour des cercles";
    // Show a message box indicating whose turn it is
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Tour du joueur", message, MainWindow);
}

void BoardView_sayCannotPutPiece (void)
{
    // Show a message box indicating an invalid move
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", "Placement interdit !", MainWindow);
}

#endif // defined CONFIG_SDLUI

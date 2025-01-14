/**
 * @file player_manager_scanf.c
 *
 * @date 7 oct. 2016
 * @author jilias
 */

#include "board.h"
#include "board_view.h"
#include <assert.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#if defined CONFIG_PLAYER_MANAGER_SDL

static PieceType currentPlayer;

void PlayerManager_init (void)
{
    assert(SDL_WasInit(SDL_INIT_VIDEO) != 0);
    currentPlayer = CROSS;  // Initialiser le premier joueur à CROIX
}

void PlayerManager_free (void)
{
    // Actuellement, rien de spécial à libérer, mais vous pouvez ajouter des opérations de nettoyage si nécessaire à l'avenir.
}

static bool tryMove (int x, int y)
{
    if (Board_getSquareContent(x, y) == NONE) {
        Board_putPiece(x, y, currentPlayer);
        return true;
    } else {
        BoardView_sayCannotPutPiece();
        return false;
    }
}

void PlayerManager_oneTurn (void)
{
    int error;
    SDL_Event event;
    bool validMove;

    do
    {
        validMove = false;
        error = SDL_WaitEvent(&event);
        assert(error == 1);
        switch (event.type)
        {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                    SDL_Quit();
                    exit(0);
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int x = event.button.x / 160;  // Convertir les coordonnées de la souris en coordonnées de grille
                    int y = event.button.y / 160;
                    validMove = tryMove(x, y);
                    if (validMove) {
                        BoardView_displaySquare(x, y, currentPlayer);
                        // Changement de joueur
                        if (currentPlayer == CROSS) {
                            currentPlayer = CIRCLE;
                        } else {
                            currentPlayer = CROSS;
                        }
                    }
                }
                break;

            case SDL_QUIT:
                SDL_Quit();
                exit(0);
                break;
        }
    }
    while (!validMove);
}

#endif // defined CONFIG_PLAYER_MANAGER_SCANF

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

static PieceType currentPlayer;  // Variable to keep track of the current player

void PlayerManager_init (void)
{
    assert(SDL_WasInit(SDL_INIT_VIDEO) != 0);  // Ensure SDL is initialized for video
    currentPlayer = CROSS;  // Initialize the first player to CROSS
}

void PlayerManager_free (void)
{
    // No special resources to free in this implementation
}

static bool tryMove (int x, int y)
{
    if (Board_getSquareContent(x, y) == NONE) {
        return Board_putPiece(x, y, currentPlayer);  // Place the piece on the board
    } else {
        BoardView_sayCannotPutPiece();  // Inform the player that the move is invalid
        return false;
    }
}

void PlayerManager_oneTurn (void)
{
    int error;
    SDL_Event event;
    bool validMove;

    // That line is fonctionnal but it's not very fun
    // We intuitively know the next player to play
    // BoardView_displayPlayersTurn(currentPlayer);

    do {
        validMove = false;
        error = SDL_WaitEvent(&event);  // Wait for an event (mouse click, window close, etc.)
        assert(error == 1);  // Ensure the event was successfully retrieved
        switch (event.type) {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                    BoardView_free();  // Free board view resources and exit the application if SDL_QUIT event occurs
                    exit(0);
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int x = event.button.x / 160;  // Convert mouse x-coordinate to grid x-coordinate
                    int y = event.button.y / 160;  // Convert mouse y-coordinate to grid y-coordinate
                    validMove = tryMove(x, y);  // Try to make the move
                    if (validMove) {
                        // Switch the player after a successful move
                        if (currentPlayer == CROSS) {
                            currentPlayer = CIRCLE;
                        } else {
                            currentPlayer = CROSS;
                        }
                    }
                }
                break;

            case SDL_QUIT:
                BoardView_free();  // Free board view resources and exit the application if SDL_QUIT event occurs
                exit(0);
                break;
        }
    }
    while (!validMove);  // Continue until a valid move is made
}

#endif // defined CONFIG_PLAYER_MANAGER_SDL

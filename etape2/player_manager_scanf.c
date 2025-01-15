/**
 * @file player_manager_scanf.c
 *
 * @date 7 oct. 2016
 * @author jilias
 */

#include "board.h"
#include "board_view.h"
#include <assert.h>
#include <stdio.h>

#if defined CONFIG_PLAYER_MANAGER_SCANF

PieceType currentPlayer;  // Variable to keep track of the current player

void PlayerManager_init (void)
{
  currentPlayer = CROSS;  // Initialize the first player to CROSS
}

void PlayerManager_free (void)
{
  // No resources to free in this implementation
}

void PlayerManager_oneTurn (void)
{
  int x, y;
  // Display which player's turn it is and prompt for input
  BoardView_displayPlayersTurn(currentPlayer);
  // Read the coordinates of the move from the player's input
  scanf("%d %d", &x, &y);
  // Try to place the piece on the board
  if (Board_putPiece(x, y, currentPlayer) != PIECE_IN_PLACE) {
    // Inform the player if the move is not valid
    BoardView_sayCannotPutPiece();
  } else {
    // Switch the player after a successful move
    switch (currentPlayer) {
      case CROSS:
        currentPlayer = CIRCLE;
        break;
      case CIRCLE:
        currentPlayer = CROSS;
        break;
      default:
        printf("Erreur lors du changement de joueur.");
    }
  } 
}

#endif // defined CONFIG_PLAYER_MANAGER_SCANF

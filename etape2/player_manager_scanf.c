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

PieceType currentPlayer;

void PlayerManager_init (void)
{
	currentPlayer = CROSS;
}

void PlayerManager_free (void)
{
}

void PlayerManager_oneTurn (void)
{
  int x, y;
  BoardView_displayPlayersTurn(currentPlayer);
  scanf("%d %d", &x, &y);
  if (Board_putPiece(x, y, currentPlayer) != PIECE_IN_PLACE) {
		BoardView_sayCannotPutPiece();
  } else {
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

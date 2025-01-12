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
  while (1){
  BoardView_displayPlayersTurn(currentPlayer);
  /*char resultat = Board_putPiece(x, y, currentPlayer);
  switch (resultat) {
        case PIECE_IN_PLACE:
            printf("PIECE_IN_PLACE\n");
            break;
        case SQUARE_IS_NOT_EMPTY:
            printf("SQUARE_IS_NOT_EMPTY\n");
            break;
        default:
            printf("Valeur inconnue\n");
            break;
    }*/
  
  if (scanf("%d %d", &x, &y) != 2) {
    printf("Entrée invalide. Veuillez entrer deux entiers (0 0).\n");
    while (getchar() != '\n'); 
    continue;
        }

  if (Board_putPiece(x, y, currentPlayer) != PIECE_IN_PLACE) {
    BoardView_sayCannotPutPiece();
    while (getchar() != '\n'); 
    }
  else{
    break;
  }
  }

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

#endif // defined CONFIG_PLAYER_MANAGER_SCANF

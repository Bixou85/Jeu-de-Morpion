/**
 * @file player_manager_mock.c
 *
 * @date 7 oct. 2016
 * @author jilias
 */

#include "board.h"
#include <assert.h>
#include <stdio.h>

#if defined CONFIG_PLAYER_MANAGER_MOCK

PieceType currentPlayer;  // Variable to keep track of the current player
int i;  // Index to track the turn number

void PlayerManager_init (void)
{
	currentPlayer = CROSS; // Set current player to CROSS
    i = 0;  // Set the turn index to 0
}

void PlayerManager_free (void)
{
}

void PlayerManager_oneTurn (void)
{
#if defined DEF_CIRCLE_WINS
	//Circle Win test set
	int test_x[6] = {0, 1, 0, 1, 2, 1};
	int test_y[6] = {0, 0, 1, 1, 2, 2};
#endif
#if defined DEF_CROSS_WINS
	//CROSS Win test set
	int test_x[5] = {0, 1, 0, 1, 0};
	int test_y[5] = {0, 0, 1, 1, 2};
#endif
#if defined DEF_DRAW
	//Draw Test set
	int test_x[9] = {0,0,1,2,1,0,2,1,2};
	int test_y[9] = {1,0,0,1,1,2,0,2,2};
#endif

    // Print the move coordinates
    printf("Coup joué automatiquement x: %d, y: %d\n", test_x[i], test_y[i]);
    // Place the piece on the board
    Board_putPiece(test_x[i], test_y[i], currentPlayer);
    // Switch the player after the move
	switch (currentPlayer) {
		case CROSS:
			currentPlayer = CIRCLE;
			break;
		case CIRCLE:
			currentPlayer = CROSS;
			break;
		default:
			printf("Error during change of player.");
	}
	i++;
}

#endif //  #if defined CONFIG_PLAYER_MANAGER_MOCK

/**
 * @file main.c
 *
 * @date 7 oct. 2016
 * @author jilias
 */

#include "player_manager.h"
#include "board_view.h"
#include "board.h"

bool TemoinFinPartie;

void Game_SquareChangeCallback(Coordinate x, Coordinate y,
                               PieceType kindOfPiece)
{
  // Update the display with the new piece placed on the board
  BoardView_displaySquare(x, y, kindOfPiece);
}

void Game_EndOfGameCallback(GameResult result)
{
  TemoinFinPartie = true;  // Set the flag to indicate the game has ended
  // Display the end of the game message
  BoardView_displayEndOfGame(result);
}

void Game_init (void)
{
  TemoinFinPartie = false;  // Initialize the end-of-game flag to false
  // Initialize the board with the provided callback functions
  Board_init(&Game_SquareChangeCallback, &Game_EndOfGameCallback);
  // Initialize the board view
  BoardView_init();
  // Initialize the player manager
  PlayerManager_init();
}

void Game_free (void)
{
  // Free resources associated with the board
  Board_free();
  // Free resources associated with the board view
  BoardView_free();
  // Free resources associated with the player manager
  PlayerManager_free();
}

void Game_loop (void)
{
  do {
      PlayerManager_oneTurn();  // Execute one turn for the player
  } while (!TemoinFinPartie);  // Continue until the Ggame ends
}

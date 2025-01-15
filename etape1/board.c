#include "board.h"
#include <assert.h>

#define LIGNES 3
#define COLONNES 3

PieceType board[3][3];
SquareChangeCallback boardOnSquareChange;
EndOfGameCallback boardOnEndOfGame;
GameResult result;

/**
 * Check if the game has to be ended. Only alignment from the last
 * modified square are checked.
 *
 * @param [in] boardSquares the board to check
 * @param [in] lastChangeX the colum where the last piece has been put
 * @param [in] lastChangeY the row where the last piece has been put
 * @param [out] gameResult the winning status if the game has ended (value is not set if
 * the game is not finished)
 *
 * @pre lastChangeX must be in [0..2]
 * @pre lastChangeY must be in [0..2]
 * @pre gameResult must point on an allocated GameResult variable
 *
 * @return a boolean that tells if the game is finished
 */

static bool isGameFinished (const PieceType boardSquares[3][3], Coordinate lastChangeX, Coordinate lastChangeY, GameResult *gameResult)
{
  bool result_returned = false, empty_case = false;
  
  // Check if there are any empty squares left
  for (int i = 0; i < LIGNES; i++) {
    for (int j = 0; j < COLONNES; j++) {
      if (boardSquares[j][i] == NONE) {
        empty_case = true;  // Found an empty square
      }
    }
  }
  if (!empty_case) {
    result_returned = true;
    *gameResult = DRAW;  // No empty squares and no winner means the game is a draw
  }

  // Check for winning conditions (line, column, and diagonals)
  for (PieceType i = CROSS; i <= CIRCLE; i++) {
    if (boardSquares[lastChangeY][0] == i && boardSquares[lastChangeY][1] == i && boardSquares[lastChangeY][2] == i) {
      // Check the row of the last placed piece
      *gameResult = i;
      result_returned = true;
    } else if (boardSquares[0][lastChangeX] == i && boardSquares[1][lastChangeX] == i && boardSquares[2][lastChangeX] == i) {
      // Check the column of the last placed piece
      *gameResult = i;
      result_returned = true;
    } else if (boardSquares[0][0] == i && boardSquares[1][1] == i && boardSquares[2][2] == i) {
      // Check the first diagonal
      *gameResult = i;
      result_returned = true;
    } else if (boardSquares[2][0] == i && boardSquares[1][1] == i && boardSquares[0][2] == i) {
      // Check the second diagonal
      *gameResult = i;
      result_returned = true;
    }
  }
  return result_returned;  // Return whether the game is finished
}

void Board_init (SquareChangeCallback onSquareChange, EndOfGameCallback onEndOfGame)
{
  // Initialize the board with NONE (empty squares)
  for (int i = 0; i < LIGNES; i++) {
    for (int j = 0; j < COLONNES; j++) {
      board[i][j] = NONE;
    }
  }

  // The callback function to be called when a square changes
  boardOnSquareChange = onSquareChange;
  // The callback function to be called when the game ends
  boardOnEndOfGame = onEndOfGame;
}

void Board_free ()
{
  // Reset the board to empty state
	for (int i = 0; i < LIGNES; ++i) {
		for (int j = 0; j < COLONNES; ++j) {
      board[i][j] = NONE;
    }
	}
}

PutPieceResult Board_putPiece (Coordinate x, Coordinate y, PieceType kindOfPiece)
{
  // Validate coordinates and piece type
  if (x < 0 || x > 2 || y < 0 || y > 2 || kindOfPiece == NONE) {
    return SQUARE_IS_NOT_EMPTY;
  }
  
  // Check if the square is empty
  if (Board_getSquareContent(x, y) == NONE) {
    board[y][x] = kindOfPiece;
    boardOnSquareChange(x, y, kindOfPiece);
    
    // Check if the game is finished after placing the piece
    if (isGameFinished(board, x, y, &result)) {
      boardOnEndOfGame(result);
    }
    return PIECE_IN_PLACE;
  } else {
    return SQUARE_IS_NOT_EMPTY;
  }
}

PieceType Board_getSquareContent (Coordinate x, Coordinate y)
{
  // Validate coordinates
  if (x > 2 || x < 0 || y > 2 || y < 0) return NONE;
  return board[y][x];
}

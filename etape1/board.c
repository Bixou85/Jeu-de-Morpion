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
  for (int i = 0; i < LIGNES; i++) {
    for (int j = 0; j < COLONNES; j++) {
      if (boardSquares[i][j] == NONE) {
        empty_case = true;
      }
    }
  }
  if (!empty_case) {
    result_returned = true;
    *gameResult = DRAW;
  }

  for (PieceType i = CROSS; i <= CIRCLE; i++) {
    if (boardSquares[lastChangeY][0] == i && boardSquares[lastChangeY][1] == i && boardSquares[lastChangeY][2] == i) { //vérification de la ligne
      *gameResult = i;
      result_returned = true;
    } else if (boardSquares[0][lastChangeX] == i && boardSquares[1][lastChangeX] == i && boardSquares[2][lastChangeX] == i) { //vérification de la colonne
      *gameResult = i;
      result_returned = true;
    } else if (boardSquares[0][0] == i && boardSquares[1][1] == i && boardSquares[2][2] == i) { //vérification de la première diagonale
      *gameResult = i;
      result_returned = true;
    } else if (boardSquares[2][0] == i && boardSquares[1][1] == i && boardSquares[0][2] == i) { //vérification de la seconde diagonale
      *gameResult = i;
      result_returned = true;
    }
  }
  return result_returned;
}

void Board_init (SquareChangeCallback onSquareChange, EndOfGameCallback onEndOfGame)
{
  for (int i = 0; i < LIGNES; i++) {
    for (int j = 0; j < COLONNES; j++) {
      board[i][j] = NONE;
    }
  }

  boardOnSquareChange = onSquareChange;
  boardOnEndOfGame = onEndOfGame;
}

void Board_free ()
{
	for (int i = 0; i < LIGNES; ++i) {
		for (int j = 0; j < COLONNES; ++j) {
      board[i][j] = NONE;
    }
	}
}

PutPieceResult Board_putPiece (Coordinate x, Coordinate y, PieceType kindOfPiece)
{
  if (x < 0 || x > 2 || y < 0 || y > 2 || kindOfPiece == NONE){
    return SQUARE_IS_NOT_EMPTY;
  }
  if (board[y][x]==NONE){
    board[y][x]=kindOfPiece;
    boardOnSquareChange(x, y, kindOfPiece);
    if (isGameFinished(board, x, y, &result)) {
      boardOnEndOfGame(result);
    }
    return PIECE_IN_PLACE;
  }
  else {
    return SQUARE_IS_NOT_EMPTY;
  }
}

PieceType Board_getSquareContent (Coordinate x, Coordinate y)
{
  if (x > 2 || x < 0 || y > 2 || y < 0) return NONE;
  return board[y][x];
}

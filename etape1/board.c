#include "board.h"
#include <assert.h>


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
  bool result = false, empty_case = false;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (boardSquares[i][j] == NONE) {
        empty_case = true;
      }
    }
  }
  if (!empty_case) {
    result = true;
    *gameResult = DRAW;
  }
  for (int i = 1; i < 3; i++) {
    if (boardSquares[0][0] == i && boardSquares[0][1] == i && boardSquares[0][2] == i) {
      *gameResult = i;
      result = true;
    } else if (boardSquares[1][0] == i && boardSquares[1][1] == i && boardSquares[1][2] == i) {
      *gameResult = i;
      result = true;
    } else if (boardSquares[2][0] == i && boardSquares[2][1] == i && boardSquares[2][2] == i) {
      *gameResult = i;
      result = true;
    } else if (boardSquares[1][0] == i && boardSquares[1][0] == i && boardSquares[2][0] == i) {
      *gameResult = i;
      result = true;
    } else if (boardSquares[0][1] == i && boardSquares[1][1] == i && boardSquares[2][1] == i) {
      *gameResult = i;
      result = true;
    } else if (boardSquares[0][2] == i && boardSquares[1][2] == i && boardSquares[2][2] == i) {
      *gameResult = i;
      result = true;
    } else if (boardSquares[0][0] == i && boardSquares[1][1] == i && boardSquares[2][2] == i) {
      *gameResult = i;
      result = true;
    } else if (boardSquares[2][0] == i && boardSquares[1][1] == i && boardSquares[0][2] == i) {
      *gameResult = i;
      result = true;
    }
  }
  return result;
}

// void Board_init (SquareChangeCallback onSquareChange, EndOfGameCallback onEndOfGame)
// {
//   // TODO: à compléter
// }

// void Board_free ()
// {
//   // TODO: à compléter
// }

// PutPieceResult Board_putPiece (Coordinate x, Coordinate y, PieceType kindOfPiece)
// {
//   // TODO: à compléter
// }

// PieceType Board_getSquareContent (Coordinate x, Coordinate y)
// {
//   // TODO: à compléter
// }

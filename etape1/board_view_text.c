#include "board_view.h"
#include <assert.h>
#include <stdio.h>

#if defined CONFIG_TEXTUI

extern PieceType board[3][3];

char boardText[5][5] = {
  {' ', '|', ' ', '|', ' '},
  {'_', '|', '_', '|', '_'},
  {' ', '|', ' ', '|', ' '},
  {'_', '|', '_', '|', '_'},
  {' ', '|', ' ', '|', ' '},
};

void BoardView_init (void)
{
}

void BoardView_free (void)
{
}

void BoardView_displayAll (void)
{
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
      printf("%c", boardText[i][j]);
    }
    printf("\n");
	}
  printf("\n\n");
}

void BoardView_displaySquare (Coordinate x, Coordinate y, PieceType kindOfPiece)
{
  char placedPiece;
  switch (kindOfPiece) {
    case CROSS:
      placedPiece = "X";
      break;

    case CIRCLE:
      placedPiece = "O";
      break;
  }
  boardText[x][y] = placedPiece;
	BoardView_displayAll();
}

void BoardView_displayEndOfGame (GameResult result)
{
  BoardView_displayAll();
  switch (result) {
  case CIRCLE_WINS:
    puts("Les cercles ont gagné");
    break;

  case CROSS_WINS:
    puts("Les croix ont gagné");
    break;

  case DRAW:
    puts("Aucun gagnant");
    break;

  default:
    puts("Gagnant invalide")
    break;
  }
}

void BoardView_displayPlayersTurn (PieceType thisPlayer)
{
  switch (thisPlayer) {
    case CIRCLE:
      puts("C'est au tour des cercles de jouer");
      break;

    case CROSS:
      puts("C'est au tour des croix de jouer");
      break;

    default:
      puts("Tour de joueur invalide");
      break;
  }
}

void BoardView_sayCannotPutPiece (void)
{
  puts("Placement interdit");
}

#endif // defined CONFIG_TEXTUI

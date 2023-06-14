/* file   : draughts.c */
/* author : Max J. Poletiek (m.j.poletiek@student.rug.nl) */
		
/* Description:
 * A game that analyzes the amount of pieces that can be taken in a move
 */

#define boardSize 8
		
#include <stdio.h>
#include <stdlib.h>

//structure where both x and y coordinates are saved into, will later be used for an array where we store all already taken pieces
typedef struct Moves {
	int x;
	int y;
} Moves;

//initialization
int isNotPastMove(int x, int y, Moves pastMoves[], int piecesTaken);

//initializtion of board, all empty squares are 0
void initializeBoard(int board[boardSize][boardSize]) {
	for (int r = 0; r < boardSize; r++) {
		for (int s = 0; s < boardSize; s++) {
			board[r][s]=0;
		}
	}

}

//Bread and butter of the program, was about to give up on this steaming hot pile but if it works it works
int capturePieces(int x, int y, int board[boardSize][boardSize], Moves pastMoves[], int piecesTaken, int mostPiecesTaken) {

	//Debug statement, will print current x y coordinates being evaluated,
	//the depth(piecestaken) and the deepest depth it has reached (mostPiecesTaken)

	//printf("x=%i y=%i piecestaken = %i mostPiecesTaken= %i\n",x,y,piecesTaken,mostPiecesTaken);

	//If current depth(piecesTaken is greater than deepest dept so far, change deepest depth)
	if (piecesTaken > mostPiecesTaken) {
		mostPiecesTaken = piecesTaken;
	}

	//sets nextmove to be North-West/left-top
	int nextY = y - 2;
	int nextX = x - 2;

	/*checks if valid move by(in order): -
	*	-is new x and y not outside of playing field?
	*	-is cell we're moving to empty?
	*	-Is there a enemy pawn to jump over?
	*	-Is it not a already taken pawn?(using is Not Past move)
	*(All if statements marked with IDEM under this one are alike, just changing next X and Y)
	*/
	if (nextX >= 0 && nextY >= 0 && board[nextY][nextX] == 0 && board[y-1][x-1] == 1 && isNotPastMove(x-1, y-1, pastMoves, piecesTaken)) {
		pastMoves[piecesTaken].x = x-1;
		pastMoves[piecesTaken].y = y-1;
		mostPiecesTaken = capturePieces(nextX, nextY, board, pastMoves, piecesTaken+1, mostPiecesTaken);
	}

	//sets nextmove to be at South-East/right-bottom
	nextY = y + 2;
	nextX = x + 2;

	//IDEM
	if (nextX < 8 && nextY < 8 && board[nextY][nextX] == 0 && board[y+1][x+1] == 1 && isNotPastMove(x+1, y+1, pastMoves, piecesTaken)) {
		pastMoves[piecesTaken].x = x+1;
		pastMoves[piecesTaken].y = y+1;
		mostPiecesTaken = capturePieces(nextX, nextY, board, pastMoves, piecesTaken+1, mostPiecesTaken);
	}

	//sets nextmove to be at South-West/left-bottom
	nextY = y + 2;
	nextX = x - 2;

	//IDEM
	if (nextX >= 0 && nextY < 8 && board[nextY][nextX] == 0 && board[y+1][x-1] == 1 && isNotPastMove(x-1, y+1, pastMoves, piecesTaken)) {
		pastMoves[piecesTaken].x = x-1;
		pastMoves[piecesTaken].y = y+1;
		mostPiecesTaken = capturePieces(nextX, nextY, board, pastMoves, piecesTaken+1, mostPiecesTaken);
	}

	//sets nextmove to be at North-East/right-Top
	nextY = y - 2;
	nextX = x + 2;

	//IDEM
	if (nextX < 8 && nextY >= 0 && board[nextY][nextX] == 0 && board[y-1][x+1] == 1 && isNotPastMove(x+1, y-1, pastMoves, piecesTaken)) {
		pastMoves[piecesTaken].x = x+1;
		pastMoves[piecesTaken].y = y-1;
		mostPiecesTaken = capturePieces(nextX, nextY, board, pastMoves, piecesTaken+1, mostPiecesTaken);
	}

	//returns the highest amount of pieces taken
	return mostPiecesTaken;
}

int isNotPastMove(int x, int y, Moves pastMoves[], int piecesTaken) {
	//loops through all moves taken so far and compares them to current move
	for (int r = 0; r < piecesTaken; r++) {
		//if given coordinates have already been visited once return false
		if (x == pastMoves[r].x && y == pastMoves[r].y) {
			return 0;
		}
	}
	//else return true
	return 1;
}
		
int main(int argc, char *argv[]) {
	int board [boardSize][boardSize];
	
	int startX, startY, pieces;
	scanf("%i %i %i\n", &startX, &startY, &pieces);

	initializeBoard(board);

	int x, y;
	for (int r = 0; r < pieces; r++) {
		scanf("%i %i",&x, &y);
		board[y][x] = 1;
	}

	Moves pastMoves[pieces];

	printf("%i\n",capturePieces(startX, startY, board, pastMoves, 0, 0));


	//Debug statement, prints out board.
	/*
	for (int r = 0; r < boardSize; r++) {
		for (int s = 0; s < boardSize-1; s++) {
			printf("%i ",board[r][s]);
		}
		printf("%i\n",board[r][boardSize-1]);
	}*/

	return 0;
}
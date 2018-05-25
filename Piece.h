
#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "Rotation.h"
#include "Const.h"

using namespace std;

class Piece {
	public:
	vector<Rotation> rotations;
	int x;
	int y;
	int rotationCount;
	int color;
	
	Piece(vector<Rotation>);
	
	Piece(int, int);
	
	bool isInBounds(int, int);
	
	int getRotate(int);
	
	int rotate(int);
	
	bool isValidPlacement(int, int, int);
	
	void kill();
	
	void setRealCoordinates(int, int);
	
	bool boardIsInBounds(int, int);
	
};

extern Piece pieces[7];
extern Piece currentPiece;
extern Piece nextPiece;

Piece genNextPiece();

#endif
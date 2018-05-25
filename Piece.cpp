#include "Piece.h"
#include "Const.h"
#include <time.h>
#include <iostream>

using namespace std;

void Piece::setRealCoordinates(int rx, int ry){
	x = rx - rotations.at(rotationCount).offX;
	y = ry - rotations.at(rotationCount).offY;
}

bool Piece::isValidPlacement(int ofX, int ofY, int ofR){
	int size = rotations.at(0).shape.size();
	int cX = x + ofX;
	int cY = y + ofY;
	int cR = getRotate(ofR);
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if ((boardIsInBounds(cX + i, cY + j) && rotations.at(cR).shape.at(j).at(i) == 1 && board[cX + i][cY + j] != 0) 
			|| ((!boardIsInBounds(cX + i, cY + j)) && (rotations.at(cR).shape.at(j).at(i) == 1))){
				return false;
			}
		}
	}
	return true;
}

int gRand(int max, int min){
	static bool init;
	if (!init){
		srand((int)time(NULL));
		init = true;
	}
	return (rand()%(max - min)+min);
}

Piece pieces[7] = {Piece(2, 1), Piece(4, 2), Piece(3, 4), Piece(3, 4), Piece(3, 4), Piece(3, 2), Piece(3, 2)};
Piece currentPiece(4,4);
Piece nextPiece(4,4);

Piece genNewPiece(int pIndex){
	if (pIndex == -1){
		pIndex = gRand(6, 0);
	}
	int coord = 4;
	int rot = gRand(INT_MAX, 0);
	Piece newPiece = pieces[pIndex];
	newPiece.setRealCoordinates(coord, 0);
	newPiece.rotate(rot);
	return newPiece;
}

Piece genNextPiece(){
	static vector<Piece> pieces;
	if (pieces.size() == 0){
		for (int i = 0; i < 7; i++){
			pieces.push_back(genNewPiece(i));
		}
	}
	int randVal = gRand(pieces.size(), 0);
	int pIndex = randVal;
	Piece retVal = pieces.at(pIndex);
	pieces.erase(pieces.begin() + pIndex);
	return retVal;
}

void Piece::kill(){
	int size = rotations.at(0).shape.size();
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if (rotations.at(rotationCount).shape.at(j).at(i) == 1){
				board[x + i][y + j] = color;
			}
		}
	}
	currentPiece = nextPiece;
	nextPiece = genNextPiece();
}

bool Piece::boardIsInBounds(int tx, int ty){
	return (tx >= 0 && tx < WIDTH && ty >= 0 && ty < HEIGHT);
}

int Piece::rotate(int amount){
	rotationCount = (rotationCount + amount) % rotations.size();
	return rotationCount;
}

int Piece::getRotate(int amount){
	return (rotationCount + amount) % rotations.size();
}

bool Piece::isInBounds(int cx, int cy){
	signed int newX = cx - x;
	signed int newY = cy - y;
	if (newX > -1 && newX < (signed int)rotations.at(0).shape.at(0).size() && newY > -1 && newY < (signed int)rotations.at(0).shape.at(0).size()){
		return true;
	}
	return false;
}

Piece::Piece(int size, int rotationCount){
	rotations = vector<Rotation> (rotationCount, Rotation(size, 0, 0));
	x = 0;
	y = 0;
	color = gRand(15, 1);
}

Piece::Piece(vector<Rotation> r){
	rotations = r;
	x = 0;
	y = 0;
	color = gRand(15, 1);
}
















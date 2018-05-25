#include "Rotation.h"
#include <vector>

Rotation::Rotation(int size, int x, int y){
	shape = vector< vector<int>> (size, vector<int>(size, 0));
	offX = x;
	offY = y;
}
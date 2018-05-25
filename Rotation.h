
#include <vector>

#ifndef ROTATION_H
#define ROTATION_H

using namespace std;

class Rotation {
	public:
	vector< vector<int> > shape;
	int offX;
	int offY;
	
	Rotation(int, int, int);
};

#endif
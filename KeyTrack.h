
#ifndef KEYTRACK_H
#define KEYTRACK_H

#include <windows.h>

class KeyTrack {
	public:
	static bool lAr;
	static bool rAr;
	static bool uAr;
	static bool dAr;
	static bool spa;
	
	KeyTrack();
	
	static void setKeyInput();
	
	static bool keyValid(bool *, short);
};

#endif
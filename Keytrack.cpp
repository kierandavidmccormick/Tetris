
#include "KeyTrack.h"

void KeyTrack::setKeyInput(){
	KeyTrack::lAr = GetKeyState(VK_LEFT) & 0x8000;
	KeyTrack::rAr = GetKeyState(VK_RIGHT) & 0x8000;
	KeyTrack::uAr = GetKeyState(VK_UP) & 0x8000;
	KeyTrack::dAr = GetKeyState(VK_DOWN) & 0x8000;
	KeyTrack::spa = GetKeyState(VK_SPACE) & 0x8000;
}

KeyTrack::KeyTrack(){
	lAr = false;
	rAr = false;
	uAr = false;
	dAr = false;
	spa = false;
}

bool KeyTrack::keyValid(bool *key, short keyCode){
	return !*key && (GetKeyState(keyCode) & 0x8000);
}
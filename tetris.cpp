/** =========================================================
 Kieran McCormick
 Windows 7
 CIS 161 VanGundy Spring 2018
 Homework Assignment 
 Program Description: The game Tetris
 Academic Honesty Statement:
 I attest that this is my original work.
 I have not used unauthorized source code, either modified or unmodified.
 I have not given other fellow student(s) access to my program.
=========================================================== **/

#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <Windows.h>
#include <time.h>
#include <mmsystem.h>

//manually includes library 
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "winmm.lib")

using namespace std;

#include "Const.h"
#include "KeyTrack.h"
#include "Rotation.h"
#include "Piece.h"

const int HEIGHT = 24;
const int WIDTH = 10;
const int GAME_SPEED = 1;
double DROP_SPEED = 150;
const int SCALE = 4;
const int DISPLAY_WIDTH = WIDTH * SCALE + 2;
const int NEXT_PIECE_X_OFFSET = DISPLAY_WIDTH + SCALE;
const int NEXT_PIECE_Y_OFFSET = SCALE;
const int SCORE_X_OFFSET = DISPLAY_WIDTH + SCALE;
const int SCORE_Y_OFFSET = SCALE * 6;
const char BLOCK = (char)219;
const char PIECE = (char)176;
const char SPACE = (char)32;

MCI_OPEN_PARMS mPar = {0};
bool enhanced_features;

int board [WIDTH][HEIGHT];
int score;
int lines_cleared;

KeyTrack keyTrack();

bool KeyTrack::lAr;
bool KeyTrack::rAr;
bool KeyTrack::uAr;
bool KeyTrack::dAr;
bool KeyTrack::spa;

void setCursorPosition(int x, int y);
void setCursorColor(int c);
void toggleState();
void printBoard();
void printData();
void printScore();
void printLine(int line);
void clearLine(int line, int value);
void clearLines(int start, int stop, int value);
bool isFull(int b[WIDTH][HEIGHT], int line, int val);
bool hasNone(int b[WIDTH][HEIGHT], int line, int val);
vector<int> clearFullLines();
void cpyRow(int (*boardTo)[WIDTH][HEIGHT], int boardFrom[WIDTH][HEIGHT], int lineTo, int lineFrom);
void cpyBoard (int (*boardTo)[WIDTH][HEIGHT], int boardFrom[WIDTH][HEIGHT]);
void shiftAllDown();
bool hasLost();
bool userInputResponse();
void exit_handler();
BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType);

int main(int argc, char **argv){
	
	atexit(exit_handler);
	at_quick_exit(exit_handler);
	SetConsoleCtrlHandler(ConsoleHandlerRoutine, true);
	
	setCursorColor(7);
	
	Rotation blockR(2, 0, 0);
	blockR.shape.at(0).at(0) = 1;
	blockR.shape.at(1).at(0) = 1;
	blockR.shape.at(0).at(1) = 1;
	blockR.shape.at(1).at(1) = 1;
	pieces[0].rotations.at(0) = blockR;
	pieces[0].color = 14;
	
	Piece line = pieces[1];
	Rotation lineH(4, 0, 0);
	Rotation lineV(4, 2, 0);
	lineH.shape.at(2).at(0) = 1;
	lineH.shape.at(2).at(1) = 1;
	lineH.shape.at(2).at(2) = 1;
	lineH.shape.at(2).at(3) = 1;
	lineV.shape.at(0).at(2) = 1;
	lineV.shape.at(1).at(2) = 1;
	lineV.shape.at(2).at(2) = 1;
	lineV.shape.at(3).at(2) = 1;
	line.rotations.at(0) = lineH;
	line.rotations.at(1) = lineV;
	pieces[1] = line;
	pieces[1].color = 11;
	
	Piece tblock = pieces[2];
	Rotation tup(3, 0, 0);
	Rotation tdown(3, 0, 1);
	Rotation tleft(3, 0, 0);
	Rotation tright(3, 0, 0);
	tup.shape.at(1).at(0) = 1;
	tup.shape.at(0).at(1) = 1;
	tup.shape.at(1).at(1) = 1;
	tup.shape.at(1).at(2) = 1;
	tdown.shape.at(1).at(0) = 1;
	tdown.shape.at(2).at(1) = 1;
	tdown.shape.at(1).at(1) = 1;
	tdown.shape.at(1).at(2) = 1;
	tleft.shape.at(1).at(0) = 1;
	tleft.shape.at(0).at(1) = 1;
	tleft.shape.at(1).at(1) = 1;
	tleft.shape.at(2).at(1) = 1;
	tright.shape.at(1).at(2) = 1;
	tright.shape.at(0).at(1) = 1;
	tright.shape.at(1).at(1) = 1;
	tright.shape.at(2).at(1) = 1;
	tblock.rotations.at(0) = tup;
	tblock.rotations.at(1) = tright;
	tblock.rotations.at(2) = tdown;
	tblock.rotations.at(3) = tleft;
	pieces[2] = tblock;
	pieces[2].color = 13;
	
	Piece lbent = pieces[3];
	Rotation lbentup(3, 0, 0);
	Rotation lbentleft(3, 1, 0);
	Rotation lbentdown(3, 0, 1);
	Rotation lbentright(3, 0, 0);
	lbentup.shape.at(1).at(0) = 1;
	lbentup.shape.at(1).at(1) = 1;
	lbentup.shape.at(1).at(2) = 1;
	lbentup.shape.at(0).at(2) = 1;
	lbentright.shape.at(0).at(0) = 1;
	lbentright.shape.at(0).at(1) = 1;
	lbentright.shape.at(1).at(1) = 1;
	lbentright.shape.at(2).at(1) = 1;
	lbentleft.shape.at(0).at(1) = 1;
	lbentleft.shape.at(1).at(1) = 1;
	lbentleft.shape.at(2).at(1) = 1;
	lbentleft.shape.at(2).at(2) = 1;
	lbentdown.shape.at(1).at(0) = 1;
	lbentdown.shape.at(1).at(1) = 1;
	lbentdown.shape.at(1).at(2) = 1;
	lbentdown.shape.at(2).at(0) = 1;
	lbent.rotations.at(0) = lbentup;
	lbent.rotations.at(3) = lbentright;
	lbent.rotations.at(2) = lbentdown;
	lbent.rotations.at(1) = lbentleft;
	pieces[3] = lbent;
	pieces[3].color = 12;
	
	Piece rbent = pieces[4];
	Rotation rbentup(3, 0, 0);
	Rotation rbentleft(3, 1, 0);
	Rotation rbentdown(3, 0, 1);
	Rotation rbentright(3, 0, 0);
	rbentup.shape.at(0).at(0) = 1;
	rbentup.shape.at(1).at(0) = 1;
	rbentup.shape.at(1).at(1) = 1;
	rbentup.shape.at(1).at(2) = 1;
	rbentleft.shape.at(0).at(1) = 1;
	rbentleft.shape.at(2).at(0) = 1;
	rbentleft.shape.at(1).at(1) = 1;
	rbentleft.shape.at(2).at(1) = 1;
	rbentdown.shape.at(2).at(2) = 1;
	rbentdown.shape.at(1).at(0) = 1;
	rbentdown.shape.at(1).at(1) = 1;
	rbentdown.shape.at(1).at(2) = 1;
	rbentright.shape.at(0).at(1) = 1;
	rbentright.shape.at(0).at(2) = 1;
	rbentright.shape.at(1).at(1) = 1;
	rbentright.shape.at(2).at(1) = 1;
	rbent.rotations.at(0) = rbentup;
	rbent.rotations.at(1) = rbentright;
	rbent.rotations.at(2) = rbentdown;
	rbent.rotations.at(3) = rbentleft;
	pieces[4] = rbent;
	pieces[4].color = 9;
	
	Piece ls = pieces[5];
	Rotation lsvert(3, 0, 0);
	Rotation lshoriz(3, 0, 0);
	lsvert.shape.at(0).at(1) = 1;
	lsvert.shape.at(1).at(0) = 1;
	lsvert.shape.at(1).at(1) = 1;
	lsvert.shape.at(2).at(0) = 1;
	lshoriz.shape.at(0).at(0) = 1;
	lshoriz.shape.at(0).at(1) = 1;
	lshoriz.shape.at(1).at(1) = 1;
	lshoriz.shape.at(1).at(2) = 1;
	ls.rotations.at(0) = lsvert;
	ls.rotations.at(1) = lshoriz;
	pieces[5] = ls;
	pieces[5].color = 10;
	
	Piece rs = pieces[6];
	Rotation rsvert(3, 0, 0);
	Rotation rshoriz(3, 0, 0);
	rsvert.shape.at(0).at(0) = 1;
	rsvert.shape.at(1).at(0) = 1;
	rsvert.shape.at(1).at(1) = 1;
	rsvert.shape.at(2).at(1) = 1;
	rshoriz.shape.at(1).at(0) = 1;
	rshoriz.shape.at(0).at(1) = 1;
	rshoriz.shape.at(1).at(1) = 1;
	rshoriz.shape.at(0).at(2) = 1;
	rs.rotations.at(0) = rsvert;
	rs.rotations.at(1) = rshoriz;
	pieces[6] = rs;
	pieces[6].color = 12;
	
	currentPiece = genNextPiece();
	nextPiece = genNextPiece();
	score = 0;
	
	system("cls");
	
	cout << "Welcome to TETRIS!" << endl << endl;
	Sleep(100);
	cout << "NOTE: It is strongly recommended to set the terminal to a square font" << endl << endl;
	Sleep(2000);
	char in;
	do {
		cout << "Would you like to enable ENHANCED FEATURES? (y/n): ";
		cin >> in;
	} while (in != 'y' && in != 'n' && in != 'Y' && in != 'N');
	enhanced_features = in == 'y' || in == 'Y';
	
	if (enhanced_features){
		mPar.lpstrDeviceType = (reinterpret_cast<LPCSTR>(MCI_DEVTYPE_CD_AUDIO));
		mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID, (DWORD)&mPar);
	}
	
	system("cls");
	
	bool print = false;
	int killCount = 0;
	int dropCount = 0;
	while(true){
		if (userInputResponse()){
			print = true;
		}
		if (dropCount * GAME_SPEED >= DROP_SPEED) {
			if (!currentPiece.isValidPlacement(0, 1, 0)){
				if ((killCount * GAME_SPEED) * .5 >= DROP_SPEED){
					currentPiece.kill();
					killCount = 0;
					dropCount = 0;
					print = true;
				} else {
					killCount++;
				}
			} else {
				currentPiece.y++;
				dropCount = 0;
				print = true;
			}
		}
		if (print){
			clearFullLines();
			shiftAllDown();
			printBoard();
			printData();
			printScore();
			print = false;
		}
		if (hasLost()){
			setCursorPosition(0,HEIGHT * SCALE);
			cout << "You Lose!" << flush;
			exit(0);
		}
		dropCount++;
		Sleep(GAME_SPEED);
	}
	cout.flush();
	return 0;
}

void setCursorPosition(int x, int y){
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = {(short)x, (short)y};
	SetConsoleCursorPosition(hOut, coord);
}

void setCursorColor(int c){
	static const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	static int prev;
	if (prev != c){
		SetConsoleTextAttribute(hout, c);
		prev = c;
	}
}

void toggleState(){
	static bool isToggled = false;
	if (isToggled){
		mciSendCommand(mPar.wDeviceID, MCI_SET, MCI_SET_DOOR_CLOSED, 0);
		isToggled = false;
	} else {
		mciSendCommand(mPar.wDeviceID, MCI_SET, MCI_SET_DOOR_OPEN, 0);
		isToggled = true;
	}
}

void printBoard(){
	static char oldBoard [HEIGHT * SCALE][WIDTH * SCALE + 2];
	static char newBoard [HEIGHT * SCALE][WIDTH * SCALE + 2];
	static int oldColors [HEIGHT * SCALE][WIDTH * SCALE + 2];
	static int newColors [HEIGHT * SCALE][WIDTH * SCALE + 2];
	for (int i = 0; i < HEIGHT; i++){
		string line;
		vector<int> colors;
		line.push_back('|');
		colors.push_back(7);
		for (int j = 0; j < WIDTH; j++){
			char addToLine = SPACE;
			int addToColor = 0;
			if (currentPiece.rotations.at(currentPiece.rotationCount).shape.size() > 0 && currentPiece.isInBounds(j, i) && currentPiece.rotations.at(currentPiece.rotationCount).shape.at(i - currentPiece.y).at(j - currentPiece.x) == 1){
				addToLine = PIECE;
				addToColor = currentPiece.color;
			} else if (board[j][i] != 0){
				addToLine = BLOCK;
				addToColor = board[j][i];
			}
				for (int k = 0; k < SCALE; k++){
					line.push_back(addToLine);
					colors.push_back(addToColor);
				}
			}
			line.push_back('|');
			colors.push_back(7);
			for (int j = 0; j < SCALE; j++){
				const char *cLine = line.c_str();
				for (int k = 0; k < WIDTH * SCALE + 2; k++){
					newBoard[(i * SCALE) + j][k] = cLine[k];
					newColors[(i * SCALE) + j][k] = colors.at(k);
				}
			}
		}
	for (int i = 0; i < HEIGHT * SCALE; i++){
		for (int j = 0; j < WIDTH * SCALE + 2; j++){
			if (newBoard[i][j] != oldBoard[i][j] || newColors[i][j] != oldColors[i][j]){
				setCursorPosition(j, i);
				setCursorColor(newColors[i][j]);
				cout << newBoard[i][j];
				oldBoard[i][j] = newBoard[i][j];
				oldColors[i][j] = newColors[i][j];
			}
		}
	}
	cout << flush;
	setCursorColor(7);
}

void printData(){
	static char oldData[4 * SCALE][4 * SCALE];
	static char newData[4 * SCALE][4 * SCALE];
	static int oldColors[4 * SCALE][4 * SCALE];
	static int newColors[4 * SCALE][4 * SCALE];
	for (unsigned int i = 0; i < 4; i++){
		string line;
		vector<int> colors;
		for (unsigned int j = 0; j < 4; j++){
			char addToLine = SPACE;
			int addToColor = 0;
			if (nextPiece.rotations.at(0).shape.size() > i && nextPiece.rotations.at(0).shape.size() > j && nextPiece.rotations.at(nextPiece.rotationCount).shape.at(i).at(j) == 1){
				addToLine = BLOCK;
				addToColor = nextPiece.color;
			}
			for (int k = 0; k < SCALE; k++){
				line.push_back(addToLine);
				colors.push_back(addToColor);
			}
		}
		for (int j = 0; j < SCALE; j++){
			const char *cLine = line.c_str();
			for (int k = 0; k < 4 * SCALE; k++){
				newData[(i * SCALE) + j][k] = cLine[k];
				newColors[(i * SCALE) + j][k] = colors.at(k);
			}
		}
	}
	for (int i = 0; i < 4 * SCALE; i++){
		for (int j = 0; j < 4 * SCALE; j++){
			if (newData[i][j] != oldData[i][j] || newColors[i][j] != oldColors[i][j]){
				setCursorPosition(j + NEXT_PIECE_X_OFFSET, i + NEXT_PIECE_Y_OFFSET);
				setCursorColor(newColors[i][j]);
				cout << newData[i][j];
				oldData[i][j] = newData[i][j];
				oldColors[i][j] = newColors[i][j];
			}
		}
	}
	cout << flush;
	setCursorColor(7);
}

void printScore(){
	setCursorPosition(SCORE_X_OFFSET, SCORE_Y_OFFSET);
	cout << "Lines cleared: " << to_string(lines_cleared);
	setCursorPosition(SCORE_X_OFFSET, SCORE_Y_OFFSET + 1);
	cout << "Score: " << to_string(score);
	cout << flush;
}

void printLine(int line){
	for (int i = 0; i < WIDTH; i++){
		cout << board[i][line];
	}
	cout << endl;
}

void clearLine(int line, int value){
	for (int i = 0; i < WIDTH; i++){
		board[i][line] = value;
	}
}

void clearLines(int start, int stop, int value){
	int imod = start < stop ? 1 : -1;
	for (int i = start; i < stop; i += imod){
		clearLine(i, value);
	}
}

bool isFull(int b[WIDTH][HEIGHT], int line, int val){
	for (int i = 0; i < WIDTH; i++){
		if (b[i][line] != val){
			return false;
		}	
	}
	return true;
}	

bool hasNone(int b[WIDTH][HEIGHT], int line, int val){
	for (int i = 0; i < WIDTH; i++){
		if (b[i][line] == val){
			return false;
		}	
	}
	return true;
}

vector<int> clearFullLines(){
	vector<int> clearedLines(0);
	for (int i = 0; i < HEIGHT; i++){
		if (hasNone(board, i, 0)){
			lines_cleared++;
			clearLine(i, 0);
			clearedLines.push_back(i);
		}
	}
	score += clearedLines.size()*clearedLines.size();
	if (clearedLines.size() > 0){
		DROP_SPEED -= 2;
		if (enhanced_features){
			toggleState();
		}
	}
	return clearedLines;
}

void cpyRow(int (*boardTo)[WIDTH][HEIGHT], int boardFrom[WIDTH][HEIGHT], int lineTo, int lineFrom){
	for (int i = 0; i < WIDTH; i++){
		(*boardTo)[i][lineTo] = boardFrom[i][lineFrom];
	}
}

void cpyBoard (int (*boardTo)[WIDTH][HEIGHT], int boardFrom[WIDTH][HEIGHT]){
	for (int i = 0; i < HEIGHT; i++){
		cpyRow(boardTo, boardFrom, i, i);
	}
}

void shiftAllDown(){
	int boardCpy[WIDTH][HEIGHT];
	cpyBoard(&boardCpy, board);
	clearLines(0, 23, 0);
	int boardIndex = 23;
	for (int boardCpyIndex = 23; boardCpyIndex >= 0; boardCpyIndex--){
		if (!isFull(boardCpy, boardCpyIndex, 0)){
			cpyRow(&board, boardCpy, boardIndex, boardCpyIndex);
			boardIndex--;
		}
	}
}

bool hasLost(){
	for (int i = 0; i < 4; i++){
		if (!isFull(board, i, 0)){
			return true;
		}
	}
	return false;
}

bool userInputResponse(){
	int xOff, yOff, rOff;
	bool kill = false;
	xOff = yOff = rOff = 0;
	if (KeyTrack::keyValid(&(KeyTrack::spa), VK_SPACE)){
		do {
			yOff++;
		} while (currentPiece.isValidPlacement(xOff, yOff, rOff));
		yOff--;
		kill = true;
	} else if (KeyTrack::keyValid(&(KeyTrack::lAr), VK_LEFT)){
		xOff = -1;
	} else if (KeyTrack::keyValid(&(KeyTrack::rAr), VK_RIGHT)){
		xOff = 1;
	} else if (KeyTrack::keyValid(&(KeyTrack::uAr), VK_UP)){
		rOff = 1;
	} else if (KeyTrack::keyValid(&(KeyTrack::dAr), VK_DOWN)){
		yOff = 1;
	}
	if (currentPiece.isValidPlacement(xOff, yOff, rOff)){
		currentPiece.x += xOff;
		currentPiece.y += yOff;
		currentPiece.rotate(rOff);
	}
	if (kill){
		currentPiece.kill();
	}
	KeyTrack::setKeyInput();
	return !(xOff == 0 && yOff == 0 && rOff == 0);
}

void exit_handler(){
	setCursorColor(7);
	setCursorPosition(0, HEIGHT * SCALE + 1);
	cout << "Thank you for playing TETRIS" << endl << flush;
	mciSendCommand(mPar.wDeviceID, MCI_SET, MCI_SET_DOOR_CLOSED, 0);
	Sleep(100);
	mciSendCommand(mPar.wDeviceID, MCI_CLOSE, MCI_WAIT, 0);
}

BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType){
	exit_handler();
	return 0;
}
#ifndef CONST_H
#define CONST_H

extern const int HEIGHT;
extern const int WIDTH;
extern const int GAME_SPEED;
extern double DROP_SPEED;
extern const int SCALE;
extern const int DISPLAY_WIDTH;
extern const int NEXT_PIECE_X_OFFSET;
extern const int NEXT_PIECE_Y_OFFSET;
extern const int SCORE_X_OFFSET;
extern const int SCORE_Y_OFFSET;
extern const char BLOCK;
extern const char PIECE;
extern const char SPACE;

extern int board[10][24];	//ensure that this is modified at the same time as width and height
extern int score;
extern int lines_cleared;

#endif
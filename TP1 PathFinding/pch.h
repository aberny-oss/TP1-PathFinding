#ifndef PCH_H
#define PCH_H

#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <algorithm>
#include <ctime>
#include <cassert>

//COLOR
#define WHITE	"\033[0m"
#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define BLUE	"\033[34m"
#define YELLOW	"\033[33m"

//ELEMENT update
//#define VOID	0
//#define CURSOR	1
//#define PLAYER	2
//#define PATH	3
//#define KAYOU	4

//ELEMENT draw
#define VOID_DRAW	" "
#define CURSOR_DRAW "0"
#define PLAYER_DRAW "$"
#define PATH_DRAW	"p"
#define KAYOU_DRAW	"#"

//GRID
#define GRID_LINE	10
#define GRID_COLUMN	10


#endif
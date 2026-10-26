#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <vector>

#include "Grid2D.h"


//int Grid2D(int p_line, int p_column)
//{
//    grid(p_line, std::vector<int>(p_column, 0));
//
//
//}

int main()
{

#define WHITE	"\033[0m"
#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define BLUE	"\033[34m"

	int line = 10;
	int column = 10;

	//ELEMENT update
#define VOID	0
#define CURSOR	1
#define PLAYER	2
#define PATH	3

	//ELEMENT draw
#define VOID_DRAW " "
#define CURSOR_DRAW "0"
#define PLAYER_DRAW "$"
#define PATH_DRAW "p"



	//CURSOR
	int linePosStartCursor = line - 1;
	int columnPosStartCursor = column - 1;

	int PosCursorLine = linePosStartCursor;
	int PosCursorColumn = columnPosStartCursor;

	int newPosCursorLine = 0;
	int newPosCursorColumn = 0;

	//PLAYER 
	int linePosStartPlayer = 0;
	int columnPosStartPlayer = 0;

	int PosPlayerLine = linePosStartPlayer;
	int PosPlayerColumn = columnPosStartPlayer;

	int newPosPlayerLine = 0;
	int newPosPlayerColumn = 0;

	//PATH
	int distanceLinePlayerToCursor;
	int distanceColumnPlayerToCursor;

	//USER INPUT
	char userInputChar = 0;
	int userInputInt = 0;

	//CREATE GRID
	std::vector<std::vector<int>> grid(line, std::vector<int>(column, 0));

	grid[linePosStartCursor][columnPosStartCursor] = CURSOR;
	grid[linePosStartPlayer][columnPosStartPlayer] = PLAYER;


	bool drawInput = true;

	//Frame start
	std::system("cls");

	if (drawInput == true)
	{
		std::cerr << userInputChar << std::endl;
		std::cerr << userInputInt << std::endl;
	}
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j] == VOID)//rien
			{
				std::cerr << WHITE << "[";
				std::cerr << WHITE VOID_DRAW;
				std::cerr << WHITE << "]";
			}
			else if (grid[i][j] == CURSOR) //curseur
			{
				std::cerr << WHITE << "[";
				std::cerr << RED CURSOR_DRAW;
				std::cerr << WHITE << "]";
			}
			else if (grid[i][j] == PLAYER) //player
			{
				std::cerr << WHITE << "[";
				std::cerr << BLUE PLAYER_DRAW;
				std::cerr << WHITE << "]";
			}
		}
		std::cerr << "\n";
	}

	while (true)
	{
	
		//INPUT
		userInputChar = _getch();
		userInputInt = userInputChar;


		switch (userInputChar)
		{
		case -128: //erreur
		{
			return 0;
		}
		case 111: // O
		{
			newPosCursorLine = -1;
			break;
		}
		case 108: // S
		{
			newPosCursorLine = 1;
			break;
		}
		case 107: // K
		{
			newPosCursorColumn = -1;
			break;
		}
		case 109: // M
		{
			newPosCursorColumn = 1;
			break;
		}
		case 13: // ENTRER
		{
			newPosPlayerLine = PosCursorLine;
			newPosPlayerColumn = PosCursorColumn;
			break;
		}
		}

		//UPDATE
		//UPDATE CURSOR
		if (newPosCursorLine != 0 || newPosCursorColumn != 0)
		{
			grid[PosCursorLine][PosCursorColumn] = VOID;
			PosCursorLine += newPosCursorLine;
			PosCursorColumn += newPosCursorColumn;

			if (PosCursorLine < 0)
				PosCursorLine = 0;
			if (PosCursorLine > line - 1)
				PosCursorLine = line - 1;
			if (PosCursorColumn < 0)
				PosCursorColumn = 0;
			if (PosCursorColumn > column - 1)
				PosCursorColumn = column - 1;

			grid[PosCursorLine][PosCursorColumn] = CURSOR;
			newPosCursorLine = 0;
			newPosCursorColumn = 0;
		}
		//UPDATE PLAYER
		if (newPosPlayerLine != PosPlayerLine || newPosPlayerColumn != PosPlayerColumn)
		{
			grid[PosPlayerLine][PosPlayerColumn] = VOID;
			PosPlayerLine = newPosPlayerLine;
			PosPlayerColumn = newPosPlayerColumn;

			if (PosPlayerLine < 0)
				PosPlayerLine = 0;
			if (PosPlayerLine > line - 1)
				PosPlayerLine = line - 1;
			if (PosPlayerColumn < 0)
				PosPlayerColumn = 0;
			if (PosPlayerColumn > column - 1)
				PosPlayerColumn = column - 1;
		}
		//pose lu player si pas cursor
		if (grid[PosPlayerLine][PosPlayerColumn] != CURSOR)
		{
			grid[PosPlayerLine][PosPlayerColumn] = PLAYER;
		}
		//UPDATE PATH
		if ((PosPlayerLine != PosCursorLine) || (PosPlayerColumn != PosCursorColumn))
		{
			//reset
			for (int i = 0; i < grid.size(); i++)
			{
				for (int j = 0; j < grid[i].size(); j++)
				{
					if (grid[i][j] == PATH) //path
					{
						grid[i][j] = VOID;
					}
				}
			}

			//Calcul Line
			distanceLinePlayerToCursor = std::abs(PosPlayerLine - PosCursorLine);
			bool playerIsAtUpCursor = false;
			if (PosPlayerLine < PosCursorLine) //Player dessus le curseur en Line
			{
				for (int i = 0; i < distanceLinePlayerToCursor; i++)
				{
					int tempLine = PosPlayerLine + 1 + i;
					grid[tempLine][PosPlayerColumn] = PATH;
				}
				playerIsAtUpCursor = true;

			}
			else //Player dessous le curseur en Line
			{
				for (int i = 0; i < distanceLinePlayerToCursor; i++)
				{
					int tempLine = PosPlayerLine - 1 - i;
					grid[tempLine][PosPlayerColumn] = PATH;
				}
				playerIsAtUpCursor = false;
			}
			//Calcul Column
			distanceColumnPlayerToCursor = std::abs(PosPlayerColumn - PosCursorColumn);
			if (PosPlayerColumn < PosCursorColumn) //Player a gauche du curseur en column
			{
				for (int i = 0; i < distanceColumnPlayerToCursor - 1; i++)
				{
					int tempColumn = PosPlayerColumn + 1 + i;
					int tempLine;
					if (playerIsAtUpCursor)
					{
						tempLine = PosPlayerLine + distanceLinePlayerToCursor;
					}
					else
					{
						tempLine = PosPlayerLine - distanceLinePlayerToCursor;
					}
					grid[tempLine][tempColumn] = PATH;
				}

			}
			else //Player a droite du curseur en column
			{
				for (int i = 0; i < distanceColumnPlayerToCursor - 1; i++)
				{
					int tempColumn = PosPlayerColumn - 1 - i;
					int tempLine;
					if (playerIsAtUpCursor)
					{
						tempLine = PosPlayerLine + distanceLinePlayerToCursor;
					}
					else
					{
						tempLine = PosPlayerLine - distanceLinePlayerToCursor;
					}
					grid[tempLine][tempColumn] = PATH;
				}
			}






		}



		//DRAW
		std::system("cls");

		if (drawInput == true)
		{
			std::cerr << userInputChar << std::endl;
			std::cerr << userInputInt << std::endl;
		}
		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[i].size(); j++)
			{
				if (grid[i][j] == VOID) //rien
				{
					std::cerr << WHITE << "[";
					std::cerr << WHITE VOID_DRAW;
					std::cerr << WHITE << "]";
				}
				else if (grid[i][j] == CURSOR) //curseur
				{
					std::cerr << WHITE << "[";
					std::cerr << RED CURSOR_DRAW;
					std::cerr << WHITE << "]";
				}
				else if (grid[i][j] == PLAYER) //player
				{
					std::cerr << WHITE << "[";
					std::cerr << BLUE PLAYER_DRAW;
					std::cerr << WHITE << "]";
				}
				else if (grid[i][j] == PATH) //path
				{
					std::cerr << WHITE << "[";
					std::cerr << GREEN PATH_DRAW;
					std::cerr << WHITE << "]";
				}
			}
			std::cerr << "\n";
		}

		userInputChar = -128;
	}






	return 0;
}

#pragma once
#include <vector>

enum class Element
{
	FREE,	
	CURSOR,
	PLAYER,
	PATH,
	KAYOU,
};

struct Cell
{
	int s_line, s_column;
	bool s_obstacle;

	int s_elementIn;

	bool s_added;
	Cell* s_cameFrom;

	int s_difficulty;

	Cell()
	{
		s_line = -1;
		s_column = -1;
		s_obstacle = false;
		s_elementIn = (int)Element::FREE;
		s_added = false;
		s_cameFrom = nullptr;
		s_difficulty = 1 + (rand() % CELL_DIFFICULTY_MAX);
	}
	void SetLineColumn(int p_line, int p_column) { s_line = p_line; s_column = p_column; }
};

class Grid2D
{
public:

	Grid2D();
	~Grid2D();

	bool Init(int p_line, int p_column);

	//void SetCell(int p_line, int p_column, int p_value);
	Cell* GetCell(int p_line, int p_column);

	int GetLine() const { return m_line; }
	int GetColumn() const { return m_column; }

private:

	int m_line;
	int m_column;

	//std::vector<std::vector<int>> m_grid;
	std::vector<std::vector<Cell>> m_grid;






};


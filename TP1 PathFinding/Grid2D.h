#pragma once
#include <vector>

class Grid2D
{
public:

	Grid2D();
	~Grid2D();

	bool Init(int p_line, int p_column);

	void SetCell(int p_line, int p_column, int p_value);
	int GetCell(int p_line, int p_column) const;

	int GetLine() const { return m_line; }
	int GetColumn() const { return m_column; }

private:

	int m_line;
	int m_column;

	std::vector<std::vector<int>> m_grid;







};


#include "pch.h"
#include "Grid2D.h"

Grid2D::Grid2D()
{
	m_line = 0;
	m_column = 0;
}

Grid2D::~Grid2D()
{




}

bool Grid2D::Init(int p_line, int p_column)
{
	m_line = p_line;
	m_column = p_column;

	m_grid.resize(p_line);

	for (int line = 0; line < p_line; line++)
	{
		m_grid[line].resize(p_column);
		for (int column = 0; column < p_column; column++)
		{
			Cell cell;
			cell.SetLineColumn(line, column);
			m_grid[line][column] = cell;
		}
	}

	//m_grid.assign(m_line, std::vector<int>(m_column, 0));
	//m_grid.assign(m_line, std::vector<Cell>(m_column, Cell()));

	return true;
}

//void Grid2D::SetCell(int p_line, int p_column, int p_value)
//{
//	//assert(p_line >= 0 && p_line < m_line, "Line index out of bounds");
//	//assert(p_column >= 0 && p_column < m_column, "Column index out of bounds");
//
//	p_line = std::clamp(p_line, 0, m_line - 1);
//	p_column = std::clamp(p_column, 0, m_column - 1);
//
//	m_grid[p_line][p_column] = p_value;
//}

Cell* Grid2D::GetCell(int p_line, int p_column)
{
	if (p_line < 0 || p_line >= m_line)
		return nullptr;

	if (p_column < 0 || p_column >= m_column)
		return nullptr;

	return &m_grid[p_line][p_column];
}

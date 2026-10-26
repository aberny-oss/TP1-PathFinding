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

	m_grid.assign(m_line, std::vector<int>(m_column, 0));

	return true;
}

void Grid2D::SetCell(int p_line, int p_column, int p_value)
{
	assert(p_line >= 0 && p_line < m_line, "Line index out of bounds");
	assert(p_column >= 0 && p_column < m_column, "Column index out of bounds");

	m_grid[p_line][p_column] = p_value;
}

int Grid2D::GetCell(int p_line, int p_column) const
{
	assert(p_line >= 0 && p_line < m_line, "Line index out of bounds");
	assert(p_column >= 0 && p_column < m_column, "Column index out of bounds");

	return m_grid[p_line][p_column];
}

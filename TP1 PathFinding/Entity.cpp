#include "pch.h"
#include "Entity.h"

Entity::Entity()
{
	m_posLine = -1;
	m_posColumn = -1;
}

void Entity::Init(int p_gridLine, int p_gridColumn)
{
	m_maxPosLine = p_gridLine;
	m_maxPosColumn = p_gridColumn;
}

void Entity::SetPosition(int p_line, int p_column)
{
	p_line = std::clamp(p_line, 0, m_maxPosLine - 1);
	p_column = std::clamp(p_column, 0, m_maxPosColumn - 1);

	m_posLine = p_line;
	m_posColumn = p_column;
}

void Entity::UpdatePosition(int p_directionLine, int p_directionColumn)
{
	m_posLine += p_directionLine;
	m_posColumn += p_directionColumn;

	m_posLine = std::clamp(m_posLine, 0, m_maxPosLine - 1);
	m_posColumn = std::clamp(m_posColumn, 0, m_maxPosColumn - 1);
}

int Entity::GetPosLine() const
{
	return m_posLine;
}

int Entity::GetPosColumn() const
{
	return m_posColumn;
}


#include "pch.h"
#include "Entity.h"

Entity::Entity()
{
	m_posLine = -1;
	m_posColumn = -1;
}

void Entity::SetPosition(int p_line, int p_column)
{
	m_posLine = p_line;
	m_posColumn = p_column;
}

void Entity::UpdatePosition(int p_directionLine, int p_directionColumn)
{
	m_posLine += p_directionLine;
	m_posColumn += p_directionColumn;
}

int Entity::GetPosLine() const
{
	return m_posLine;
}

int Entity::GetPosColumn() const
{
	return m_posColumn;
}


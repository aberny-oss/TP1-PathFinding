#pragma once
class Entity
{
public:

	Entity();
	~Entity() = default;

	void Init(int p_gridLine, int p_gridColumn);

	void SetPosition(int p_line, int p_column);
	void UpdatePosition(int p_directionLine, int p_directionColumn);
	int GetPosLine() const;
	int GetPosColumn() const;

private:

	int m_posLine;
	int m_posColumn;

	int m_maxPosLine;
	int m_maxPosColumn;

};


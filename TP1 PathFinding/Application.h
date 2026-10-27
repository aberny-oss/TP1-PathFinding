#pragma once

class Grid2D;
class Entity;
struct Cell;

class Application
{
public:

	Application();

	~Application();

	static Application* GetInstance();

	void Init();
	void Run();
	void Shutdown();

	void HandleInput();
	void Update();
	void Draw();

	void gotoxy(short x, short y);

	void hidecursor();

	void Refresh();

	bool FindPath(Cell* p_start, Cell* p_end);

private:

	bool m_running;
	bool m_drawInput;

	//GRID
	Grid2D* m_grid;	

	//ENTITY
	Entity* m_cursor;
	Entity* m_player;

};


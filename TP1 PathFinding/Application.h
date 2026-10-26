#pragma once

class Grid2D;
class Entity;

class Application
{
public:

	Application() = default;

	~Application();

	static Application* GetInstance();

	void Init();
	void Run();
	void Shutdown();

private:

	bool m_running = true;
	bool m_drawInput = true;

	//GRID
	Grid2D* m_grid;	

	//ENTITY
	Entity* m_cursor;
	Entity* m_player;

};


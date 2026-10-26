#include "pch.h"
#include "Application.h"
#include "Grid2D.h"
#include "Entity.h"
#include "Input.h"

Application::~Application()
{
	Shutdown();
}

Application* Application::GetInstance()
{
	static Application instance;
	return &instance;
}

void Application::Init()
{
	m_grid = new Grid2D();
	m_grid->Init(GRID_LINE, GRID_COLUMN);

	m_cursor = new Entity();
	m_cursor->SetPosition(GRID_LINE - 1, GRID_COLUMN - 1);

	m_player = new Entity();
	m_player->SetPosition(0, 0);

	m_grid->SetCell(m_cursor->GetPosLine(), m_cursor->GetPosColumn(), CURSOR);
	m_grid->SetCell(m_player->GetPosLine(), m_player->GetPosColumn(), PLAYER);

	int spawnKayouLine = 0;
	int spawnKayouColumn = 0;
	for (int i = 0; i < 1; i++)
	{
		spawnKayouLine = rand() % GRID_LINE;
		spawnKayouColumn = rand() % GRID_COLUMN;
		if (m_grid->GetCell(spawnKayouLine, spawnKayouColumn) == VOID)
			m_grid->SetCell(spawnKayouLine, spawnKayouColumn, KAYOU);
	}
}

void Application::Run()
{
	if (m_drawInput == true)
	{
		std::cerr << 0 << std::endl;
		std::cerr << 0 << std::endl;
	}
	//int deplacement = distanceLinePlayerToCursor + distanceColumnPlayerToCursor;
	//std::cerr << "Deplacement a effectuer : " << deplacement << std::endl;
	for (int i = 0; i < m_grid->GetLine(); i++)
	{
		for (int j = 0; j < m_grid->GetColumn(); j++)
		{
			if (m_grid->GetCell(i, j) == VOID) //rien
			{
				std::cerr << WHITE << "[";
				std::cerr << WHITE VOID_DRAW;
				std::cerr << WHITE << "]";
			}
			else if (m_grid->GetCell(i, j) == CURSOR) //curseur
			{
				std::cerr << WHITE << "[";
				std::cerr << RED CURSOR_DRAW;
				std::cerr << WHITE << "]";
			}
			else if (m_grid->GetCell(i, j) == PLAYER) //player
			{
				std::cerr << WHITE << "[";
				std::cerr << BLUE PLAYER_DRAW;
				std::cerr << WHITE << "]";
			}
			else if (m_grid->GetCell(i, j) == PATH) //path
			{
				std::cerr << WHITE << "[";
				std::cerr << GREEN PATH_DRAW;
				std::cerr << WHITE << "]";
			}
			else if (m_grid->GetCell(i, j) == KAYOU) //kayou
			{
				std::cerr << WHITE << "[";
				std::cerr << YELLOW KAYOU_DRAW;
				std::cerr << WHITE << "]";
			}
		}
		std::cerr << "\n";
	}
	while (m_running)
	{

		Input::GetInstance()->Update();
		char userInputChar = Input::GetInstance()->GetInputChar();
		//INPUT
		switch (userInputChar)
		{
		case -128: //erreur
		{
			return;
		}
		case 111: // O
		{
			m_cursor->UpdatePosition(-1, 0);
			break;
		}
		case 108: // S
		{
			m_cursor->UpdatePosition(1, 0);
			break;
		}
		case 107: // K
		{
			m_cursor->UpdatePosition(0, -1);
			break;
		}
		case 109: // M
		{
			m_cursor->UpdatePosition(0, 1);
			break;
		}
		case 13: // ENTRER
		{
			m_player->SetPosition(m_cursor->GetPosLine(), m_cursor->GetPosColumn());
			break;
		}
		}

		//reset grid
		for (int i = 0; i < m_grid->GetLine(); i++)
		{
			for (int j = 0; j < m_grid->GetColumn(); j++)
			{
				m_grid->SetCell(i, j, VOID);
			}
		}

		//UPDATE CURSOR
		m_grid->SetCell(m_cursor->GetPosLine(), m_cursor->GetPosColumn(), CURSOR);
	
		
		//UPDATE PLAYER
		//pose lu player si pas cursor
		if (m_grid->GetCell(m_player->GetPosLine(), m_player->GetPosColumn()) != CURSOR)
		{
			m_grid->SetCell(m_player->GetPosLine(), m_player->GetPosColumn(), PLAYER);
		}


		std::system("cls");



		//DRAW


		if (m_drawInput == true)
		{
			int userInputInt = userInputChar;
			std::cerr << userInputChar << std::endl;
			std::cerr << userInputInt << std::endl;
		}
		//int deplacement = distanceLinePlayerToCursor + distanceColumnPlayerToCursor;
		//std::cerr << "Deplacement a effectuer : " << deplacement << std::endl;
		for (int i = 0; i < m_grid->GetLine(); i++)
		{
			for (int j = 0; j < m_grid->GetColumn(); j++)
			{
				if (m_grid->GetCell(i, j) == VOID) //rien
				{
					std::cerr << WHITE << "[";
					std::cerr << WHITE VOID_DRAW;
					std::cerr << WHITE << "]";
				}
				else if (m_grid->GetCell(i, j) == CURSOR) //curseur
				{
					std::cerr << WHITE << "[";
					std::cerr << RED CURSOR_DRAW;
					std::cerr << WHITE << "]";
				}
				else if (m_grid->GetCell(i, j) == PLAYER) //player
				{
					std::cerr << WHITE << "[";
					std::cerr << BLUE PLAYER_DRAW;
					std::cerr << WHITE << "]";
				}
				else if (m_grid->GetCell(i, j) == PATH) //path
				{
					std::cerr << WHITE << "[";
					std::cerr << GREEN PATH_DRAW;
					std::cerr << WHITE << "]";
				}
				else if (m_grid->GetCell(i, j) == KAYOU) //kayou
				{
					std::cerr << WHITE << "[";
					std::cerr << YELLOW KAYOU_DRAW;
					std::cerr << WHITE << "]";
				}
			}
			std::cerr << "\n";
		}
		userInputChar = -128;
	}
}

void Application::Shutdown()
{


}

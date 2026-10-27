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
	m_cursor->Init(GRID_LINE, GRID_COLUMN);
	m_cursor->SetPosition(GRID_LINE - 1, GRID_COLUMN - 1);

	m_player = new Entity();
	m_player->Init(GRID_LINE, GRID_COLUMN);
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
	Draw();
	while (m_running)
	{

		HandleInput();
		
		Update();

		Draw();
	}
}

void Application::Shutdown()
{


}

void Application::HandleInput()
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
}

void Application::Update()
{
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

	if ((m_player->GetPosLine() != m_cursor->GetPosLine()) || (m_player->GetPosColumn() != m_cursor->GetPosColumn()))
	{
		//Calcul Line
		int PosPlayerLine = m_player->GetPosLine();
		int PosPlayerColumn = m_player->GetPosColumn();
		int PosCursorLine = m_cursor->GetPosLine();
		int PosCursorColumn = m_cursor->GetPosColumn();

		int distanceLinePlayerToCursor = std::abs(PosPlayerLine - PosCursorLine);
		bool playerIsAtUpCursor = false;
		if (PosPlayerLine < PosCursorLine) //Player dessus le curseur en Line
		{
			for (int i = 0; i < distanceLinePlayerToCursor - 1; i++)
			{
				int tempLine = PosPlayerLine + 1 + i;
				m_grid->SetCell(tempLine, PosPlayerColumn, PATH);
			}
			playerIsAtUpCursor = true;

		}
		else //Player dessous le curseur en Line
		{
			for (int i = 0; i < distanceLinePlayerToCursor - 1; i++)
			{
				int tempLine = PosPlayerLine - 1 - i;
				m_grid->SetCell(tempLine, PosPlayerColumn, PATH);
			}
			playerIsAtUpCursor = false;
		}
		//Calcul Column
		int distanceColumnPlayerToCursor = std::abs(PosPlayerColumn - PosCursorColumn);
		if (PosPlayerColumn < PosCursorColumn) //Player a gauche du curseur en column
		{
			for (int i = 0; i < distanceColumnPlayerToCursor; i++)
			{
				int tempColumn = PosPlayerColumn + i;
				int tempLine;
				if (playerIsAtUpCursor)
				{
					tempLine = PosPlayerLine + distanceLinePlayerToCursor;
				}
				else
				{
					tempLine = PosPlayerLine - distanceLinePlayerToCursor;
				}
				m_grid->SetCell(tempLine, tempColumn, PATH);
			}
		}
		else //Player a droite du curseur en column
		{
			for (int i = 0; i < distanceColumnPlayerToCursor; i++)
			{
				int tempColumn = PosPlayerColumn - i;
				int tempLine;
				if (playerIsAtUpCursor)
				{
					tempLine = PosPlayerLine + distanceLinePlayerToCursor;
				}
				else
				{
					tempLine = PosPlayerLine - distanceLinePlayerToCursor;
				}
				m_grid->SetCell(tempLine, tempColumn, PATH);
			}
		}
	}
}

void Application::Draw()
{
	std::system("cls");

	if (m_drawInput == true)
	{
		char userInputChar = Input::GetInstance()->GetInputChar();
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
	Input::GetInstance()->SetInputChar(-128);
}

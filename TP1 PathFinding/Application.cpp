#include "pch.h"
#include <queue>

#include "Application.h"
#include "Grid2D.h"
#include "Entity.h"
#include "Input.h"

Application::Application()
{
	m_running = true;
	m_drawInput = true;

	//GRID
	m_grid = nullptr;

	//ENTITY
	m_cursor = nullptr;
	m_player = nullptr;
}

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
	hidecursor();

	srand(time(NULL));

	m_grid = new Grid2D();
	m_grid->Init(GRID_LINE, GRID_COLUMN);


	m_cursor = new Entity();
	m_cursor->Init(GRID_LINE, GRID_COLUMN);
	m_cursor->SetPosition(GRID_LINE - 1, GRID_COLUMN - 1);

	m_player = new Entity();
	m_player->Init(GRID_LINE, GRID_COLUMN);
	m_player->SetPosition(0, 0);

	//m_grid->SetCell(m_cursor->GetPosLine(), m_cursor->GetPosColumn(), CURSOR);
	//m_grid->SetCell(m_player->GetPosLine(), m_player->GetPosColumn(), PLAYER);
	m_grid->GetCell(m_cursor->GetPosLine(), m_cursor->GetPosColumn())->s_elementIn = (int)Element::CURSOR;
	m_grid->GetCell(m_player->GetPosLine(), m_player->GetPosColumn())->s_elementIn = (int)Element::PLAYER;

	int spawnKayouLine = 0;
	int spawnKayouColumn = 0;

	int nbKayou = 6;
	m_kayoux.reserve(nbKayou);

	for (int i = 0; i < nbKayou; i++)
	{
		Entity* kayou = new Entity();
		kayou->Init(GRID_LINE, GRID_COLUMN);
		spawnKayouLine = rand() % GRID_LINE;
		spawnKayouColumn = rand() % GRID_COLUMN;
		kayou->SetPosition(spawnKayouLine, spawnKayouColumn);
		//if (m_grid->GetCell(spawnKayouLine, spawnKayouColumn) == VOID)
		//	m_grid->SetCell(spawnKayouLine, spawnKayouColumn, KAYOU);
		m_kayoux.push_back(kayou);
		if (m_grid->GetCell(spawnKayouLine, spawnKayouColumn)->s_elementIn == (int)Element::FREE)
			m_grid->GetCell(spawnKayouLine, spawnKayouColumn)->s_elementIn = (int)Element::KAYOU;
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
	case 'o': // O
	{
		m_cursor->UpdatePosition(-1, 0);
		break;
	}
	case 'l': // L
	{
		m_cursor->UpdatePosition(1, 0);
		break;
	}
	case 'k': // K
	{
		m_cursor->UpdatePosition(0, -1);
		break;
	}
	case 'm': // M
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
			//m_grid->SetCell(i, j, VOID);
			//m_grid->SetCell(i, j, VOID);
			m_grid->GetCell(i, j)->s_elementIn = (int)Element::FREE;
		}
	}

	//UPDATE CURSOR
	//m_grid->SetCell(m_cursor->GetPosLine(), m_cursor->GetPosColumn(), CURSOR);
	m_grid->GetCell(m_cursor->GetPosLine(), m_cursor->GetPosColumn())->s_elementIn = (int)Element::CURSOR;

	//UPDATE PLAYER
	//pose lu player si pas cursor
	//if (m_grid->GetCell(m_player->GetPosLine(), m_player->GetPosColumn()) != CURSOR)
	//{
	//	m_grid->SetCell(m_player->GetPosLine(), m_player->GetPosColumn(), PLAYER);
	//}
	if (m_grid->GetCell(m_player->GetPosLine(), m_player->GetPosColumn())->s_elementIn != (int)Element::CURSOR)
	{
		m_grid->GetCell(m_player->GetPosLine(), m_player->GetPosColumn())->s_elementIn = (int)Element::PLAYER;
	}

	for (Entity* kayou : m_kayoux)
	{
		int posLineKaoyu = kayou->GetPosLine();
		int posColumnKaoyu = kayou->GetPosColumn();

		if (m_grid->GetCell(posLineKaoyu, posColumnKaoyu)->s_elementIn != (int)Element::CURSOR)
		{
			m_grid->GetCell(posLineKaoyu, posColumnKaoyu)->s_elementIn = (int)Element::KAYOU;
		}
	}

	if ((m_player->GetPosLine() != m_cursor->GetPosLine()) || (m_player->GetPosColumn() != m_cursor->GetPosColumn()))
	{
		ResetPath();

		FindPath(m_grid->GetCell(m_player->GetPosLine(), m_player->GetPosColumn()), m_grid->GetCell(m_cursor->GetPosLine(), m_cursor->GetPosColumn()));

	
	}
}

void Application::Draw()
{
	Refresh();
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
			if (m_grid->GetCell(i, j)->s_elementIn == (int)Element::FREE) //rien
			{
				std::cerr << WHITE << "[";
				std::cerr << WHITE VOID_DRAW;
				std::cerr << WHITE << "]";
			}
			else if (m_grid->GetCell(i, j)->s_elementIn == (int)Element::CURSOR) //curseur
			{
				std::cerr << WHITE << "[";
				std::cerr << RED CURSOR_DRAW;
				std::cerr << WHITE << "]";
			}
			else if (m_grid->GetCell(i, j)->s_elementIn == (int)Element::PLAYER) //player
			{
				std::cerr << WHITE << "[";
				std::cerr << BLUE PLAYER_DRAW;
				std::cerr << WHITE << "]";
			}
			else if (m_grid->GetCell(i, j)->s_elementIn == (int)Element::PATH) //path
			{
				std::cerr << WHITE << "[";
				std::cerr << GREEN_BG PATH_DRAW;
				std::cerr << WHITE << "]";
			}
			else if (m_grid->GetCell(i, j)->s_elementIn == (int)Element::KAYOU) //kayou
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

void Application::gotoxy(short x, short y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };
	SetConsoleCursorPosition(hConsole, position);
}

void Application::hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void Application::Refresh()
{
	gotoxy(0, 0);
}

bool Application::FindPath(Cell* p_start, Cell* p_end)
{
	// Créer une file
	std::queue<Cell*> cellQueue;

	// Ajouter "start" à la file
	cellQueue.push(p_start);

	// Marquer la tile comme "ajouté"
	p_start->s_added = true;

	/* la file n'est pas vide */
	while (cellQueue.empty() == false)
	{
		Cell* current = cellQueue.front();
		// Récupérer la tile en tête de file et la retirer de la file
		cellQueue.pop();

		/* la tile a les coordonnées de end */
		if (p_end == current)
		{
			Cell* cell = current;
			while (cell != nullptr)
			{
				//isInPath[cell->s_line][cell->s_column] = true;
				if (cell->s_elementIn == (int)Element::FREE)
				{
					cell->s_elementIn = (int)Element::PATH;
				}
				cell = cell->s_cameFrom;
			}

			return true; // chemin trouvé
		}

		const int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, };

		/* chaque voisin de la tile courante */
		for (int i = 0; i < 4; i++) 
		{
			int line = current->s_line + directions[i][0];
			int col = current->s_column + directions[i][1];

			Cell* neighbor = m_grid->GetCell(line, col);
			if (neighbor == nullptr)
				continue;
			/*
			* Explication du filtre d'obstacle :
			*
			* Face à un rocher (KAYOU) :
			* 1. Est-ce qu'il est différent du vide ? Oui.
			* 2. Est-ce qu'il est différent du curseur ? Oui.
			* 3. Conclusion : Oui ET Oui. L'ordinateur exécute le continue et ignore le rocher. Le mur bloque bien le chemin.
			*
			* Face à une case vide (FREE) :
			* 1. Est-ce qu'elle est différente du vide ? Non (puisque c'est du vide).
			* 2. L'ordinateur s'arrête de lire. Puisque la première partie est fausse, le && (ET) fait que la condition entière est fausse.
			* 3. Conclusion : Le continue n'est pas exécuté. La case vide est acceptée pour construire le chemin.
			*/
			if (neighbor->s_elementIn != (int)Element::FREE && neighbor->s_elementIn != (int)Element::CURSOR)
				continue;

			if (neighbor->s_added)
				continue;

			neighbor->s_cameFrom = current;
			neighbor->s_added = true;
			cellQueue.push(neighbor);
		}
	}

	return false; // chemin non trouvé
}

void Application::ResetPath()
{
	for (int line = 0; line < m_grid->GetLine(); line++)
	{
		for (int column = 0; column < m_grid->GetColumn(); column++)
		{
			Cell* cell = m_grid->GetCell(line, column);
			cell->s_added = false;
			cell->s_cameFrom = nullptr;
		}
	}
}


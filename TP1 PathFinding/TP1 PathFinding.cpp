#include "pch.h"
#include "Application.h"

int main()
{
	Application* app = Application::GetInstance();
	app->Init();
	app->Run();
	app->Shutdown();
	return 0;
}

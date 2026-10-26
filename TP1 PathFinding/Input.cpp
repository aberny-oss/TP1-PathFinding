#include "pch.h"
#include "Input.h"

Input::Input()
{

}

Input::~Input()
{

}

Input* Input::GetInstance()
{
	static Input instance;
	return &instance;
}

void Input::Update()
{
	m_inputChar = _getch();
	m_inputInt = m_inputChar;
}

char Input::GetInputChar()
{
	return m_inputChar;
}

int Input::GetInputInt()
{
	return m_inputInt;
}

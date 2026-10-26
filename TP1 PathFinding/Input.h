#pragma once
class Input
{
public:

	Input();

	~Input();

	static Input* GetInstance();

	void Update();

	char GetInputChar();
	int GetInputInt();

private:

	char m_inputChar;
	int m_inputInt;

	
};


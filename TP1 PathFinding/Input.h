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

	void SetInputChar(char p_inputChar);

private:

	char m_inputChar;
	int m_inputInt;

	
};


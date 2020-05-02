#pragma once
#include "pch.h"

using namespace std;

void gotoxy(int x, int y)
{
	COORD point;
	point.X = x; point.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

void SetCursorVisible(BOOL _bVisible, DWORD _dwSize)
{
	CONSOLE_CURSOR_INFO CCI;
	CCI.bVisible = _bVisible;
	CCI.dwSize = _dwSize;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CCI);
}

// �C��s�X �аѦ� https://blog.wildsky.cc/posts/c-code-note/
void SetColor(int color)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

vector<string> initialmap(vector<string> m)
{
	m.push_back("|_______________________________________________________________________|");
	m.push_back("|  �_�I  |        |        |        |        |        |        |        |");
	m.push_back("| | || | | | || | | | || | | | || | | | || | | | || | | | || | | | || | |");
	m.push_back("|        |        |        |        |        |        |        |        |");
	m.push_back("|_______________________________________________________________________|");
	m.push_back("|        |                                                     |        |");
	m.push_back("| | || | |                                                     | | || | |");
	m.push_back("|        |                                                     |        |");
	m.push_back("|________|                                                     |________|");
	m.push_back("|        |                                                     |        |");
	m.push_back("| | || | |                                                     | | || | |");
	m.push_back("|        |                                                     |        |");
	m.push_back("|________|                                                     |________|");
	m.push_back("|        |                                                     |        |");
	m.push_back("| | || | |                                                     | | || | |");
	m.push_back("|        |                                                     |        |");
	m.push_back("|________|                                                     |________|");
	m.push_back("|        |                                                     |        |");
	m.push_back("| | || | |                                                     | | || | |");
	m.push_back("|        |                                                     |        |");
	m.push_back("|________|                                                     |________|");
	m.push_back("|        |                                                     |        |");
	m.push_back("| | || | |                                                     | | || | |");
	m.push_back("|        |                                                     |        |");
	m.push_back("|________|                                                     |________|");
	m.push_back("|        |                                                     |        |");
	m.push_back("| | || | |                                                     | | || | |");
	m.push_back("|        |                                                     |        |");
	m.push_back("|________|_____________________________________________________|________|");
	m.push_back("|        |        |        |        |        |        |        |        |");
	m.push_back("| | || | | | || | | | || | | | || | | | || | | | || | | | || | | | || | |");
	m.push_back("|        |        |        |        |        |        |        |        |");
	m.push_back("|_______________________________________________________________________|");
	return m;
}

vector <string> initialplayerMap(vector<string> pMap)
{
	pMap.clear();
	pMap.push_back("_________________________________________________________________________");
	pMap.push_back("|                 |                 |                 |                 |");
	pMap.push_back("|                 |                 |                 |                 |");
	pMap.push_back("|                 |                 |                 |                 |");
	pMap.push_back("|                 |                 |                 |                 |");
	pMap.push_back("|_______________________________________________________________________|");
	pMap.push_back("|�ثe�C����                                                   ��e�^�X��|");
	pMap.push_back("|                                                                       |");
	pMap.push_back("|_______________________________________________________________________|");
	pMap.push_back("|***********************************************************************|");
	return pMap;
}

vector <string> mainMenu(vector<string> menu)
{
	menu.push_back("|�áááááááá�|");
	menu.push_back("|     �~��C��     |");
	menu.push_back("|�X�X�X�X�X�X�X�X�X|");
	menu.push_back("|     ���s�}�l     |");
	menu.push_back("|�X�X�X�X�X�X�X�X�X|");
	menu.push_back("|     �s��         |");
	menu.push_back("|�X�X�X�X�X�X�X�X�X|");
	menu.push_back("|     Ū��         |");
	menu.push_back("|�X�X�X�X�X�X�X�X�X|");
	menu.push_back("|     ���}�C��     |");
	menu.push_back("|__________________|");
	return menu;
}

vector <string> playerAction(vector<string> act)
{
	act.push_back("| �ááááááá�| �ááááááá�|�ááááááá� | �ááááááá�|");
	act.push_back("|  �� �Y��l      |  �� �Ȧ�        |  �� �Ѳ�        |  �� �D��        |");
	act.push_back("|_________________|_________________|_________________|_________________|");
	return act;
}
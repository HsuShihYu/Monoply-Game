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

// 顏色編碼 請參考 https://blog.wildsky.cc/posts/c-code-note/
void SetColor(int color)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

vector<string> initialmap(vector<string> m)
{
	m.push_back("|_______________________________________________________________________|");
	m.push_back("|  起點  |        |        |        |        |        |        |        |");
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
	pMap.push_back("|目前遊戲者                                                   當前回合數|");
	pMap.push_back("|                                                                       |");
	pMap.push_back("|_______________________________________________________________________|");
	pMap.push_back("|***********************************************************************|");
	return pMap;
}

vector <string> mainMenu(vector<string> menu)
{
	menu.push_back("|￣￣￣￣￣￣￣￣￣|");
	menu.push_back("|     繼續遊戲     |");
	menu.push_back("|—————————|");
	menu.push_back("|     重新開始     |");
	menu.push_back("|—————————|");
	menu.push_back("|     存檔         |");
	menu.push_back("|—————————|");
	menu.push_back("|     讀檔         |");
	menu.push_back("|—————————|");
	menu.push_back("|     離開遊戲     |");
	menu.push_back("|__________________|");
	return menu;
}

vector <string> playerAction(vector<string> act)
{
	act.push_back("| ￣￣￣￣￣￣￣￣| ￣￣￣￣￣￣￣￣|￣￣￣￣￣￣￣￣ | ￣￣￣￣￣￣￣￣|");
	act.push_back("|  １ 擲骰子      |  ２ 銀行        |  ３ 股票        |  ４ 道具        |");
	act.push_back("|_________________|_________________|_________________|_________________|");
	return act;
}
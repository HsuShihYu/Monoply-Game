#pragma once
#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>  
#include <sstream>
#include <fstream>
#include<conio.h>
#include<windows.h>

using namespace std;

// 先定義 上,下,左,右,ESC,ENTER
#define ESC	27
#define DIRECTION_KEYBOARD	224
#define UP     72
#define DOWN   80
#define LEFT   75
#define RIGHT  77
#define ENTER  13

// 初始化 Map 邊框
vector<string>initialmap(vector<string> m);
// 初始化 Player 表邊框
vector <string> initialplayerMap(vector<string> pMap);
//初始主選單
vector <string> mainMenu(vector<string> menu);
//玩家動作選單
vector <string> playerAction(vector<string> act);
// 游標移動 "至" (x, y)  
void gotoxy(int x, int y);
// 設定游標的樣式
void SetCursorVisible(BOOL _bVisible, DWORD _dwSize);
// 字體背景顏色
void SetColor(int color);

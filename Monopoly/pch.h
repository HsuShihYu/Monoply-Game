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

// ���w�q �W,�U,��,�k,ESC,ENTER
#define ESC	27
#define DIRECTION_KEYBOARD	224
#define UP     72
#define DOWN   80
#define LEFT   75
#define RIGHT  77
#define ENTER  13

// ��l�� Map ���
vector<string>initialmap(vector<string> m);
// ��l�� Player �����
vector <string> initialplayerMap(vector<string> pMap);
//��l�D���
vector <string> mainMenu(vector<string> menu);
//���a�ʧ@���
vector <string> playerAction(vector<string> act);
// ��в��� "��" (x, y)  
void gotoxy(int x, int y);
// �]�w��Ъ��˦�
void SetCursorVisible(BOOL _bVisible, DWORD _dwSize);
// �r��I���C��
void SetColor(int color);

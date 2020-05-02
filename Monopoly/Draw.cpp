#include"Draw.h"


using namespace std;


void Draw::renewOutput()
{
	gotoxy(0, 0);
	system("cls");

	// 先畫出上層介面
	Player::renewPlayerState();
	// 再畫出中層 地圖背景(無顏色，有字)
	gotoxy(0, 10);
	Map::renewMap();
	// 填入數字到 地圖背景
	Player::putPlayerOnMap();
	// 更新並填入 玩家產地到地圖背景 (上色，加字)
	Player::renewProperty();

	gotoxy(0, 43);
	cout << "目前股價：" << Game::currentStockPriceMsg << "\n";
	gotoxy(0, 44);
	cout << "";

	vector<string> act = playerAction(act);
	gotoxy(0, 46);
	for (int i = 0; i < act.size(); i++)
	{
		SetColor(15);
		cout << act[i];
		cout << "\n";
	}
}

void Draw::renewOutput(string msg)
{
	gotoxy(0, 0);
	system("cls");

	// 先畫出上層介面
	Player::renewPlayerState();
	// 再畫出中層 地圖背景(無顏色，有字)
	gotoxy(0, 10);
	Map::renewMap();
	// 填入數字到 地圖背景
	Player::putPlayerOnMap();
	// 更新並填入 玩家產地到地圖背景 (上色，加字)
	Player::renewProperty();

	gotoxy(0, 43);
	cout << Game::currentStockPriceMsg << "\n";
	gotoxy(0, 44);
	cout << "" << msg << "\n";

	vector<string> act = playerAction(act);
	gotoxy(0, 46);
	for (int i = 0; i < act.size(); i++)
	{
		SetColor(15);
		cout << act[i];
		cout << "\n";
	}
}










#include"Draw.h"


using namespace std;


void Draw::renewOutput()
{
	gotoxy(0, 0);
	system("cls");

	// ���e�X�W�h����
	Player::renewPlayerState();
	// �A�e�X���h �a�ϭI��(�L�C��A���r)
	gotoxy(0, 10);
	Map::renewMap();
	// ��J�Ʀr�� �a�ϭI��
	Player::putPlayerOnMap();
	// ��s�ö�J ���a���a��a�ϭI�� (�W��A�[�r)
	Player::renewProperty();

	gotoxy(0, 43);
	cout << "�ثe�ѻ��G" << Game::currentStockPriceMsg << "\n";
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

	// ���e�X�W�h����
	Player::renewPlayerState();
	// �A�e�X���h �a�ϭI��(�L�C��A���r)
	gotoxy(0, 10);
	Map::renewMap();
	// ��J�Ʀr�� �a�ϭI��
	Player::putPlayerOnMap();
	// ��s�ö�J ���a���a��a�ϭI�� (�W��A�[�r)
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










#include "pch.h"
#include "Game.h"
#include"Draw.h"

using namespace std;

int main()
{
	Game mainGame("basemap.txt");
	Draw GUI;
	srand(time(NULL));

	GUI.renewOutput();
	int k;
	bool exit;

	//�o�̥u�O�հ� ����n�Q�k�i���
	while (true)
	{
		k = mainGame.selectAction();
		if (k == 0)
		{
			exit = mainGame.gameMenu();
		}

		//������}�C���� ���X�j��
		//if (exit == true)
		//{			
		//	system("cls");
		//	cout << "�C������";
		//	break;
		//}
	}
	
	
	
	cout << "Press Enter to Continue...\n";
	
	getchar();
	return 0;
}
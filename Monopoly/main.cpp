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

	//這裡只是試做 有更好想法可更改
	while (true)
	{
		k = mainGame.selectAction();
		if (k == 0)
		{
			exit = mainGame.gameMenu();
		}

		//選擇離開遊戲時 跳出迴圈
		//if (exit == true)
		//{			
		//	system("cls");
		//	cout << "遊戲結束";
		//	break;
		//}
	}
	
	
	
	cout << "Press Enter to Continue...\n";
	
	getchar();
	return 0;
}
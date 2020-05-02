#include "Player.h"
#include"Game.h"

using namespace std;

Player::Player()
{
	hasChunk.playerNumber = PlayerQuantity;
	hasChunk.playerName = "N/A";
	hasChunk.playerPosition = 0;
	hasChunk.hasMoney.moneyInPocket = 0;
	hasChunk.hasMoney.moneyInBank = 0;
	hasChunk.hasMoney.stock = 0;
	addPlayerQuantity(this);
}
Player::Player(string preferName)
{
	hasChunk.playerNumber = PlayerQuantity;
	hasChunk.playerName = preferName;
	hasChunk.playerPosition = 0;
	hasChunk.hasMoney.moneyInPocket = 0;
	hasChunk.hasMoney.moneyInBank = 0;
	hasChunk.hasMoney.stock = 0;

	addPlayerQuantity(this);
}
Player::Player(hasChunkStatus preferHasChunk)
{
	hasChunk.playerNumber = preferHasChunk.playerNumber;
	hasChunk.playerName = preferHasChunk.playerName;
	hasChunk.playerPosition = preferHasChunk.playerPosition;
	hasChunk.hasMoney = preferHasChunk.hasMoney;
	hasChunk.hasBuffNuff = preferHasChunk.hasBuffNuff;
	hasChunk.hasChunkNumber = preferHasChunk.hasChunkNumber;
	hasChunk.hasChunkStage = preferHasChunk.hasChunkStage;
	hasChunk.hasChunkStagePrice = preferHasChunk.hasChunkStagePrice;

	addPlayerQuantity(this);
}
void Player::addPlayerQuantity(Player* preferPlayerPointer)
{
	PlayerQuantity += 1; //玩家總數+1
	PlayerList.push_back(*preferPlayerPointer); //玩家清單加入新玩家
}
// 更新上排 player 資訊
void Player::renewPlayerState()
{
	SetColor(15);
	drawPlayer = initialplayerMap(drawPlayer);
	for (int i = 0; i < drawPlayer.size(); i++)
	{
		cout << drawPlayer[i] << endl;
	}

	for (int i = 0; i < PlayerQuantity; i++)
	{
		gotoxy(18 * i + 1, 1);
		SetColor(144 + 16 * i);
		cout << PlayerList[i].hasChunk.playerNumber << "                " <<endl;

		gotoxy(18 * i + 1, 2);
		SetColor(15);
		cout << "現金: $" << PlayerList[i].hasChunk.hasMoney.moneyInPocket << endl;

		gotoxy(18 * i + 1, 3);
		cout << "存款: $" << PlayerList[i].hasChunk.hasMoney.moneyInBank << endl;

		gotoxy(18 * i + 1, 4);
		cout << "股票: " << PlayerList[i].hasChunk.hasMoney.stock << "張"<< endl;
	}
	gotoxy(1, 7);
	cout << Game::currentPlayer << endl;
	gotoxy(70, 7);
	cout << Game::currentCount << endl;
	SetColor(15);
}

// 更新 player 位置
void Player::putPlayerOnMap()
{
	for (int i = 0; i < PlayerQuantity; i++)
	{
		int pos = PlayerList[i].hasChunk.playerPosition;
		int num = PlayerList[i].hasChunk.playerNumber;
		if (num == 0)
		{
			SetColor(144);
			if (pos <= 6)
			{
				gotoxy(1, 12 + pos * 4);
				cout << num << endl;
			}
			else if (pos <= 14)
			{
				gotoxy(1 + 9 * (pos - 7), 40);
				cout << num << endl;
			}
			else if (pos <= 20)
			{
				gotoxy(64, 36 - 4 * (pos - 15));
				cout << num << endl;
			}
			else if (pos <= 27)
			{
				gotoxy(64 - 9 * (pos - 21), 12);
				cout << num << endl;
			}
		}
		else if (num == 1)
		{
			SetColor(160);
			if (pos <= 6)
			{
				gotoxy(3, 12 + pos * 4);
				cout << num << endl;
			}
			else if (pos <= 14)
			{
				gotoxy(3 + 9 * (pos - 7), 40);
				cout << num << endl;
			}
			else if (pos <= 20)
			{
				gotoxy(66, 36 - 4 * (pos - 15));
				cout << num << endl;
			}
			else if (pos <= 27)
			{
				gotoxy(66 - 9 * (pos - 21), 12);
				cout << num << endl;
			}
		}
		else if (num == 2)
		{
			SetColor(176);
			if (pos <= 6)
			{
				gotoxy(6, 12 + pos * 4);
				cout << num << endl;
			}
			else if (pos <= 14)
			{
				gotoxy(6 + 9 * (pos - 7), 40);
				cout << num << endl;
			}
			else if (pos <= 20)
			{
				gotoxy(69, 36 - 4 * (pos - 15));
				cout << num << endl;
			}
			else if (pos <= 27)
			{
				gotoxy(69 - 9 * (pos - 21), 12);
				cout << num << endl;
			}
		}
		else if (num == 3)
		{
			SetColor(192);
			if (pos <= 6)
			{
				gotoxy(8, 12 + pos * 4);
				cout << num << endl;
			}
			else if (pos <= 14)
			{
				gotoxy(8 + 9 * (pos - 7), 40);
				cout << num << endl;
			}
			else if (pos <= 20)
			{
				gotoxy(71, 36 - 4 * (pos - 15));
				cout << num << endl;
			}
			else if (pos <= 27)
			{
				gotoxy(71 - 9 * (pos - 21), 12);
				cout << num << endl;
			}
		}
		SetColor(15);
	}
}

// 轉換文字到正中間
string trans2color(string x)
{
	string temp;
	if (x.length() == 4)
	{
		temp = "  " + x + "  ";
	}
	else if (x.length() == 6)
	{
		temp = " " + x + " ";
	}
	else if (x.length() == 8)
	{
		temp =  x;
	}
	return temp;
}

// 轉換等級到文字敘述
string levelTable(int x)
{
	string temp = "";
	if (x == 0)
	{
		temp = "宿舍";
	}
	else if (x == 1)
	{
		temp = "套房";
	}
	else if (x == 2)
	{
		temp = "別墅";
	}
	else if (x == 3)
	{
		temp = "帝寶";
	}
	return temp;
}

// 更新 player 的產地到地圖
void Player::renewProperty()
{
	for (int i = 0; i < PlayerQuantity; i++)
	{
		vector<int> numList = PlayerList[i].hasChunk.hasChunkNumber;
		vector<int> levelList = PlayerList[i].hasChunk.hasChunkStagePrice;

		if (PlayerList[i].hasChunk.playerNumber == 0)
		{
			for (int j = 0; j < numList.size(); j++)
			{
				SetColor(144);
				string temp;
				string tempLevel;
				temp = trans2color(Game::mainMap.chunkList[numList[j]].chunkName);
				tempLevel = levelTable(levelList[j]);

				if (numList[j] <= 6)
				{
					gotoxy(1, 11 + numList[j] * 4);
					cout << temp << endl;

					gotoxy(3, 13 + numList[j] * 4);
					SetColor(224);
					cout << tempLevel << endl;
				}
				else if (numList[j] <= 14)
				{
					gotoxy(3 + 9 * (numList[j] - 7), 39);
					cout << temp << endl;

					gotoxy(5 + 9 * (numList[j] - 7), 41);
					SetColor(224);
					cout << tempLevel << endl;

				}
				else if (numList[j] <= 20)
				{
					gotoxy(64, 35 - 4 * (numList[j] - 15));
					cout << temp << endl;

					gotoxy(66, 37 - 4 * (numList[j] - 15));
					SetColor(224);
					cout << tempLevel << endl;
				}
				else if (numList[j] <= 27)
				{
					gotoxy(64 - 9 * (numList[j] - 21), 11);
					cout << temp << endl;

					gotoxy(66 - 9 * (numList[j] - 21), 13);
					SetColor(224);
					cout << tempLevel << endl;
				}
			}
		}
		else if (PlayerList[i].hasChunk.playerNumber == 1)
		{
			for (int j = 0; j < numList.size(); j++)
			{
				SetColor(160);
				string temp;
				string tempLevel;
				temp = trans2color(Game::mainMap.chunkList[numList[j]].chunkName);
				tempLevel = levelTable(levelList[j]);

				if (numList[j] <= 6)
				{
					gotoxy(1, 11 + numList[j] * 4);
					cout << temp << endl;

					gotoxy(3, 13 + numList[j] * 4);
					SetColor(224);
					cout << tempLevel << endl;
				}
				else if (numList[j] <= 14)
				{
					gotoxy(1 + 9 * (numList[j] - 7), 39);
					cout << temp << endl;

					gotoxy(3 + 9 * (numList[j] - 7), 41);
					SetColor(224);
					cout << tempLevel << endl;

				}
				else if (numList[j] <= 20)
				{
					gotoxy(64, 35 - 4 * (numList[j] - 15));
					cout << temp << endl;

					gotoxy(66, 37 - 4 * (numList[j] - 15));
					SetColor(224);
					cout << tempLevel << endl;
				}
				else if (numList[j] <= 27)
				{
					gotoxy(64 - 9 * (numList[j] - 21), 11);
					cout << temp << endl;

					gotoxy(66 - 9 * (numList[j] - 21), 13);
					SetColor(224);
					cout << tempLevel << endl;
				}
			}
		}
		else if (PlayerList[i].hasChunk.playerNumber == 2)
		{
			for (int j = 0; j < numList.size(); j++)
			{
				SetColor(176);
				string temp;
				string tempLevel;
				temp = trans2color(Game::mainMap.chunkList[numList[j]].chunkName);
				tempLevel = levelTable(levelList[j]);

				if (numList[j] <= 6)
				{
					gotoxy(1, 11 + numList[j] * 4);
					cout << temp << endl;

					gotoxy(3, 13 + numList[j] * 4);
					SetColor(224);
					cout << tempLevel << endl;
				}
				else if (numList[j] <= 14)
				{
					gotoxy(1 + 9 * (numList[j] - 7), 39);
					cout << temp << endl;

					gotoxy(3 + 9 * (numList[j] - 7), 41);
					SetColor(224);
					cout << tempLevel << endl;

				}
				else if (numList[j] <= 20)
				{
					gotoxy(64, 35 - 4 * (numList[j] - 15));
					cout << temp << endl;

					gotoxy(66, 37 - 4 * (numList[j] - 15));
					SetColor(224);
					cout << tempLevel << endl;
				}
				else if (numList[j] <= 27)
				{
					gotoxy(64 - 9 * (numList[j] - 21), 11);
					cout << temp << endl;

					gotoxy(66 - 9 * (numList[j] - 21), 13);
					SetColor(224);
					cout << tempLevel << endl;
				}
			}
		}
		else if (PlayerList[i].hasChunk.playerNumber == 3)
		{
			for (int j = 0; j < numList.size(); j++)
			{
				SetColor(192);
				string temp;
				string tempLevel;
				temp = trans2color(Game::mainMap.chunkList[numList[j]].chunkName);
				tempLevel = levelTable(levelList[j]);

				if (numList[j] <= 6)
				{
					gotoxy(1, 11 + numList[j] * 4);
					cout << temp << endl;

					gotoxy(3, 13 + numList[j] * 4);
					SetColor(224);
					cout << tempLevel << endl;
				}
				else if (numList[j] <= 14)
				{
					gotoxy(1 + 9 * (numList[j] - 7), 39);
					cout << temp << endl;

					gotoxy(3 + 9 * (numList[j] - 7), 41);
					SetColor(224);
					cout << tempLevel << endl;

				}
				else if (numList[j] <= 20)
				{
					gotoxy(64, 35 - 4 * (numList[j] - 15));
					cout << temp << endl;

					gotoxy(66, 37 - 4 * (numList[j] - 15));
					SetColor(224);
					cout << tempLevel << endl;
				}
				else if (numList[j] <= 27)
				{
					gotoxy(64 - 9 * (numList[j] - 21), 11);
					cout << temp << endl;

					gotoxy(66 - 9 * (numList[j] - 21), 13);
					SetColor(224);
					cout << tempLevel << endl;
				}
			}
		}
		SetColor(7);
	}
	gotoxy(0, 38);
}


vector<string> Player::drawPlayer = {};
int Player::PlayerQuantity = 0;
vector<Player> Player::PlayerList;
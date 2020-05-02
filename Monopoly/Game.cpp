#include "Game.h"
#include "Map.h"
#include "Player.h"
#include <random>
using namespace std;

Map Game::mainMap = {};
int Game::currentPlayer = 0;
int Game::currentCount = 0;
int Game::currentStockPrice = 1000;
string Game::currentStockPriceMsg = "";
vector<int> Game::BlockList = {};

Game::Game(string preferFile)
{
	// ...讀檔
	ifstream fin(preferFile);
	vector<string> inputString;
	if (!fin.is_open())
		cout << "Open file error" << endl;
	while (!fin.eof())
	{
		char input[200];
		fin.getline(input, 200);
		string temp(input);
		inputString.push_back(temp);
	}
	fin.close();
	stringstream sin("");
	sin.clear();
	sin << inputString[0];
	sin >> mainMap.mapName >> currentCount >> totalPlayer;
	for (int i = 0; i <= 27; i++)
	{
		sin.clear();
		sin << inputString[i + 1];
		Map::chunk inputChunk;
		sin >> inputChunk.chunkNumber >> inputChunk.chunkName >> inputChunk.chunkType;
		if (inputChunk.chunkType == 1)
		{
			sin >> inputChunk.chunkInitialPrice
				>> inputChunk.chunkPassPrice0
				>> inputChunk.chunkPassPrice1
				>> inputChunk.chunkPassPrice2
				>> inputChunk.chunkPassPrice3;
		}
		mainMap.chunkList.push_back(inputChunk);
	}
	sin.clear();
	string buffer;
	sin << inputString[29];
	sin >> buffer >> currentPlayer;
	for (int i = 30; i <= inputString.size() - 1; i++)
	{
		hasChunkStatus whoseChunk;
		string allProperty;
		sin.clear();
		sin << inputString[i];
		sin >> whoseChunk.playerNumber
			>> whoseChunk.playerPosition
			>> allProperty;
		//set data of propertys
		stringstream setProperty(allProperty);
		try
		{
			int error;
			//set moneyInPocket
			char tempP[10000];
			setProperty.getline(tempP, 10000, ',');
			string pMon(tempP);
			whoseChunk.hasMoney.moneyInPocket = stoi(pMon);
			//set moneyInBank
			char tempB[10000];
			setProperty.getline(tempB, 10000, ',');
			string bMon(tempB);
			if (bMon == "")
			{
				error = 0;
				whoseChunk.hasMoney.moneyInBank = 0;
				whoseChunk.hasMoney.stock = 0;
				throw error;
			}
			whoseChunk.hasMoney.moneyInBank = stoi(bMon);
			//set stock
			char tempS[10000];
			setProperty.getline(tempS, 10000, ',');
			string sMon(tempS);
			if (sMon == "")
			{
				error = 0;
				whoseChunk.hasMoney.stock = 0;
				throw error;
			}

			whoseChunk.hasMoney.stock = stoi(sMon);
		}

		//set chunks
		catch (...) {};
		while (!sin.eof())
		{
			int chunkNumber = 0, chunkStage = 0;
			sin >> chunkNumber >> chunkStage;

			whoseChunk.hasChunkNumber.push_back(chunkNumber);
			whoseChunk.hasChunkStagePrice.push_back(chunkStage);
		}


		Player addPlayer(whoseChunk);
	}
	// 更新mainMap、currentPlayer、currentCount、totalPlayer等
}

void Game::LoadGame(string preferFile)
{
	// ...讀檔
	ifstream fin(preferFile);
	vector<string> inputString;
	if (!fin.is_open())
		cout << "Open file error" << endl;
	while (!fin.eof())
	{
		char input[200];
		fin.getline(input, 200);
		string temp(input);
		inputString.push_back(temp);
	}
	fin.close();

	stringstream sin("");

	sin.clear();
	sin << inputString[0];
	sin >> mainMap.mapName >> currentCount >> totalPlayer;
	for (int i = 0; i <= 27; i++)
	{
		sin.clear();
		sin << inputString[i + 1];
		Map::chunk inputChunk;
		sin >> inputChunk.chunkNumber >> inputChunk.chunkName >> inputChunk.chunkType;
		if (inputChunk.chunkType == 1)
		{
			sin >> inputChunk.chunkInitialPrice
				>> inputChunk.chunkPassPrice0
				>> inputChunk.chunkPassPrice1
				>> inputChunk.chunkPassPrice2
				>> inputChunk.chunkPassPrice3;
		}
		mainMap.chunkList.push_back(inputChunk);
	}
	sin.clear();
	string buffer;
	sin << inputString[29];
	sin >> buffer >> currentPlayer;
	for (int i = 30; i <= inputString.size() - 1; i++)
	{
		cout << i << endl;
		hasChunkStatus whoseChunk;
		string allProperty;
		sin.clear();
		sin << inputString[i];
		sin >> whoseChunk.playerNumber
			>> whoseChunk.playerPosition
			>> allProperty;
		//set data of propertys
		stringstream setProperty(allProperty);
		try
		{
			int error;
			//set moneyInPocket
			char tempP[10000];
			setProperty.getline(tempP, 10000, ',');
			string pMon(tempP);
			whoseChunk.hasMoney.moneyInPocket = stoi(pMon);
			//set moneyInBank
			char tempB[10000];
			setProperty.getline(tempB, 10000, ',');
			string bMon(tempB);
			if (bMon == "")
			{
				error = 0;
				whoseChunk.hasMoney.moneyInBank = 0;
				whoseChunk.hasMoney.stock = 0;
				throw error;
			}
			whoseChunk.hasMoney.moneyInBank = stoi(bMon);
			//set stock
			char tempS[10000];
			setProperty.getline(tempS, 10000, ',');
			string sMon(tempS);
			if (sMon == "")
			{
				error = 0;
				whoseChunk.hasMoney.stock = 0;
				throw error;
			}

			whoseChunk.hasMoney.stock = stoi(sMon);
		}

		//set chunks
		catch (...) {};
		while (!sin.eof())
		{
			int chunkNumber = 0, chunkStage = 0;
			sin >> chunkNumber >> chunkStage;
			whoseChunk.hasChunkNumber.push_back(chunkNumber);
			whoseChunk.hasChunkStagePrice.push_back(chunkStage);
		}
		Player addPlayer(whoseChunk);
	}

	// 更新mainMap、currentPlayer、currentCount、totalPlayer等
}

void Game::SaveGame(string preferFile)// 存檔
{

	vector<string>outputString;
	//base xx x
	string base = "base ";
	base += to_string(currentCount);
	base += " ";
	base += to_string(totalPlayer);
	outputString.push_back(base);

	//存入區塊 
	//位置 名稱 類型 購買價格 0階過路費 1階過路費 2階過路費 3階過路費
	for (int i = 0; i < mainMap.chunkList.size(); i++)
	{
		string num;
		if (i < 10)
		{
			num = '0';
			num += to_string(i);
		}
		else
			num = to_string(i);

		string saveChunk = num;
		saveChunk += " ";
		saveChunk += mainMap.chunkList[i].chunkName;
		saveChunk += " ";
		saveChunk += to_string(mainMap.chunkList[i].chunkType);
		if (mainMap.chunkList[i].chunkType == 1)
		{
			saveChunk += " ";
			saveChunk += to_string(mainMap.chunkList[i].chunkInitialPrice);
			saveChunk += " ";
			saveChunk += to_string(mainMap.chunkList[i].chunkPassPrice0);
			saveChunk += " ";
			saveChunk += to_string(mainMap.chunkList[i].chunkPassPrice1);
			saveChunk += " ";
			saveChunk += to_string(mainMap.chunkList[i].chunkPassPrice2);
			saveChunk += " ";
			saveChunk += to_string(mainMap.chunkList[i].chunkPassPrice3);
		}
		outputString.push_back(saveChunk);
	}
	//playerstate x
	string playerState = "playerstate ";
	playerState += to_string(currentPlayer);
	outputString.push_back(playerState);
	//存入玩家
	//編號 位置 現金,存款,股票 地產 地產等級
	for (int i = 0; i < totalPlayer; i++)
	{
		string savePlayer;
		savePlayer = to_string(Player::PlayerList[i].hasChunk.playerNumber);
		savePlayer += " ";
		string pNum = "";
		if (Player::PlayerList[i].hasChunk.playerPosition < 10)
			pNum += '0';
		pNum += to_string(Player::PlayerList[i].hasChunk.playerPosition);
		savePlayer += pNum;
		savePlayer += " ";
		savePlayer += to_string(Player::PlayerList[i].hasChunk.hasMoney.moneyInPocket);
		savePlayer += ",";
		savePlayer += to_string(Player::PlayerList[i].hasChunk.hasMoney.moneyInBank);
		savePlayer += ",";
		savePlayer += to_string(Player::PlayerList[i].hasChunk.hasMoney.stock);
		savePlayer += " ";
		//存入地產 地產等級
		for (int j = 0; j < Player::PlayerList[i].hasChunk.hasChunkNumber.size(); j++)
		{
			int cn = Player::PlayerList[i].hasChunk.hasChunkNumber[j];
			string chunkNum;
			if (cn < 10)
			{
				chunkNum = '0';
				chunkNum += to_string(cn);
			}
			else
				chunkNum = to_string(cn);

			savePlayer += chunkNum;
			savePlayer += " ";
			savePlayer += to_string(Player::PlayerList[i].hasChunk.hasChunkStagePrice[j]);
			//最後一個地產等級後不用加空格
			if (j != Player::PlayerList[i].hasChunk.hasChunkNumber.size() - 1)
				savePlayer += " ";
		}
		outputString.push_back(savePlayer);
	}
	//開啟檔案寫入
	ofstream fout(preferFile);
	for (int i = 0; i < outputString.size(); i++)
	{
		fout << outputString[i] << endl;
	}
	fout.flush();
	fout.close();
}

void Game::NewGame()
{
	// ...讀取basemap檔案
	ifstream fin("basemap.txt");
	vector<string> inputString;
	if (!fin.is_open())
		cout << "Open file error" << endl;
	while (!fin.eof())
	{
		char input[200];
		fin.getline(input, 200);
		string temp(input);
		inputString.push_back(temp);
	}
	fin.close();

	stringstream sin("");

	sin.clear();
	sin << inputString[0];
	sin >> mainMap.mapName >> currentCount >> totalPlayer;
	for (int i = 0; i <= 27; i++)
	{
		sin.clear();
		sin << inputString[i + 1];
		Map::chunk inputChunk;
		sin >> inputChunk.chunkNumber >> inputChunk.chunkName >> inputChunk.chunkType;
		if (inputChunk.chunkType == 1)
		{
			sin >> inputChunk.chunkInitialPrice
				>> inputChunk.chunkPassPrice0
				>> inputChunk.chunkPassPrice1
				>> inputChunk.chunkPassPrice2
				>> inputChunk.chunkPassPrice3;
		}
		mainMap.chunkList.push_back(inputChunk);
	}
	sin.clear();
	string buffer;
	sin << inputString[29];
	sin >> buffer >> currentPlayer;
	for (int i = 30; i <= inputString.size() - 1; i++)
	{
		cout << i << endl;
		hasChunkStatus whoseChunk;
		string allProperty;
		sin.clear();
		sin << inputString[i];
		sin >> whoseChunk.playerNumber
			>> whoseChunk.playerPosition
			>> allProperty;
		//set data of propertys
		stringstream setProperty(allProperty);
		try
		{
			int error;
			//set moneyInPocket
			char tempP[10000];
			setProperty.getline(tempP, 10000, ',');
			string pMon(tempP);
			whoseChunk.hasMoney.moneyInPocket = stoi(pMon);
			//set moneyInBank
			char tempB[10000];
			setProperty.getline(tempB, 10000, ',');
			string bMon(tempB);
			if (bMon == "")
			{
				error = 0;
				whoseChunk.hasMoney.moneyInBank = 0;
				whoseChunk.hasMoney.stock = 0;
				throw error;
			}
			whoseChunk.hasMoney.moneyInBank = stoi(bMon);
			//set stock
			char tempS[10000];
			setProperty.getline(tempS, 10000, ',');
			string sMon(tempS);
			if (sMon == "")
			{
				error = 0;
				whoseChunk.hasMoney.stock = 0;
				throw error;
			}

			whoseChunk.hasMoney.stock = stoi(sMon);
		}

		//set chunks
		catch (...) {};
		while (!sin.eof())
		{
			int chunkNumber = 0, chunkStage = 0;
			sin >> chunkNumber >> chunkStage;
			whoseChunk.hasChunkNumber.push_back(chunkNumber);
			whoseChunk.hasChunkStagePrice.push_back(chunkStage);
		}
		Player addPlayer(whoseChunk);
	}
	// 更新mainMap、currentPlayer、currentCount、totalPlayer等
	// 更新mainMap、currentPlayer、currentCount、totalPlayer等
}

void Game::RollingDice(Player &preferPlayer, int preferStep, bool global)
{
	int diceNumber(0);
	if (preferStep != 0 && global)
	{
		diceNumber = preferStep;
	}
	else if (preferStep != 0 && !global)
	{
		diceNumber = min(preferStep, 6);
		// 檢查路障清單
		int check = preferPlayer.hasChunk.playerPosition;
		int i = 1;
		while (i < diceNumber)
		{
			// 27進位
			if (check + 1 > 27)
			{
				check = 0;
			}
			else
			{
				check += 1;
			}

			auto it = find(Game::BlockList.begin(), Game::BlockList.end(), check);
			if (it != Game::BlockList.end())
			{
				diceNumber = i;
				Game::BlockList.erase(it);

				break;
			}

			i++;
		}
	}
	else if(preferStep == 0)
	{
		diceNumber = rand() % 6 + 1;	//擲骰子，1-6
		// 檢查路障清單
		int check = preferPlayer.hasChunk.playerPosition;
		int i = 1;
		while (i < diceNumber)
		{
			// 27進位
			if (check + 1 > 27)
			{
				check = 0;
			}
			else
			{
				check += 1;
			}

			auto it = find(Game::BlockList.begin(), Game::BlockList.end(), check);
			if (it != Game::BlockList.end())
			{
				diceNumber = i;
				Game::BlockList.erase(it);

				break;
			}

			i++;
		}
	}	
	string prefermsg = "玩家" + to_string(preferPlayer.hasChunk.playerNumber) + "：擲出了" + to_string(diceNumber) + "點\n"; //印出提示訊息
	Draw::renewOutput(prefermsg);

	if (preferPlayer.hasChunk.hasBuffNuff.size() > 0)
	{
		// 有增減益效果，需檢查
	}
	else
	{
		// 玩家移動到向前移動
		if (preferPlayer.hasChunk.playerPosition + diceNumber > 27)
		{
			preferPlayer.hasChunk.playerPosition = preferPlayer.hasChunk.playerPosition + diceNumber - 27 - 1;
		}
		else
		{
			preferPlayer.hasChunk.playerPosition += diceNumber;
		}		

		// 如果是建築
		if (mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkType == 1)
		{
			bool alreadyBuy(false);
			bool self(false);
			int findPlayer;
			int findIndex;
			for (int i = 0; i < Player::PlayerList.size(); i++)
			{
				for (int j = 0; j < Player::PlayerList[i].hasChunk.hasChunkNumber.size(); j++)
				{
					if (Player::PlayerList[i].hasChunk.hasChunkNumber[j] == mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkNumber)
					{
						alreadyBuy = true;
						self = (i == currentPlayer) ? true : false;
						findPlayer = i;
						findIndex = j;

						break;
					}
				}
			}
			// 如果房地產還不屬於任何人
			if (!alreadyBuy)
			{
				cout << "\r這塊地還沒有玩家購買，您是否要購買 ( " + to_string(mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkInitialPrice) + " ) ？ (y/n)";
				string buyCheck;
				cin >> buyCheck;

				// 如果使用者要買
				if (buyCheck == "y")
				{
					// 如果現金夠
					if (preferPlayer.hasChunk.hasMoney.moneyInPocket >= mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkInitialPrice)
					{
						// 扣款
						preferPlayer.hasChunk.hasMoney.moneyInPocket -= mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkInitialPrice;
						// 過戶
						preferPlayer.hasChunk.hasChunkNumber.push_back(mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkNumber);
						preferPlayer.hasChunk.hasChunkStagePrice.push_back(1);
					}
					// 如果現金不夠
					else
					{
						cout << "\r不好意思您的現金好像不夠喔";
					}
					
				}
				else
				{
					// ...nothing
					// cout << "錢錢不能一直扣著喔<3\n";
				}

			}
			else if (alreadyBuy && self)
			{
				// 還可以升級
				if (preferPlayer.hasChunk.hasChunkStagePrice[findIndex] < 3)
				{
					cout << "\r您是否要升級這個房地產？";
					string buyCheck;
					cin >> buyCheck;

					// 要升級
					if (buyCheck == "y")
					{
						preferPlayer.hasChunk.hasChunkStagePrice[findIndex] += 1;
					}
					// 不升級
					else
					{
						// ...好ㄅ
					}
				}
				// 等級已滿
				else
				{
					// ...等級滿了
				}				

			}
			else if (alreadyBuy && !self)
			{
				int needPlay;
				if (Player::PlayerList[findPlayer].hasChunk.hasChunkStagePrice[findIndex] == 0)
				{
					cout << "\r支付過路費 $" << mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkPassPrice0;
					preferPlayer.hasChunk.hasMoney.moneyInPocket -= mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkPassPrice0;
				}
				else if (Player::PlayerList[findPlayer].hasChunk.hasChunkStagePrice[findIndex] == 1)
				{
					cout << "\r支付過路費 $" << mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkPassPrice1;
					preferPlayer.hasChunk.hasMoney.moneyInPocket -= mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkPassPrice1;
				}
				else if (Player::PlayerList[findPlayer].hasChunk.hasChunkStagePrice[findIndex] == 2)
				{
					cout << "\r支付過路費 $" << mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkPassPrice2;
					preferPlayer.hasChunk.hasMoney.moneyInPocket -= mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkPassPrice2;
				}
				else if (Player::PlayerList[findPlayer].hasChunk.hasChunkStagePrice[findIndex] == 3)
				{
					cout << "\r支付過路費 $" << mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkPassPrice3;
					preferPlayer.hasChunk.hasMoney.moneyInPocket -= mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkPassPrice3;
				}
								
				getchar();
			}
			
		}
		else if (mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkType == -1 || mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkType == -2)
		{
			// 如果是機會...
			int chanceNum = rand() % 3 + 1;
			if (chanceNum == 1)
			{
				cout << "\r獲得機會：現金股利分紅（您獲得持有股票現值的5%現金紅利），$" << (preferPlayer.hasChunk.hasMoney.stock * Game::currentStockPrice * 0.05) << "\n";
				preferPlayer.hasChunk.hasMoney.moneyInPocket += (preferPlayer.hasChunk.hasMoney.stock * Game::currentStockPrice * 0.05);
				getchar();
			}
			else if (chanceNum == 2)
			{
				cout << "\r獲得機會：除障器（立即清除地圖上所有路障）";
				Game::BlockList.clear();
				getchar();
			}
			else if (chanceNum == 3)
			{
				cout << "\r獲得機會：環遊世界券（特殊道具已解鎖（c, 限購一次），可以$4000無條件移動至地圖上任何地點）";
				preferPlayer.hasChunk.hasBuffNuff.push_back("Global");
				getchar();
			}

			
			getchar();
		}
		else if (mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkType == 0)
		{
			// 如果起點...
			cout << "\r恭喜繞完一圈囉";
			getchar();
		}
	}

	currentCount -= 1; //已完成一局
	if (currentPlayer + 1 > totalPlayer - 1)
	{
		currentPlayer = currentPlayer + 1 - totalPlayer;
	}
	else
	{
		currentPlayer += 1;
	}
	
	// ---更新股票價格---
	double preferStockPrice;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> genStockPrice(Game::currentStockPrice * 0.85, Game::currentStockPrice * 1.15);

	preferStockPrice = genStockPrice(gen);
	if (preferStockPrice > Game::currentStockPrice * 1.1)
	{
		Game::currentStockPrice = Game::currentStockPrice * 1.1;
		Game::currentStockPriceMsg = "今日股價：" + to_string(Game::currentStockPrice) + " ( 漲停 )";
	}
	else if (preferStockPrice < Game::currentStockPrice * 0.9)
	{
		Game::currentStockPrice = Game::currentStockPrice * 0.9;
		Game::currentStockPriceMsg = "今日股價：" + to_string(Game::currentStockPrice) + " ( 跌停 )";
	}
	else
	{
		Game::currentStockPrice = preferStockPrice;
		Game::currentStockPriceMsg = "今日股價：" + to_string(Game::currentStockPrice);
	}
	// ---

	// 顯示畫面，畫面不確定是要另外獨立一個class還是直接在Game裡，明天可以再討論
	// 玩家輪流擲骰子，這樣會形成無限迴圈
	if (preferPlayer.hasChunk.playerNumber < Player::PlayerQuantity - 1 && currentCount > 0)
	{
		//RollingDice(Player::PlayerList[preferPlayer.hasChunk.playerNumber + 1]);
	}
	else if (preferPlayer.hasChunk.playerNumber == Player::PlayerQuantity - 1 && currentCount > 0)
	{
		//RollingDice(Player::PlayerList[0]);
	}
	else
	{
		// 20局已進行完成，遊戲結束
		cout << "Game Over\n";
	}

	Draw::renewOutput();
}

// 選功能
int Game::selectAction()
{
	// 以下程式碼是移動游標
	unsigned short int ch1, ch2;
	unsigned short int X = 0, Y = 0;
	vector<string> act = playerAction(act);
	gotoxy(0, 46);
	SetColor(15);
	for (int i = 0; i < act.size(); i++)
	{
		cout << act[i];
		cout << endl;
	}
	// 200 是變成橫向游標
	SetCursorVisible(TRUE, 200);
	gotoxy(3, 47);
	X = 3;
	Y = 47;
	int action = 1;
	while (true)
	{
		ch1 = _getch();
		if (ch1 == ESC)
		{
			action = 0;
			break;
		}
		else if (ch1 == DIRECTION_KEYBOARD)
		{
			ch2 = _getch();
			switch (ch2)
			{
			case LEFT:
				if (X == 3)
					break;
				X = X - 18;
				gotoxy(X, Y);
				action -= 1;
				break;
			case RIGHT:
				if (X == 57)
					break;
				X = X + 18;
				gotoxy(X, Y);
				action += 1;
				break;
			}
		}
		else if (ch1 == ENTER)
		{
			
			switch (action)
			{			
				case 1:
					RollingDice(Player::PlayerList[currentPlayer], 0, false);
					gotoxy(3, 47);
					break;
				// 銀行系統
				case 2:
				{
					gotoxy(0, 49);
					cout << "\r請輸入存提款金額 ( s/b金額 )\n";
					string inputPara("");
					cin >> inputPara;
				
					// 存款
					if (inputPara[0] == 's')
					{
						// 現金足夠的情況
						if (Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInPocket >= stoi(inputPara.substr(1)))
						{
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInPocket -= stoi(inputPara.substr(1));
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInBank += stoi(inputPara.substr(1));
							cout << "\r已存入金額 $" << inputPara.substr(1) << "\n";
							getchar();
							Draw::renewOutput();
						}
						else
						{
							cout << "\r現金不足\n";
							getchar();
							Draw::renewOutput();
						}
					}
					else if (inputPara[0] == 'b')
					{
						// 存款足夠的情況
						if (Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInBank >= stoi(inputPara.substr(1)))
						{
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInBank -= stoi(inputPara.substr(1));
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInPocket += stoi(inputPara.substr(1));
							cout << "\r已提領金額 $" << inputPara.substr(1) << "\n";
							getchar();
							Draw::renewOutput();
						}
						else
						{
							cout << "\r存款不足\n";
							getchar();
							Draw::renewOutput();
						}
					}
					gotoxy(21, 47);
					break;
				}
				// 股票買賣系統
				case 3:
				{
					gotoxy(0, 49);
					cout << "\r請輸入買賣張數 ( s/b張數 )\n";
					string inputPara("");
					cin >> inputPara;

					if (inputPara[0] == 's')
					{
						// 賣股票
						if (Player::PlayerList[currentPlayer].hasChunk.hasMoney.stock >= stoi(inputPara.substr(1)))
						{
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.stock -= stoi(inputPara.substr(1));
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInBank += (Game::currentStockPrice * stoi(inputPara.substr(1))); //修改此行
							cout << "\r已賣出股票 " << inputPara.substr(1) << "張，換算現值：$" << (Game::currentStockPrice * stoi(inputPara.substr(1)));
							getchar();
							Draw::renewOutput();
						}
						else
						{
							cout << "\r股票不足\n";
							getchar();
							Draw::renewOutput();
						}
					}
					else if (inputPara[0] == 'b')
					{
						// 買股票
						if (Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInBank >= (Game::currentStockPrice * stoi(inputPara.substr(1)))) //修改此行
						{
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInBank -= (Game::currentStockPrice * stoi(inputPara.substr(1))); //修改此行
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.stock += stoi(inputPara.substr(1));
							cout << "\r已買入股票 " << inputPara.substr(1) << "張，共花費：$" << (Game::currentStockPrice * stoi(inputPara.substr(1)));
							getchar();
							Draw::renewOutput();
						}
						else
						{
							cout << "\r存款不足\n";
							getchar();
							Draw::renewOutput();
						}
					}
					gotoxy(39, 47);
					break;
				}
				// 道具系統
				case 4:
				{
					gotoxy(0, 49);
					cout << "\r請輸入想用的道具 ( 遙控骰子$1500, 路障$1000 )，( a/b )\n";
					string inputPara("");
					cin >> inputPara;
					
					// 遙控骰子
					if (inputPara == "a")
					{
						// 錢夠
						if (Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInPocket >= 1500)
						{
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInPocket -= 1500;

							int preferPoint;
							cout << "\r請輸入您要擲出的點數\n";
							cin >> preferPoint;
							Game::RollingDice(Player::PlayerList[currentPlayer], preferPoint, false);
						}
						// 錢不夠
						else
						{
							cout << "\r現金不足\n";
						}
					}
					// 路障
					else if (inputPara == "b")
					{
						// 錢夠
						if (Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInPocket >= 1000)
						{
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInPocket -= 1000;

							int preferPoint;
							cout << "\r請輸入您要放置的位置編號 ( n )\n";
							cin >> preferPoint;
							Game::BlockList.push_back(preferPoint);
							cout << "\r已在 " << preferPoint << " 上放置路障\n";
							getchar();
							Draw::renewOutput();
						}
						// 錢不夠
						else
						{
							cout << "\r現金不足\n";
						}
					}
					else if (inputPara == "c" && Player::PlayerList[currentPlayer].hasChunk.hasBuffNuff.size()!=0)
					{
						// 錢夠
						if (Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInPocket >= 4000)
						{
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInPocket -= 4000;

							int preferPoint;
							cout << "\r請輸入您要環遊世界旅行的位置編號 ( n )\n";
							cin >> preferPoint;

							Player::PlayerList[currentPlayer].hasChunk.hasBuffNuff.clear();
							Game::RollingDice(Player::PlayerList[currentPlayer], preferPoint, true);
						}
						// 錢不夠
						else
						{
							cout << "\r現金不足\n";
						}
					}
					gotoxy(57, 47);
					break;
				}
				break;
			}
		}
	}
	return action;
}

//saveGame的txt最後會有一行空白
//造成loadGame後會多一個玩家
bool Game::gameMenu()
{
	unsigned short int ch1, ch2;
	unsigned short int X = 0, Y = 0;
	string temp;
	vector<string> menu = mainMenu(menu);
	int menuAct = 0;
	bool exit = false;
	for (int i = 0;i < menu.size();i++)
	{
		gotoxy(30, 20 + i);
		cout << menu[i] << endl;
	}
	gotoxy(36, 21);
	X = 36;
	Y = 21;
	while (true)
	{
		ch1 = _getch();
		if (ch1 == DIRECTION_KEYBOARD)
		{
			ch2 = _getch();
			switch (ch2)
			{
			case UP:
				if (Y == 21)
					break;
				Y = Y - 2;
				gotoxy(X, Y);
				menuAct -= 1;
				break;
			case DOWN:
				if (Y == 29)
					break;
				Y = Y + 2;
				gotoxy(X, Y);
				menuAct += 1;
				break;
			}
		}
		else if (ch1 == ENTER)
		{
			switch (menuAct)
			{
			case 0:
				Draw::renewOutput();
				break;
			case 1:
				Player::PlayerQuantity = 0;
				NewGame();
				
				Draw::renewOutput();
				break;
			case 2:
				system("cls");
				cout << "請 輸 入 檔 名 + .副檔名" << endl;				
				cin >> temp;
				SaveGame(temp);
				gotoxy(0, 0);
				Draw::renewOutput();
				break;
			case 3:
				system("cls");
				cout << "請 輸 入 檔 名 + .副檔名" << endl;
				cin >> temp;
				Player::PlayerQuantity = 0;
				LoadGame(temp);
				gotoxy(0, 0);
				Draw::renewOutput();
				break;
			case 4:
				exit = true;
				break;
			}
			break;
		}
	}
	return exit;
}
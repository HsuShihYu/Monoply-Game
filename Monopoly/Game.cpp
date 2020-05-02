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
	// ...Ū��
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
	// ��smainMap�BcurrentPlayer�BcurrentCount�BtotalPlayer��
}

void Game::LoadGame(string preferFile)
{
	// ...Ū��
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

	// ��smainMap�BcurrentPlayer�BcurrentCount�BtotalPlayer��
}

void Game::SaveGame(string preferFile)// �s��
{

	vector<string>outputString;
	//base xx x
	string base = "base ";
	base += to_string(currentCount);
	base += " ";
	base += to_string(totalPlayer);
	outputString.push_back(base);

	//�s�J�϶� 
	//��m �W�� ���� �ʶR���� 0���L���O 1���L���O 2���L���O 3���L���O
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
	//�s�J���a
	//�s�� ��m �{��,�s��,�Ѳ� �a�� �a������
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
		//�s�J�a�� �a������
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
			//�̫�@�Ӧa�����ūᤣ�Υ[�Ů�
			if (j != Player::PlayerList[i].hasChunk.hasChunkNumber.size() - 1)
				savePlayer += " ";
		}
		outputString.push_back(savePlayer);
	}
	//�}���ɮ׼g�J
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
	// ...Ū��basemap�ɮ�
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
	// ��smainMap�BcurrentPlayer�BcurrentCount�BtotalPlayer��
	// ��smainMap�BcurrentPlayer�BcurrentCount�BtotalPlayer��
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
		// �ˬd���ٲM��
		int check = preferPlayer.hasChunk.playerPosition;
		int i = 1;
		while (i < diceNumber)
		{
			// 27�i��
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
		diceNumber = rand() % 6 + 1;	//�Y��l�A1-6
		// �ˬd���ٲM��
		int check = preferPlayer.hasChunk.playerPosition;
		int i = 1;
		while (i < diceNumber)
		{
			// 27�i��
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
	string prefermsg = "���a" + to_string(preferPlayer.hasChunk.playerNumber) + "�G�Y�X�F" + to_string(diceNumber) + "�I\n"; //�L�X���ܰT��
	Draw::renewOutput(prefermsg);

	if (preferPlayer.hasChunk.hasBuffNuff.size() > 0)
	{
		// ���W��q�ĪG�A���ˬd
	}
	else
	{
		// ���a���ʨ�V�e����
		if (preferPlayer.hasChunk.playerPosition + diceNumber > 27)
		{
			preferPlayer.hasChunk.playerPosition = preferPlayer.hasChunk.playerPosition + diceNumber - 27 - 1;
		}
		else
		{
			preferPlayer.hasChunk.playerPosition += diceNumber;
		}		

		// �p�G�O�ؿv
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
			// �p�G�Цa���٤��ݩ����H
			if (!alreadyBuy)
			{
				cout << "\r�o���a�٨S�����a�ʶR�A�z�O�_�n�ʶR ( " + to_string(mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkInitialPrice) + " ) �H (y/n)";
				string buyCheck;
				cin >> buyCheck;

				// �p�G�ϥΪ̭n�R
				if (buyCheck == "y")
				{
					// �p�G�{����
					if (preferPlayer.hasChunk.hasMoney.moneyInPocket >= mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkInitialPrice)
					{
						// ����
						preferPlayer.hasChunk.hasMoney.moneyInPocket -= mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkInitialPrice;
						// �L��
						preferPlayer.hasChunk.hasChunkNumber.push_back(mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkNumber);
						preferPlayer.hasChunk.hasChunkStagePrice.push_back(1);
					}
					// �p�G�{������
					else
					{
						cout << "\r���n�N��z���{���n��������";
					}
					
				}
				else
				{
					// ...nothing
					// cout << "��������@�����۳�<3\n";
				}

			}
			else if (alreadyBuy && self)
			{
				// �٥i�H�ɯ�
				if (preferPlayer.hasChunk.hasChunkStagePrice[findIndex] < 3)
				{
					cout << "\r�z�O�_�n�ɯųo�өЦa���H";
					string buyCheck;
					cin >> buyCheck;

					// �n�ɯ�
					if (buyCheck == "y")
					{
						preferPlayer.hasChunk.hasChunkStagePrice[findIndex] += 1;
					}
					// ���ɯ�
					else
					{
						// ...�n�t
					}
				}
				// ���Ťw��
				else
				{
					// ...���ź��F
				}				

			}
			else if (alreadyBuy && !self)
			{
				int needPlay;
				if (Player::PlayerList[findPlayer].hasChunk.hasChunkStagePrice[findIndex] == 0)
				{
					cout << "\r��I�L���O $" << mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkPassPrice0;
					preferPlayer.hasChunk.hasMoney.moneyInPocket -= mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkPassPrice0;
				}
				else if (Player::PlayerList[findPlayer].hasChunk.hasChunkStagePrice[findIndex] == 1)
				{
					cout << "\r��I�L���O $" << mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkPassPrice1;
					preferPlayer.hasChunk.hasMoney.moneyInPocket -= mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkPassPrice1;
				}
				else if (Player::PlayerList[findPlayer].hasChunk.hasChunkStagePrice[findIndex] == 2)
				{
					cout << "\r��I�L���O $" << mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkPassPrice2;
					preferPlayer.hasChunk.hasMoney.moneyInPocket -= mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkPassPrice2;
				}
				else if (Player::PlayerList[findPlayer].hasChunk.hasChunkStagePrice[findIndex] == 3)
				{
					cout << "\r��I�L���O $" << mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkPassPrice3;
					preferPlayer.hasChunk.hasMoney.moneyInPocket -= mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkPassPrice3;
				}
								
				getchar();
			}
			
		}
		else if (mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkType == -1 || mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkType == -2)
		{
			// �p�G�O���|...
			int chanceNum = rand() % 3 + 1;
			if (chanceNum == 1)
			{
				cout << "\r��o���|�G�{���ѧQ�����]�z��o�����Ѳ��{�Ȫ�5%�{�����Q�^�A$" << (preferPlayer.hasChunk.hasMoney.stock * Game::currentStockPrice * 0.05) << "\n";
				preferPlayer.hasChunk.hasMoney.moneyInPocket += (preferPlayer.hasChunk.hasMoney.stock * Game::currentStockPrice * 0.05);
				getchar();
			}
			else if (chanceNum == 2)
			{
				cout << "\r��o���|�G���پ��]�ߧY�M���a�ϤW�Ҧ����١^";
				Game::BlockList.clear();
				getchar();
			}
			else if (chanceNum == 3)
			{
				cout << "\r��o���|�G���C�@�ɨ�]�S��D��w����]c, ���ʤ@���^�A�i�H$4000�L���󲾰ʦܦa�ϤW����a�I�^";
				preferPlayer.hasChunk.hasBuffNuff.push_back("Global");
				getchar();
			}

			
			getchar();
		}
		else if (mainMap.chunkList[preferPlayer.hasChunk.playerPosition].chunkType == 0)
		{
			// �p�G�_�I...
			cout << "\r����¶���@���o";
			getchar();
		}
	}

	currentCount -= 1; //�w�����@��
	if (currentPlayer + 1 > totalPlayer - 1)
	{
		currentPlayer = currentPlayer + 1 - totalPlayer;
	}
	else
	{
		currentPlayer += 1;
	}
	
	// ---��s�Ѳ�����---
	double preferStockPrice;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> genStockPrice(Game::currentStockPrice * 0.85, Game::currentStockPrice * 1.15);

	preferStockPrice = genStockPrice(gen);
	if (preferStockPrice > Game::currentStockPrice * 1.1)
	{
		Game::currentStockPrice = Game::currentStockPrice * 1.1;
		Game::currentStockPriceMsg = "����ѻ��G" + to_string(Game::currentStockPrice) + " ( ���� )";
	}
	else if (preferStockPrice < Game::currentStockPrice * 0.9)
	{
		Game::currentStockPrice = Game::currentStockPrice * 0.9;
		Game::currentStockPriceMsg = "����ѻ��G" + to_string(Game::currentStockPrice) + " ( �^�� )";
	}
	else
	{
		Game::currentStockPrice = preferStockPrice;
		Game::currentStockPriceMsg = "����ѻ��G" + to_string(Game::currentStockPrice);
	}
	// ---

	// ��ܵe���A�e�����T�w�O�n�t�~�W�ߤ@��class�٬O�����bGame�̡A���ѥi�H�A�Q��
	// ���a���y�Y��l�A�o�˷|�Φ��L���j��
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
		// 20���w�i�槹���A�C������
		cout << "Game Over\n";
	}

	Draw::renewOutput();
}

// ��\��
int Game::selectAction()
{
	// �H�U�{���X�O���ʴ��
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
	// 200 �O�ܦ���V���
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
				// �Ȧ�t��
				case 2:
				{
					gotoxy(0, 49);
					cout << "\r�п�J�s���ڪ��B ( s/b���B )\n";
					string inputPara("");
					cin >> inputPara;
				
					// �s��
					if (inputPara[0] == 's')
					{
						// �{�����������p
						if (Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInPocket >= stoi(inputPara.substr(1)))
						{
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInPocket -= stoi(inputPara.substr(1));
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInBank += stoi(inputPara.substr(1));
							cout << "\r�w�s�J���B $" << inputPara.substr(1) << "\n";
							getchar();
							Draw::renewOutput();
						}
						else
						{
							cout << "\r�{������\n";
							getchar();
							Draw::renewOutput();
						}
					}
					else if (inputPara[0] == 'b')
					{
						// �s�ڨ��������p
						if (Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInBank >= stoi(inputPara.substr(1)))
						{
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInBank -= stoi(inputPara.substr(1));
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInPocket += stoi(inputPara.substr(1));
							cout << "\r�w������B $" << inputPara.substr(1) << "\n";
							getchar();
							Draw::renewOutput();
						}
						else
						{
							cout << "\r�s�ڤ���\n";
							getchar();
							Draw::renewOutput();
						}
					}
					gotoxy(21, 47);
					break;
				}
				// �Ѳ��R��t��
				case 3:
				{
					gotoxy(0, 49);
					cout << "\r�п�J�R��i�� ( s/b�i�� )\n";
					string inputPara("");
					cin >> inputPara;

					if (inputPara[0] == 's')
					{
						// ��Ѳ�
						if (Player::PlayerList[currentPlayer].hasChunk.hasMoney.stock >= stoi(inputPara.substr(1)))
						{
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.stock -= stoi(inputPara.substr(1));
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInBank += (Game::currentStockPrice * stoi(inputPara.substr(1))); //�ק惡��
							cout << "\r�w��X�Ѳ� " << inputPara.substr(1) << "�i�A����{�ȡG$" << (Game::currentStockPrice * stoi(inputPara.substr(1)));
							getchar();
							Draw::renewOutput();
						}
						else
						{
							cout << "\r�Ѳ�����\n";
							getchar();
							Draw::renewOutput();
						}
					}
					else if (inputPara[0] == 'b')
					{
						// �R�Ѳ�
						if (Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInBank >= (Game::currentStockPrice * stoi(inputPara.substr(1)))) //�ק惡��
						{
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInBank -= (Game::currentStockPrice * stoi(inputPara.substr(1))); //�ק惡��
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.stock += stoi(inputPara.substr(1));
							cout << "\r�w�R�J�Ѳ� " << inputPara.substr(1) << "�i�A�@��O�G$" << (Game::currentStockPrice * stoi(inputPara.substr(1)));
							getchar();
							Draw::renewOutput();
						}
						else
						{
							cout << "\r�s�ڤ���\n";
							getchar();
							Draw::renewOutput();
						}
					}
					gotoxy(39, 47);
					break;
				}
				// �D��t��
				case 4:
				{
					gotoxy(0, 49);
					cout << "\r�п�J�Q�Ϊ��D�� ( ������l$1500, ����$1000 )�A( a/b )\n";
					string inputPara("");
					cin >> inputPara;
					
					// ������l
					if (inputPara == "a")
					{
						// ����
						if (Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInPocket >= 1500)
						{
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInPocket -= 1500;

							int preferPoint;
							cout << "\r�п�J�z�n�Y�X���I��\n";
							cin >> preferPoint;
							Game::RollingDice(Player::PlayerList[currentPlayer], preferPoint, false);
						}
						// ������
						else
						{
							cout << "\r�{������\n";
						}
					}
					// ����
					else if (inputPara == "b")
					{
						// ����
						if (Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInPocket >= 1000)
						{
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInPocket -= 1000;

							int preferPoint;
							cout << "\r�п�J�z�n��m����m�s�� ( n )\n";
							cin >> preferPoint;
							Game::BlockList.push_back(preferPoint);
							cout << "\r�w�b " << preferPoint << " �W��m����\n";
							getchar();
							Draw::renewOutput();
						}
						// ������
						else
						{
							cout << "\r�{������\n";
						}
					}
					else if (inputPara == "c" && Player::PlayerList[currentPlayer].hasChunk.hasBuffNuff.size()!=0)
					{
						// ����
						if (Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInPocket >= 4000)
						{
							Player::PlayerList[currentPlayer].hasChunk.hasMoney.moneyInPocket -= 4000;

							int preferPoint;
							cout << "\r�п�J�z�n���C�@�ɮȦ檺��m�s�� ( n )\n";
							cin >> preferPoint;

							Player::PlayerList[currentPlayer].hasChunk.hasBuffNuff.clear();
							Game::RollingDice(Player::PlayerList[currentPlayer], preferPoint, true);
						}
						// ������
						else
						{
							cout << "\r�{������\n";
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

//saveGame��txt�̫�|���@��ť�
//�y��loadGame��|�h�@�Ӫ��a
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
				cout << "�� �� �J �� �W + .���ɦW" << endl;				
				cin >> temp;
				SaveGame(temp);
				gotoxy(0, 0);
				Draw::renewOutput();
				break;
			case 3:
				system("cls");
				cout << "�� �� �J �� �W + .���ɦW" << endl;
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
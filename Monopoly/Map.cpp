#include "Map.h"
#include"Player.h"
#include "Game.h"

using namespace std;

// Ū mainMap �̪� chunkName �� �a�ϤW
string trans(string x)
{
	string temp;
	if (x.length() == 4)
	{
		temp = "|  " + x + "  ";
	}
	else if (x.length() == 6)
	{
		temp = "| " + x + " ";
	}
	else if (x.length() == 8)
	{
		temp = "|" + x + "";
	}
	return temp;
}

void Map::renewMap()
{
	vector<string>transMap;
	transMap = initialmap(transMap);

	// ��J�a�ϤW�Ĥ@��
	//////////////////////////////////////////////
	string temp;
	string row1 = "";
	temp = trans(Game::mainMap.chunkList[0].chunkName);
	row1.append(temp);
	for (int i = 27; i >= 21; i--)
	{
		temp = trans(Game::mainMap.chunkList[i].chunkName);
		row1.append(temp);
	}
	row1 = row1 + "|";

	// ��J�a�ϤW�ĤG��~�ĤC��
	/////////////////////////////////////////////////
	vector<string>row2_7;
	for (int i = 1; i <= 6; i++)
	{
		string newRow = "";
		temp = trans(Game::mainMap.chunkList[i].chunkName);
		newRow.append(temp);
		newRow.append("|                                                     ");
		temp = trans(Game::mainMap.chunkList[21 - i].chunkName);
		newRow.append(temp);
		newRow = newRow + "|";
		row2_7.push_back(newRow);
	}

	// ��J�a�ϤW�ĤK��
	////////////////////////////////////////////////
	string row8 = "";
	for (int i = 7; i <= 14; i++)
	{
		temp = trans(Game::mainMap.chunkList[i].chunkName);
		row8.append(temp);
	}
	row8 = row8 + "|";

	// ��J�D�nMap
	//////////////////////////////////////////////////
	transMap[1] = row1;
	for (int i = 0; i <= 5; i++)
	{
		transMap[4 * i + 5] = row2_7[i];
	}
	transMap[29] = row8;
	drawMap = transMap;

	// �L�X�I��
	for (int i = 0; i < drawMap.size(); i++)
	{
		cout << drawMap[i] << endl;
	}
}

vector<string> Map::drawMap = {};











